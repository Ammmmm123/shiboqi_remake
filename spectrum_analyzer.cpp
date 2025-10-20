#include "spectrum_analyzer.h"
#include <QDebug>
#include <cmath>
#include <algorithm>

/**
 * @brief 构造函数实现
 */
SpectrumAnalyzer::SpectrumAnalyzer(QObject *parent)
    : QObject(parent)
    , targetCount(1024)
    , sampleRate(50000000.0) // 默认50MHz采样率
{
}

/**
 * @brief 析构函数实现
 */
SpectrumAnalyzer::~SpectrumAnalyzer()
{
}

/**
 * @brief 设置目标数据点数量
 */
void SpectrumAnalyzer::setTargetDataCount(quint32 count)
{
    targetCount = count;
    qDebug() << "频谱分析器：目标数据点设置为" << targetCount;
}

/**
 * @brief 设置采样率
 */
void SpectrumAnalyzer::setSampleRate(double rate)
{
    sampleRate = rate;
    qDebug() << "频谱分析器：采样率设置为" << sampleRate << "Hz";
}

/**
 * @brief 重置累积的数据
 */
void SpectrumAnalyzer::reset()
{
    accumulatedVoltages.clear();
    accumulatedTimes.clear();
    qDebug() << "频谱分析器：数据已重置";
}

/**
 * @brief 接收电压数据并累积
 */
void SpectrumAnalyzer::onDataReceived(const QVector<double> &voltages, const QVector<double> &times)
{
    // 追加新数据
    accumulatedVoltages.append(voltages);
    accumulatedTimes.append(times);

    qDebug() << "频谱分析器：已累积" << accumulatedVoltages.size() << "/" << targetCount << "个数据点";

    // 检查是否达到目标数量
    if (accumulatedVoltages.size() >= static_cast<int>(targetCount)) {
        qDebug() << "频谱分析器：数据已满，开始FFT分析...";
        performFFT();
        // 分析完成后清空，准备下一轮
        reset();
    }
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
    if (accumulatedVoltages.isEmpty()) {
        qDebug() << "频谱分析器：无数据可分析";
        return;
    }

    // 准备FFT输入（扩展到2的幂次）
    int n = nextPowerOf2(accumulatedVoltages.size());
    QVector<std::complex<double>> fftInput(n);

    // 复制实际数据并去除直流分量
    double mean = 0.0;
    for (int i = 0; i < accumulatedVoltages.size(); ++i) {
        mean += accumulatedVoltages[i];
    }
    mean /= accumulatedVoltages.size();

    for (int i = 0; i < accumulatedVoltages.size(); ++i) {
        fftInput[i] = std::complex<double>(accumulatedVoltages[i] - mean, 0.0);
    }
    // 零填充
    for (int i = accumulatedVoltages.size(); i < n; ++i) {
        fftInput[i] = std::complex<double>(0.0, 0.0);
    }

    // 应用汉宁窗减少频谱泄漏
    for (int i = 0; i < n; ++i) {
        double window = 0.5 * (1.0 - std::cos(2.0 * M_PI * i / (n - 1)));
        fftInput[i] *= window;
    }

    // 执行FFT
    fft(fftInput);

    // 计算幅度谱（只取前半部分，因为是实信号）
    int halfN = n / 2;
    QVector<double> frequencies(halfN);
    QVector<double> amplitudes(halfN);

    double freqResolution = sampleRate / n;

    for (int i = 0; i < halfN; ++i) {
        frequencies[i] = i * freqResolution;
        // 幅度 = |FFT[i]| * 2 / N （双边谱转单边谱）
        amplitudes[i] = std::abs(fftInput[i]) * 2.0 / accumulatedVoltages.size();
    }

    // 找出主频率（忽略DC分量，从索引1开始）
    int maxIndex = 1;
    double maxAmplitude = amplitudes[1];
    for (int i = 2; i < halfN; ++i) {
        if (amplitudes[i] > maxAmplitude) {
            maxAmplitude = amplitudes[i];
            maxIndex = i;
        }
    }

    // 构造结果
    SpectrumAnalysisResult result;
    result.dominantFrequency = frequencies[maxIndex];
    result.dominantAmplitude = maxAmplitude;
    result.frequencies = frequencies;
    result.amplitudes = amplitudes;

    qDebug() << "频谱分析完成：主频率 =" << result.dominantFrequency << "Hz, 幅度 =" << result.dominantAmplitude << "V";

    // 发射结果信号
    emit spectrumReady(result);
}
