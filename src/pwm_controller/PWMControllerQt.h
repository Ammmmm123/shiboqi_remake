#ifndef PWM_CONTROLLER_QT_H
#define PWM_CONTROLLER_QT_H

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>

/**
 * @brief Qt版本的PWM控制器
 * 
 * 使用QSerialPort实现串口通信，与Qt框架完全集成
 */
class PWMControllerQt : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit PWMControllerQt(QObject *parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~PWMControllerQt();
    
    /**
     * @brief 打开串口连接
     * @param portName 串口名称 (Windows: "COM3", Linux: "/dev/ttyACM0")
     * @param baudrate 波特率 (默认115200)
     * @return true=成功, false=失败
     */
    bool open(const QString& portName, int baudrate = 115200);
    
    /**
     * @brief 关闭串口连接
     */
    void close();
    
    /**
     * @brief 检查串口是否打开
     * @return true=已打开, false=未打开
     */
    bool isOpen() const;
    
    /**
     * @brief 配置PWM参数
     * @param div 分频系数 (1~65535)
     * @param period 周期计数值 (0~65535)
     * @param channel 通道号 (0~7)
     * @param duty 占空比计数值 (0~65535)
     * @return true=成功, false=失败
     */
    bool configurePWM(uint16_t div, uint16_t period, uint8_t channel, uint16_t duty);
    
    /**
     * @brief 计算实际PWM频率
     * @param div 分频系数
     * @param period 周期计数值
     * @return PWM频率 (Hz)
     */
    static double calculateFrequency(uint16_t div, uint16_t period);
    
    /**
     * @brief 计算占空比百分比
     * @param duty 占空比计数值
     * @param period 周期计数值
     * @return 占空比 (0.0~100.0)
     */
    static double calculateDutyCycle(uint16_t duty, uint16_t period);
    
    /**
     * @brief 根据目标频率和精度计算div和period
     * @param targetFreq 目标PWM频率 (Hz)
     * @param resolution 期望的占空比分辨率 (例如1000表示0.1%精度)
     * @param div 输出参数,计算得到的div值
     * @param period 输出参数,计算得到的period值
     * @return true=计算成功, false=参数超出范围
     */
    static bool calculateParams(double targetFreq, uint16_t resolution, 
                                uint16_t& div, uint16_t& period);

signals:
    /**
     * @brief 错误信号
     * @param errorMessage 错误信息
     */
    void error(const QString& errorMessage);

private:
    /**
     * @brief 发送命令帧 (自动重复发送两次)
     * @param data 命令数据
     * @return true=成功, false=失败
     */
    bool sendCommand(const QByteArray& data);
    
    /**
     * @brief 设置分频系数
     */
    bool setDiv(uint16_t div);
    
    /**
     * @brief 设置PWM周期
     */
    bool setPeriod(uint16_t period);
    
    /**
     * @brief 设置指定通道的占空比
     */
    bool setDuty(uint8_t channel, uint16_t duty);

private:
    QSerialPort *serialPort_;  ///< Qt串口对象
};

#endif // PWM_CONTROLLER_QT_H
