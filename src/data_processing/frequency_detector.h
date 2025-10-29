#ifndef FREQUENCY_DETECTOR_H
#define FREQUENCY_DETECTOR_H

#include <QVector>

/**
 * @brief 频率检测器类
 * 
 * 负责从波形数据中检测频率
 * 支持多种检测算法（过零检测、自相关、FFT等）
 */
class FrequencyDetector
{
public:
    FrequencyDetector();
    ~FrequencyDetector();
    
    /**
     * @brief 使用过零检测法检测频率
     * @param voltages 电压数据
     * @param samplingRate 采样率 (Hz)
     * @return 检测到的频率 (Hz)
     */
    double detectByZeroCrossing(const QVector<double> &voltages, double samplingRate);
    
    /**
     * @brief 使用自相关法检测频率
     * @param voltages 电压数据
     * @param samplingRate 采样率 (Hz)
     * @return 检测到的频率 (Hz)
     */
    double detectByAutocorrelation(const QVector<double> &voltages, double samplingRate);
    
    /**
     * @brief 使用FFT法检测频率（基频）
     * @param voltages 电压数据
     * @param samplingRate 采样率 (Hz)
     * @return 检测到的频率 (Hz)
     */
    double detectByFFT(const QVector<double> &voltages, double samplingRate);
    
    /**
     * @brief 综合检测频率（自动选择最佳算法）
     * @param voltages 电压数据
     * @param samplingRate 采样率 (Hz)
     * @return 检测到的频率 (Hz)
     */
    double detectFrequency(const QVector<double> &voltages, double samplingRate);
    
private:
    // TODO: 添加私有成员变量和辅助函数
};

#endif // FREQUENCY_DETECTOR_H
