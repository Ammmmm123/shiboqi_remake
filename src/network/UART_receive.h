#ifndef UART_RECEIVE_H
#define UART_RECEIVE_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QByteArray>
#include <QRegularExpression>

/**
 * @brief UART接收器类
 *
 * 该类用于通过串口接收UART数据。
 * 提供打开/关闭串口、接收数据等功能。
 */
class UARTReceiver : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit UARTReceiver(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UARTReceiver();

    /**
     * @brief 打开串口
     * @param portName 串口名称（如"COM1"或"/dev/ttyUSB0"）
     * @param baudRate 波特率，默认9600
     * @return 打开成功返回true，否则false
     */
    bool openPort(const QString &portName, qint32 baudRate = QSerialPort::Baud9600);

    /**
     * @brief 关闭串口
     */
    void closePort();

    /**
     * @brief 检查串口是否打开
     * @return 打开返回true，否则false
     */
    bool isOpen() const;

signals:
    /**
     * @brief 数据接收信号
     * 当接收到串口数据时发射此信号
     * @param data 接收到的数据
     */
    void dataReceived(const QByteArray &data);

    /**
     * @brief 解析后的信号
     * 每隔0.2秒发射一次最近解析出的4个值：占空比、high时间、low时间、频率(Hz)
     */
    void parsedDataReady(int duty, int highTime, int lowTime, double frequency);

private slots:
    /**
     * @brief 串口数据就绪槽函数
     * 当串口有数据可读时调用
     */
    void onReadyRead();

    /**
     * @brief 定时器槽：周期性发射最近解析到的数据
     */
    void emitParsed();

private:
    QSerialPort *serialPort;  ///< 串口对象指针
    QByteArray buffer;       ///< 接收缓冲，用于处理分片数据
    QTimer *emitTimer;       ///< 周期性发射解析结果的定时器（200ms）
    int lastDuty;            ///< 最近解析到的占空比（-1 表示无效）
    int lastHigh;            ///< 最近解析到的高电平时间
    int lastLow;             ///< 最近解析到的低电平时间
    double lastFreq;         ///< 最近解析到的频率（Hz）
    QRegularExpression parserRegex; ///< 用于匹配 "num,num,num,num" 的正则
};

#endif // UART_RECEIVE_H