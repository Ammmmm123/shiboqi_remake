#include "UART_receive.h"
#include <QDebug>

/**
 * @brief 构造函数实现
 *
 * 创建串口对象并初始化。
 * @param parent 父对象指针
 */
UARTReceiver::UARTReceiver(QObject *parent)
    : QObject(parent), serialPort(new QSerialPort(this))
{
    // 连接串口数据就绪信号到槽函数
    connect(serialPort, &QSerialPort::readyRead, this, &UARTReceiver::onReadyRead);

    // 初始化解析相关成员
    buffer.clear();
    emitTimer = new QTimer(this);
    emitTimer->setInterval(200); // 200 ms
    connect(emitTimer, &QTimer::timeout, this, &UARTReceiver::emitParsed);
    emitTimer->start();

    lastDuty = -1;
    lastHigh = -1;
    lastLow = -1;
    lastFreq = 0.0;

    // 支持形如 046,007,008,04014079 或 46,7,8,4014079 等格式
    parserRegex = QRegularExpression("(\\d+)[,](\\d+)[,](\\d+)[,](\\d+)");
}

/**
 * @brief 析构函数实现
 *
 * 清理串口资源。
 */
UARTReceiver::~UARTReceiver()
{
    closePort();
}

/**
 * @brief 打开串口
 *
 * 设置串口参数并打开串口。
 * @param portName 串口名称
 * @param baudRate 波特率
 * @return 打开成功返回true，否则false
 */
bool UARTReceiver::openPort(const QString &portName, qint32 baudRate)
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadOnly)) {
        return true;
    } else {
        qWarning() << "Failed to open UART port:" << portName << "Error:" << serialPort->errorString();
        return false;
    }
}

/**
 * @brief 关闭串口
 */
void UARTReceiver::closePort()
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }
}

/**
 * @brief 检查串口是否打开
 * @return 打开返回true，否则false
 */
bool UARTReceiver::isOpen() const
{
    return serialPort->isOpen();
}

/**
 * @brief 串口数据就绪槽函数
 *
 * 读取所有可用数据并发射数据接收信号。
 */
void UARTReceiver::onReadyRead()
{
    // 读取所有可用数据并追加到缓冲
    QByteArray data = serialPort->readAll();
    if (data.isEmpty()) return;

    // 发出原始数据接收信号（保留原有行为）
    emit dataReceived(data);

    // 追加到内部缓冲
    buffer.append(data);

    // 尝试解析缓冲中的 ASCII 数字序列
    // 转成字符串以便使用正则
    QString s = QString::fromLatin1(buffer);

    // 多次匹配，支持粘包
    QRegularExpressionMatchIterator it = parserRegex.globalMatch(s);
    int lastPos = 0;
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        if (match.hasMatch()) {
            QString g1 = match.captured(1);
            QString g2 = match.captured(2);
            QString g3 = match.captured(3);
            QString g4 = match.captured(4);

            bool ok1, ok2, ok3, ok4;
            int duty = g1.toInt(&ok1);
            int high = g2.toInt(&ok2);
            int low = g3.toInt(&ok3);
            qint64 freqRaw = g4.toLongLong(&ok4);

            if (ok1 && ok2 && ok3 && ok4) {
                // 如果第四项编码单位是 Hz 直接使用；如果需要缩放可在这里处理
                double freq = static_cast<double>(freqRaw);

                lastDuty = duty;
                lastHigh = high;
                lastLow = low;
                lastFreq = freq;
            }

            // 记录已匹配到的位置，稍后从缓冲中删除已解析部分
            lastPos = match.capturedEnd();
        }
    }

    // 移除已解析的前缀，避免缓冲无限增长
    if (lastPos > 0) {
        buffer = buffer.mid(lastPos);
    } else {
        // 如果缓冲过大（例如只有不完整的噪声），限制缓冲长度
        const int MAX_BUF = 1024;
        if (buffer.size() > MAX_BUF) {
            buffer = buffer.right(MAX_BUF/2);
        }
    }
}

void UARTReceiver::emitParsed()
{
    // 每200ms发射一次最近解析到的值（仅当有效时）
    if (lastDuty >= 0 && lastHigh >= 0 && lastLow >= 0) {
        emit parsedDataReady(lastDuty, lastHigh, lastLow, lastFreq);
    }
}