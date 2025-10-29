#include "waveform_sender_thread.h"
#include <QThread>
#include <QDebug>

/**
 * @brief 构造函数实现
 */
WaveformSenderThread::WaveformSenderThread(const QVector<quint16> &waveformData,
                                           const QHostAddress &targetAddr,
                                           quint16 targetPort,
                                           int delayMs,
                                           QObject *parent)
    : QThread(parent)
    , m_waveformData(waveformData)
    , m_targetAddress(targetAddr)
    , m_targetPort(targetPort)
    , m_delayMs(delayMs)
{
}

/**
 * @brief 析构函数实现
 */
WaveformSenderThread::~WaveformSenderThread()
{
    // 等待线程结束
    if (isRunning()) {
        quit();
        wait();
    }
}

/**
 * @brief 线程运行函数
 * 
 * 在独立线程中发送波形数据包
 */
void WaveformSenderThread::run()
{
    if (m_waveformData.size() != 1024) {
        emit sendingFailed(QString("波形数据不是1024个点，当前为%1个点").arg(m_waveformData.size()));
        return;
    }

    // 在线程中创建UDP socket
    QUdpSocket socket;
    
    qDebug() << "[波形发送线程] 开始发送手绘波形数据...";
    qDebug() << "[波形发送线程] 目标地址：" << m_targetAddress.toString() << ":" << m_targetPort;
    qDebug() << "[波形发送线程] 数据点数：" << m_waveformData.size();
    qDebug() << "[波形发送线程] 发送延迟：" << m_delayMs << "ms";

    int successCount = 0;
    int totalCount = m_waveformData.size();

    // 发送1024个数据包
    for (int i = 0; i < m_waveformData.size(); ++i) {
        // 检查线程是否被请求停止
        if (isInterruptionRequested()) {
            qDebug() << "[波形发送线程] 发送被中断";
            emit sendingFailed("发送被用户中断");
            return;
        }

        quint16 voltageValue = m_waveformData[i];
        QByteArray packet = buildWaveformPacket(voltageValue);

        // 发送UDP数据包
        qint64 bytesSent = socket.writeDatagram(packet, m_targetAddress, m_targetPort);

        if (bytesSent == packet.size()) {
            successCount++;
        } else {
            qWarning() << "[波形发送线程] 数据包" << i << "发送失败";
        }

        // 每100个包报告一次进度
        if ((i + 1) % 100 == 0 || i == totalCount - 1) {
            emit progressUpdated(i + 1, totalCount);
        }

        // 添加延迟
        if (m_delayMs > 0 && i < totalCount - 1) {
            QThread::msleep(m_delayMs);
        }
    }

    qDebug() << "[波形发送线程] 发送完成！成功：" << successCount << "/" << totalCount;
    emit sendingCompleted(successCount, totalCount);
}

/**
 * @brief 构建UDP波形数据包（参考udp_test.py的build_udp_packet）
 * @param voltageValue 10位电压值 (0-1023)
 * @return 8字节数据包: 55 A5 07 00 [byte2] [byte1] [byte0] F0
 */
QByteArray WaveformSenderThread::buildWaveformPacket(quint16 voltageValue)
{
    if (voltageValue > 1023) {
        qWarning() << "[波形发送线程] 电压值超出范围：" << voltageValue;
        voltageValue = 1023;
    }

    QByteArray packet;
    packet.reserve(8);

    // 构建8字节数据包
    packet.append(static_cast<char>(0x55));  // Header 1
    packet.append(static_cast<char>(0xA5));  // Header 2
    packet.append(static_cast<char>(0x07));  // 地址位 (固定为0x07，表示波形数据)
    packet.append(static_cast<char>(0x00));  // 固定

    // 电压值拆分为3个字节（大端序）
    quint8 byte2 = (voltageValue >> 16) & 0xFF; // 高字节（对于10位数据永远是0x00）
    quint8 byte1 = (voltageValue >> 8) & 0xFF;  // 中字节
    quint8 byte0 = voltageValue & 0xFF;         // 低字节

    packet.append(static_cast<char>(byte2));
    packet.append(static_cast<char>(byte1));
    packet.append(static_cast<char>(byte0));
    packet.append(static_cast<char>(0xF0));  // Tail

    return packet;
}
