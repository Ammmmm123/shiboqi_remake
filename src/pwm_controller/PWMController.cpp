#include "PWMController.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <termios.h>
    #include <unistd.h>
#endif

// 命令码定义
#define CMD_SET_DIV     0x10
#define CMD_SET_PERIOD  0x11
#define CMD_SET_DUTY    0x12
#define CMD_GET_DUTY    0x20
#define CMD_GET_PERIOD  0x21
#define CMD_GET_DIV     0x22
#define CMD_PING        0x2F

PWMController::PWMController(const std::string& port, int baudrate)
    : port_(port), baudrate_(baudrate), serial_fd_(-1), is_open_(false) {
}

PWMController::~PWMController() {
    close();
}

bool PWMController::open() {
    if (is_open_) {
        return true;
    }

#ifdef _WIN32
    // Windows 实现
    std::string portName = "\\\\.\\" + port_;
    HANDLE hSerial = CreateFileA(
        portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "无法打开串口 " << port_ << std::endl;
        return false;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        std::cerr << "获取串口状态失败" << std::endl;
        return false;
    }

    dcbSerialParams.BaudRate = baudrate_;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        std::cerr << "设置串口参数失败" << std::endl;
        return false;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        CloseHandle(hSerial);
        std::cerr << "设置串口超时失败" << std::endl;
        return false;
    }

    serial_fd_ = reinterpret_cast<int>(hSerial);
    
#else
    // Linux 实现
    serial_fd_ = ::open(port_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd_ < 0) {
        std::cerr << "无法打开串口 " << port_ << std::endl;
        return false;
    }

    struct termios tty;
    if (tcgetattr(serial_fd_, &tty) != 0) {
        ::close(serial_fd_);
        std::cerr << "获取串口属性失败" << std::endl;
        return false;
    }

    speed_t speed = B115200;
    switch (baudrate_) {
        case 9600:   speed = B9600;   break;
        case 19200:  speed = B19200;  break;
        case 38400:  speed = B38400;  break;
        case 57600:  speed = B57600;  break;
        case 115200: speed = B115200; break;
        default:     speed = B115200; break;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 5;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(serial_fd_, TCSANOW, &tty) != 0) {
        ::close(serial_fd_);
        std::cerr << "设置串口属性失败" << std::endl;
        return false;
    }
#endif

    is_open_ = true;
    std::cout << "串口 " << port_ << " 打开成功 (波特率: " << baudrate_ << ")" << std::endl;
    
    // 清空缓冲区
    flushInput();
    
    return true;
}

void PWMController::close() {
    if (!is_open_) {
        return;
    }

#ifdef _WIN32
    CloseHandle(reinterpret_cast<HANDLE>(serial_fd_));
#else
    ::close(serial_fd_);
#endif

    serial_fd_ = -1;
    is_open_ = false;
    std::cout << "串口 " << port_ << " 已关闭" << std::endl;
}

bool PWMController::isOpen() const {
    return is_open_;
}

bool PWMController::sendCommand(const std::vector<uint8_t>& data) {
    if (!is_open_) {
        std::cerr << "串口未打开" << std::endl;
        return false;
    }

    // 发送两次命令 (下位机要求)
    for (int attempt = 0; attempt < 2; ++attempt) {
#ifdef _WIN32
        DWORD bytes_written;
        if (!WriteFile(reinterpret_cast<HANDLE>(serial_fd_), 
                      data.data(), data.size(), &bytes_written, NULL)) {
            std::cerr << "写入串口失败 (尝试 " << attempt + 1 << ")" << std::endl;
            return false;
        }
#else
        ssize_t bytes_written = write(serial_fd_, data.data(), data.size());
        if (bytes_written < 0) {
            std::cerr << "写入串口失败 (尝试 " << attempt + 1 << ")" << std::endl;
            return false;
        }
#endif
        
        // 两次发送之间短暂延迟 (1ms)
        if (attempt == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    return true;
}

std::vector<uint8_t> PWMController::receiveResponse(size_t length, int timeout_ms) {
    std::vector<uint8_t> buffer;
    if (!is_open_ || length == 0) {
        return buffer;
    }

    buffer.resize(length);
    size_t total_read = 0;
    auto start_time = std::chrono::steady_clock::now();

    while (total_read < length) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start_time
        ).count();
        
        if (elapsed > timeout_ms) {
            std::cerr << "接收超时 (已读取 " << total_read << "/" << length << " 字节)" << std::endl;
            buffer.resize(total_read);
            return buffer;
        }

#ifdef _WIN32
        DWORD bytes_read;
        if (ReadFile(reinterpret_cast<HANDLE>(serial_fd_), 
                    buffer.data() + total_read, 
                    length - total_read, 
                    &bytes_read, NULL)) {
            total_read += bytes_read;
        }
#else
        ssize_t bytes_read = read(serial_fd_, buffer.data() + total_read, length - total_read);
        if (bytes_read > 0) {
            total_read += bytes_read;
        }
#endif

        if (total_read < length) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    return buffer;
}

void PWMController::flushInput() {
    if (!is_open_) return;

#ifdef _WIN32
    PurgeComm(reinterpret_cast<HANDLE>(serial_fd_), 
              PURGE_RXCLEAR | PURGE_TXCLEAR);
#else
    tcflush(serial_fd_, TCIOFLUSH);
#endif
}

// ==================== 写命令实现 ====================

bool PWMController::setDiv(uint16_t div) {
    if (div == 0) {
        std::cerr << "div不能为0" << std::endl;
        return false;
    }

    std::vector<uint8_t> cmd = {
        CMD_SET_DIV,
        static_cast<uint8_t>(div & 0xFF),        // div_lo
        static_cast<uint8_t>((div >> 8) & 0xFF)  // div_hi
    };

    return sendCommand(cmd);
}

bool PWMController::setPeriod(uint16_t period) {
    std::vector<uint8_t> cmd = {
        CMD_SET_PERIOD,
        static_cast<uint8_t>(period & 0xFF),        // period_lo
        static_cast<uint8_t>((period >> 8) & 0xFF)  // period_hi
    };

    return sendCommand(cmd);
}

bool PWMController::setDuty(uint8_t channel, uint16_t duty) {
    if (channel > 7) {
        std::cerr << "通道号超出范围 (0-7)" << std::endl;
        return false;
    }

    std::vector<uint8_t> cmd = {
        CMD_SET_DUTY,
        channel,
        static_cast<uint8_t>(duty & 0xFF),        // duty_lo
        static_cast<uint8_t>((duty >> 8) & 0xFF)  // duty_hi
    };

    return sendCommand(cmd);
}

bool PWMController::configurePWM(uint16_t div, uint16_t period, 
                                 uint8_t channel, uint16_t duty) {
    if (!setDiv(div)) {
        return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    if (!setPeriod(period)) {
        return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    if (!setDuty(channel, duty)) {
        return false;
    }

    std::cout << "PWM配置成功: 通道" << static_cast<int>(channel) 
              << " -> " << calculateFrequency(div, period) << "Hz, "
              << calculateDutyCycle(duty, period) << "%" << std::endl;

    return true;
}

bool PWMController::setMultiDuty(const std::vector<uint16_t>& duties) {
    if (duties.size() > 8) {
        std::cerr << "通道数超出范围 (最多8个)" << std::endl;
        return false;
    }

    for (size_t i = 0; i < duties.size(); ++i) {
        if (!setDuty(static_cast<uint8_t>(i), duties[i])) {
            return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    return true;
}

// ==================== 读命令实现 ====================

bool PWMController::getDuty(uint16_t& duty) {
    std::vector<uint8_t> cmd = {CMD_GET_DUTY};
    
    flushInput();
    if (!sendCommand(cmd)) {
        return false;
    }

    std::vector<uint8_t> resp = receiveResponse(2, 200);
    if (resp.size() != 2) {
        std::cerr << "读取duty失败: 响应长度错误" << std::endl;
        return false;
    }

    duty = resp[0] | (resp[1] << 8);
    return true;
}

bool PWMController::getPeriod(uint16_t& period) {
    std::vector<uint8_t> cmd = {CMD_GET_PERIOD};
    
    flushInput();
    if (!sendCommand(cmd)) {
        return false;
    }

    std::vector<uint8_t> resp = receiveResponse(2, 200);
    if (resp.size() != 2) {
        std::cerr << "读取period失败: 响应长度错误" << std::endl;
        return false;
    }

    period = resp[0] | (resp[1] << 8);
    return true;
}

bool PWMController::getDiv(uint16_t& div) {
    std::vector<uint8_t> cmd = {CMD_GET_DIV};
    
    flushInput();
    if (!sendCommand(cmd)) {
        return false;
    }

    std::vector<uint8_t> resp = receiveResponse(2, 200);
    if (resp.size() != 2) {
        std::cerr << "读取div失败: 响应长度错误" << std::endl;
        return false;
    }

    div = resp[0] | (resp[1] << 8);
    return true;
}

bool PWMController::ping() {
    std::vector<uint8_t> cmd = {CMD_PING};
    
    flushInput();
    if (!sendCommand(cmd)) {
        return false;
    }

    std::vector<uint8_t> resp = receiveResponse(1, 200);
    if (resp.size() != 1 || resp[0] != 0xAA) {
        std::cerr << "Ping失败" << std::endl;
        return false;
    }

    std::cout << "Ping成功: 设备响应正常" << std::endl;
    return true;
}

// ==================== 辅助函数实现 ====================

double PWMController::calculateFrequency(uint16_t div, uint16_t period) {
    if (div == 0) return 0.0;
    const double SYS_CLK = 60000000.0;  // 60MHz
    return SYS_CLK / div / (period + 1);
}

double PWMController::calculateDutyCycle(uint16_t duty, uint16_t period) {
    if (period == 0) return 0.0;
    return (duty * 100.0) / period;
}

bool PWMController::calculateParams(double targetFreq, uint16_t resolution,
                                    uint16_t& div, uint16_t& period) {
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
