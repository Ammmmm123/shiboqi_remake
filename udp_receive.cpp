#include "udp_receive.h"
#include <QDataStream>
#include <QHostAddress>

/**
 * @brief 构造函数
 *
 * 初始化UDP套接字并计算ADC参数。
 * LSB = VOL_RANGE * 2 / (2^ADC_DATA_WIDTH)
 */
UdpReceiver::UdpReceiver(QObject *parent)
    : QObject(parent), socket(new QUdpSocket(this))
{
    // 计算ADC电压分辨率
    LSB = VOL_RANGE * 2 / (1 << ADC_DATA_WIDTH);
}

/**
 * @brief 析构函数
 *
 * 清理UDP套接字资源。
 */
UdpReceiver::~UdpReceiver()
{
    delete socket;
}

/**
 * @brief 开始监听UDP端口
 *
 * 使用之前设置的IP地址和端口开始监听，并连接readyRead信号到数据处理槽。
 * 在绑定前会检查套接字状态，如果已经绑定则先关闭以避免重复绑定错误。
 * 如果绑定失败，会发射bindFailed信号。
 */
void UdpReceiver::startListening()
{
    // 如果套接字已经绑定，先关闭它以避免重复绑定错误
    if (socket->state() == QAbstractSocket::BoundState) {
        socket->close();
    }

    if (socket->bind(localAddress, port)) {
        connect(socket, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
    } else {
        emit bindFailed(socket->errorString());
        qDebug() << "Bind failed:" << socket->errorString();
    }
}

/**
 * @brief 停止监听UDP端口
 *
 * 关闭套接字并断开信号连接。
 */
void UdpReceiver::stopListening()
{
    socket->close();
    disconnect(socket, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
}

/**
 * @brief 设置采样率
 *
 * 允许动态修改采样率，用于不同ADC配置。
 * @param rate 新的采样率（Hz）
 */
void UdpReceiver::setSampleRate(double rate)
{
    sampleRate = rate;
}

/**
 * @brief 获取当前采样率
 *
 * @return 当前采样率（Hz）
 */
double UdpReceiver::getSampleRate() const
{
    return sampleRate;
}

/**
 * @brief 设置本地IP地址和端口
 *
 * 设置UDP套接字要绑定的本地IP地址和端口号。
 * 必须在调用startListening之前设置。
 * @param address 本地IP地址，默认为QHostAddress::Any
 * @param port 本地端口号，默认为12345
 */
void UdpReceiver::setLocalAddress(const QHostAddress &address, quint16 port)
{
    localAddress = address;
    this->port = port;
}

/**
 * @brief 处理待处理的UDP数据报
 *
 * 从UDP套接字读取数据，解析为16位ADC值，
 * 提取超量程信息，转换为电压值并计算时间戳，然后发射数据接收信号。
 *
 * 数据格式：小端字节序的16位无符号整数序列
 * bit15: 通道1超量程标志
 * bit14: 通道2超量程标志
 * bit13-10: 扩展位（通常为0）
 * bit9-0: 10位ADC数据
 * 电压转换：voltage = voltage_code * LSB - LSB/2
 * 时间计算：time = 1000000/SAMPLE_RATE * sample_index (微秒)
 * ADC位宽：10位
 */
void UdpReceiver::processPendingDatagrams()
{
    while (socket->hasPendingDatagrams()) {
        // 读取完整的UDP数据报
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());

        // 使用数据流解析数据（小端字节序）
        QDataStream stream(datagram);
        stream.setByteOrder(QDataStream::LittleEndian);

        QVector<double> voltages;  // 存储转换后的电压值
        QVector<double> times;     // 存储对应的时间戳

        // 逐个处理16位ADC数据
        while (!stream.atEnd()) {
            quint16 code;
            stream >> code;

            // 提取超量程位
            // bit15: 通道1超量程, bit14: 通道2超量程
            bool channel1OTR = (code & 0x8000) != 0;  // bit15
            bool channel2OTR = (code & 0x4000) != 0;  // bit14

            // 如果有超量程，发射信号
            if (channel1OTR || channel2OTR) {
                emit overRangeDetected(channel1OTR, channel2OTR, sampleIndex + 1);
            }

            // 屏蔽高位，获取10位ADC数据（bit9-0为ADC数据，bit13-10为扩展位）
            quint16 adcData = code & 0x03FF;  // 取低10位

            // 处理ADC代码的符号扩展（10位ADC，有符号）
            // 如果高于2^(ADC_DATA_WIDTH-1)，则减去2^ADC_DATA_WIDTH
            int voltageCode = adcData;
            if (voltageCode > (1 << (ADC_DATA_WIDTH - 1))) {
                voltageCode -= (1 << ADC_DATA_WIDTH);
            }

            // 转换为实际电压值
            // voltage = voltage_code * LSB - LSB/2
            double voltage = voltageCode * LSB - LSB / 2;
            voltages.append(voltage);

            // 计算采样时间（微秒）
            // time = 1000000 / SAMPLE_RATE * sample_index
            double time = 1000000.0 / sampleRate * (++sampleIndex);
            times.append(time);
        }

        // 如果有数据，发射信号通知接收者
        if (!voltages.isEmpty()) {
            emit dataReceived(voltages, times);
        }
    }
}