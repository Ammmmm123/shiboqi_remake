#ifndef FREQUENCY_DETECTOR_H
#define FREQUENCY_DETECTOR_H

#include <QVector>
#include <QString>

/**
 * @brief 采样质量评估结果
 */
struct SamplingQualityInfo
{
    bool isAdequate;              // 采样是否足够
    double detectedFrequency;     // 检测到的频率 (Hz)
    double capturedCycles;        // 捕获的完整周期数
    double currentSampleRate;     // 当前采样率 (Hz)
    quint32 currentDivider;       // 当前分频比
    quint32 recommendedDivider;   // 推荐分频比
    double recommendedSampleRate; // 推荐采样率 (Hz)
    quint32 recommendedDataNum;   // 推荐采样点数
    QString reason;               // 说明原因
    
    SamplingQualityInfo()
        : isAdequate(true)
        , detectedFrequency(0.0)
        , capturedCycles(0.0)
        , currentSampleRate(0.0)
        , currentDivider(1)
        , recommendedDivider(1)
        , recommendedSampleRate(50000000.0)
        , recommendedDataNum(1000)
        , reason("")
    {}
};

/**
 * @brief 频率检测器类
 * 
 * 负责从波形数据中检测频率
 * 支持多种检测算法（过零检测、自相关、FFT等）
 * 支持采样质量评估和参数推荐
 */
class FrequencyDetector
{
public:
    FrequencyDetector();
    ~FrequencyDetector();
    
    /**
     * @brief 使用过零检测法检测频率（基于时间戳）
     * @param voltages 电压数据
     * @param times 时间戳数据（微秒）
     * @return 检测到的频率 (Hz)
     */
    double detectByZeroCrossing(const QVector<double> &voltages, const QVector<double> &times);
    
    /**
     * @brief 使用自相关法检测频率（基于时间戳）
     * @param voltages 电压数据
     * @param times 时间戳数据（微秒）
     * @return 检测到的频率 (Hz)
     */
    double detectByAutocorrelation(const QVector<double> &voltages, const QVector<double> &times);
    
    /**
     * @brief 使用FFT法检测频率（基频，基于时间戳）
     * @param voltages 电压数据
     * @param times 时间戳数据（微秒）
     * @return 检测到的频率 (Hz)
     */
    double detectByFFT(const QVector<double> &voltages, const QVector<double> &times);
    
    /**
     * @brief 综合检测频率（自动选择最佳算法）
     * @param voltages 电压数据
     * @param times 时间戳数据（微秒）
     * @return 检测到的频率 (Hz)
     */
    double detectFrequency(const QVector<double> &voltages, const QVector<double> &times);
    
    /**
     * @brief 评估采样质量并给出优化建议
     * @param voltages 电压数据
     * @param times 时间戳数据（微秒）
     * @param currentDivider 当前分频比
     * @param softwareSampleRate 软件设置的采样率 (Hz)，如果 > 0 则使用此值，否则从时间戳计算
     * @return 采样质量评估结果
     */
    SamplingQualityInfo evaluateSamplingQuality(
        const QVector<double> &voltages, 
        const QVector<double> &times,
        quint32 currentDivider = 1,
        double softwareSampleRate = 0.0
    );
    
    /**
     * @brief 根据检测到的频率计算最优采样参数
     * @param detectedFreq 检测到的频率 (Hz)
     * @param currentSampleRate 当前采样率 (Hz)
     * @return 推荐的分频比
     */
    quint32 calculateOptimalDivider(double detectedFreq, double currentSampleRate);
    
    /**
     * @brief 检测波形中捕获的实际完整周期数（基于上升沿/下降沿）
     * @param voltages 电压数据
     * @param times 时间戳数据（微秒）
     * @return 捕获的完整周期数
     */
    double detectActualCycles(const QVector<double> &voltages, const QVector<double> &times);
    
private:
    static constexpr double BASE_CLOCK = 50000000.0;  // 50MHz基础时钟
    static constexpr int MIN_CYCLES_REQUIRED = 5;     // 最少需要的完整周期数
    static constexpr int IDEAL_CYCLES = 10;           // 理想周期数
    static constexpr double MIN_OVERSAMPLING = 10.0;  // 最小过采样倍数
    static constexpr double IDEAL_OVERSAMPLING = 20.0; // 理想过采样倍数
};

#endif // FREQUENCY_DETECTOR_H
