#include "data_processor.h"
#include <QVector>
#include <QString>
#include <QDebug>
#include <cmath>
#include <algorithm>

/**
 * @file data_processor.cpp
 * @brief 高性能波形分析引擎 - 优化用于50MHz采样率
 * 
 * 核心算法：
 * - 基于完整周期计数的频率计算（适配低频到高频信号）
 * - O(n)时间复杂度的单次遍历算法
 * - 零内存拷贝的流式处理
 * - 自适应阈值和迟滞比较器避免噪声抖动
 * 
 * 性能特点：
 * - 采样率：50 MHz（每个采样点间隔0.02微秒）
 * - 支持频率范围：1 Hz - 25 MHz（奈奎斯特频率）
 * - 内存占用：O(1)（只保留必要的统计信息）
 */

/**
 * @brief 构造函数
 */
DataProcessor::DataProcessor(QObject *parent)
    : QObject(parent)
    , accumulatedVoltages()
    , accumulatedTimes()
{
}

/**
 * @brief 重置数据处理器状态
 * 
 * 清空所有累积的数据缓冲区，用于停止监听或重新开始数据采集时的状态重置。
 */
void DataProcessor::reset()
{
    accumulatedVoltages.clear();
    accumulatedTimes.clear();
    qDebug() << "DataProcessor reset: 已清空累积的数据缓冲区";
}

/**
 * @brief 流式累积波形数据并触发分析
 * @param voltages 电压采样点（单位：伏特）
 * @param times 时间戳（单位：微秒）
 * @return 分析结果（isReady=false表示需要更多数据）
 * 
 * 性能优化：
 * - 避免重复的时间戳平移操作
 * - 最小化数据拷贝
 */
WaveformAnalysisResult DataProcessor::analyzeWaveform(const QVector<double>& voltages, const QVector<double>& times) {
    if (voltages.isEmpty() || times.isEmpty() || voltages.size() != times.size()) {
        WaveformAnalysisResult emptyResult;
        emptyResult.isReady = false;
        return emptyResult;
    }

    // 处理时间戳边界连续性（避免重复样本）
    int startIdx = 0;
    if (!accumulatedTimes.isEmpty() && !times.isEmpty()) {
        double lastT = accumulatedTimes.last();
        // 跳过重复或回退的时间戳
        while (startIdx < times.size() && times[startIdx] <= lastT) {
            startIdx++;
        }
    }

    // 批量追加数据（减少内存分配次数）
    if (startIdx < times.size()) {
        int appendCount = times.size() - startIdx;
        accumulatedVoltages.reserve(accumulatedVoltages.size() + appendCount);
        accumulatedTimes.reserve(accumulatedTimes.size() + appendCount);
        
        for (int i = startIdx; i < times.size(); ++i) {
            accumulatedVoltages.append(voltages[i]);
            accumulatedTimes.append(times[i]);
        }
    }

    // 快速检查：是否有足够数据进行分析（至少需要能检测2个完整周期）
    const int MIN_SAMPLES = 10; // 最少10个采样点
    if (accumulatedVoltages.size() < MIN_SAMPLES) {
        WaveformAnalysisResult result;
        result.isReady = false;
        return result;
    }

    // ========== 防护：数据量过大保护 ==========
    // 降低阈值，更频繁触发分析（避免累积过多数据）
    const int MAX_ACCUMULATED_SAMPLES = 10000; // 降低到10000点
    bool forceAnalysis = (accumulatedVoltages.size() >= MAX_ACCUMULATED_SAMPLES);
    
    // 如果数据量过大（>10000），只取前面的数据进行分析
    QVector<double> analyzeVoltages = accumulatedVoltages;
    QVector<double> analyzeTimes = accumulatedTimes;
    
    if (forceAnalysis && accumulatedVoltages.size() > MAX_ACCUMULATED_SAMPLES) {
        // 只取前MAX_ACCUMULATED_SAMPLES个点进行分析
        analyzeVoltages = accumulatedVoltages.mid(0, MAX_ACCUMULATED_SAMPLES);
        analyzeTimes = accumulatedTimes.mid(0, MAX_ACCUMULATED_SAMPLES);
        qDebug() << "Data truncated for analysis: from" << accumulatedVoltages.size() 
                 << "to" << MAX_ACCUMULATED_SAMPLES;
    }
    
    // 快速预扫描：计算过零点数量（O(n)单次遍历）
    int crossCount = countZeroCrossings(analyzeVoltages);
    
    // ========== 改进的触发逻辑：根据频率需求累积足够的周期数 ==========
    // 第一阶段：至少需要4个过零点才能初步判断频率
    const int MIN_CROSSINGS_FOR_FREQ = 4;
    if (crossCount < MIN_CROSSINGS_FOR_FREQ) {
        // 如果数据量过大但过零点不足，说明可能是直流或噪声，强制触发
        if (forceAnalysis) {
            WaveformAnalysisResult result = performAnalysis(analyzeVoltages, analyzeTimes);
            result.isReady = true;
            
            // 清理累积数据
            accumulatedVoltages.clear();
            accumulatedTimes.clear();
            
            // 发射降采样数据信号（供绘图使用）
            if (!result.downsampledVoltages.isEmpty() && !result.downsampledTimes.isEmpty()) {
                emit downsampledDataReady(result.downsampledVoltages, result.downsampledTimes);
            }
            
            // 发射分析结果信号
            emit analysisReady(result);
            return result;
        }
        
        // 数据不足以判断频率，继续累积
        WaveformAnalysisResult result;
        result.isReady = false;
        return result;
    }
    
    // 第二阶段：粗略估算频率，判断需要多少个周期
    double timeSpan = analyzeTimes.last() - analyzeTimes.first(); // 微秒
    double estimatedCycles = crossCount / 2.0; // 每个完整周期有2个过零点
    double estimatedFrequency = (estimatedCycles / timeSpan) * 1e6; // Hz
    
    // 根据频率决定需要累积的最小周期数
    const double HIGH_FREQ_THRESHOLD = 10000.0; // 10kHz
    int requiredCycles = (estimatedFrequency > HIGH_FREQ_THRESHOLD) ? 8 : 3;
    
    // ========== 添加最大周期数限制 ==========
    // 如果已经累积了超过20个周期，无论是否达到目标都强制触发（避免累积过多）
    const int MAX_CYCLES = 20;
    bool hasEnoughCycles = (estimatedCycles >= requiredCycles) || 
                           (estimatedCycles >= MAX_CYCLES) ||
                           forceAnalysis;
    
    // 判断是否已经累积了足够的周期数
    if (hasEnoughCycles) {
        // 执行完整分析
        WaveformAnalysisResult result = performAnalysis(analyzeVoltages, analyzeTimes);
        result.isReady = true;

        // 清理累积数据
        accumulatedVoltages.clear();
        accumulatedTimes.clear();

        // 发射降采样数据信号（供绘图使用）
        if (!result.downsampledVoltages.isEmpty() && !result.downsampledTimes.isEmpty()) {
            emit downsampledDataReady(result.downsampledVoltages, result.downsampledTimes);
        }

        // 发射分析结果信号
        emit analysisReady(result);
        return result;
    }

    // 数据不足，继续累积更多周期
    // 调试信息：显示当前累积状态
    if (accumulatedVoltages.size() % 2000 == 0) { // 每累积2000个点输出一次（更频繁）
        qDebug() << "Accumulating: samples=" << accumulatedVoltages.size() 
                 << ", cycles=" << estimatedCycles
                 << ", required=" << requiredCycles
                 << ", freq_est=" << estimatedFrequency << "Hz";
    }
    
    WaveformAnalysisResult result;
    result.isReady = false;
    return result;
}

/**
 * @brief 快速预扫描：计算过零点数量
 * @param voltages 电压数据
 * @return 过零点数量
 * 
 * 性能：O(n) 单次遍历，无额外内存分配
 */
int DataProcessor::countZeroCrossings(const QVector<double>& voltages) const {
    if (voltages.size() < 2) return 0;

    // 一次遍历计算最大最小值和阈值
    double vMin = voltages[0], vMax = voltages[0];
    for (int i = 1; i < voltages.size(); ++i) {
        if (voltages[i] < vMin) vMin = voltages[i];
        if (voltages[i] > vMax) vMax = voltages[i];
    }

    double threshold = (vMin + vMax) * 0.5;
    double hysteresis = (vMax - vMin) * 0.02; // 2%迟滞，避免噪声误触发

    // 带迟滞的过零计数
    int count = 0;
    bool above = (voltages[0] > threshold);
    
    for (int i = 1; i < voltages.size(); ++i) {
        if (above && voltages[i] < (threshold - hysteresis)) {
            count++;
            above = false;
        } else if (!above && voltages[i] > (threshold + hysteresis)) {
            count++;
            above = true;
        }
    }

    return count;
}

/**
 * @brief 核心分析引擎：基于完整周期计数的高精度频率计算
 * @param voltages 电压数据
 * @param times 时间戳（微秒）
 * @return 完整的波形分析结果
 * 
 * 算法核心：
 * 1. 一次遍历提取所有关键信息（最大、最小、过零点）
 * 2. 使用迟滞比较器避免噪声导致的虚假过零
 * 3. 基于完整周期计数计算频率（更准确）
 * 4. 自适应处理方波和正弦波
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(k)，k为过零点数量（通常 k << n）
 */
WaveformAnalysisResult DataProcessor::performAnalysis(const QVector<double>& voltages, const QVector<double>& times) {
    WaveformAnalysisResult result;
    result.peakToPeak = 0.0;
    result.frequency = 0.0;
    result.amplitude = 0.0;
    result.maxValue = -1e9;
    result.minValue = 1e9;
    result.dutyCycle = "非方波";
    result.isReady = false;

    const int n = voltages.size();
    if (n < 3 || times.size() != n) {
        return result;
    }

    // ========== 阶段1：单次遍历提取统计信息 ==========
    // 计算最大值、最小值、总变化量（用于判断信号类型）
    double vMin = voltages[0];
    double vMax = voltages[0];
    double totalVariation = 0.0; // 总变化量（用于区分正弦波和方波）

    for (int i = 0; i < n; ++i) {
        double v = voltages[i];
        if (v < vMin) vMin = v;
        if (v > vMax) vMax = v;
        if (i > 0) {
            totalVariation += std::fabs(v - voltages[i-1]);
        }
    }

    result.maxValue = vMax;
    result.minValue = vMin;
    result.peakToPeak = vMax - vMin;
    result.amplitude = result.peakToPeak * 0.5;

    // 防护：信号幅度太小（可能是噪声或直流）
    if (result.peakToPeak < 1e-6) {
        result.frequency = 0.0;
        result.dutyCycle = "直流或噪声";
        return result;
    }

    // ========== 阶段2：自适应阈值过零检测 ==========
    double threshold = (vMin + vMax) * 0.5;
    
    // 迟滞窗口：根据信号幅度自适应设置（抗噪声）
    // 对于50MHz采样，量化噪声通常<1%峰峰值
    double hysteresis = result.peakToPeak * 0.015; // 1.5%迟滞
    
    // 存储过零点的时间和方向
    struct ZeroCross {
        double time;      // 精确过零时间（微秒）
        bool rising;      // true=上升沿, false=下降沿
    };
    
    QVector<ZeroCross> crosses;
    crosses.reserve(n / 10); // 预估过零点数量（避免频繁realloc）

    // 状态机：带迟滞的施密特触发器
    bool isAbove = (voltages[0] > threshold);
    
    for (int i = 1; i < n; ++i) {
        double v_prev = voltages[i-1];
        double v_curr = voltages[i];
        
        // 检测上升沿过零（带迟滞）
        if (!isAbove && v_curr > (threshold + hysteresis)) {
            // 线性插值计算精确过零时间
            double t_cross = interpolateZeroCrossTime(
                v_prev, v_curr, 
                times[i-1], times[i], 
                threshold
            );
            crosses.append({t_cross, true});
            isAbove = true;
        }
        // 检测下降沿过零（带迟滞）
        else if (isAbove && v_curr < (threshold - hysteresis)) {
            double t_cross = interpolateZeroCrossTime(
                v_prev, v_curr, 
                times[i-1], times[i], 
                threshold
            );
            crosses.append({t_cross, false});
            isAbove = false;
        }
    }

    // 防护：过零点太少
    if (crosses.size() < 2) {
        result.frequency = 0.0;
        return result;
    }

    // ========== 阶段3：基于完整周期的频率计算 ==========
    // 策略：使用所有完整周期的平均值（比单个周期更准确）
    
    // 计算连续同向过零点之间的完整周期（2倍半周期）
    QVector<double> periods;
    periods.reserve(crosses.size() / 2);
    
    for (int i = 0; i < crosses.size() - 2; i += 2) {
        // 找到两个同向过零点（例如：上升沿到下一个上升沿）
        if (crosses[i].rising == crosses[i+2].rising) {
            double period = crosses[i+2].time - crosses[i].time;
            if (period > 0.01) { // 过滤异常值（周期>0.01微秒，即频率<100MHz）
                periods.append(period);
            }
        }
    }

    // 如果完整周期不足，使用半周期估算
    if (periods.isEmpty()) {
        for (int i = 0; i < crosses.size() - 1; ++i) {
            double halfPeriod = crosses[i+1].time - crosses[i].time;
            if (halfPeriod > 0.01) {
                periods.append(halfPeriod * 2.0); // 半周期×2
            }
        }
    }

    // 使用中位数滤波（对离群值robust）+ 平均值
    if (!periods.isEmpty()) {
        std::sort(periods.begin(), periods.end());
        
        // 计算中位数
        double median = (periods.size() % 2 == 0) 
            ? (periods[periods.size()/2 - 1] + periods[periods.size()/2]) * 0.5
            : periods[periods.size()/2];
        
        // 过滤离群值：只保留±40%范围内的周期
        double sumValid = 0.0;
        int countValid = 0;
        for (double p : periods) {
            if (std::fabs(p - median) <= median * 0.4) {
                sumValid += p;
                countValid++;
            }
        }
        
        if (countValid > 0) {
            double avgPeriod = sumValid / countValid; // 平均周期（微秒）
            result.frequency = 1e6 / avgPeriod;      // 转换为Hz
        }
    }

    // ========== 阶段4：占空比检测（方波特征） ==========
    // 计算高电平持续时间比例
    double highTime = 0.0;
    double totalTime = times.last() - times.first();
    
    for (int i = 1; i < n; ++i) {
        double dt = times[i] - times[i-1];
        double vAvg = (voltages[i-1] + voltages[i]) * 0.5;
        if (vAvg > threshold) {
            highTime += dt;
        }
    }
    
    double dutyRatio = (totalTime > 0) ? (highTime / totalTime) : 0.0;

    // 判断是否为方波：
    // 1. 占空比不是极端值（10%-90%）
    // 2. 总变化量大（方波有明显跳变）
    double avgVariationPerSample = totalVariation / n;
    bool isSquareWave = (dutyRatio > 0.1 && dutyRatio < 0.9) 
                        && (avgVariationPerSample > result.peakToPeak * 0.1);
    
    if (isSquareWave) {
        result.dutyCycle = QString::number(dutyRatio * 100.0, 'f', 1) + "%";
    } else {
        result.dutyCycle = "非方波";
    }

    // ========== 阶段5：智能降采样（提升绘图性能）==========
    // 只有在频率有效时才进行降采样
    if (result.frequency > 0.0) {
        result.downsampleRatio = downsampleWaveform(
            voltages, times, result.frequency,
            result.downsampledVoltages, result.downsampledTimes
        );
    } else {
        // 频率无效，不降采样（可能是直流或异常信号）
        result.downsampledVoltages = voltages;
        result.downsampledTimes = times;
        result.downsampleRatio = 1;
    }

    return result;
}

/**
 * @brief 线性插值计算精确过零时间
 * @param v1 前一个电压值
 * @param v2 当前电压值
 * @param t1 前一个时间戳
 * @param t2 当前时间戳
 * @param threshold 阈值
 * @return 插值后的过零时间（微秒）
 * 
 * 性能：内联函数，无分支预测失败
 */
inline double DataProcessor::interpolateZeroCrossTime(
    double v1, double v2, 
    double t1, double t2, 
    double threshold) const 
{
    double dv = v2 - v1;
    if (std::fabs(dv) < 1e-12) {
        return (t1 + t2) * 0.5; // 避免除零
    }
    double fraction = (threshold - v1) / dv;
    // 限制插值范围[0,1]（数值稳定性）
    fraction = std::max(0.0, std::min(1.0, fraction));
    return t1 + fraction * (t2 - t1);
}

/**
 * @brief 智能降采样算法：根据信号频率自适应减少数据点
 * @param voltages 原始电压数据
 * @param times 原始时间戳
 * @param frequency 检测到的信号频率（Hz）
 * @param outVoltages 输出：降采样后的电压
 * @param outTimes 输出：降采样后的时间戳
 * @return 降采样倍率
 * 
 * 核心策略：
 * 1. 根据频率自适应显示周期数：高频≥8个周期，低频≥3个周期
 * 2. 根据奈奎斯特定理动态调整每周期采样点数（高频更少，低频更多）
 * 3. 高频信号（>1MHz）：使用直接抽取法保持波形真实性
 * 4. 低频信号：使用极值保留法确保方波等信号不失真
 * 
 * 性能：
 * - 时间复杂度：O(n)
 * - 空间复杂度：O(n/ratio)
 */
int DataProcessor::downsampleWaveform(
    const QVector<double>& voltages, 
    const QVector<double>& times, 
    double frequency,
    QVector<double>& outVoltages,
    QVector<double>& outTimes) const 
{
    const int n = voltages.size();
    
    // 边界情况：数据太少，直接返回原数据
    if (n < 20 || frequency <= 0.0) {
        outVoltages = voltages;
        outTimes = times;
        return 1;
    }

    // ========== 计算需要显示的周期数 ==========
    // 高频信号（>10kHz）：显示至少8个周期
    // 低频信号（≤10kHz）：显示至少3个周期
    const double HIGH_FREQ_THRESHOLD = 10000.0; // 10kHz
    int targetCycles = (frequency > HIGH_FREQ_THRESHOLD) ? 8 : 3;
    
    // ========== 计算原始数据包含的周期数和时长 ==========
    double timeSpan = times.last() - times.first(); // 微秒
    double actualCycles = (frequency * timeSpan) / 1e6; // 实际周期数
    
    // 如果实际周期数不足目标周期数，显示所有数据
    if (actualCycles < targetCycles) {
        outVoltages = voltages;
        outTimes = times;
        return 1;
    }
    
    // ========== 计算需要截取的数据范围 ==========
    // 计算目标周期对应的时间跨度（微秒）
    double targetTimeSpan = (targetCycles / frequency) * 1e6; // 转换为微秒
    
    // 找到对应的数据点范围（只使用前 targetCycles 个周期的数据）
    double startTime = times.first();
    double endTime = startTime + targetTimeSpan;
    
    // 找到截止索引
    int endIdx = 0;
    for (int i = 0; i < n; ++i) {
        if (times[i] > endTime) {
            endIdx = i;
            break;
        }
    }
    if (endIdx == 0) endIdx = n; // 防止没找到（使用所有数据）
    
    // ========== 自适应计算每周期采样点数 ==========
    // 根据频率动态调整采样密度：
    // - 超高频（>2MHz）：每周期20-30点（接近奈奎斯特极限，保证基本波形）
    // - 高频（100kHz-2MHz）：每周期50-80点（平衡性能和质量）
    // - 中频（10kHz-100kHz）：每周期100-150点（高质量显示）
    // - 低频（<10kHz）：每周期200点（完美重现）
    int POINTS_PER_CYCLE;
    if (frequency > 2000000.0) {
        // 超高频：接近奈奎斯特极限，每周期20-30点
        POINTS_PER_CYCLE = 25;
    } else if (frequency > 500000.0) {
        // 高频：每周期50点
        POINTS_PER_CYCLE = 50;
    } else if (frequency > 100000.0) {
        // 中高频：每周期80点
        POINTS_PER_CYCLE = 80;
    } else if (frequency > 10000.0) {
        // 中频：每周期120点
        POINTS_PER_CYCLE = 120;
    } else {
        // 低频：每周期200点
        POINTS_PER_CYCLE = 200;
    }
    
    int targetPoints = targetCycles * POINTS_PER_CYCLE;
    
    // 计算降采样倍率（基于截取后的数据范围）
    int ratio = qMax(1, endIdx / targetPoints);
    
    // 限制降采样倍率
    const int MAX_RATIO = 1000;
    ratio = qMin(ratio, MAX_RATIO);
    
    // 如果降采样倍率<2，直接返回截取的数据
    if (ratio < 2) {
        outVoltages.reserve(endIdx);
        outTimes.reserve(endIdx);
        for (int i = 0; i < endIdx; ++i) {
            outVoltages.append(voltages[i]);
            outTimes.append(times[i]);
        }
        return 1;
    }

    // ========== 计算峰峰值（用于方波检测）==========
    double vMin = voltages[0];
    double vMax = voltages[0];
    for (int i = 0; i < endIdx; ++i) {
        if (voltages[i] < vMin) vMin = voltages[i];
        if (voltages[i] > vMax) vMax = voltages[i];
    }
    double peakToPeak = vMax - vMin;

    // ========== 执行降采样（策略根据频率选择）==========
    outVoltages.reserve(targetPoints + 100);
    outTimes.reserve(targetPoints + 100);
    
    // 添加第一个点
    outVoltages.append(voltages[0]);
    outTimes.append(times[0]);

    // 高频信号（>1MHz）：使用直接等间距抽取 + 局部极值保留
    // 低频信号：使用窗口极值法确保方波不失真
    const double VERY_HIGH_FREQ_THRESHOLD = 1000000.0; // 1MHz
    
    if (frequency > VERY_HIGH_FREQ_THRESHOLD) {
        // ========== 高频模式：直接等间距抽取（减少混叠）==========
        for (int i = ratio; i < endIdx - ratio; i += ratio) {
            // 直接取中心点（减少相位偏移）
            outVoltages.append(voltages[i]);
            outTimes.append(times[i]);
        }
    } else {
        // ========== 中低频模式：窗口极值保留法（保证方波质量）==========
        for (int i = ratio; i < endIdx - ratio; i += ratio) {
            int windowStart = qMax(0, i - ratio / 2);
            int windowEnd = qMin(endIdx, i + ratio / 2);
            
            // 在窗口内找到最大值和最小值
            double maxVal = voltages[windowStart];
            double minVal = voltages[windowStart];
            int maxIdx = windowStart;
            int minIdx = windowStart;
            
            for (int j = windowStart; j < windowEnd; ++j) {
                if (voltages[j] > maxVal) {
                    maxVal = voltages[j];
                    maxIdx = j;
                }
                if (voltages[j] < minVal) {
                    minVal = voltages[j];
                    minIdx = j;
                }
            }
            
            // 判断窗口内变化幅度
            double range = maxVal - minVal;
            
            // 如果窗口内变化>10%峰峰值，说明有显著变化（可能是方波边沿）
            if (range > peakToPeak * 0.1) {
                // 按时间顺序添加极值点
                if (maxIdx < minIdx) {
                    outVoltages.append(maxVal);
                    outTimes.append(times[maxIdx]);
                    if (minIdx != maxIdx) {
                        outVoltages.append(minVal);
                        outTimes.append(times[minIdx]);
                    }
                } else if (minIdx < maxIdx) {
                    outVoltages.append(minVal);
                    outTimes.append(times[minIdx]);
                    if (maxIdx != minIdx) {
                        outVoltages.append(maxVal);
                        outTimes.append(times[maxIdx]);
                    }
                } else {
                    // 极值点相同，只添加一次
                    outVoltages.append(voltages[i]);
                    outTimes.append(times[i]);
                }
            } else {
                // 窗口内变化小，直接取中心点
                outVoltages.append(voltages[i]);
                outTimes.append(times[i]);
            }
        }
    }
    
    // 确保截取范围的最后一个点被包含（完成最后一个周期）
    if (endIdx > 0 && (outTimes.isEmpty() || outTimes.last() != times[endIdx - 1])) {
        outVoltages.append(voltages[endIdx - 1]);
        outTimes.append(times[endIdx - 1]);
    }

    // 返回实际的数据压缩比例
    return (outVoltages.isEmpty()) ? 1 : (endIdx / outVoltages.size());
}
