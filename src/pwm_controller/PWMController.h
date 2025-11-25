#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

#include <string>
#include <vector>
#include <cstdint>

class PWMController {
public:
    /**
     * @brief 构造函数
     * @param port 串口名称 (Windows: "COM3", Linux: "/dev/ttyACM0")
     * @param baudrate 波特率 (默认115200)
     */
    PWMController(const std::string& port, int baudrate = 115200);
    
    /**
     * @brief 析构函数
     */
    ~PWMController();
    
    /**
     * @brief 打开串口连接
     * @return true=成功, false=失败
     */
    bool open();
    
    /**
     * @brief 关闭串口连接
     */
    void close();
    
    /**
     * @brief 检查串口是否打开
     * @return true=已打开, false=未打开
     */
    bool isOpen() const;
    
    // ==================== 写命令 ====================
    
    /**
     * @brief 设置分频系数
     * @param div 分频值 (1~65535), tick频率 = 60MHz/div
     * @return true=成功, false=失败
     * 
     * 示例: setDiv(60) -> tick = 1MHz
     */
    bool setDiv(uint16_t div);
    
    /**
     * @brief 设置PWM周期
     * @param period 周期计数值 (0~65535), PWM频率 = tick频率/(period+1)
     * @return true=成功, false=失败
     * 
     * 示例: setPeriod(999) -> 1kHz (当div=60时)
     */
    bool setPeriod(uint16_t period);
    
    /**
     * @brief 设置指定通道的占空比
     * @param channel 通道号 (0~7)
     * @param duty 高电平计数值 (0~65535), 占空比% = duty/period * 100
     * @return true=成功, false=失败
     * 
     * 示例: setDuty(0, 500) -> 50% (当period=999时)
     */
    bool setDuty(uint8_t channel, uint16_t duty);
    
    /**
     * @brief 一次性配置PWM参数 (推荐使用)
     * @param div 分频系数
     * @param period 周期计数值
     * @param channel 通道号
     * @param duty 占空比计数值
     * @return true=成功, false=失败
     * 
     * 示例: configurePWM(60, 999, 0, 500) -> 通道0输出1kHz 50%占空比
     */
    bool configurePWM(uint16_t div, uint16_t period, uint8_t channel, uint16_t duty);
    
    /**
     * @brief 批量设置多通道占空比 (共享相同频率)
     * @param duties 占空比数组 (最多8个通道)
     * @return true=成功, false=失败
     * 
     * 示例: 
     *   std::vector<uint16_t> duties = {500, 250, 750}; // 通道0,1,2
     *   setMultiDuty(duties);
     */
    bool setMultiDuty(const std::vector<uint16_t>& duties);
    
    // ==================== 读命令 ====================
    
    /**
     * @brief 读取最近设置的duty值
     * @param duty 输出参数,返回读取的duty值
     * @return true=成功, false=失败
     */
    bool getDuty(uint16_t& duty);
    
    /**
     * @brief 读取当前period值
     * @param period 输出参数,返回读取的period值
     * @return true=成功, false=失败
     */
    bool getPeriod(uint16_t& period);
    
    /**
     * @brief 读取当前div值
     * @param div 输出参数,返回读取的div值
     * @return true=成功, false=失败
     */
    bool getDiv(uint16_t& div);
    
    /**
     * @brief Ping测试,检查通信是否正常
     * @return true=通信正常, false=通信失败
     */
    bool ping();
    
    // ==================== 辅助函数 ====================
    
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

private:
    /**
     * @brief 发送命令帧 (自动重复发送两次)
     * @param data 命令数据
     * @return true=成功, false=失败
     */
    bool sendCommand(const std::vector<uint8_t>& data);
    
    /**
     * @brief 接收响应数据
     * @param length 期望接收的字节数
     * @param timeout_ms 超时时间(毫秒)
     * @return 接收到的数据
     */
    std::vector<uint8_t> receiveResponse(size_t length, int timeout_ms = 100);
    
    /**
     * @brief 清空接收缓冲区
     */
    void flushInput();

    std::string port_;
    int baudrate_;
    int serial_fd_;  // 串口文件描述符 (Windows用HANDLE)
    bool is_open_;
};

#endif // PWM_CONTROLLER_H
