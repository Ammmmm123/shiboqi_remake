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
    
private:
    // TODO: 添加私有成员变量和辅助函数
};

#endif // FFT_PROCESSOR_H
