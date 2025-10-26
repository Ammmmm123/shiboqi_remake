#ifndef SPECTRUM_ANALYZER_H
#define SPECTRUM_ANALYZER_H

#include <QObject>
#include <QVector>
#include <complex>

/**
 * @brief 频谱分析结果结构体
 */
struct SpectrumAnalysisResult {
    double dominantFrequency;    ///< 主频率（Hz）
    double dominantAmplitude;    ///< 主频率对应的幅度（V）
    double totalPower;           ///< 总功率（V²）
    double snr;                  ///< 信噪比（dB）
    double thd;                  ///< 总谐波失真（%）
    double bandwidth;            ///< -3dB带宽（Hz）
    int harmonicCount;           ///< 检测到的谐波数量
    QVector<double> harmonicFreqs;  ///< 谐波频率列表
    QVector<double> harmonicAmps;   ///< 谐波幅度列表
    QVector<double> frequencies; ///< 频率轴数据（Hz）
    QVector<double> amplitudes;  ///< 幅度谱数据（V）
};

/**
 * @brief 频谱分析器类
 * 
 * 累积UDP接收的电压数据，达到指定数量后进行FFT频谱分析
 */
class SpectrumAnalyzer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit SpectrumAnalyzer(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~SpectrumAnalyzer();

    /**
     * @brief 设置目标数据点数量
     * @param count 需要累积的数据点数量
     */
    void setTargetDataCount(quint32 count);

    /**
     * @brief 设置采样率
     * @param rate 采样率（Hz）
     */
    void setSampleRate(double rate);

    /**
     * @brief 重置累积的数据
     */
    void reset();

signals:
    /**
     * @brief 频谱分析完成信号
     * @param result 频谱分析结果
     */
    void spectrumReady(const SpectrumAnalysisResult &result);

public slots:
    /**
     * @brief 接收电压数据并累积
     * @param voltages 电压数据
     * @param times 时间戳（微秒）
     */
    void onDataReceived(const QVector<double> &voltages, const QVector<double> &times);

private:
    /**
     * @brief 执行FFT频谱分析
     */
    void performFFT();

    /**
     * @brief FFT实现（Cooley-Tukey算法）
     * @param data 复数数据（输入/输出）
     */
    void fft(QVector<std::complex<double>> &data);

    /**
     * @brief 计算下一个2的幂次
     * @param n 输入值
     * @return 不小于n的最小2的幂次
     */
    int nextPowerOf2(int n);

    quint32 targetCount;           ///< 目标数据点数量
    double sampleRate;             ///< 采样率（Hz）
    QVector<double> accumulatedVoltages; ///< 累积的电压数据
    QVector<double> accumulatedTimes;    ///< 累积的时间戳数据
};

#endif // SPECTRUM_ANALYZER_H
