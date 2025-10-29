#include "fft_processor.h"
#include <QDebug>

/**
 * @brief 构造函数
 */
FFTProcessor::FFTProcessor()
{
    // TODO: 初始化FFT处理器
    qDebug() << "FFTProcessor 构造函数";
}

/**
 * @brief 析构函数
 */
FFTProcessor::~FFTProcessor()
{
    // TODO: 清理资源
    qDebug() << "FFTProcessor 析构函数";
}

/**
 * @brief 执行FFT变换
 * @param timeData 时域数据
 * @return 频域复数数据
 */
QVector<std::complex<double>> FFTProcessor::computeFFT(const QVector<double> &timeData)
{
    // TODO: 实现FFT算法
    Q_UNUSED(timeData);
    return QVector<std::complex<double>>();
}

/**
 * @brief 计算幅度谱
 * @param fftData FFT变换后的复数数据
 * @return 幅度谱
 */
QVector<double> FFTProcessor::computeMagnitude(const QVector<std::complex<double>> &fftData)
{
    // TODO: 实现幅度谱计算
    Q_UNUSED(fftData);
    return QVector<double>();
}

/**
 * @brief 计算功率谱
 * @param fftData FFT变换后的复数数据
 * @return 功率谱
 */
QVector<double> FFTProcessor::computePowerSpectrum(const QVector<std::complex<double>> &fftData)
{
    // TODO: 实现功率谱计算
    Q_UNUSED(fftData);
    return QVector<double>();
}
