#include "PWMControllerQt.h"
#include <QThread>
#include <cmath>

// 命令码定义
#define CMD_SET_DIV     0x10
#define CMD_SET_PERIOD  0x11
#define CMD_SET_DUTY    0x12

PWMControllerQt::PWMControllerQt(QObject *parent)
    : QObject(parent)
    , serialPort_(nullptr)
{
}

PWMControllerQt::~PWMControllerQt()
{
    close();
}

bool PWMControllerQt::open(const QString& portName, int baudrate)
{
    if (serialPort_ && serialPort_->isOpen()) {
        close();
    }
    
    serialPort_ = new QSerialPort(this);
    serialPort_->setPortName(portName);
    serialPort_->setBaudRate(baudrate);
    serialPort_->setDataBits(QSerialPort::Data8);
    serialPort_->setParity(QSerialPort::NoParity);
    serialPort_->setStopBits(QSerialPort::OneStop);
    serialPort_->setFlowControl(QSerialPort::NoFlowControl);
    
    if (!serialPort_->open(QIODevice::ReadWrite)) {
        QString errorMsg = QString("无法打开串口 %1: %2").arg(portName).arg(serialPort_->errorString());
        emit error(errorMsg);
        delete serialPort_;
        serialPort_ = nullptr;
        return false;
    }
    
    // 清空缓冲区
    serialPort_->clear();
    
    qDebug() << "[PWM] 串口" << portName << "打开成功 (波特率:" << baudrate << ")";
    return true;
}

void PWMControllerQt::close()
{
    if (serialPort_) {
        if (serialPort_->isOpen()) {
            serialPort_->close();
        }
        delete serialPort_;
        serialPort_ = nullptr;
    }
}

bool PWMControllerQt::isOpen() const
{
    return serialPort_ && serialPort_->isOpen();
}

bool PWMControllerQt::sendCommand(const QByteArray& data)
{
    if (!isOpen()) {
        emit error("串口未打开");
        return false;
    }
    
    // 发送两次命令 (下位机要求)
    for (int attempt = 0; attempt < 2; ++attempt) {
        qint64 bytesWritten = serialPort_->write(data);
        if (bytesWritten != data.size()) {
            emit error(QString("写入串口失败 (尝试 %1)").arg(attempt + 1));
            return false;
        }
        
        // 等待数据发送完成
        if (!serialPort_->waitForBytesWritten(100)) {
            emit error("数据发送超时");
            return false;
        }
        
        // 两次发送之间短暂延迟 (1ms)
        if (attempt == 0) {
            QThread::msleep(1);
        }
    }
    
    return true;
}

bool PWMControllerQt::setDiv(uint16_t div)
{
    if (div == 0) {
        emit error("div不能为0");
        return false;
    }
    
    QByteArray cmd;
    cmd.append(static_cast<char>(CMD_SET_DIV));
    cmd.append(static_cast<char>(div & 0xFF));         // div_lo
    cmd.append(static_cast<char>((div >> 8) & 0xFF));  // div_hi
    
    qDebug() << QString("[PWM] setDiv(%1) -> 发送: %2").arg(div).arg(QString(cmd.toHex(' ')));
    return sendCommand(cmd);
}

bool PWMControllerQt::setPeriod(uint16_t period)
{
    QByteArray cmd;
    cmd.append(static_cast<char>(CMD_SET_PERIOD));
    cmd.append(static_cast<char>(period & 0xFF));         // period_lo
    cmd.append(static_cast<char>((period >> 8) & 0xFF));  // period_hi
    
    qDebug() << QString("[PWM] setPeriod(%1) -> 发送: %2").arg(period).arg(QString(cmd.toHex(' ')));
    return sendCommand(cmd);
}

bool PWMControllerQt::setDuty(uint8_t channel, uint16_t duty)
{
    if (channel > 7) {
        emit error("通道号超出范围 (0-7)");
        return false;
    }
    
    QByteArray cmd;
    cmd.append(static_cast<char>(CMD_SET_DUTY));
    cmd.append(static_cast<char>(channel));
    cmd.append(static_cast<char>(duty & 0xFF));         // duty_lo
    cmd.append(static_cast<char>((duty >> 8) & 0xFF));  // duty_hi
    
    qDebug() << QString("[PWM] setDuty(通道%1, duty=%2) -> 发送: %3").arg(channel).arg(duty).arg(QString(cmd.toHex(' ')));
    return sendCommand(cmd);
}

bool PWMControllerQt::configurePWM(uint16_t div, uint16_t period, 
                                   uint8_t channel, uint16_t duty)
{
    if (!setDiv(div)) {
        return false;
    }
    QThread::msleep(5);
    
    if (!setPeriod(period)) {
        return false;
    }
    QThread::msleep(5);
    
    if (!setDuty(channel, duty)) {
        return false;
    }
    
    qDebug() << QString("[PWM] 配置成功: 通道%1 -> %2Hz, %3%")
                .arg(channel)
                .arg(calculateFrequency(div, period), 0, 'f', 2)
                .arg(calculateDutyCycle(duty, period), 0, 'f', 2);
    
    return true;
}

double PWMControllerQt::calculateFrequency(uint16_t div, uint16_t period)
{
    if (div == 0) return 0.0;
    const double SYS_CLK = 60000000.0;  // 60MHz
    return SYS_CLK / div / (period + 1);
}

double PWMControllerQt::calculateDutyCycle(uint16_t duty, uint16_t period)
{
    if (period == 0) return 0.0;
    return (duty * 100.0) / period;
}

bool PWMControllerQt::calculateParams(double targetFreq, uint16_t resolution,
                                     uint16_t& div, uint16_t& period)
{
    if (targetFreq <= 0 || resolution == 0) {
        return false;
    }
    
    const double SYS_CLK = 60000000.0;  // 60MHz
    
    // period = resolution - 1
    period = resolution - 1;
    if (period > 65535) {
        return false;
    }
    
    // div = SYS_CLK / (targetFreq * resolution)
    double div_calc = SYS_CLK / (targetFreq * resolution);
    div = static_cast<uint16_t>(std::round(div_calc));
    
    if (div < 1 || div > 65535) {
        return false;
    }
    
    return true;
}
