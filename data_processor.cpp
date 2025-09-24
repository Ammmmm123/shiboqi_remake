#include "data_processor.h"
#include <QVector>
#include <QString>
#include <cmath>
#include <algorithm>

/**
 * @brief 分析波形数据（累积模式）
 * @param voltages 电压值向量
 * @param times 时间向量 (单位: 微秒)
 * @return 波形分析结果，如果未累积足够数据，isReady为false
 */
WaveformAnalysisResult DataProcessor::analyzeWaveform(const QVector<double>& voltages, const QVector<double>& times) {
    // 累积数据
    accumulatedVoltages += voltages;
    accumulatedTimes += times;
    callCount++;

    if (callCount >= 10) {
        // 执行分析
        WaveformAnalysisResult result = performAnalysis(accumulatedVoltages, accumulatedTimes);
        result.isReady = true;

        // 清空累积数据
        accumulatedVoltages.clear();
        accumulatedTimes.clear();
        callCount = 0;

        return result;
    } else {
        // 未准备好，返回空结果
        WaveformAnalysisResult result;
        result.isReady = false;
        return result;
    }
}

/**
 * @brief 执行实际的波形分析
 * @param voltages 电压值向量
 * @param times 时间向量
 * @return 分析结果
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

    if (voltages.isEmpty() || times.isEmpty() || voltages.size() != times.size()) {
        return result;
    }

    // 计算最大值和最小值
    for (double v : voltages) {
        if (v > result.maxValue) result.maxValue = v;
        if (v < result.minValue) result.minValue = v;
    }

    result.peakToPeak = result.maxValue - result.minValue;
    result.amplitude = result.peakToPeak / 2.0;

    // 计算频率：使用零交叉检测
    double threshold = (result.maxValue + result.minValue) / 2.0;
    QVector<double> zeroCrossTimes;
    int n = voltages.size();
    for (int i = 1; i < n; ++i) {
        if ((voltages[i-1] - threshold) * (voltages[i] - threshold) < 0) {
            // 线性插值找到交叉时间
            double t1 = times[i-1];
            double t2 = times[i];
            double v1 = voltages[i-1] - threshold;
            double v2 = voltages[i] - threshold;
            double fraction = v1 / (v1 - v2);
            double crossTime = t1 + fraction * (t2 - t1);
            zeroCrossTimes.append(crossTime);
        }
    }

    if (zeroCrossTimes.size() >= 2) {
        double totalPeriod = 0.0;
        for (int i = 1; i < zeroCrossTimes.size(); ++i) {
            totalPeriod += zeroCrossTimes[i] - zeroCrossTimes[i-1];
        }
        double avgPeriod = totalPeriod / (zeroCrossTimes.size() - 1);
        result.frequency = 1e6 / avgPeriod; // times in us, frequency in Hz
    }

    // 检测占空比：计算高于阈值的时间比例
    double highTime = 0.0;
    double totalTime = times.last() - times.first();
    for (int i = 1; i < n; ++i) {
        double dt = times[i] - times[i-1];
        double avgV = (voltages[i-1] + voltages[i]) / 2.0;
        if (avgV > threshold) {
            highTime += dt;
        }
    }
    double dutyRatio = highTime / totalTime;

    // 判断是否为方波：如果占空比在10%-90%之间，且电压变化明显
    if (dutyRatio > 0.1 && dutyRatio < 0.9 && result.peakToPeak > 0.1) { // 阈值可调
        result.dutyCycle = QString::number(dutyRatio * 100, 'f', 1) + "%";
    } else {
        result.dutyCycle = "非方波";
    }

    return result;
}