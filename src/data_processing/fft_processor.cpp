#include "fft_processor.h"
#include <QDebug>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief 构造函数
 */
FFTProcessor::FFTProcessor()
{
}

/**
 * @brief 析构函数
 */
FFTProcessor::~FFTProcessor()
{
}

/**
 * @brief 将数据填充到2的幂次长度
 * @param n 原始长度
 * @return 填充后的长度（2的幂）
 */
int FFTProcessor::paddToNextPowerOfTwo(int n)
{
    int power = 1;
    while (power < n) {
        power *= 2;
    }
    return power;
}

/**
 * @brief Cooley-Tukey FFT算法实现（递归版本）
 * @param data 复数数据（长度必须是2的幂）
 * 
 * 算法原理：分治法
 * 1. 将序列分为偶数项和奇数项
 * 2. 分别对两部分进行FFT
 * 3. 合并结果
 */
void FFTProcessor::fft(QVector<std::complex<double>> &data)
{
    int n = data.size();
    
    // 基础情况：长度为1，直接返回
    if (n <= 1) {
        return;
    }
    
    // 分离偶数项和奇数项
    QVector<std::complex<double>> even(n / 2);
    QVector<std::complex<double>> odd(n / 2);
    
    for (int i = 0; i < n / 2; ++i) {
        even[i] = data[i * 2];
        odd[i] = data[i * 2 + 1];
    }
    
    // 递归计算FFT
    fft(even);
    fft(odd);
    
    // 合并结果
    for (int k = 0; k < n / 2; ++k) {
        // 旋转因子：e^(-2πik/n)
        double angle = -2.0 * M_PI * k / n;
        std::complex<double> twiddle(std::cos(angle), std::sin(angle));
        std::complex<double> t = twiddle * odd[k];
        
        data[k] = even[k] + t;
        data[k + n / 2] = even[k] - t;
    }
}

/**
 * @brief 执行FFT变换
 * @param timeData 时域数据
 * @return 频域复数数据
 */
QVector<std::complex<double>> FFTProcessor::computeFFT(const QVector<double> &timeData)
{
    if (timeData.isEmpty()) {

        return QVector<std::complex<double>>();
    }
    
    // 填充到2的幂次长度
    int paddedLength = paddToNextPowerOfTwo(timeData.size());
    
    // 转换为复数数据并零填充
    QVector<std::complex<double>> complexData(paddedLength);
    for (int i = 0; i < timeData.size(); ++i) {
        complexData[i] = std::complex<double>(timeData[i], 0.0);
    }
    for (int i = timeData.size(); i < paddedLength; ++i) {
        complexData[i] = std::complex<double>(0.0, 0.0); // 零填充
    }
    
    // 执行FFT
    fft(complexData);
    

    
    return complexData;
}

/**
 * @brief 计算幅度谱
 * @param fftData FFT变换后的复数数据
 * @return 幅度谱
 */
QVector<double> FFTProcessor::computeMagnitude(const QVector<std::complex<double>> &fftData)
{
    QVector<double> magnitude(fftData.size());
    
    for (int i = 0; i < fftData.size(); ++i) {
        // 幅度 = sqrt(real^2 + imag^2)
        magnitude[i] = std::abs(fftData[i]);
    }
    
    return magnitude;
}

/**
 * @brief 计算功率谱
 * @param fftData FFT变换后的复数数据
 * @return 功率谱
 */
QVector<double> FFTProcessor::computePowerSpectrum(const QVector<std::complex<double>> &fftData)
{
    QVector<double> power(fftData.size());
    
    for (int i = 0; i < fftData.size(); ++i) {
        // 功率 = real^2 + imag^2
        double real = fftData[i].real();
        double imag = fftData[i].imag();
        power[i] = real * real + imag * imag;
    }
    
    return power;
}

/**
 * @brief 寻找频谱中的主频率峰值
 * @param magnitude 幅度谱
 * @param samplingRate 采样率 (Hz)
 * @param startIndex 搜索起始索引（跳过DC分量）
 * @return 主频率 (Hz)
 */
double FFTProcessor::findDominantFrequency(const QVector<double> &magnitude, double samplingRate, int startIndex)
{
    if (magnitude.size() < 2) {
        return 0.0;
    }
    
    // 只搜索前半部分（奈奎斯特频率以下）
    int searchLength = magnitude.size() / 2;
    
    if (startIndex >= searchLength) {
        return 0.0;
    }
    
    // 寻找最大幅度的索引
    int maxIndex = startIndex;
    double maxMagnitude = magnitude[startIndex];
    
    for (int i = startIndex + 1; i < searchLength; ++i) {
        if (magnitude[i] > maxMagnitude) {
            maxMagnitude = magnitude[i];
            maxIndex = i;
        }
    }
    
    // 频率分辨率 = 采样率 / FFT长度
    double frequencyResolution = samplingRate / magnitude.size();
    
    // ========== 优化1：抛物线插值提高频率精度（亚bin精度）==========
    // 原理：真实峰值通常在两个离散bin之间，通过拟合抛物线可以找到真实峰值位置
    double refinedIndex = maxIndex;
    
    if (maxIndex > 0 && maxIndex < searchLength - 1) {
        // 获取峰值及其相邻点的幅度
        double y1 = magnitude[maxIndex - 1];  // 左侧点
        double y2 = magnitude[maxIndex];      // 峰值点
        double y3 = magnitude[maxIndex + 1];  // 右侧点
        
        // ========== 优化2：加权质心法（备选方案）==========
        // 如果相邻点幅度接近，使用加权质心法可能更稳定
        double ratio = (y1 + y3) / (2.0 * y2);
        
        if (ratio > 0.8) {
            // 峰值不明显，使用加权质心法
            double sum = y1 + y2 + y3;
            if (sum > 1e-10) {
                double weightedSum = (maxIndex - 1) * y1 + maxIndex * y2 + (maxIndex + 1) * y3;
                refinedIndex = weightedSum / sum;
            }
        } else {
            // 峰值明显，使用抛物线插值（Quinn's第一估计器）
            // 公式：delta = 0.5 * (y1 - y3) / (y1 - 2*y2 + y3)
            double denominator = y1 - 2.0 * y2 + y3;
            
            if (std::abs(denominator) > 1e-10) {  // 避免除以0
                double delta = 0.5 * (y1 - y3) / denominator;
                
                // ========== 优化3：限制插值范围，提高鲁棒性 ==========
                // delta 应该在 [-0.5, 0.5] 范围内，超出说明峰值形状异常
                if (delta >= -0.5 && delta <= 0.5) {
                    refinedIndex = maxIndex + delta;
                } else {
                    // 插值异常，回退到加权质心法
                    double sum = y1 + y2 + y3;
                    if (sum > 1e-10) {
                        double weightedSum = (maxIndex - 1) * y1 + maxIndex * y2 + (maxIndex + 1) * y3;
                        refinedIndex = weightedSum / sum;
                    }
                }
            }
        }
    }
    
    // 主频率 = 精确索引 × 频率分辨率
    double dominantFrequency = refinedIndex * frequencyResolution;
    
    return dominantFrequency;
}


/**
 * @brief 对信号应用汉宁窗，以减少频谱泄漏
 * @param data 要处理的信号数据（将被就地修改）
 */
void FFTProcessor::applyWindow(QVector<double> &data)
{
    int size = data.size();
    if (size == 0) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        // 汉宁窗公式: 0.5 * (1 - cos(2 * PI * i / (N - 1)))
        double multiplier = 0.5 * (1.0 - std::cos(2.0 * M_PI * i / (size - 1)));
        data[i] *= multiplier;
    }
}

/**
 * @brief 使用抛物线插值在FFT幅度谱中寻找精确的峰值频率
 * @param magnitude 幅度谱 (只使用前半部分)
 * @param samplingRate 采样率 (Hz)
 * @param startIndex 搜索的起始索引 (通常为1，以跳过直流分量)
 * @return 精确的峰值频率 (Hz)
 */
double FFTProcessor::findPeakWithInterpolation(const QVector<double> &magnitude, double samplingRate, int startIndex)
{
    if (magnitude.size() < 3) {
        return 0.0;
    }

    // 只搜索前半部分（奈奎斯特频率以下）
    int searchLength = magnitude.size() / 2;
    if (startIndex >= searchLength) {
        startIndex = 1; // 回退到默认值
    }
    if (searchLength <= startIndex) {
        return 0.0;
    }


    // 1. 寻找最大幅度的索引
    int maxIndex = -1;
    double maxMagnitude = -1.0;
    
    for (int i = startIndex; i < searchLength; ++i) {
        if (magnitude[i] > maxMagnitude) {
            maxMagnitude = magnitude[i];
            maxIndex = i;
        }
    }

    if (maxIndex <= 0 || maxIndex >= searchLength - 1) {
        // 峰值在边界，无法插值，直接返回粗略计算
        if (maxIndex != -1) {
            double frequencyResolution = samplingRate / magnitude.size();
            return maxIndex * frequencyResolution;
        }
        return 0.0;
    }

    // 2. 抛物线插值
    // 使用峰值点及其左右两点进行拟合: y = ax^2 + bx + c
    // 真实峰值的偏移量 delta = -b / (2a)
    // a = (y_left - 2*y_peak + y_right) / 2
    // b = (y_right - y_left) / 2
    // delta = (y_left - y_right) / (2 * (y_left - 2*y_peak + y_right))
    double y1 = magnitude[maxIndex - 1]; // 左侧点
    double y2 = magnitude[maxIndex];     // 峰值点
    double y3 = magnitude[maxIndex + 1]; // 右侧点

    double denominator = 2.0 * (y1 - 2.0 * y2 + y3);
    
    double delta = 0.0;
    if (std::abs(denominator) > 1e-9) { // 避免除以零
        delta = (y1 - y3) / denominator;
    }

    // 限制插值范围，防止异常值
    if (delta > 0.5) delta = 0.5;
    if (delta < -0.5) delta = -0.5;

    double refinedIndex = maxIndex + delta;

    // 3. 计算最终频率
    double frequencyResolution = samplingRate / magnitude.size();
    double dominantFrequency = refinedIndex * frequencyResolution;

    return dominantFrequency;
}
