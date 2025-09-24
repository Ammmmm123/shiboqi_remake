#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <QVector>
#include <QString>

/**
 * @brief 波形分析结果结构体
 */
struct WaveformAnalysisResult {
    double peakToPeak;    ///< 峰峰值
    double frequency;     ///< 频率 (Hz)
    double amplitude;     ///< 幅度 (峰峰值的一半)
    double maxValue;      ///< 最大值
    double minValue;      ///< 最小值
    QString dutyCycle;    ///< 占空比 (如果是方波) 或 "非方波"
    bool isReady;         ///< 是否已累积足够数据并完成分析
};

/**
 * @brief 数据处理器类
 *
 * 提供波形数据分析功能，包括峰峰值、频率、幅度、最大最小值和占空比检测。
 * 至少累积10次数据后进行合并分析。
 */
class DataProcessor {
public:
    /**
     * @brief 分析波形数据（累积模式）
     * @param voltages 电压值向量
     * @param times 时间向量 (单位: 微秒)
     * @return 波形分析结果，如果未累积足够数据，isReady为false
     */
    WaveformAnalysisResult analyzeWaveform(const QVector<double>& voltages, const QVector<double>& times);

private:
    QVector<double> accumulatedVoltages;  ///< 累积的电压数据
    QVector<double> accumulatedTimes;     ///< 累积的时间数据
    int callCount = 0;                    ///< 调用次数

    /**
     * @brief 执行实际的波形分析
     * @param voltages 电压值向量
     * @param times 时间向量
     * @return 分析结果
     */
    WaveformAnalysisResult performAnalysis(const QVector<double>& voltages, const QVector<double>& times);
};

#endif // DATA_PROCESSOR_H