#include "spectrum_analyzer.h"
#include <QDebug>
#include <cmath>
#include <algorithm>

// 定义数学常量 M_PI（MinGW可能未定义）
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief 构造函数实现
 */
SpectrumAnalyzer::SpectrumAnalyzer(QObject *parent)
    : QObject(parent)
    , analysisCount(0)
    , updateInterval(2) // 每2次分析才更新一次结果
{
}

/**
 * @brief 析构函数实现
 */
SpectrumAnalyzer::~SpectrumAnalyzer()
{
}

/**
 * @brief 重置累积的数据
 */
void SpectrumAnalyzer::reset()
{
    analysisCount = 0;
    recentResults.clear();
}

/**
 * @brief 接收电压数据并直接分析
 */
void SpectrumAnalyzer::onDataReceived(const QVector<double> &voltages, const QVector<double> &times)
{
    // 直接使用接收到的数据进行分析，不累积
    if (voltages.isEmpty() || times.isEmpty()) {
        return;
    }
    
    // 临时存储当前数据用于分析
    accumulatedVoltages = voltages;
    accumulatedTimes = times;
    
    // 直接进行FFT分析
    performFFT();
    
    // 分析完成后清空临时数据
    accumulatedVoltages.clear();
    accumulatedTimes.clear();
}

/**
 * @brief 计算下一个2的幂次
 */
int SpectrumAnalyzer::nextPowerOf2(int n)
{
    int power = 1;
    while (power < n) {
        power *= 2;
    }
    return power;
}

/**
 * @brief FFT实现（Cooley-Tukey算法）
 */
void SpectrumAnalyzer::fft(QVector<std::complex<double>> &data)
{
    int n = data.size();
    if (n <= 1) return;

    // 分治递归
    QVector<std::complex<double>> even, odd;
    for (int i = 0; i < n; i += 2) even.append(data[i]);
    for (int i = 1; i < n; i += 2) odd.append(data[i]);

    fft(even);
    fft(odd);

    // 合并
    for (int k = 0; k < n / 2; ++k) {
        std::complex<double> t = std::polar(1.0, -2.0 * M_PI * k / n) * odd[k];
        data[k] = even[k] + t;
        data[k + n / 2] = even[k] - t;
    }
}

/**
 * @brief 执行FFT频谱分析
 */
void SpectrumAnalyzer::performFFT()
{
    if (accumulatedVoltages.isEmpty() || accumulatedTimes.isEmpty()) {
        return;
    }

    // ========== 关键修复：从时间戳计算实际采样率 ==========
    // 参考 frequency_detector.cpp 的实现
    double totalTime = accumulatedTimes.last() - accumulatedTimes.first(); // 微秒
    double avgSampleInterval = totalTime / (accumulatedVoltages.size() - 1); // 微秒
    double actualSampleRate = 1000000.0 / avgSampleInterval; // Hz（1秒 = 1,000,000微秒）
    
    // 准备FFT输入（扩展到2的幂次）
    int n = nextPowerOf2(accumulatedVoltages.size());
    QVector<std::complex<double>> fftInput(n);

    // 去除直流分量（提高检测精度）
    double mean = 0.0;
    for (int i = 0; i < accumulatedVoltages.size(); ++i) {
        mean += accumulatedVoltages[i];
    }
    mean /= accumulatedVoltages.size();

    // 复制实际数据并去除直流分量
    for (int i = 0; i < accumulatedVoltages.size(); ++i) {
        fftInput[i] = std::complex<double>(accumulatedVoltages[i] - mean, 0.0);
    }
    // 零填充
    for (int i = accumulatedVoltages.size(); i < n; ++i) {
        fftInput[i] = std::complex<double>(0.0, 0.0);
    }

    // 应用汉宁窗减少频谱泄漏
    double windowCorrection = 0.0;
    for (int i = 0; i < n; ++i) {
        double window = 0.5 * (1.0 - std::cos(2.0 * M_PI * i / (n - 1)));
        fftInput[i] *= window;
        windowCorrection += window;
    }
    windowCorrection /= n;

    // 执行FFT
    fft(fftInput);

    // 计算幅度谱（只取前半部分，因为是实信号）
    int halfN = n / 2;
    QVector<double> frequencies(halfN);
    QVector<double> amplitudes(halfN);

    // ========== 关键修复：使用实际采样率计算频率分辨率 ==========
    // 频率分辨率 = 实际采样率 / FFT点数
    double freqResolution = actualSampleRate / n;
    
    for (int i = 0; i < halfN; ++i) {
        frequencies[i] = i * freqResolution;
        // 幅度 = |FFT[i]| * 2 / N，并补偿汉宁窗衰减
        amplitudes[i] = std::abs(fftInput[i]) * 2.0 / (accumulatedVoltages.size() * windowCorrection);
    }

    // 找出主频率和次频率（忽略DC分量，从索引1开始）
    int maxIndex = 1;
    double maxAmplitude = amplitudes[1];
    int secondMaxIndex = 1;
    double secondMaxAmplitude = 0.0;
    
    for (int i = 2; i < halfN; ++i) {
        if (amplitudes[i] > maxAmplitude) {
            // 当前峰值成为新的主频率
            secondMaxIndex = maxIndex;
            secondMaxAmplitude = maxAmplitude;
            maxIndex = i;
            maxAmplitude = amplitudes[i];
        } else if (amplitudes[i] > secondMaxAmplitude) {
            // 当前峰值成为次频率
            secondMaxIndex = i;
            secondMaxAmplitude = amplitudes[i];
        }
    }

    // 构造结果
    SpectrumAnalysisResult result;
    result.dominantFrequency = frequencies[maxIndex];
    result.dominantAmplitude = maxAmplitude;
    result.secondFrequency = frequencies[secondMaxIndex];
    result.secondAmplitude = secondMaxAmplitude;
    result.frequencies = frequencies;
    result.amplitudes = amplitudes;

    // 累积最近的结果用于平滑
    recentResults.append(result);
    analysisCount++;
    
    // 降低刷新率：每N次分析才发射一次信号
    if (analysisCount % updateInterval == 0) {
        // 发射最新的频谱结果
        emit spectrumReady(result);
        
        // 清空最近结果，准备下一轮统计
        recentResults.clear();
    }
}
