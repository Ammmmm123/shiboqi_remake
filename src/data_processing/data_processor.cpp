#include "data_processor.h"
#include "fft_processor.h"
#include "frequency_detector.h"
#include <QDebug>
#include <cmath>
#include <algorithm>

/**
 * @brief 构造函数
 */
DataProcessor::DataProcessor(QObject *parent)
    : QObject(parent)
    , dataNum(0)
    , sampleRate(50000000.0)  // 默认 50MHz
{
    qDebug() << "DataProcessor 构造函数";
}

/**
 * @brief 析构函数
 */
DataProcessor::~DataProcessor()
{
    // TODO: 清理资源
    qDebug() << "DataProcessor 析构函数";
}

/**
 * @brief 设置采样配置
 * @param dataNum 数据个数
 * @param sampleRate 采样率
 */
void DataProcessor::setSamplingConfig(quint32 dataNum, double sampleRate)
{
    this->dataNum = dataNum;
    this->sampleRate = sampleRate;
    qDebug() << "DataProcessor 设置采样配置: dataNum =" << dataNum << ", sampleRate =" << sampleRate << "Hz";
}

/**
 * @brief 重置数据处理器
 */
void DataProcessor::reset()
{
    // TODO: 重置内部状态
    qDebug() << "DataProcessor 已重置";
}

/**
 * @brief 处理接收到的波形数据并返回result和波形帧
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 */
void DataProcessor::processWaveformData(const QVector<double> &voltages, const QVector<double> &times)
{
    if (voltages.isEmpty() || times.isEmpty() || voltages.size() != times.size()) {
        qDebug() << "数据无效或长度不匹配，跳过处理";
        return;
    }
    
    qDebug() << "开始处理波形数据，共" << voltages.size() << "个数据点";
    
    // ========== 1. 使用已同步的采样率 ==========
    // 采样率已在模块间同步，直接使用成员变量 sampleRate
    const double BASE_CLOCK = 50000000.0;
    quint32 currentDivider = static_cast<quint32>(BASE_CLOCK / sampleRate + 0.5);
    if (currentDivider < 1) currentDivider = 1;
    
    qDebug() << "当前采样率：" << sampleRate << "Hz，分频比：" << currentDivider;
    
    // ========== 2. 频率检测（使用 FrequencyDetector）==========
    FrequencyDetector freqDetector;
    SamplingQualityInfo qualityInfo = freqDetector.evaluateSamplingQuality(voltages, times, currentDivider);
    
    double detectedFreq = qualityInfo.detectedFrequency;
    
    // ========== 3. 综合评估并生成采样参数推荐 ==========
    if (!qualityInfo.isAdequate) {
        // FrequencyDetector 判断采样质量不足，使用 generateSamplingRecommendation 生成推荐
        // 将 qualityInfo 作为参考输入，综合考虑频率、周期数、过采样倍数等因素
        SamplingRecommendation recommendation = generateSamplingRecommendation(
            detectedFreq, 
            sampleRate, 
            qualityInfo  // 传入 FrequencyDetector 的评估结果作为参考
        );
        
        emit samplingRecommendationReady(recommendation);
    }
    
    // ========== 4. 基本波形分析（最大值、最小值、峰峰值）==========
    WaveformAnalysisResult result;
    result.frequency = detectedFreq;
    
    if (!voltages.isEmpty()) {
        result.maxValue = *std::max_element(voltages.begin(), voltages.end());
        result.minValue = *std::min_element(voltages.begin(), voltages.end());
        result.peakToPeak = result.maxValue - result.minValue;
        result.amplitude = result.peakToPeak / 2.0;
        
        // 计算RMS（有效值）
        double sumSquares = 0.0;
        for (double v : voltages) {
            sumSquares += v * v;
        }
        result.rmsValue = std::sqrt(sumSquares / voltages.size());
    }
    
    emit analysisReady(result);
    
    // ========== 5. 降采样处理（用于绘图）==========
    // 暂时直接发送原始数据，后续可添加降采样算法
    emit downsampledDataReady(voltages, times);
    
    qDebug() << "波形数据处理完成";
}

/**
 * @brief 根据检测到的频率生成采样参数推荐
 * @param signalFreq 检测到的信号频率 (Hz)
 * @param currentSampleRate 当前采样率 (Hz)
 * @param qualityInfo FrequencyDetector 的评估结果（作为参考）
 * @return 采样参数推荐
 */
SamplingRecommendation DataProcessor::generateSamplingRecommendation(
    double signalFreq, 
    double currentSampleRate, 
    const SamplingQualityInfo &qualityInfo)
{
    SamplingRecommendation rec;
    
    if (signalFreq <= 0) {
        rec.reason = "无法检测到有效频率";
        return rec;
    }
    
    // ========== 参考 FrequencyDetector 的评估结果 ==========
    // qualityInfo 提供了：
    // - detectedFrequency: 检测到的频率
    // - isAdequate: 当前采样是否足够
    // - reason: 不足的原因（如"周期数不足"、"过采样倍数不足"等）
    // - actualCycles: 实际捕获的周期数
    // - recommendedDivider/SampleRate/DataNum: FrequencyDetector 的初步建议
    
    // ========== 采样率推荐策略 ==========
    // 策略目标：
    // 1. 高频信号：保证过采样倍数（降低分频比，提高采样率）
    // 2. 低频信号：增大分频比（降低采样率），在固定采样点数内捕获更多周期
    // 3. 参考 FrequencyDetector 的评估：如果是因为周期数不足，优先调整采样点数或分频比
    // 4. 优先保证波形平滑度：使用更高的过采样倍数，确保波形细节清晰
    
    const double minOversamplingRatio = 50.0;   // 最小过采样倍数（提高以保证波形平滑）
    const double idealOversamplingRatio = 100.0; // 理想过采样倍数（提高以获得更好的波形质量）
    
    // 如果 FrequencyDetector 检测到周期数不足，需要更激进的调整
    bool needMoreCycles = qualityInfo.reason.contains("周期") || qualityInfo.reason.contains("cycle");
    if (needMoreCycles) {
        qDebug() << "⚠️ FrequencyDetector 检测到周期数不足，将采用更激进的分频调整策略";
    }
    
    double minSampleRate = signalFreq * minOversamplingRatio;
    double idealSampleRate = signalFreq * idealOversamplingRatio;
    
    // 下位机基础时钟频率
    const double BASE_CLOCK = 50000000.0; // 50MHz
    
    // 支持的分频范围：1~10000
    // 计算理想分频比（频率越低，分频比越大）
    double idealDivider = BASE_CLOCK / idealSampleRate;
    
    // 如果 FrequencyDetector 提供了推荐分频比，将其作为参考下限
    // （确保新的分频比不会比 FrequencyDetector 的建议更小，除非有充分理由）
    if (needMoreCycles && qualityInfo.recommendedDivider > 0) {
        double freqDetectorDivider = static_cast<double>(qualityInfo.recommendedDivider);
        if (freqDetectorDivider > idealDivider) {
            qDebug() << "采纳 FrequencyDetector 的激进建议，分频比从" << idealDivider 
                     << "提升到" << freqDetectorDivider;
            idealDivider = freqDetectorDivider;
        }
    }
    
    // 限制在合理范围内
    if (idealDivider < 1.0) {
        idealDivider = 1.0;
    } else if (idealDivider > 10000.0) {
        idealDivider = 10000.0;
    }
    
    // 向上取整（对于低频信号，宁可分频比大一点，降低采样率）
    rec.recommendedDivider = static_cast<quint32>(std::ceil(idealDivider));
    if (rec.recommendedDivider < 1) rec.recommendedDivider = 1;
    if (rec.recommendedDivider > 10000) rec.recommendedDivider = 10000;
    
    // 计算实际采样率
    rec.recommendedSampleRate = BASE_CLOCK / rec.recommendedDivider;
    
    qDebug() << "信号频率:" << signalFreq << "Hz";
    qDebug() << "理想采样率:" << idealSampleRate << "Hz (过采样" << idealOversamplingRatio << "x)";
    qDebug() << "理想分频比:" << idealDivider << " (向上取整到" << rec.recommendedDivider << ")";
    qDebug() << "实际采样率:" << rec.recommendedSampleRate << "Hz";
    
    // 验证过采样倍数
    double actualOversampling = rec.recommendedSampleRate / signalFreq;
    
    // 如果过采样倍数低于最小要求，需要降低分频比（提高采样率）
    // 这通常发生在高频信号或需要更平滑波形的情况
    while (actualOversampling < minOversamplingRatio && rec.recommendedDivider > 1) {
        rec.recommendedDivider--;
        rec.recommendedSampleRate = BASE_CLOCK / rec.recommendedDivider;
        actualOversampling = rec.recommendedSampleRate / signalFreq;
        qDebug() << "过采样不足，降低分频比到" << rec.recommendedDivider << "，采样率" << rec.recommendedSampleRate << "Hz";
    }
    
    qDebug() << "✅ 最终分频比:" << rec.recommendedDivider 
             << ", 采样率:" << rec.recommendedSampleRate << "Hz"
             << ", 过采样倍数:" << actualOversampling << "x";
    
    // 如果采样率仍不足，给出警告
    if (rec.recommendedSampleRate < minSampleRate) {
        rec.reason = QString("⚠️ 警告：信号频率(%1 Hz)过高，推荐采样率(%2 Hz)可能不足\n建议：降低信号频率或接受较低的采样质量")
                     .arg(signalFreq, 0, 'f', 2)
                     .arg(rec.recommendedSampleRate, 0, 'f', 0);
    } else {
        rec.reason = QString("✅ 信号频率=%1 Hz，过采样倍数=%2x (波形平滑)\n分频比=%3，采样率=%4 Hz")
                     .arg(signalFreq, 0, 'f', 2)
                     .arg(actualOversampling, 0, 'f', 1)
                     .arg(rec.recommendedDivider)
                     .arg(rec.recommendedSampleRate, 0, 'f', 0);
    }
    
    // ========== 采样点数推荐策略 ==========
    // 目标：捕获至少3-5个完整周期，且总采样时间适中
    // 如果 FrequencyDetector 建议需要更多采样点，优先采纳
    
    const int minCycles = 6;      // 最少周期数
    const int idealCycles = 9;    // 理想周期数
    
    // 如果 FrequencyDetector 提供了采样点数建议，将其作为参考
    int targetCycles = idealCycles;
    if (needMoreCycles && qualityInfo.recommendedDataNum > 0) {
        // 计算 FrequencyDetector 建议的周期数
        double freqDetectorCycles = (qualityInfo.recommendedDataNum / qualityInfo.recommendedSampleRate) * signalFreq;
        if (freqDetectorCycles > idealCycles) {
            qDebug() << "采纳 FrequencyDetector 的建议，目标周期数从" << idealCycles 
                     << "提升到" << static_cast<int>(freqDetectorCycles);
            targetCycles = static_cast<int>(std::ceil(freqDetectorCycles));
        }
    }
    
    double signalPeriod = 1.0 / signalFreq; // 秒
    double idealSamplingTime = signalPeriod * targetCycles; // 秒（使用动态目标周期数）
    
    // 采样点数 = 采样时间 × 采样率
    rec.recommendedDataNum = static_cast<quint32>(idealSamplingTime * rec.recommendedSampleRate);
    
    // 限制在合理范围内（100 ~ 100000点）
    if (rec.recommendedDataNum < 100) {
        rec.recommendedDataNum = 100;
    } else if (rec.recommendedDataNum > 100000) {
        rec.recommendedDataNum = 100000;
    }
    
    // 圆整到方便的数值（如100的倍数）
    rec.recommendedDataNum = (rec.recommendedDataNum / 100) * 100;
    
    double actualCycles = (rec.recommendedDataNum / rec.recommendedSampleRate) * signalFreq;
    rec.reason += QString("\n推荐采样点数=%1，可捕获约%2个完整周期")
                  .arg(rec.recommendedDataNum)
                  .arg(actualCycles, 0, 'f', 1);
    
    return rec;
}
