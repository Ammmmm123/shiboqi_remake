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
     * @brief 设置ADC采样配置（用于智能累积策略）
     * @param totalSamples 一次连续采样的总点数（分多个UDP包发送）
     * @param sampleRate 采样率（Hz），默认50MHz
     * 
     * 关键理解：
     * - totalSamples是一次连续采样的总数据点（例如500,000）
     * - 这些数据会被分成多个UDP包发送
     * - 采样窗口时间 = totalSamples / sampleRate
     * - 处理器需要累积所有UDP包，直到收集完整的一次采样批次
     */
    void setSamplingConfig(int totalSamples, double sampleRate = 50e6);
    
    /**
     * @brief 标记新的采样批次开始
     * 
     * 当检测到时间戳重置或不连续时调用，表示开始接收新一批采样数据
     */
    void markNewSamplingBatch();

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
    QVector<double> accumulatedVoltages;  ///< 累积的电压数据（单次采样批次内）
    QVector<double> accumulatedTimes;     ///< 累积的时间数据（单次采样批次内）
    
    // ADC采样配置（新理解）
    int configTotalSamples;   ///< 一次连续采样的总点数（分多个UDP包发送）
    double configSampleRate;  ///< ADC采样率（Hz）
    double samplingWindowUs;  ///< 单次采样窗口时间（微秒）= totalSamples / sampleRate * 1e6
    
    bool isNewBatch;          ///< 是否是新的采样批次
    int currentBatchSize;     ///< 当前批次已收到的数据点数
    double lastDetectedFrequency; ///< 上次检测到的频率（用于动态调节阈值）

    /**
     * @brief 根据信号频率动态计算批次完成阈值
     * @param estimatedFreq 估计的信号频率（Hz）
     * @return 批次完成阈值（0.0-1.0）
     * 
     * 动态策略：
     * - 高频信号（>100kHz）：30-50%阈值，快速刷新
     * - 中频信号（1kHz-100kHz）：60-80%阈值，平衡刷新率和精度
     * - 低频信号（<1kHz）：90-95%阈值，保证测量精度
     */
    double calculateDynamicThreshold(double estimatedFreq) const;

    /**
     * @brief 快速估算信号频率（用于动态阈值计算）
     * @param voltages 当前累积的电压数据
     * @param times 当前累积的时间数据
     * @return 估算的频率（Hz），0表示无法估算
     * 
     * 轻量级实现：只计算前几个过零点，避免全量扫描
     */
    double quickFrequencyEstimate(const QVector<double>& voltages, const QVector<double>& times) const;

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
     * @brief 基于FFT的频率检测（更准确，抗噪声能力强）
     * @param voltages 电压数据
     * @param sampleRate 采样率（Hz）
     * @return 检测到的主频率（Hz），0表示检测失败
     */
    double calculateFrequencyFFT(const QVector<double>& voltages, double sampleRate) const;

private:
    /**
     * @brief Cooley-Tukey FFT算法实现（原位计算）
     */
    void fft(QVector<double>& real, QVector<double>& imag, bool inverse = false) const;

    /**
     * @brief 应用Hann窗函数
     */
    void applyHannWindow(QVector<double>& data) const;

    /**
     * @brief 计算下一个2的幂次方
     */
    int nextPowerOfTwo(int n) const;
};

#endif // DATA_PROCESSOR_H