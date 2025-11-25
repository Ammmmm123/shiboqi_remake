#include "udp_send.h"
#include <QDataStream>

/**
 * @brief 构造函数实现
 *
 * 初始化UDP套接字，设置默认目标地址。
 * @param parent 父对象指针
 */
UdpSender::UdpSender(QObject *parent)
    : QObject(parent), socket(new QUdpSocket(this))
{
    // 设置默认目标地址（可以根据需要修改）
    targetAddress = QHostAddress("192.168.0.2");
    targetPort = 5000;

    // 设置默认参数值
    defaultDataNum = 1;
    defaultDivider = 0;
    channel = 0;
    waveformType = 0;  // 默认锯齿波
    protocol = 0;      // 默认UART协议
}

/**
 * @brief 析构函数实现
 *
 * 清理UDP套接字资源。
 */
UdpSender::~UdpSender()
{
    delete socket;
}

/**
 * @brief 设置目标地址和端口
 *
 * 设置UDP数据包发送的目标IP地址和端口号。
 * @param address 目标IP地址
 * @param port 目标端口
 */
void UdpSender::setTargetAddress(const QHostAddress &address, quint16 port)
{
    targetAddress = address;
    targetPort = port;
}

/**
 * @brief 发送重新启动采集命令
 *
 * 发送命令地址0，重新启动数据采集。
 */
void UdpSender::sendRestartCommand()
{   
    sendChannelSelectCommand();
    sendDataNumCommand();
    sendDividerCommand();
    sendUdpPacket(0);
}

/**
 * @brief 发送通道选择设置命令
 *
 * 发送命令地址1，设置数据采集通道。
 */
void UdpSender::sendChannelSelectCommand()
{
    // 通道选择使用低2位
    sendUdpPacket(1, channel & 0x03);
}

/**
 * @brief 发送数据个数设置命令
 *
 * 发送命令地址2，设置要采集的数据个数。
 */
void UdpSender::sendDataNumCommand()
{
    sendUdpPacket(2, defaultDataNum);
}

/**
 * @brief 发送分频系数设置命令
 *
 * 发送命令地址3，设置ADC分频系数，50Mhz/分频系数=采样率。
 */
void UdpSender::sendDividerCommand()
{
    sendUdpPacket(3, defaultDivider);
}

/**
 * @brief 设置分频系数
 *
 * 设置默认分频系数，用于发送分频系数设置命令。
 * @param divider 分频系数
 */
void UdpSender::setDivider(quint32 divider)
{
    defaultDivider = divider;
}

/**
 * @brief 设置采集数据个数
 *
 * 设置默认数据个数，用于发送数据个数设置命令。
 * @param dataNum 数据个数
 */
void UdpSender::setDataNum(quint32 dataNum)
{
    defaultDataNum = dataNum;
}

/**
 * @brief 设置通道选择
 *
 * 设置默认通道选择，用于发送通道选择设置命令。
 * @param channel 通道选择 (0-2)
 */
void UdpSender::setChannel(quint8 channel)
{
    this->channel = channel;
}

/**
 * @brief 发送开始循环发送命令
 *
 * 发送命令地址4，开始循环发送数据。
 */
void UdpSender::sendStartLoopCommand()
{   
    sendChannelSelectCommand();
    sendDataNumCommand();
    sendDividerCommand();
    sendUdpPacket(4);
}

/**
 * @brief 发送停止循环发送命令
 *
 * 发送命令地址5，停止循环发送数据。
 */
void UdpSender::sendStopLoopCommand()
{
    sendUdpPacket(5);
}

/**
 * @brief 设置波形类型
 *
 * 设置波形类型，用于发送波形设置命令。
 * @param waveformType 波形类型 (0-4)
 *        0: 锯齿波
 *        1: 正弦波
 *        2: 方波
 *        3: 三角波
 *        4: 手绘波形
 */
void UdpSender::setWaveformType(quint8 waveformType)
{
    // 限制波形类型在有效范围内 (0-4)
    this->waveformType = waveformType & 0x07;
}

/**
 * @brief 发送波形设置命令
 *
 * 发送命令设置波形类型，低三位表示波形类型：
 * 3'b000: 锯齿波 (0)
 * 3'b001: 正弦波 (1)
 * 3'b010: 方波   (2)
 * 3'b011: 三角波 (3)
 * 3'b100: 手绘波形 (4)
 */
void UdpSender::sendWaveformCommand()
{
    // 发送波形设置命令，地址6，参数为波形类型
    sendUdpPacket(6, waveformType);
}

/**
 * @brief 发送频率增加命令
 */
void UdpSender::sendFrequencyUpCommand()
{
    // cmd_dds_key_temp = 100 (位5:1, 位4:0, 位3:0) - 调整频率，增加
    // 参数 = (控制码 << 3) | 当前波形类型
    quint32 param = (4 << 3) | waveformType;
    sendUdpPacket(6, param);
}

/**
 * @brief 发送频率减少命令
 */
void UdpSender::sendFrequencyDownCommand()
{
    // cmd_dds_key_temp = 010 (位5:0, 位4:1, 位3:0) - 调整频率，减少
    // 参数 = (控制码 << 3) | 当前波形类型
    quint32 param = (2 << 3) | waveformType;
    sendUdpPacket(6, param);
}

/**
 * @brief 发送幅度增加命令
 */
void UdpSender::sendAmplitudeUpCommand()
{
    // cmd_dds_key_temp = 101 (位5:1, 位4:0, 位3:0) - 调整幅度，增加
    // 参数 = (控制码 << 3) | 当前波形类型
    quint32 param = (5 << 3) | waveformType;
    sendUdpPacket(6, param);
}


/**
 * @brief 发送幅度减少命令
 */
void UdpSender::sendAmplitudeDownCommand()
{
    // cmd_dds_key_temp = 011 (位5:0, 位4:1, 位3:1) - 调整幅度，减少
    // 参数 = (控制码 << 3) | 当前波形类型
    quint32 param = (3 << 3) | waveformType;
    sendUdpPacket(6, param);
}


/**
 * @brief 发送UDP数据包
 *
 * 构建8字节的UDP数据包并发送。
 * 数据包格式：
 * - 字节0: 0x55
 * - 字节1: 0xA5
 * - 字节2: 地址位 (8位)
 * - 字节3-6: 参数位 (32位)
 * - 字节7: 0xF0
 *
 * @param cmdAddr 命令地址
 * @param cmdData 命令数据
 */
void UdpSender::sendUdpPacket(quint8 cmdAddr, quint32 cmdData)
{
    QByteArray datagram;

    // 构建8字节数据包
    datagram.append(HEADER_1);        // 字节0: 0x55
    datagram.append(HEADER_2);        // 字节1: 0xA5
    datagram.append(cmdAddr);         // 字节2: 地址
    datagram.append((cmdData >> 24) & 0xFF);  // 字节3: 参数高字节
    datagram.append((cmdData >> 16) & 0xFF);  // 字节4: 参数字节2
    datagram.append((cmdData >> 8) & 0xFF);   // 字节5: 参数字节1
    datagram.append(cmdData & 0xFF);          // 字节6: 参数低字节
    datagram.append(TAIL);            // 字节7: 0xF0

    // 发送UDP数据包
    qint64 bytesSent = socket->writeDatagram(datagram, targetAddress, targetPort);

    if (bytesSent == datagram.size()) {
        emit dataSent();
    } else {
        // 可以添加错误处理
        qWarning() << "Failed to send UDP packet";
    }
}

/**
 * @brief 发送原始UDP数据包
 * @param datagram 要发送的数据包
 * @return 实际发送的字节数
 */
qint64 UdpSender::sendRawDatagram(const QByteArray &datagram)
{
    return socket->writeDatagram(datagram, targetAddress, targetPort);
}

/**
 * @brief 设置下位机协议类型
 * @param protocol 协议类型
 */
void UdpSender::setProtocol(ProtocolType protocol)
{
    this->protocol = static_cast<quint8>(protocol) & 0x07;
}

/**
 * @brief 发送协议选择命令
 * 
 * 发送命令地址8，设置下位机协议类型。
 * 参数低字节对应关系：
 * - 0b000 (0): UART
 * - 0b001 (1): PWM
 * - 0b010 (2): SUMP
 * - 0b011 (3): I2C
 * - 0b100 (4): SPI
 */
void UdpSender::sendProtocolSelectCommand()
{
    sendUdpPacket(8, protocol);
}
