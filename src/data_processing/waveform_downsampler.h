#ifndef WAVEFORM_DOWNSAMPLER_H
#define WAVEFORM_DOWNSAMPLER_H

#include <QVector>

/**
 * @brief 波形降采样器类
 * 
 * 负责对波形数据进行降采样处理
 * 用于优化绘图性能，减少需要绘制的数据点数量
 */
class WaveformDownsampler
{
public:
    WaveformDownsampler();
    ~WaveformDownsampler();
    
    /**
     * @brief 使用抽取法降采样
     * @param data 原始数据
     * @param factor 降采样因子（每factor个点取1个）
     * @return 降采样后的数据
     */
    QVector<double> decimation(const QVector<double> &data, int factor);
    
    /**
     * @brief 使用平均法降采样
     * @param data 原始数据
     * @param factor 降采样因子（每factor个点求平均）
     * @return 降采样后的数据
     */
    QVector<double> averaging(const QVector<double> &data, int factor);
    
    /**
     * @brief 使用峰值保持法降采样（适合波形显示）
     * @param data 原始数据
     * @param targetPoints 目标点数
     * @return 降采样后的数据
     */
    QVector<double> peakPreserving(const QVector<double> &data, int targetPoints);
    
    /**
     * @brief 自适应降采样（根据数据量和显示宽度自动选择最佳方法）
     * @param voltages 原始电压数据
     * @param times 原始时间数据
     * @param targetPoints 目标点数（通常为显示器像素宽度）
     * @param downsampledVoltages 降采样后的电压数据（输出）
     * @param downsampledTimes 降采样后的时间数据（输出）
     */
    void adaptiveDownsample(
        const QVector<double> &voltages,
        const QVector<double> &times,
        int targetPoints,
        QVector<double> &downsampledVoltages,
        QVector<double> &downsampledTimes
    );
    
private:
    // TODO: 添加私有成员变量和辅助函数
};

#endif // WAVEFORM_DOWNSAMPLER_H
