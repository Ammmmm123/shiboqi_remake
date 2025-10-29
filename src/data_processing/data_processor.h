#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <QObject>
#include <QVector>
#include <QByteArray>
#include "frequency_detector.h"  // 引入 SamplingQualityInfo

/**
 * @brief 波形分析结果结构体
 * 
 * 存储波形数据分析后的各种特征参数
 */
struct WaveformAnalysisResult
{
    double frequency;      ///< 频率 (Hz)
    double amplitude;      ///< 幅度 (V)
    double peakToPeak;     ///< 峰峰值 (V)
    double maxValue;       ///< 最大值 (V)
    double minValue;       ///< 最小值 (V)
    double rmsValue;       ///< 有效值 (V)
    double dutyCycle;      ///< 占空比 (%)
    
    WaveformAnalysisResult()
        : frequency(0.0)
        , amplitude(0.0)
        , peakToPeak(0.0)
        , maxValue(0.0)
        , minValue(0.0)
        , rmsValue(0.0)
        , dutyCycle(0.0)
    {}
};

/**
 * @brief 采样参数推荐结构体
 * 
 * 根据检测到的信号频率，推荐合适的采样率和采样点数
 */
struct SamplingRecommendation
{
    double recommendedSampleRate;  ///< 推荐采样率 (Hz)
    quint32 recommendedDataNum;    ///< 推荐采样点数
    quint32 recommendedDivider;    ///< 推荐分频比（下位机使用）
    QString reason;                ///< 推荐原因说明
    
    SamplingRecommendation()
        : recommendedSampleRate(0.0)
        , recommendedDataNum(0)
        , recommendedDivider(0)
        , reason("")
    {}
};

/**
 * @brief 数据处理器类
 * 
 * 负责波形数据的处理、分析和降采样
 * 运行在独立线程中，避免阻塞GUI
 */
class DataProcessor : public QObject
{
    Q_OBJECT
    
public:
    explicit DataProcessor(QObject *parent = nullptr);
    ~DataProcessor();
    
public slots:
    /**
     * @brief 设置采样配置
     * @param dataNum 数据个数
     * @param sampleRate 采样率
     */
    void setSamplingConfig(quint32 dataNum, double sampleRate);
    
    /**
     * @brief 重置数据处理器
     */
    void reset();
    
    /**
     * @brief 处理接收到的波形数据
     * @param voltages 电压数据
     * @param times 时间戳数据（微秒）
     */
    void processWaveformData(const QVector<double> &voltages, const QVector<double> &times);
    
signals:
    /**
     * @brief 分析结果就绪信号
     * @param result 波形分析结果
     */
    void analysisReady(const WaveformAnalysisResult &result);
    
    /**
     * @brief 降采样数据就绪信号（用于绘图）
     * @param voltages 降采样后的电压数据
     * @param times 降采样后的时间戳（微秒）
     */
    void downsampledDataReady(const QVector<double> &voltages, const QVector<double> &times);
    
    /**
     * @brief 采样参数推荐信号
     * @param recommendation 推荐的采样参数
     */
    void samplingRecommendationReady(const SamplingRecommendation &recommendation);
    
private:
    /**
     * @brief 根据检测到的频率生成采样参数推荐
     * @param signalFreq 检测到的信号频率 (Hz)
     * @param currentSampleRate 当前采样率 (Hz)
     * @param qualityInfo FrequencyDetector 的评估结果（作为参考）
     * @return 采样参数推荐
     */
    SamplingRecommendation generateSamplingRecommendation(
        double signalFreq, 
        double currentSampleRate,
        const SamplingQualityInfo &qualityInfo);
    
    quint32 dataNum;        ///< 采样数据个数
    double sampleRate;      ///< 实际采样率 (Hz)
};

// ========== 关键修复：声明元类型，支持跨线程信号传递 ==========
Q_DECLARE_METATYPE(SamplingRecommendation)

#endif // DATA_PROCESSOR_H
