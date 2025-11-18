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
}

/**
 * @brief 析构函数
 */
FrequencyDetector::~FrequencyDetector()
{
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
    

    
    // 去除直流分量
    double mean = 0.0;
    for (double v : voltages) {
        mean += v;
    }
    mean /= voltages.size();
    
    QVector<double> acVoltages(voltages.size());
    for (int i = 0; i < voltages.size(); ++i) {
        acVoltages[i] = voltages[i] - mean;
    }

    // 应用汉宁窗以减少频谱泄漏
    FFTProcessor::applyWindow(acVoltages);
    
    // 执行FFT变换
    FFTProcessor fftProc;
    QVector<std::complex<double>> fftData = fftProc.computeFFT(acVoltages);
    
    if (fftData.isEmpty()) {

        return 0.0;
    }
    
    // 计算幅度谱
    QVector<double> magnitude = fftProc.computeMagnitude(fftData);
    
    // 使用抛物线插值寻找主频率
    double dominantFreq = FFTProcessor::findPeakWithInterpolation(magnitude, samplingRate, 1);
    
    return dominantFreq;
}

/**
 * @brief 通过阈值穿越法检测频率（DSO原理）
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @return 检测到的频率 (Hz)
 * 
 * 算法原理：
 * 1. 通过直方图确定信号的高电平(VHigh)和低电平(VLow)。
 * 2. 计算50%幅值中点 Vmid = VLow + 0.5 * (VHigh - VLow)。
 * 3. 查找所有穿过Vmid的上升沿，并用线性插值计算精确的过零时间。
 * 4. 计算相邻过零时间的间隔（周期）。
 * 5. 使用周期的中位数来抵抗噪声，并计算最终频率。
 */
double FrequencyDetector::detectByThresholdCrossing(const QVector<double> &voltages, const QVector<double> &times)
{
    if (voltages.size() < 10 || times.size() < 10) { // 需要足够的数据点
        return 0.0;
    }

    // 1. 确定高低电平
    double v_min = voltages[0], v_max = voltages[0];
    for (double v : voltages) {
        if (v < v_min) v_min = v;
        if (v > v_max) v_max = v;
    }

    if (v_max - v_min < 1e-3) { // 幅度过小
        return 0.0;
    }

    // 使用简化的直方图方法确定稳定高低电平
    const int num_bins = 100;
    QVector<int> bins(num_bins, 0);
    double bin_size = (v_max - v_min) / num_bins;

    for (double v : voltages) {
        int bin_index = static_cast<int>((v - v_min) / bin_size);
        if (bin_index >= 0 && bin_index < num_bins) {
            bins[bin_index]++;
        }
    }

    int low_bin_peak_count = 0, high_bin_peak_count = 0;
    int low_bin_index = -1, high_bin_index = -1;

    for (int i = 0; i < num_bins; ++i) {
        if (bins[i] > low_bin_peak_count) {
            low_bin_peak_count = bins[i];
            low_bin_index = i;
        }
    }
    
    // 寻找高电平峰值，避免与低电平峰值重合
    for (int i = 0; i < num_bins; ++i) {
        // 必须与低电平峰值有一定距离
        if (std::abs(i - low_bin_index) * bin_size > (v_max - v_min) * 0.3) {
             if (bins[i] > high_bin_peak_count) {
                high_bin_peak_count = bins[i];
                high_bin_index = i;
            }
        }
    }

    double v_low, v_high;
    if (low_bin_index != -1 && high_bin_index != -1 && low_bin_index != high_bin_index) {
        v_low = v_min + (low_bin_index + 0.5) * bin_size;
        v_high = v_min + (high_bin_index + 0.5) * bin_size;
        if (v_low > v_high) std::swap(v_low, v_high);
    } else {
        // 直方图方法失败，回退到取95%和5%分位点
        QVector<double> sorted_voltages = voltages;
        std::sort(sorted_voltages.begin(), sorted_voltages.end());
        v_low = sorted_voltages[sorted_voltages.size() * 0.05];
        v_high = sorted_voltages[sorted_voltages.size() * 0.95];
    }

    // 2. 计算50%阈值
    double v_mid = v_low + 0.5 * (v_high - v_low);

    // 3. 查找上升沿穿越点
    QVector<double> crossing_times;
    for (int i = 1; i < voltages.size(); ++i) {
        if (voltages[i-1] <= v_mid && voltages[i] > v_mid) {
            double prev_v = voltages[i-1];
            double curr_v = voltages[i];
            double prev_t = times[i-1];
            double curr_t = times[i];
            
            // 线性插值
            double ratio = (v_mid - prev_v) / (curr_v - prev_v);
            double crossing_time = prev_t + ratio * (curr_t - prev_t);
            crossing_times.append(crossing_time);
        }
    }

    if (crossing_times.size() < 2) {
        return 0.0; // 周期数不足
    }

    // 4. 计算周期并用中位数滤波
    QVector<double> periods;
    for (int i = 1; i < crossing_times.size(); ++i) {
        periods.append(crossing_times[i] - crossing_times[i-1]);
    }

    if (periods.isEmpty()) {
        return 0.0;
    }

    std::sort(periods.begin(), periods.end());
    double median_period = periods[periods.size() / 2];

    if (median_period < 1e-3) { // 周期过小，可能出错
        return 0.0;
    }

    // 5. 计算频率
    return 1000000.0 / median_period;
}

/**
 * @brief 综合检测频率（自动选择最佳算法）
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @return 检测到的频率 (Hz)
 * 
 * 智能检测策略：
 * 1. 最终频率测量统一使用高精度阈值穿越法
 * 2. 对结果进行合理性验证
 */
double FrequencyDetector::detectFrequency(const QVector<double> &voltages, const QVector<double> &times)
{
    if (voltages.isEmpty() || times.isEmpty() || voltages.size() != times.size()) {
        return 0.0;
    }
    
    // 最终频率测量统一使用高精度阈值穿越法
    double finalFreq = detectByThresholdCrossing(voltages, times);

    // ========== 合理性验证 ==========
    if (finalFreq > 0.1) {
        double samplingRate = 0.0;
        if (times.size() >= 2) {
            double totalTime = times.last() - times.first(); // 微秒
            double avgSampleInterval = totalTime / (times.size() - 1); // 微秒
            samplingRate = 1000000.0 / avgSampleInterval; // Hz
        }

        if (samplingRate > 0.0) {
            double nyquistFreq = samplingRate / 2.0;
            // 频率应在 0.1Hz ~ 奈奎斯特频率 之间
            if (finalFreq > nyquistFreq) {
                 // 超过奈奎斯特频率，结果无效
                 return 0.0;
            }
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
    
    // 至少需要2个上升沿才能计算周期
    if (risingEdgeTimes.size() < 2) {
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
    
    // 计算总时长
    double totalTime = times.last() - times.first(); // 微秒
    
    // 完整周期数 = 总时长 / 单个周期
    double actualCycles = totalTime / medianPeriod;
    
    return actualCycles;
}

/**
 * @brief 评估采样质量并给出优化建议
 * @param voltages 电压数据
 * @param times 时间戳数据（微秒）
 * @param currentDivider 当前分频比
 * @param softwareSampleRate 软件设置的采样率 (Hz)，如果 > 0 则使用此值，否则从时间戳计算
 * @return 采样质量评估结果
 */
SamplingQualityInfo FrequencyDetector::evaluateSamplingQuality(
    const QVector<double> &voltages, 
    const QVector<double> &times,
    quint32 currentDivider,
    double softwareSampleRate)
{
    SamplingQualityInfo info;
    info.currentDivider = currentDivider;
    
    if (voltages.isEmpty() || times.isEmpty() || voltages.size() != times.size()) {
        info.isAdequate = false;
        info.reason = "数据无效";
        return info;
    }
    
    // ========== 直接从时间戳计算当前采样率 ==========
    // 时间戳已修复：从0开始、连续递增、无周期性重置
    // 可以直接信任时间戳的准确性
    if (times.size() >= 2) {
        double totalTime = times.last() - times.first(); // 微秒
        double avgSampleInterval = totalTime / (times.size() - 1); // 微秒
        info.currentSampleRate = 1000000.0 / avgSampleInterval; // Hz
    } else {
        info.isAdequate = false;
        info.reason = "数据点数不足";
        return info;
    }
    
    // ========== 可选：与软件设置的采样率对比，用于诊断 ==========
    if (softwareSampleRate > 0.0) {
        double sampleRateDiff = std::abs(info.currentSampleRate - softwareSampleRate);
        double relativeError = sampleRateDiff / softwareSampleRate;
        
        // 如果差异超过1%，可能存在问题
        // if (relativeError > 0.01) {
        //     qDebug() << "⚠️ 采样率不一致：";
        //     qDebug() << "  ├─ 从时间戳计算：" << info.currentSampleRate << "Hz";
        //     qDebug() << "  ├─ 软件设置：" << softwareSampleRate << "Hz";
        //     qDebug() << "  └─ 相对误差：" << (relativeError * 100) << "%";
        // }
    }
    
    // 直接使用原始时间戳进行频率检测
    // 用于评估采样质量的频率，使用FFT法，因为它对信号形态不敏感
    info.detectedFrequency = detectByFFT(voltages, times);
    
    if (info.detectedFrequency < 0.1) {
        // 频率检测失败，可能需要调整采样参数
        info.isAdequate = false;
        info.reason = "无法检测到有效频率，建议检查信号源或调整采样参数";
        return info;
    }
    
    // 计算信号周期（使用原始时间戳）
    double totalTimeSeconds = (times.last() - times.first()) / 1000000.0; // 秒
    double signalPeriod = 1.0 / info.detectedFrequency; // 秒
    
    // ========== 使用上升沿/下降沿检测精确计算周期数（使用原始时间戳）==========
    info.capturedCycles = detectActualCycles(voltages, times);
    
    // 检查过采样倍数
    double oversamplingRatio = info.currentSampleRate / info.detectedFrequency;
    
    // 评估标准：
    // 1. 至少捕获 MIN_CYCLES_REQUIRED 个完整周期
    // 2. 过采样倍数至少为 MIN_OVERSAMPLING_FOR_QUALITY
    
    const double MIN_OVERSAMPLING_FOR_QUALITY = 100.0; // 关键修复：大幅提高过采样倍数要求
    
    bool enoughCycles = info.capturedCycles >= MIN_CYCLES_REQUIRED;
    bool enoughOversampling = oversamplingRatio >= MIN_OVERSAMPLING_FOR_QUALITY;
    
    // 关键修复：增加对高频信号的强制检查
    // 如果频率很高（>300kHz），但过采样率不足150x，则强制认为不足
    if (info.detectedFrequency > 300000.0 && oversamplingRatio < 150.0) {
        enoughOversampling = false;
        info.reason = QString("高频信号采样率不足 (仅%1x)").arg(oversamplingRatio, 0, 'f', 1);
    }
    
    // ========== 特殊情况：周期数严重不足（<1个周期）==========
    if (info.capturedCycles < 1.0) {
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
        if (requiredDivider > 4000.0) requiredDivider = 4000.0;
        
        info.recommendedDivider = static_cast<quint32>(std::ceil(requiredDivider));
        info.recommendedSampleRate = BASE_CLOCK / info.recommendedDivider;
        
        // 验证推荐参数下的周期数
        double newSamplingTime = voltages.size() / info.recommendedSampleRate;
        double newCycles = newSamplingTime / signalPeriod;
        
        // 如果推荐的分频比达到上限仍不足，建议增加采样点数
        if (newCycles < MIN_CYCLES_REQUIRED && info.recommendedDivider >= 4000) {
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
    }
    
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
    
    // 限制在 1~4000 范围内
    if (idealDivider < 1.0) {
        idealDivider = 1.0;
    } else if (idealDivider > 4000.0) {
        idealDivider = 4000.0;
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
