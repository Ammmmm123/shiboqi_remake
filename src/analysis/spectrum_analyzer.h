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
    double secondFrequency;      ///< 次频率（Hz）
    double secondAmplitude;      ///< 次频率对应的幅度（V）
    QVector<double> frequencies; ///< 频率轴数据（Hz）
    QVector<double> amplitudes;  ///< 幅度谱数据（V）
};

/**
 * @brief 频谱分析器类
 * 
 * 每次接收到电压数据后直接进行FFT频谱分析
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

signals:
    /**
     * @brief 频谱分析完成信号
     * @param result 频谱分析结果
     */
    void spectrumReady(const SpectrumAnalysisResult &result);

public slots:
    /**
     * @brief 重置累积的数据（线程安全）
     */
    void reset();

    /**
     * @brief 接收电压数据并直接分析
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

    QVector<double> accumulatedVoltages; ///< 临时存储的电压数据
    QVector<double> accumulatedTimes;    ///< 临时存储的时间戳数据
    
    // 统计平滑相关
    int analysisCount;             ///< 已完成的分析次数
    int updateInterval;            ///< 更新间隔（每N次分析才发射一次结果）
    QVector<SpectrumAnalysisResult> recentResults; ///< 最近几次的分析结果
};

#endif // SPECTRUM_ANALYZER_H
