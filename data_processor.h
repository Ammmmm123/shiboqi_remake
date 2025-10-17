#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <QVector>
#include <QString>
#include <QObject>

/**
 * @brief 波形分析结果结构体（包含智能降采样数据）
 */
struct WaveformAnalysisResult {
    // === 分析结果 ===
    double peakToPeak;    ///< 峰峰值
    double frequency;     ///< 频率 (Hz)
    double amplitude;     ///< 幅度 (峰峰值的一半)
    double maxValue;      ///< 最大值
    double minValue;      ///< 最小值
    QString dutyCycle;    ///< 占空比 (如果是方波) 或 "非方波"
    bool isReady;         ///< 是否已累积足够数据并完成分析
    
    // === 降采样数据（用于高效绘图）===
    QVector<double> downsampledVoltages;  ///< 降采样后的电压数据
    QVector<double> downsampledTimes;     ///< 降采样后的时间戳
    int downsampleRatio;                  ///< 降采样倍率（原始数据点数/降采样后点数）
};

/**
 * @brief 数据处理器类 - 高性能波形分析引擎
 *
 * 核心特性：
 * - 优化用于50MHz采样率
 * - O(n)时间复杂度的单遍扫描算法
 * - 自适应阈值和迟滞比较器
 * - 支持低频（1Hz）到高频（25MHz）信号
 * - 特殊优化方波检测
 */
class DataProcessor : public QObject {
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr);

    /**
     * @brief 流式分析波形数据（累积模式）
     * @param voltages 电压值向量（单位：伏特）
     * @param times 时间向量（单位：微秒）
     * @return 波形分析结果，isReady=false表示需要更多数据
     */
    WaveformAnalysisResult analyzeWaveform(const QVector<double>& voltages, const QVector<double>& times);

    /**
     * @brief 重置数据处理器状态
     * 
     * 清空所有累积的数据缓冲区，将处理器恢复到初始状态。
     * 建议在停止监听或开始新的数据采集前调用此方法。
     */
    void reset();

signals:
    /**
     * @brief 当分析完成并准备好结果时发射此信号
     */
    void analysisReady(const WaveformAnalysisResult &result);

    /**
     * @brief 发送降采样后的数据供绘图使用
     * @param voltages 降采样后的电压数据
     * @param times 降采样后的时间戳（微秒）
     * 
     * 此信号在每次分析完成后发射，主窗口可以直接使用这些数据进行高效绘图
     */
    void downsampledDataReady(const QVector<double> &voltages, const QVector<double> &times);

private:
    QVector<double> accumulatedVoltages;  ///< 累积的电压数据
    QVector<double> accumulatedTimes;     ///< 累积的时间数据

    /**
     * @brief 核心分析引擎：基于完整周期计数的频率计算
     * @param voltages 电压值向量
     * @param times 时间向量（微秒）
     * @return 完整的波形分析结果
     */
    WaveformAnalysisResult performAnalysis(const QVector<double>& voltages, const QVector<double>& times);

    /**
     * @brief 快速预扫描：计算过零点数量（O(n)单次遍历）
     * @param voltages 电压数据
     * @return 过零点数量
     */
    int countZeroCrossings(const QVector<double>& voltages) const;

    /**
     * @brief 线性插值计算精确过零时间
     * @param v1 前一个电压值
     * @param v2 当前电压值
     * @param t1 前一个时间戳
     * @param t2 当前时间戳
     * @param threshold 阈值
     * @return 插值后的过零时间（微秒）
     */
    double interpolateZeroCrossTime(double v1, double v2, double t1, double t2, double threshold) const;

    /**
     * @brief 智能降采样：根据频率自适应减少数据点
     * @param voltages 原始电压数据
     * @param times 原始时间戳
     * @param frequency 检测到的信号频率（Hz）
     * @param outVoltages 输出：降采样后的电压
     * @param outTimes 输出：降采样后的时间戳
     * @return 降采样倍率
     * 
     * 策略：
     * - 根据频率计算每周期最少保留点数（15个点/周期）
     * - 使用抗混叠的降采样（局部平均而非简单跳点）
     * - 保证极值点不丢失（峰值和谷值）
     * - 自动适配不同频率（1Hz - 25MHz）
     */
    int downsampleWaveform(
        const QVector<double>& voltages, 
        const QVector<double>& times, 
        double frequency,
        QVector<double>& outVoltages,
        QVector<double>& outTimes) const;
};

#endif // DATA_PROCESSOR_H