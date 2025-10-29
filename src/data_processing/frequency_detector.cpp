#include "frequency_detector.h"
#include "fft_processor.h"
#include <QDebug>
#include <cmath>
#include <algorithm>

/**
 * @brief 构造函数
 */
FrequencyDetector::FrequencyDetector()
{
    qDebug() << "FrequencyDetector 构造函数";
}

/**
 * @brief 析构函数
 */
FrequencyDetector::~FrequencyDetector()
{
    qDebug() << "FrequencyDetector 析构函数";
}

/**
 * @brief 使用过零检测法检测频率（基于时间戳）
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @return 检测到的频率 (Hz)
 * 
 * 算法原理：
 * 1. 计算信号平均值作为零点参考
 * 2. 检测信号从负到正的过零点（上升沿）
 * 3. 记录每个过零点对应的时间戳
 * 4. 计算相邻过零点的时间间隔（周期）
 * 5. 频率 = 1 / 平均周期
 */
double FrequencyDetector::detectByZeroCrossing(const QVector<double> &voltages, const QVector<double> &times)
{
    if (voltages.size() < 3 || times.size() < 3 || voltages.size() != times.size()) {
        qDebug() << "数据点太少或数据长度不匹配，无法检测频率";
        return 0.0;
    }
    
    // 计算信号平均值作为零点参考（适应有直流偏置的信号）
    double mean = 0.0;
    for (double v : voltages) {
        mean += v;
    }
    mean /= voltages.size();
    
    // 检测上升沿过零点（从负到正），记录对应的时间戳
    QVector<double> zeroCrossingTimes;
    for (int i = 1; i < voltages.size(); ++i) {
        double prev = voltages[i - 1] - mean;
        double curr = voltages[i] - mean;
        
        // 上升沿过零：前一个点 <= 0，当前点 > 0
        if (prev <= 0.0 && curr > 0.0) {
            // 线性插值计算精确过零时刻
            double ratio = -prev / (curr - prev);
            double zeroTime = times[i - 1] + ratio * (times[i] - times[i - 1]);
            zeroCrossingTimes.append(zeroTime);
        }
    }
    
    // 至少需要2个过零点才能计算周期
    if (zeroCrossingTimes.size() < 2) {
        qDebug() << "过零点太少（" << zeroCrossingTimes.size() << "个），无法计算频率";
        return 0.0;
    }
    
    // 计算相邻过零点之间的时间间隔（周期，单位：微秒）
    QVector<double> periods;
    for (int i = 1; i < zeroCrossingTimes.size(); ++i) {
        double period = zeroCrossingTimes[i] - zeroCrossingTimes[i - 1];
        periods.append(period);
    }
    
    // 去除异常值（使用中位数滤波）
    std::sort(periods.begin(), periods.end());
    double medianPeriod = periods[periods.size() / 2]; // 单位：微秒
    
    // 计算频率（周期单位为微秒，转换为Hz）
    double frequency = 1000000.0 / medianPeriod; // 1秒 = 1000000微秒
    
    qDebug() << "过零检测: 检测到" << zeroCrossingTimes.size() << "个过零点，"
             << "中位数周期 =" << medianPeriod << "us，"
             << "频率 =" << frequency << "Hz";
    
    return frequency;
}

/**
 * @brief 使用自相关法检测频率（基于时间戳）
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @return 检测到的频率 (Hz)
 */
double FrequencyDetector::detectByAutocorrelation(const QVector<double> &voltages, const QVector<double> &times)
{
    // TODO: 实现自相关算法（暂未实现，返回0）
    Q_UNUSED(voltages);
    Q_UNUSED(times);
    return 0.0;
}

/**
 * @brief 使用FFT法检测频率（基频，基于时间戳）
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @return 检测到的频率 (Hz)
 * 
 * 算法原理：
 * 1. 计算实际采样率（从时间戳）
 * 2. 对电压数据进行FFT变换
 * 3. 计算幅度谱
 * 4. 寻找幅度谱中的最大峰值（跳过DC分量）
 * 5. 根据峰值索引和频率分辨率计算主频率
 */
double FrequencyDetector::detectByFFT(const QVector<double> &voltages, const QVector<double> &times)
{
    if (voltages.size() < 4 || times.size() < 4 || voltages.size() != times.size()) {

        return 0.0;
    }
    
    // 计算实际采样率（从时间戳）
    double totalTime = times.last() - times.first(); // 微秒
    double avgSampleInterval = totalTime / (times.size() - 1); // 微秒
    double samplingRate = 1000000.0 / avgSampleInterval; // Hz
    

    
    // 去除直流分量（可选，提高检测精度）
    double mean = 0.0;
    for (double v : voltages) {
        mean += v;
    }
    mean /= voltages.size();
    
    QVector<double> acVoltages(voltages.size());
    for (int i = 0; i < voltages.size(); ++i) {
        acVoltages[i] = voltages[i] - mean;
    }
    
    // 执行FFT变换
    FFTProcessor fftProc;
    QVector<std::complex<double>> fftData = fftProc.computeFFT(acVoltages);
    
    if (fftData.isEmpty()) {

        return 0.0;
    }
    
    // 计算幅度谱
    QVector<double> magnitude = fftProc.computeMagnitude(fftData);
    
    // 寻找主频率（跳过索引0的DC分量）
    double dominantFreq = fftProc.findDominantFrequency(magnitude, samplingRate, 1);
    
    return dominantFreq;
}

/**
 * @brief 综合检测频率（自动选择最佳算法）
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @return 检测到的频率 (Hz)
 * 
 * 智能检测策略：
 * 1. 先用过零检测进行初步判断（快速、低开销）
 * 2. 根据初步结果和信号特征选择最佳算法：
 *    - 低频信号（<10kHz）：使用过零检测（精确、抗噪声）
 *    - 高频信号（≥10kHz）：使用FFT检测（频域分析更准确）
 * 3. 如果过零检测失败，自动降级使用FFT
 * 4. 对最终结果进行合理性验证
 */
double FrequencyDetector::detectFrequency(const QVector<double> &voltages, const QVector<double> &times)
{
    if (voltages.isEmpty() || times.isEmpty() || voltages.size() != times.size()) {

        return 0.0;
    }
    
    // 计算实际采样率（用于合理性检查）
    double samplingRate = 0.0;
    if (times.size() >= 2) {
        double totalTime = times.last() - times.first(); // 微秒
        double avgSampleInterval = totalTime / (times.size() - 1); // 微秒
        samplingRate = 1000000.0 / avgSampleInterval; // Hz
    }
    

    
    // ========== 第一步：过零检测（初步判断）==========
    double zeroCrossingFreq = detectByZeroCrossing(voltages, times);
    
    // 定义频率阈值（10kHz）
    const double FREQ_THRESHOLD = 10000.0; // 10kHz
    
    double finalFreq = 0.0;
    QString detectionMethod = "未知";
    
    // ========== 第二步：根据初步结果选择最佳算法 ==========
    
    if (zeroCrossingFreq > 0.1) {
        // 过零检测成功
        
        if (zeroCrossingFreq < FREQ_THRESHOLD) {
            // 低频信号：过零检测已经足够准确
            finalFreq = zeroCrossingFreq;
            detectionMethod = "过零检测（低频）";

            
        } else {

            double fftFreq = detectByFFT(voltages, times);
            
            if (fftFreq > 0.1) {
                // FFT检测成功
                
                // 比较两种方法的结果，如果差异<5%，说明结果一致
                double diff = std::abs(fftFreq - zeroCrossingFreq);
                double relativeError = diff / zeroCrossingFreq;
                
                if (relativeError < 0.05) {
                    // 结果一致，使用FFT结果（频域分析更精确）
                    finalFreq = fftFreq;
                    detectionMethod = "FFT检测（高频，与过零一致）";

                } else {
                    // 结果不一致，说明可能有谐波或噪声，FFT更可靠
                    finalFreq = fftFreq;
                    detectionMethod = "FFT检测（高频，主频检测）";

                }
            } else {
                // FFT检测失败，回退到过零检测结果
                finalFreq = zeroCrossingFreq;
                detectionMethod = "过零检测（FFT失败，回退）";

            }
        }
        
    } else {
        // 过零检测失败（可能是噪声信号、复杂波形或高频信号）
        qDebug() << "过零检测失败，尝试FFT检测";
        
        double fftFreq = detectByFFT(voltages, times);
        
        if (fftFreq > 0.1) {
            finalFreq = fftFreq;
            detectionMethod = "FFT检测（过零失败，降级）";

        } else {
            // 两种方法都失败
            finalFreq = 0.0;
            detectionMethod = "检测失败";

        }
    }
    
    // ========== 第三步：合理性验证 ==========
    if (finalFreq > 0.1 && samplingRate > 0.0) {
        double nyquistFreq = samplingRate / 2.0;
        
        // 频率应在 0.1Hz ~ 奈奎斯特频率 之间
        if (finalFreq > nyquistFreq) {

            // 可以选择返回0或保留结果
            // finalFreq = 0.0;
        }
        
        // 检查是否满足最小采样点数要求（至少2个周期）
        double period = 1.0 / finalFreq; // 秒
        double totalTimeSeconds = (times.last() - times.first()) / 1000000.0; // 秒
        double cycles = totalTimeSeconds / period;
        
        if (cycles < 2.0) {

        }
    }
    

    
    return finalFreq;
}

/**
 * @brief 检测波形中捕获的实际完整周期数（基于上升沿/下降沿）
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @return 捕获的完整周期数
 * 
 * 算法原理：
 * 1. 计算信号均值作为阈值
 * 2. 检测所有上升沿（从低到高穿过阈值）
 * 3. 计算相邻上升沿之间的时间间隔（周期）
 * 4. 使用中位数周期作为标准周期
 * 5. 完整周期数 = 总时长 / 标准周期
 */
double FrequencyDetector::detectActualCycles(const QVector<double> &voltages, const QVector<double> &times)
{
    if (voltages.size() < 3 || times.size() < 3 || voltages.size() != times.size()) {
        qDebug() << "周期检测：数据点太少";
        return 0.0;
    }
    
    // 计算信号均值作为阈值
    double mean = 0.0;
    for (double v : voltages) {
        mean += v;
    }
    mean /= voltages.size();
    
    // 检测上升沿（从负到正穿过均值）
    QVector<double> risingEdgeTimes;
    for (int i = 1; i < voltages.size(); ++i) {
        double prev = voltages[i - 1] - mean;
        double curr = voltages[i] - mean;
        
        if (prev <= 0.0 && curr > 0.0) {
            // 线性插值计算精确穿越时刻
            double ratio = -prev / (curr - prev);
            double edgeTime = times[i - 1] + ratio * (times[i] - times[i - 1]);
            risingEdgeTimes.append(edgeTime);
        }
    }
    
    qDebug() << "周期检测：检测到" << risingEdgeTimes.size() << "个上升沿";
    
    // 至少需要2个上升沿才能计算周期
    if (risingEdgeTimes.size() < 2) {
        qDebug() << "周期检测：上升沿不足，无法计算周期";
        
        // 回退策略：假设信号单调或噪声，返回一个保守估计
        // 如果只有0-1个上升沿，说明数据窗口内不足1个周期
        return 0.5; // 保守估计为半个周期
    }
    
    // 计算相邻上升沿之间的时间间隔（周期）
    QVector<double> periods;
    for (int i = 1; i < risingEdgeTimes.size(); ++i) {
        double period = risingEdgeTimes[i] - risingEdgeTimes[i - 1]; // 微秒
        periods.append(period);
    }
    
    // 使用中位数滤波去除异常值
    std::sort(periods.begin(), periods.end());
    double medianPeriod = periods[periods.size() / 2]; // 微秒
    
    qDebug() << "周期检测：中位数周期 =" << medianPeriod << "us";
    
    // 计算总时长
    double totalTime = times.last() - times.first(); // 微秒
    
    // 完整周期数 = 总时长 / 单个周期
    double actualCycles = totalTime / medianPeriod;
    
    qDebug() << "周期检测：总时长 =" << totalTime << "us，完整周期数 =" << actualCycles;
    
    return actualCycles;
}

/**
 * @brief 评估采样质量并给出优化建议
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @param currentDivider 当前分频比
 * @return 采样质量评估结果
 */
SamplingQualityInfo FrequencyDetector::evaluateSamplingQuality(
    const QVector<double> &voltages, 
    const QVector<double> &times,
    quint32 currentDivider)
{
    SamplingQualityInfo info;
    info.currentDivider = currentDivider;
    
    if (voltages.isEmpty() || times.isEmpty() || voltages.size() != times.size()) {
        info.isAdequate = false;
        info.reason = "数据无效";
        return info;
    }
    
    // 计算当前采样率
    if (times.size() >= 2) {
        double totalTime = times.last() - times.first(); // 微秒
        double avgSampleInterval = totalTime / (times.size() - 1); // 微秒
        info.currentSampleRate = 1000000.0 / avgSampleInterval; // Hz
    } else {
        info.isAdequate = false;
        info.reason = "数据点数不足";
        return info;
    }
    
    qDebug() << "======== 采样质量评估 ========";
    qDebug() << "当前分频比：" << currentDivider;
    qDebug() << "当前采样率：" << info.currentSampleRate << "Hz";
    qDebug() << "数据点数：" << voltages.size();
    
    // 检测频率
    info.detectedFrequency = detectFrequency(voltages, times);
    
    if (info.detectedFrequency < 0.1) {
        // 频率检测失败，可能需要调整采样参数
        info.isAdequate = false;
        info.reason = "无法检测到有效频率，建议检查信号源或调整采样参数";
        qDebug() << "评估结果：频率检测失败";
        return info;
    }
    
    // 计算信号周期
    double totalTimeSeconds = (times.last() - times.first()) / 1000000.0; // 秒
    double signalPeriod = 1.0 / info.detectedFrequency; // 秒
    
    qDebug() << "检测频率：" << info.detectedFrequency << "Hz";
    qDebug() << "信号周期：" << signalPeriod * 1000000.0 << "us";
    qDebug() << "采样时长：" << totalTimeSeconds * 1000000.0 << "us";
    
    // ========== 使用上升沿/下降沿检测精确计算周期数 ==========
    info.capturedCycles = detectActualCycles(voltages, times);
    
    qDebug() << "捕获周期数（精确检测）：" << info.capturedCycles;
    
    // 检查过采样倍数
    double oversamplingRatio = info.currentSampleRate / info.detectedFrequency;
    qDebug() << "过采样倍数：" << oversamplingRatio << "x";
    
    // 评估标准：
    // 1. 至少捕获 MIN_CYCLES_REQUIRED 个完整周期
    // 2. 过采样倍数至少为 MIN_OVERSAMPLING
    
    bool enoughCycles = info.capturedCycles >= MIN_CYCLES_REQUIRED;
    bool enoughOversampling = oversamplingRatio >= MIN_OVERSAMPLING;
    
    // ========== 特殊情况：周期数严重不足（<1个周期）==========
    if (info.capturedCycles < 1.0) {
        qDebug() << "⚠️ 严重警告：捕获周期数不足1个（" << info.capturedCycles << "）";
        info.isAdequate = false;
        
        // 策略：大幅提高分频比，降低采样率，延长采样时间窗口
        // 目标：在当前数据点数下，捕获 IDEAL_CYCLES 个周期
        
        // 需要的采样时长 = 理想周期数 × 单个周期时长
        double requiredSamplingTime = signalPeriod * IDEAL_CYCLES; // 秒
        
        // 需要的采样率 = 数据点数 / 采样时长
        double requiredSampleRate = voltages.size() / requiredSamplingTime; // Hz
        
        // 计算对应的分频比
        double requiredDivider = BASE_CLOCK / requiredSampleRate;
        
        // 限制范围并向上取整（宁可采样率低一点，确保捕获足够周期）
        if (requiredDivider < 1.0) requiredDivider = 1.0;
        if (requiredDivider > 10000.0) requiredDivider = 10000.0;
        
        info.recommendedDivider = static_cast<quint32>(std::ceil(requiredDivider));
        info.recommendedSampleRate = BASE_CLOCK / info.recommendedDivider;
        
        // 验证推荐参数下的周期数
        double newSamplingTime = voltages.size() / info.recommendedSampleRate;
        double newCycles = newSamplingTime / signalPeriod;
        
        // 如果推荐的分频比达到上限仍不足，建议增加采样点数
        if (newCycles < MIN_CYCLES_REQUIRED && info.recommendedDivider >= 10000) {
            // 计算需要的采样点数
            info.recommendedDataNum = static_cast<quint32>(MIN_CYCLES_REQUIRED * signalPeriod * info.recommendedSampleRate);
            if (info.recommendedDataNum > 1000000) info.recommendedDataNum = 1000000;
            
            info.reason = QString("⚠️ 严重不足：仅%1个周期！\n建议：分频比=%2（最大值），采样率=%3 Hz\n同时增加采样点数到 %4")
                          .arg(info.capturedCycles, 0, 'f', 2)
                          .arg(info.recommendedDivider)
                          .arg(info.recommendedSampleRate, 0, 'f', 0)
                          .arg(info.recommendedDataNum);
        } else {
            info.recommendedDataNum = voltages.size(); // 保持当前采样点数
            
            info.reason = QString("⚠️ 周期严重不足：仅%1个周期！\n建议：大幅提高分频比到 %2（采样率降至 %3 Hz）\n预计可捕获 %4 个周期")
                          .arg(info.capturedCycles, 0, 'f', 2)
                          .arg(info.recommendedDivider)
                          .arg(info.recommendedSampleRate, 0, 'f', 0)
                          .arg(newCycles, 0, 'f', 1);
        }
        
        qDebug() << "评估结果：周期严重不足，需要大幅提高分频比";
        qDebug() << "推荐方案：分频比" << info.recommendedDivider 
                 << "，采样率" << info.recommendedSampleRate << "Hz"
                 << "，预计捕获" << newCycles << "个周期";
        qDebug() << "================================";
        
        return info;
    }
    
    // ========== 正常评估流程 ==========
    
    if (enoughCycles && enoughOversampling) {
        // 采样质量良好
        info.isAdequate = true;
        info.recommendedDivider = currentDivider;
        info.recommendedSampleRate = info.currentSampleRate;
        info.recommendedDataNum = voltages.size();
        info.reason = QString("采样质量良好：捕获%1个周期，过采样%2倍")
                      .arg(info.capturedCycles, 0, 'f', 1)
                      .arg(oversamplingRatio, 0, 'f', 1);
        qDebug() << "评估结果：采样质量良好";
        
    } else if (!enoughCycles && enoughOversampling) {
        // 周期数不足，但采样率足够 -> 需要增加采样点数或降低采样率
        info.isAdequate = false;
        
        // 策略：降低采样率以延长采样时间，捕获更多周期
        info.recommendedDivider = calculateOptimalDivider(info.detectedFrequency, info.currentSampleRate);
        info.recommendedSampleRate = BASE_CLOCK / info.recommendedDivider;
        
        // 计算需要的采样点数（捕获 IDEAL_CYCLES 个周期）
        double idealSamplingTime = signalPeriod * IDEAL_CYCLES;
        info.recommendedDataNum = static_cast<quint32>(idealSamplingTime * info.recommendedSampleRate);
        
        // 限制范围
        if (info.recommendedDataNum < 1000) info.recommendedDataNum = 1000;
        if (info.recommendedDataNum > 1000000) info.recommendedDataNum = 1000000;
        
        info.reason = QString("周期数不足（仅%1个），建议：分频比=%2（采样率=%3 Hz），采样点数=%4")
                      .arg(info.capturedCycles, 0, 'f', 1)
                      .arg(info.recommendedDivider)
                      .arg(info.recommendedSampleRate, 0, 'f', 0)
                      .arg(info.recommendedDataNum);
        
        qDebug() << "评估结果：周期数不足，需要调整";
        
    } else if (enoughCycles && !enoughOversampling) {
        // 周期数足够，但过采样倍数不足 -> 需要提高采样率
        info.isAdequate = false;
        
        // 策略：提高采样率（降低分频比）
        info.recommendedDivider = calculateOptimalDivider(info.detectedFrequency, info.currentSampleRate);
        info.recommendedSampleRate = BASE_CLOCK / info.recommendedDivider;
        
        // 保持相同的采样时长
        info.recommendedDataNum = static_cast<quint32>(totalTimeSeconds * info.recommendedSampleRate);
        
        // 限制范围
        if (info.recommendedDataNum < 1000) info.recommendedDataNum = 1000;
        if (info.recommendedDataNum > 1000000) info.recommendedDataNum = 1000000;
        
        info.reason = QString("过采样倍数不足（仅%1x），建议：分频比=%2（采样率=%3 Hz），采样点数=%4")
                      .arg(oversamplingRatio, 0, 'f', 1)
                      .arg(info.recommendedDivider)
                      .arg(info.recommendedSampleRate, 0, 'f', 0)
                      .arg(info.recommendedDataNum);
        
        qDebug() << "评估结果：过采样倍数不足，需要提高采样率";
        
    } else {
        // 两者都不足 -> 综合调整
        info.isAdequate = false;
        
        info.recommendedDivider = calculateOptimalDivider(info.detectedFrequency, info.currentSampleRate);
        info.recommendedSampleRate = BASE_CLOCK / info.recommendedDivider;
        
        // 计算需要的采样点数
        double idealSamplingTime = signalPeriod * IDEAL_CYCLES;
        info.recommendedDataNum = static_cast<quint32>(idealSamplingTime * info.recommendedSampleRate);
        
        // 限制范围
        if (info.recommendedDataNum < 1000) info.recommendedDataNum = 1000;
        if (info.recommendedDataNum > 1000000) info.recommendedDataNum = 1000000;
        
        info.reason = QString("采样参数不足（周期%1个，过采样%2x），建议：分频比=%3（采样率=%4 Hz），采样点数=%5")
                      .arg(info.capturedCycles, 0, 'f', 1)
                      .arg(oversamplingRatio, 0, 'f', 1)
                      .arg(info.recommendedDivider)
                      .arg(info.recommendedSampleRate, 0, 'f', 0)
                      .arg(info.recommendedDataNum);
        
        qDebug() << "评估结果：采样参数全面不足，需要综合调整";
    }
    
    qDebug() << "推荐方案：分频比" << info.recommendedDivider 
             << "，采样率" << info.recommendedSampleRate << "Hz"
             << "，采样点数" << info.recommendedDataNum;
    qDebug() << "================================";
    
    return info;
}

/**
 * @brief 根据检测到的频率计算最优采样参数
 * @param detectedFreq 检测到的频率 (Hz)
 * @param currentSampleRate 当前采样率 (Hz)
 * @return 推荐的分频比
 */
quint32 FrequencyDetector::calculateOptimalDivider(double detectedFreq, double currentSampleRate)
{
    if (detectedFreq <= 0) {
        return 1; // 默认不分频
    }
    
    // 计算理想采样率（过采样20倍）
    double idealSampleRate = detectedFreq * IDEAL_OVERSAMPLING;
    
    // 计算理想分频比
    double idealDivider = BASE_CLOCK / idealSampleRate;
    
    // 限制在 1~10000 范围内
    if (idealDivider < 1.0) {
        idealDivider = 1.0;
    } else if (idealDivider > 10000.0) {
        idealDivider = 10000.0;
    }
    
    // 取整（向下取整以确保采样率不低于理想值）
    quint32 divider = static_cast<quint32>(idealDivider);
    if (divider < 1) divider = 1;
    
    // 验证过采样倍数
    double actualSampleRate = BASE_CLOCK / divider;
    double actualOversampling = actualSampleRate / detectedFreq;
    
    // 如果过采样倍数低于最小要求，降低分频比
    while (actualOversampling < MIN_OVERSAMPLING && divider > 1) {
        divider--;
        actualSampleRate = BASE_CLOCK / divider;
        actualOversampling = actualSampleRate / detectedFreq;
    }
    
    
    return divider;
}
