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
    qDebug() << "FFTProcessor 构造函数";
}

/**
 * @brief 析构函数
 */
FFTProcessor::~FFTProcessor()
{
    qDebug() << "FFTProcessor 析构函数";
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
    
    // 主频率 = 峰值索引 × 频率分辨率
    double dominantFrequency = maxIndex * frequencyResolution;
    

    
    return dominantFrequency;
}
