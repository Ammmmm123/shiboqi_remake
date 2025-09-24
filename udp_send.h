#ifndef UDP_SENDER_H
#define UDP_SENDER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

/**
 * @brief UdpSender类
 *
 * 该类用于发送UDP控制命令包，实现对数据采集设备的远程控制。
 * 数据包格式：8字节，包含识别码、地址位、参数位。
 */
class UdpSender : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit UdpSender(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UdpSender();

    /**
     * @brief 设置目标地址和端口
     * @param address 目标IP地址
     * @param port 目标端口
     */
    void setTargetAddress(const QHostAddress &address, quint16 port);

    /**
     * @brief 发送重新启动采集命令
     */
    void sendRestartCommand();

    /**
     * @brief 发送通道选择设置命令
     */
    void sendChannelSelectCommand();

    /**
     * @brief 设置通道选择
     * @param channel 通道选择 (0-2)
     */
    void setChannel(quint8 channel);

    /**
     * @brief 发送数据个数设置命令
     */
    void sendDataNumCommand();

    /**
     * @brief 发送分频系数设置命令
     */
    void sendDividerCommand();

    /**
     * @brief 设置分频系数
     * @param divider 分频系数
     */
    void setDivider(quint32 divider);

    /**
     * @brief 设置采集数据个数
     * @param dataNum 数据个数
     */
    void setDataNum(quint32 dataNum);

    /**
     * @brief 发送开始循环发送命令
     */
    void sendStartLoopCommand();

    /**
     * @brief 发送停止循环发送命令
     */
    void sendStopLoopCommand();

signals:
    /**
     * @brief 发送完成信号
     * 当UDP数据包发送完成时发射此信号
     */
    void dataSent();

private:
    /**
     * @brief 发送UDP数据包
     * @param cmdAddr 命令地址
     * @param cmdData 命令数据
     */
    void sendUdpPacket(quint8 cmdAddr, quint32 cmdData = 0);

    QUdpSocket *socket;           ///< UDP套接字指针
    QHostAddress targetAddress;   ///< 目标IP地址
    quint16 targetPort;           ///< 目标端口

    // 默认参数值
    quint32 defaultDataNum;       ///< 默认数据个数
    quint32 defaultDivider;       ///< 默认分频系数
    quint8 channel;               ///< 默认通道选择

    // 识别码常量
    static const quint8 HEADER_1 = 0x55;  ///< 包头第一个字节
    static const quint8 HEADER_2 = 0xA5;  ///< 包头第二个字节
    static const quint8 TAIL = 0xF0;      ///< 包尾
};

#endif // UDP_SENDER_H