#include "UdpWorker.h"
#include <QHostAddress>
#include <QThread>
#include <QDataStream>
#include <algorithm>
#include <array>

UdpWorker::UdpWorker(quint16 listenPort, QObject *parent)
    : QObject(parent), m_listenPort(listenPort)
{
}

UdpWorker::~UdpWorker()
{
    stop();
}

void UdpWorker::start()
{
    if (m_running) return;
    m_running = true;
    m_socket = new QUdpSocket(this);
    // 如果主线程提前通过 setLocalAddress 指定了地址与端口，优先使用
    QHostAddress bindAddr = QHostAddress::AnyIPv4;
    if (!m_listenAddressStr.isEmpty()) {
        QHostAddress a(m_listenAddressStr);
        if (!a.isNull()) bindAddr = a;
    }
    bool ok = m_socket->bind(bindAddr, m_listenPort, QUdpSocket::ShareAddress);
    if (!ok) {
        QString err = QString("bind failed: %1").arg(m_socket->errorString());
        emit bindFailed(err);
        // keep running false and cleanup socket
        m_socket->deleteLater();
        m_socket = nullptr;
        m_running = false;
        return;
    }
    connect(m_socket, &QUdpSocket::readyRead, this, &UdpWorker::onReadyRead);

    m_flushTimer = new QTimer(this);
    m_flushTimer->setInterval(m_flushMs);
    connect(m_flushTimer, &QTimer::timeout, this, &UdpWorker::flushIfNeeded);
    m_flushTimer->start();
}

void UdpWorker::stop()
{
    if (!m_running) return;
    m_running = false;
    if (m_flushTimer) {
        m_flushTimer->stop();
        m_flushTimer->deleteLater();
        m_flushTimer = nullptr;
    }
    if (m_socket) {
        m_socket->close();
        m_socket->deleteLater();
        m_socket = nullptr;
    }
}

void UdpWorker::onReadyRead()
{
    if (!m_socket) return;
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(m_socket->pendingDatagramSize()));
        QHostAddress sender; quint16 senderPort;
        m_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        // 使用 QDataStream 小端解析，与 UdpReceiver 保持一致
        QDataStream stream(datagram);
        stream.setByteOrder(QDataStream::LittleEndian);

        QVector<double> voltagesLocal;
        QVector<double> timesLocal;

        while (!stream.atEnd()) {
            quint16 code;
            stream >> code;

            bool channel1OTR = (code & 0x8000) != 0;
            bool channel2OTR = (code & 0x4000) != 0;
            if (channel1OTR || channel2OTR) {
                emit overRangeDetected(channel1OTR, channel2OTR, sampleIndex + 1);
            }

            quint16 adcData = code & 0x03FF; // 10-bit
            int voltageCode = adcData;
            if (voltageCode > (1 << (ADC_DATA_WIDTH - 1))) {
                voltageCode -= (1 << ADC_DATA_WIDTH);
            }

            // ensure LSB computed
            if (LSB == 0.0) LSB = VOL_RANGE * 2 / (1 << ADC_DATA_WIDTH);

            double voltage = voltageCode * LSB - LSB / 2.0;
            double time = 1000000.0 / sampleRate * (++sampleIndex);

            voltagesLocal.append(voltage);
            timesLocal.append(time);
        }

        // 去毛刺：优先使用5点中值，回退到3点
        if (!voltagesLocal.isEmpty()) {
            if (voltagesLocal.size() >= 5) {
                QVector<double> filtered = voltagesLocal;
                int m = voltagesLocal.size();
                for (int i = 2; i < m - 2; ++i) {
                    std::array<double,5> w = {voltagesLocal[i-2], voltagesLocal[i-1], voltagesLocal[i], voltagesLocal[i+1], voltagesLocal[i+2]};
                    std::sort(w.begin(), w.end());
                    filtered[i] = w[2];
                }
                if (voltagesLocal.size() == 4) {
                    for (int i = 1; i <= 2; ++i) {
                        std::array<double,5> w = {voltagesLocal[0], voltagesLocal[1], voltagesLocal[2], voltagesLocal[3], voltagesLocal[3]};
                        std::sort(w.begin(), w.end());
                        filtered[i] = w[2];
                    }
                }
                voltagesLocal = std::move(filtered);
            } else if (voltagesLocal.size() >= 3) {
                QVector<double> filtered = voltagesLocal;
                for (int i = 1; i < voltagesLocal.size() - 1; ++i) {
                    double a = voltagesLocal[i-1];
                    double b = voltagesLocal[i];
                    double c = voltagesLocal[i+1];
                    double med;
                    if ((a <= b && b <= c) || (c <= b && b <= a)) med = b;
                    else if ((b <= a && a <= c) || (c <= a && a <= b)) med = a;
                    else med = c;
                    filtered[i] = med;
                }
                voltagesLocal = std::move(filtered);
            }

            // 把过滤后的数据追加到 worker 的批量缓存中
            for (int i = 0; i < voltagesLocal.size(); ++i) {
                m_bufVoltages.append(voltagesLocal[i]);
                m_bufTimes.append(timesLocal[i]);
            }
        }
    }

    if (m_bufVoltages.size() >= m_batchSize) flushIfNeeded();
}

void UdpWorker::flushIfNeeded()
{
    if (m_bufVoltages.isEmpty()) return;
    QVector<double> v = std::move(m_bufVoltages);
    QVector<double> t = std::move(m_bufTimes);
    m_bufVoltages.clear();
    m_bufTimes.clear();
    emit batchReady(v, t);
}

void UdpWorker::setLocalAddress(const QString &address, quint16 port)
{
    // 这个方法可能在主线程调用，因此我们只保存字符串与端口
    m_listenAddressStr = address;
    m_listenPort = port;
    // 如果 socket 已存在且已绑定，需要重新绑定：先关闭现有 socket
    if (m_socket) {
        m_socket->close();
        m_socket->deleteLater();
        m_socket = nullptr;
    }
}
