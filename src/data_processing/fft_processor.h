#ifndef FFT_PROCESSOR_H
#define FFT_PROCESSOR_H

#include <QVector>
#include <complex>

/**
 * @brief FFT处理器类
 * 
 * 负责快速傅里叶变换（FFT）的计算
 * 用于频域分析和频率检测
 */
class FFTProcessor
{
public:
    FFTProcessor();
    ~FFTProcessor();
    
    /**
     * @brief 执行FFT变换
     * @param timeData 时域数据
     * @return 频域复数数据
     */
    QVector<std::complex<double>> computeFFT(const QVector<double> &timeData);
    
    /**
     * @brief 计算幅度谱
     * @param fftData FFT变换后的复数数据
     * @return 幅度谱
     */
    QVector<double> computeMagnitude(const QVector<std::complex<double>> &fftData);
    
    /**
     * @brief 计算功率谱
     * @param fftData FFT变换后的复数数据
     * @return 功率谱
     */
    QVector<double> computePowerSpectrum(const QVector<std::complex<double>> &fftData);
    
    /**
     * @brief 寻找频谱中的主频率峰值
     * @param magnitude 幅度谱
     * @param samplingRate 采样率 (Hz)
     * @param startIndex 搜索起始索引（跳过DC分量）
     * @return 主频率 (Hz)
     */
    double findDominantFrequency(const QVector<double> &magnitude, double samplingRate, int startIndex = 1);

    /**
     * @brief 对信号应用汉宁窗，以减少频谱泄漏
     * @param data 要处理的信号数据（将被就地修改）
     */
    static void applyWindow(QVector<double> &data);

    /**
     * @brief 使用抛物线插值在FFT幅度谱中寻找精确的峰值频率
     * @param magnitude 幅度谱 (只使用前半部分)
     * @param samplingRate 采样率 (Hz)
     * @param startIndex 搜索的起始索引 (通常为1，以跳过直流分量)
     * @return 精确的峰值频率 (Hz)
     */
    static double findPeakWithInterpolation(const QVector<double> &magnitude, double samplingRate, int startIndex = 1);
    
private:
    /**
     * @brief Cooley-Tukey FFT算法实现（递归版本）
     * @param data 复数数据（长度必须是2的幂）
     */
    void fft(QVector<std::complex<double>> &data);
    
    /**
     * @brief 将数据填充到2的幂次长度
     * @param data 原始数据
     * @return 填充后的数据长度
     */
    int paddToNextPowerOfTwo(int n);
};

#endif // FFT_PROCESSOR_H
