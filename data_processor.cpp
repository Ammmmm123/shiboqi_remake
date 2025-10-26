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
    , configTotalSamples(500000)  // 默认50万点（10ms @ 50MHz）
    , configSampleRate(50e6)      // 默认50MHz
    , samplingWindowUs(10000.0)   // 默认窗口 = 500000 / 50MHz * 1e6 = 10ms
    , isNewBatch(true)            // 初始为新批次
    , currentBatchSize(0)         // 当前批次大小为0
    , lastDetectedFrequency(0.0)  // 初始频率为0
{
}

/**
 * @brief 设置ADC采样配置（基于实际采样机制）
 * @param totalSamples 一次连续采样的总点数（分多个UDP包发送）
 * @param sampleRate 采样率（Hz），默认50MHz
 */
void DataProcessor::setSamplingConfig(int totalSamples, double sampleRate)
{
    configTotalSamples = totalSamples;
    configSampleRate = sampleRate;
    samplingWindowUs = (totalSamples / sampleRate) * 1e6;
    
    qDebug() << "========================================";
    qDebug() << "DataProcessor采样配置：";
    qDebug() << "  - 连续采样点数：" << totalSamples;
    qDebug() << "  - 采样窗口：" << (samplingWindowUs / 1000.0) << "ms";
    qDebug() << "  - 可检测最低频率：" << (2e6 / samplingWindowUs) << "Hz (2周期)";
    qDebug() << "========================================";
}

/**
 * @brief 标记新的采样批次开始
 */
void DataProcessor::markNewSamplingBatch()
{
    isNewBatch = true;
    currentBatchSize = 0;
    qDebug() << "标记新采样批次";
}

/**
 * @brief 根据信号频率动态计算批次完成阈值
 * @param estimatedFreq 估计的信号频率（Hz）
 * @return 批次完成阈值（0.0-1.0）
 * 
 * 动态策略（全面优化刷新率，低频信号也快速响应）：
 * - 超高频（>1MHz）：15%阈值，极速刷新
 * - 高频（100kHz-1MHz）：25%阈值，高速刷新
 * - 中高频（10kHz-100kHz）：35%阈值，快速刷新
 * - 中频（1kHz-10kHz）：45%阈值，快速响应
 * - 低频（100Hz-1kHz）：55%阈值，较快响应
 * - 极低频（<100Hz）：70%阈值，保证完整周期
 */
double DataProcessor::calculateDynamicThreshold(double estimatedFreq) const {
    if (estimatedFreq <= 0.0) {
        // 无法估算频率时，使用保守阈值（中等）
        return 0.45;
    }
    
    // 超高频：极速刷新优先
    if (estimatedFreq > 1000000.0) {
        return 0.15;  // 15%即触发（例如500k点只需75k点）
    }
    // 高频：高速刷新
    else if (estimatedFreq > 100000.0) {
        return 0.25;  // 25%触发
    }
    // 中高频：快速刷新
    else if (estimatedFreq > 10000.0) {
        return 0.35;  // 35%触发（降低15%）
    }
    // 中频：快速响应
    else if (estimatedFreq > 1000.0) {
        return 0.45;  // 45%触发（降低25%）⚡
    }
    // 低频：较快响应
    else if (estimatedFreq > 100.0) {
        return 0.55;  // 55%触发（降低35%）⚡⚡
    }
    // 极低频：保证完整周期
    else {
        return 0.70;  // 70%触发（降低18%）
    }
}

/**
 * @brief 快速估算信号频率（用于动态阈值计算）
 * @param voltages 当前累积的电压数据
 * @param times 当前累积的时间数据
 * @return 估算的频率（Hz），0表示无法估算
 * 
 * 轻量级实现：
 * - 只扫描前5000个点（避免全量扫描）
 * - 使用简单的过零检测
 * - 计算前几个周期的平均频率
 */
double DataProcessor::quickFrequencyEstimate(const QVector<double>& voltages, const QVector<double>& times) const {
    const int n = voltages.size();
    if (n < 100 || times.size() != n) {
        return 0.0;
    }

    // 限制扫描范围（最多5000个点，或全部数据）
    const int scanLimit = qMin(5000, n);
    
    // 快速计算最大最小值和阈值
    double vMin = voltages[0];
    double vMax = voltages[0];
    for (int i = 0; i < scanLimit; ++i) {
        if (voltages[i] < vMin) vMin = voltages[i];
        if (voltages[i] > vMax) vMax = voltages[i];
    }
    
    double peakToPeak = vMax - vMin;
    if (peakToPeak < 1e-6) {
        return 0.0;  // 信号幅度太小
    }
    
    double threshold = (vMin + vMax) * 0.5;
    double hysteresis = peakToPeak * 0.02;
    
    // 检测前几个过零点
    QVector<double> crossTimes;
    crossTimes.reserve(20);
    
    bool isAbove = (voltages[0] > threshold);
    
    for (int i = 1; i < scanLimit && crossTimes.size() < 10; ++i) {
        double v_prev = voltages[i-1];
        double v_curr = voltages[i];
        
        // 上升沿过零
        if (!isAbove && v_curr > (threshold + hysteresis)) {
            double t_cross = interpolateZeroCrossTime(v_prev, v_curr, times[i-1], times[i], threshold);
            crossTimes.append(t_cross);
            isAbove = true;
        }
        // 下降沿过零
        else if (isAbove && v_curr < (threshold - hysteresis)) {
            double t_cross = interpolateZeroCrossTime(v_prev, v_curr, times[i-1], times[i], threshold);
            crossTimes.append(t_cross);
            isAbove = false;
        }
    }
    
    // 至少需要4个过零点（2个完整周期）才能估算
    if (crossTimes.size() < 4) {
        return 0.0;
    }
    
    // 计算前几个完整周期的平均周期
    QVector<double> periods;
    for (int i = 0; i < crossTimes.size() - 2; i += 2) {
        double period = crossTimes[i+2] - crossTimes[i];
        if (period > 0.01) {  // 过滤异常值
            periods.append(period);
        }
    }
    
    if (periods.isEmpty()) {
        return 0.0;
    }
    
    // 计算平均周期
    double sumPeriods = 0.0;
    for (double p : periods) {
        sumPeriods += p;
    }
    double avgPeriod = sumPeriods / periods.size();  // 微秒
    
    // 转换为频率（Hz）
    return 1e6 / avgPeriod;
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
    currentBatchSize = 0;
    isNewBatch = true;
    qDebug() << "DataProcessor reset";
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

    // ========== 基于频率自适应的动态分析触发逻辑 ==========
    // 追加到当前批次计数
    currentBatchSize += (times.size() - startIdx);
    
    // 每累积一定数量的点，进行快速频率估算
    double estimatedFreq = 0.0;
    if (currentBatchSize >= 1000 && currentBatchSize % 2000 == 0) {
        estimatedFreq = quickFrequencyEstimate(accumulatedVoltages, accumulatedTimes);
        
        // 调试输出
        if (estimatedFreq > 0.0) {
            qDebug() << "快速频率估算：" << QString::number(estimatedFreq / 1000.0, 'f', 2) << "kHz";
        }
    } else if (lastDetectedFrequency > 0.0) {
        // 使用上次检测到的频率
        estimatedFreq = lastDetectedFrequency;
    }
    
    // 根据估算频率计算动态阈值
    double dynamicThreshold = calculateDynamicThreshold(estimatedFreq);
    
    // 显示累积进度
    double progress = (currentBatchSize * 100.0) / configTotalSamples;
    if (currentBatchSize % 5000 == 0 || currentBatchSize < 1000) {
        QString freqInfo = (estimatedFreq > 0.0) 
            ? QString("估算频率：%1kHz，阈值：%2%").arg(estimatedFreq / 1000.0, 0, 'f', 2).arg(dynamicThreshold * 100.0, 0, 'f', 0)
            : QString("阈值：%1%").arg(dynamicThreshold * 100.0, 0, 'f', 0);
        qDebug() << "累积进度：" << currentBatchSize << "/" << configTotalSamples 
                 << "(" << QString::number(progress, 'f', 1) << "%)"
                 << freqInfo;
    }
    
    // 判断是否达到动态阈值
    bool isBatchComplete = (currentBatchSize >= configTotalSamples * dynamicThreshold);
    
    // 防护：如果累积超过120%，强制触发（防止无限累积）
    bool forceAnalysis = (currentBatchSize >= configTotalSamples * 1.2);
    
    if (isBatchComplete || forceAnalysis) {
        qDebug() << "========================================";
        qDebug() << "批次完成，开始分析：" << currentBatchSize << "个采样点";
        double timeSpan = accumulatedTimes.last() - accumulatedTimes.first();
        qDebug() << "时间跨度：" << QString::number(timeSpan / 1000.0, 'f', 2) << "ms";
        if (estimatedFreq > 0.0) {
            qDebug() << "触发阈值：" << QString::number(dynamicThreshold * 100.0, 'f', 0) << "%（基于" 
                     << QString::number(estimatedFreq / 1000.0, 'f', 2) << "kHz估算）";
        }
        qDebug() << "========================================";
        
        // 执行完整分析
        WaveformAnalysisResult result = performAnalysis(accumulatedVoltages, accumulatedTimes);
        result.isReady = true;
        
        // 保存检测到的频率（用于下次动态阈值计算）
        if (result.frequency > 0.0) {
            lastDetectedFrequency = result.frequency;
        }

        // ========== 保留部分数据以保证波形连续性 ==========
        // 策略：根据频率动态调整保留比例
        // - 高频（>10kHz）：保留20%数据
        // - 中频（1kHz-10kHz）：保留15%数据
        // - 低频（<1kHz）：保留10%数据（加快低频刷新）⚡
        double keepRatio;
        if (estimatedFreq > 10000.0) {
            keepRatio = 0.20;  // 高频：20%
        } else if (estimatedFreq > 1000.0) {
            keepRatio = 0.15;  // 中频：15%
        } else {
            keepRatio = 0.10;  // 低频：10%（减少保留数据）
        }
        
        int keepCount = qMin(static_cast<int>(currentBatchSize * keepRatio), 50000); // 动态保留，最多5万点
        
        if (keepCount > 0 && accumulatedVoltages.size() > keepCount) {
            int startKeep = accumulatedVoltages.size() - keepCount;
            
            // 创建临时缓冲区保存要保留的数据
            QVector<double> keepVoltages;
            QVector<double> keepTimes;
            keepVoltages.reserve(keepCount);
            keepTimes.reserve(keepCount);
            
            for (int i = startKeep; i < accumulatedVoltages.size(); ++i) {
                keepVoltages.append(accumulatedVoltages[i]);
                keepTimes.append(accumulatedTimes[i]);
            }
            
            // 清空原数据
            accumulatedVoltages.clear();
            accumulatedTimes.clear();
            
            // 恢复保留的数据
            accumulatedVoltages = keepVoltages;
            accumulatedTimes = keepTimes;
            currentBatchSize = keepCount;
            
            qDebug() << "保留" << keepCount << "个数据点用于下一批次，保证波形连续性";
        } else {
            // 数据太少，全部清空
            accumulatedVoltages.clear();
            accumulatedTimes.clear();
            currentBatchSize = 0;
        }
        
        isNewBatch = false; // 已经不是新批次了

        // 发射降采样数据信号（供绘图使用）
        if (!result.downsampledVoltages.isEmpty() && !result.downsampledTimes.isEmpty()) {
            emit downsampledDataReady(result.downsampledVoltages, result.downsampledTimes);
        }

        // 发射分析结果信号
        emit analysisReady(result);
        return result;
    }
    
    // 继续累积
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

    // ========== 阶段3：波形类型识别 ==========
    // 识别方波的特征：
    // 1. 信号主要集中在两个电平（高低电平）
    // 2. 跳变速度快（总变化量大）
    // 3. 占空比在合理范围内（10%-90%）
    
    // 计算电平分布（统计接近最大值和最小值的样本数量）
    double levelThreshold = result.peakToPeak * 0.2; // 20%的范围内视为稳定电平
    int nearMaxCount = 0;
    int nearMinCount = 0;
    
    for (int i = 0; i < n; ++i) {
        if (voltages[i] > (vMax - levelThreshold)) {
            nearMaxCount++;
        } else if (voltages[i] < (vMin + levelThreshold)) {
            nearMinCount++;
        }
    }
    
    // 方波特征判断：
    // 1. 大部分样本点集中在高低电平（>60%）
    // 2. 平均变化量大（跳变明显）
    double levelConcentration = (nearMaxCount + nearMinCount) * 100.0 / n;
    double avgVariationPerSample = totalVariation / n;
    bool isSquareWave = (levelConcentration > 60.0) 
                        && (avgVariationPerSample > result.peakToPeak * 0.05);
    
    QString waveType = isSquareWave ? "方波" : "正弦波/其他";
    qDebug() << "[波形识别] 类型：" << waveType 
             << "，电平集中度：" << QString::number(levelConcentration, 'f', 1) << "%"
             << "，平均变化：" << QString::number(avgVariationPerSample, 'f', 4) << "V";
    
    // ========== 阶段4：频率计算（基于波形类型和频率范围）==========
    double timeSpan = times.last() - times.first(); // 微秒
    double effectiveSampleRate = (n - 1) / (timeSpan * 1e-6); // 有效采样率（Hz）
    
    // 方法1：FFT频率检测
    double fftFrequency = calculateFrequencyFFT(voltages, effectiveSampleRate);
    
    // 方法2：过零点检测
    double zeroCrossFrequency = 0.0;
    
    // 决策逻辑：
    // 1. 高频（≥30kHz）：FFT + 过零点综合
    // 2. 低频方波（<30kHz + 方波）：优先过零点检测（避免FFT谐波干扰）
    // 3. 低频非方波（<30kHz + 正弦波等）：只用FFT（避免倍频问题）
    
    if (fftFrequency >= 30000.0) {
        // 高频信号：综合FFT和过零点
        QVector<double> sameDirTimes;
        for (const auto& cross : crosses) {
            if (cross.rising) {  // 只统计上升沿
                sameDirTimes.append(cross.time);
            }
        }
        
        if (sameDirTimes.size() >= 2) {
            // 计算相邻上升沿的周期
            QVector<double> periods;
            for (int i = 0; i < sameDirTimes.size() - 1; ++i) {
                double period = sameDirTimes[i+1] - sameDirTimes[i];
                if (period > 0.01 && period < 10e6) {
                    periods.append(period);
                }
            }
            
            if (!periods.isEmpty()) {
                // 排序并取中位数
                std::sort(periods.begin(), periods.end());
                double median = periods[periods.size() / 2];
                zeroCrossFrequency = 1e6 / median;
            }
        }
        
        // 高频信号：综合FFT和过零点
        if (fftFrequency > 0.0 && zeroCrossFrequency > 0.0) {
            double errorPercent = std::fabs(fftFrequency - zeroCrossFrequency) / ((fftFrequency + zeroCrossFrequency) / 2.0) * 100.0;
            result.frequency = (errorPercent < 5.0) ? fftFrequency : ((fftFrequency + zeroCrossFrequency) / 2.0);
            qDebug() << "[频率≥30kHz] FFT:" << fftFrequency << "Hz, 过零点:" << zeroCrossFrequency << "Hz, 误差:" << errorPercent << "%";
        } else if (fftFrequency > 0.0) {
            result.frequency = fftFrequency;
            qDebug() << "[频率≥30kHz] 使用FFT:" << fftFrequency << "Hz";
        } else if (zeroCrossFrequency > 0.0) {
            result.frequency = zeroCrossFrequency;
            qDebug() << "[频率≥30kHz] 使用过零点:" << zeroCrossFrequency << "Hz";
        } else {
            result.frequency = 0.0;
        }
    } else if (isSquareWave) {
        // 低频方波：优先使用过零点检测（方波FFT受谐波影响）
        QVector<double> sameDirTimes;
        for (const auto& cross : crosses) {
            if (cross.rising) {  // 只统计上升沿
                sameDirTimes.append(cross.time);
            }
        }
        
        if (sameDirTimes.size() >= 2) {
            // 计算相邻上升沿的周期
            QVector<double> periods;
            for (int i = 0; i < sameDirTimes.size() - 1; ++i) {
                double period = sameDirTimes[i+1] - sameDirTimes[i];
                if (period > 0.01 && period < 10e6) {
                    periods.append(period);
                }
            }
            
            if (!periods.isEmpty()) {
                // 排序并取中位数
                std::sort(periods.begin(), periods.end());
                double median = periods[periods.size() / 2];
                zeroCrossFrequency = 1e6 / median;
                
                // 方波优先使用过零点，但如果FFT结果接近则取平均
                if (fftFrequency > 0.0 && zeroCrossFrequency > 0.0) {
                    double errorPercent = std::fabs(fftFrequency - zeroCrossFrequency) / ((fftFrequency + zeroCrossFrequency) / 2.0) * 100.0;
                    result.frequency = (errorPercent < 10.0) ? zeroCrossFrequency : ((fftFrequency + zeroCrossFrequency) / 2.0);
                    qDebug() << "[低频方波] 过零点:" << zeroCrossFrequency << "Hz, FFT:" << fftFrequency << "Hz, 误差:" << errorPercent << "%，使用过零点";
                } else if (zeroCrossFrequency > 0.0) {
                    result.frequency = zeroCrossFrequency;
                    qDebug() << "[低频方波] 使用过零点:" << zeroCrossFrequency << "Hz";
                } else if (fftFrequency > 0.0) {
                    result.frequency = fftFrequency;
                    qDebug() << "[低频方波] 过零点失败，使用FFT:" << fftFrequency << "Hz";
                } else {
                    result.frequency = 0.0;
                }
            } else if (fftFrequency > 0.0) {
                result.frequency = fftFrequency;
                qDebug() << "[低频方波] 过零点周期异常，使用FFT:" << fftFrequency << "Hz";
            } else {
                result.frequency = 0.0;
            }
        } else if (fftFrequency > 0.0) {
            result.frequency = fftFrequency;
            qDebug() << "[低频方波] 过零点不足，使用FFT:" << fftFrequency << "Hz";
        } else {
            result.frequency = 0.0;
        }
    } else {
        // 低频正弦波/其他波形：只使用FFT（避免倍频问题）
        result.frequency = fftFrequency;
        if (fftFrequency > 0.0) {
            qDebug() << "[低频非方波] 仅使用FFT（避免倍频）:" << fftFrequency << "Hz";
        } else {
            qDebug() << "[低频非方波] FFT检测失败";
        }
    }

    // ========== 阶段5：占空比计算（用于显示）==========
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

    // 根据波形类型设置占空比显示
    if (isSquareWave) {
        result.dutyCycle = QString::number(dutyRatio * 100.0, 'f', 1) + "%";
    } else {
        result.dutyCycle = "非方波";
    }

    // ========== 阶段6：简化的数据输出（基于半周期数量）==========
    if (result.frequency > 0.0 && crosses.size() >= 2) {
        // 低频（<1kHz）：输出2个半周期（1个完整周期）
        // 高频（≥1kHz）：输出8个半周期（4个完整周期）
        int targetHalfCycles = (result.frequency < 1000.0) ? 2 : 8;
        
        // 确保不超过实际过零点数量
        int availableHalfCycles = qMin(targetHalfCycles, crosses.size() - 1);
        
        if (availableHalfCycles >= 1) {
            // 找到起始和结束时间
            double startTime = crosses[0].time;
            double endTime = crosses[availableHalfCycles].time;
            
            // 提取该时间范围内的所有数据点
            result.downsampledVoltages.clear();
            result.downsampledTimes.clear();
            
            for (int i = 0; i < n; ++i) {
                if (times[i] >= startTime && times[i] <= endTime) {
                    result.downsampledVoltages.append(voltages[i]);
                    result.downsampledTimes.append(times[i]);
                }
            }
            
            result.downsampleRatio = n / qMax(1, result.downsampledVoltages.size());
            qDebug() << "[数据输出] 输出" << availableHalfCycles << "个半周期，共" 
                     << result.downsampledVoltages.size() << "个数据点";
        } else {
            // 数据不足，输出全部
            result.downsampledVoltages = voltages;
            result.downsampledTimes = times;
            result.downsampleRatio = 1;
        }
    } else {
        // 频率无效，输出全部数据
        result.downsampledVoltages = voltages;
        result.downsampledTimes = times;
        result.downsampleRatio = 1;
    }

    return result;
}

/**
 * @brief 线性插值计算精确过零时间
 */
inline double DataProcessor::interpolateZeroCrossTime(
    double v1, double v2, 
    double t1, double t2, 
    double threshold) const 
{
    double dv = v2 - v1;
    if (std::fabs(dv) < 1e-12) {
        return (t1 + t2) * 0.5;
    }
    double fraction = (threshold - v1) / dv;
    fraction = std::max(0.0, std::min(1.0, fraction));
    return t1 + fraction * (t2 - t1);
}

/**
 * @brief 计算下一个2的幂次方
 * @param n 输入数字
 * @return 大于等于n的最小2的幂次方
 */
int DataProcessor::nextPowerOfTwo(int n) const {
    int power = 1;
    while (power < n) {
        power *= 2;
    }
    return power;
}

/**
 * @brief 应用Hann窗函数
 * @param data 输入/输出数据
 * 
 * Hann窗：w(n) = 0.5 * (1 - cos(2πn/(N-1)))
 * 作用：减少频谱泄漏，提高频率分辨率
 */
void DataProcessor::applyHannWindow(QVector<double>& data) const {
    const int N = data.size();
    if (N < 2) return;
    
    const double PI = 3.14159265358979323846;
    for (int i = 0; i < N; ++i) {
        double window = 0.5 * (1.0 - std::cos(2.0 * PI * i / (N - 1)));
        data[i] *= window;
    }
}

/**
 * @brief Cooley-Tukey FFT算法实现（原位计算）
 * @param real 输入/输出：实部
 * @param imag 输入/输出：虚部
 * @param inverse false=正变换，true=逆变换
 * 
 * 要求：real.size() = imag.size() = 2^n
 * 时间复杂度：O(N log N)
 */
void DataProcessor::fft(QVector<double>& real, QVector<double>& imag, bool inverse) const {
    const int N = real.size();
    if (N <= 1) return;
    
    // 检查是否为2的幂次方
    if ((N & (N - 1)) != 0) {
        qWarning() << "FFT: 数据大小必须是2的幂次方，当前大小：" << N;
        return;
    }
    
    // 位反转排序（Bit-reversal permutation）
    int j = 0;
    for (int i = 0; i < N - 1; ++i) {
        if (i < j) {
            std::swap(real[i], real[j]);
            std::swap(imag[i], imag[j]);
        }
        int k = N / 2;
        while (k <= j) {
            j -= k;
            k /= 2;
        }
        j += k;
    }
    
    // Cooley-Tukey FFT主算法
    const double PI = 3.14159265358979323846;
    const double direction = inverse ? 1.0 : -1.0;
    
    for (int len = 2; len <= N; len *= 2) {
        double angle = direction * 2.0 * PI / len;
        double wlen_real = std::cos(angle);
        double wlen_imag = std::sin(angle);
        
        for (int i = 0; i < N; i += len) {
            double w_real = 1.0;
            double w_imag = 0.0;
            
            for (int j = 0; j < len / 2; ++j) {
                int idx1 = i + j;
                int idx2 = i + j + len / 2;
                
                double t_real = w_real * real[idx2] - w_imag * imag[idx2];
                double t_imag = w_real * imag[idx2] + w_imag * real[idx2];
                
                real[idx2] = real[idx1] - t_real;
                imag[idx2] = imag[idx1] - t_imag;
                real[idx1] = real[idx1] + t_real;
                imag[idx1] = imag[idx1] + t_imag;
                
                // 更新旋转因子
                double w_temp = w_real;
                w_real = w_real * wlen_real - w_imag * wlen_imag;
                w_imag = w_temp * wlen_imag + w_imag * wlen_real;
            }
        }
    }
    
    // 逆变换需要归一化
    if (inverse) {
        for (int i = 0; i < N; ++i) {
            real[i] /= N;
            imag[i] /= N;
        }
    }
}

/**
 * @brief 基于FFT的频率检测（更准确，抗噪声能力强）
 * @param voltages 电压数据
 * @param sampleRate 采样率（Hz）
 * @return 检测到的主频率（Hz），0表示检测失败
 * 
 * 算法流程：
 * 1. 数据预处理：去除直流分量
 * 2. 应用Hann窗函数减少频谱泄漏
 * 3. 填充到2的幂次方大小
 * 4. 执行FFT
 * 5. 计算功率谱
 * 6. 找出峰值频率（使用抛物线插值提高精度）
 */
double DataProcessor::calculateFrequencyFFT(const QVector<double>& voltages, double sampleRate) const {
    const int N = voltages.size();
    
    // 最少需要32个采样点
    if (N < 32 || sampleRate <= 0.0) {
        return 0.0;
    }
    
    // 限制FFT大小（避免内存占用过大）
    // 对于50MHz采样率，使用最多65536点已足够
    const int MAX_FFT_SIZE = 65536;
    int fftSize = nextPowerOfTwo(qMin(N, MAX_FFT_SIZE));
    
    // 准备FFT输入数据
    QVector<double> real(fftSize, 0.0);
    QVector<double> imag(fftSize, 0.0);
    
    // 步骤1：去除直流分量（计算均值）
    double mean = 0.0;
    int usedSamples = qMin(N, fftSize);
    for (int i = 0; i < usedSamples; ++i) {
        mean += voltages[i];
    }
    mean /= usedSamples;
    
    // 复制数据并去除直流分量
    for (int i = 0; i < usedSamples; ++i) {
        real[i] = voltages[i] - mean;
    }
    
    // 步骤2：应用Hann窗函数
    applyHannWindow(real);
    
    // 步骤3：执行FFT
    fft(real, imag, false);
    
    // 步骤4：计算功率谱（只需要前半部分，因为后半部分是镜像）
    QVector<double> powerSpectrum(fftSize / 2);
    for (int i = 0; i < fftSize / 2; ++i) {
        powerSpectrum[i] = real[i] * real[i] + imag[i] * imag[i];
    }
    
    // 步骤5：找出最大功率的频率分量（跳过DC分量，从索引1开始）
    int maxIdx = 1;
    double maxPower = powerSpectrum[1];
    
    for (int i = 2; i < powerSpectrum.size(); ++i) {
        if (powerSpectrum[i] > maxPower) {
            maxPower = powerSpectrum[i];
            maxIdx = i;
        }
    }
    
    // 防护：功率太小可能是噪声
    if (maxPower < 1e-10) {
        qDebug() << "[FFT] 信号功率太小，可能是噪声";
        return 0.0;
    }
    
    // 步骤6：使用抛物线插值提高频率精度
    // 三点抛物线插值公式：delta = 0.5 * (left - right) / (left - 2*center + right)
    double peakFrequency = 0.0;
    
    if (maxIdx > 0 && maxIdx < powerSpectrum.size() - 1) {
        double left = powerSpectrum[maxIdx - 1];
        double center = powerSpectrum[maxIdx];
        double right = powerSpectrum[maxIdx + 1];
        
        // 抛物线插值修正
        double delta = 0.5 * (left - right) / (left - 2.0 * center + right);
        double refinedIdx = maxIdx + delta;
        
        // 计算频率（频率分辨率 = sampleRate / fftSize）
        peakFrequency = (refinedIdx * sampleRate) / fftSize;
    } else {
        // 边界情况，直接使用索引
        peakFrequency = (maxIdx * sampleRate) / fftSize;
    }
    
    // 频率验证：不应超过奈奎斯特频率
    double nyquistFreq = sampleRate / 2.0;
    if (peakFrequency > nyquistFreq) {
        qDebug() << "[FFT] 检测到的频率超过奈奎斯特频率，可能是混叠";
        return 0.0;
    }
    
    qDebug() << "[FFT] 检测到主频率：" << QString::number(peakFrequency, 'f', 2) << "Hz"
             << "（FFT点数：" << fftSize << "，频率分辨率：" 
             << QString::number(sampleRate / fftSize, 'f', 2) << "Hz）";
    
    return peakFrequency;
}
