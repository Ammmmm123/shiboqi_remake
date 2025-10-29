#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <QObject>
#include <QVector>
#include <QByteArray>

/**
 * @brief 波形分析结果结构体
 * 
 * 存储波形数据分析后的各种特征参数
 */
struct WaveformAnalysisResult
{
    double frequency;      ///< 频率 (Hz)
    double amplitude;      ///< 幅度 (V)
    double peakToPeak;     ///< 峰峰值 (V)
    double maxValue;       ///< 最大值 (V)
    double minValue;       ///< 最小值 (V)
    double rmsValue;       ///< 有效值 (V)
    double dutyCycle;      ///< 占空比 (%)
    
    WaveformAnalysisResult()
        : frequency(0.0)
        , amplitude(0.0)
        , peakToPeak(0.0)
        , maxValue(0.0)
        , minValue(0.0)
        , rmsValue(0.0)
        , dutyCycle(0.0)
    {}
};

/**
 * @brief 数据处理器类
 * 
 * 负责波形数据的处理、分析和降采样
 * 运行在独立线程中，避免阻塞GUI
 */
class DataProcessor : public QObject
{
    Q_OBJECT
    
public:
    explicit DataProcessor(QObject *parent = nullptr);
    ~DataProcessor();
    
public slots:
    /**
     * @brief 设置采样配置
     * @param dataNum 数据个数
     * @param sampleRate 采样率
     */
    void setSamplingConfig(quint32 dataNum, double sampleRate);
    
    /**
     * @brief 重置数据处理器
     */
    void reset();
    
    /**
     * @brief 处理接收到的波形数据
     * @param voltages 电压数据
     * @param times 时间戳数据（微秒）
     */
    void processWaveformData(const QVector<double> &voltages, const QVector<double> &times);
    
signals:
    /**
     * @brief 分析结果就绪信号
     * @param result 波形分析结果
     */
    void analysisReady(const WaveformAnalysisResult &result);
    
    /**
     * @brief 降采样数据就绪信号（用于绘图）
     * @param voltages 降采样后的电压数据
     * @param times 降采样后的时间戳（微秒）
     */
    void downsampledDataReady(const QVector<double> &voltages, const QVector<double> &times);
    
private:
    quint32 dataNum;        ///< 采样数据个数
    double sampleRate;      ///< 实际采样率 (Hz)
};

#endif // DATA_PROCESSOR_H
