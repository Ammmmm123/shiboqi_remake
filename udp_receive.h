#ifndef UDP_RECEIVER_H
#define UDP_RECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QVector>


/**
 * @brief UdpReceiver类
 *
 * 该类用于接收UDP数据包，解析ADC数据并转换为电压值。
 * 基于MATLAB代码的逻辑，实现10位ADC数据的处理。
 * 支持动态设置采样率和本地绑定地址。
 */
class UdpReceiver : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit UdpReceiver(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~UdpReceiver();

    /**
     * @brief 开始监听UDP端口
     * 使用之前设置的IP地址和端口开始监听
     */
    void startListening();

    /**
     * @brief 停止监听UDP端口
     */
    void stopListening();

    /**
     * @brief 设置采样率
     * @param rate 新的采样率（Hz）
     */
    void setSampleRate(double rate);

    /**
     * @brief 获取当前采样率
     * @return 当前采样率（Hz）
     */
    double getSampleRate() const;

    /**
     * @brief 设置本地IP地址和端口
     * @param address 要绑定的本地IP地址，默认为QHostAddress::Any
     * @param port 要绑定的端口号，默认为12345
     */
    void setLocalAddress(const QHostAddress &address = QHostAddress::Any, quint16 port = 12345);

signals:
    /**
     * @brief 数据接收信号
     * 当接收并处理完UDP数据包后发射此信号
     * @param voltages 转换后的电压值向量
     * @param times 对应的时间向量（微秒）
     */
    void dataReceived(const QVector<double> &voltages, const QVector<double> &times);

    /**
     * @brief 超量程检测信号
     * 当检测到ADC超量程时发射此信号
     * @param channel1OTR 通道1超量程标志
     * @param channel2OTR 通道2超量程标志
     * @param sampleIndex 对应的样本索引
     */
    void overRangeDetected(bool channel1OTR, bool channel2OTR, int sampleIndex);

    /**
     * @brief 绑定失败信号
     * 当UDP套接字绑定失败时发射此信号
     * @param errorString 错误描述信息
     */
    void bindFailed(const QString &errorString);

private slots:
    /**
     * @brief 处理待处理的UDP数据报
     * 当socket有数据可读时自动调用
     */
    void processPendingDatagrams();

private:
    QUdpSocket *socket;              ///< UDP套接字指针
    const int ADC_DATA_WIDTH = 10;   ///< ADC数据位宽（10位）
    const double VOL_RANGE = 5.0;    ///< ADC电压范围（±5V）
    double sampleRate = 50000000.0;    ///< 采样率（Hz），可动态设置
    double LSB;                      ///< ADC电压分辨率（LSB）
    int sampleIndex = 0;             ///< 样本索引，用于时间计算
    QHostAddress localAddress = QHostAddress("192.168.0.3"); ///< 本地绑定IP地址
    quint16 port = 6102;            ///< 本地绑定端口号
};

#endif // UDP_RECEIVER_H
