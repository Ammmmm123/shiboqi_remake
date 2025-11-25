#ifndef TRIGGER_PROCESSOR_H
#define TRIGGER_PROCESSOR_H

#include <QObject>
#include <QVector>

/**
 * @brief 触发处理器类
 * 
 * 负责对波形数据进行触发采样处理
 * 根据触发条件（电平、边沿、模式）对数据进行筛选和截取
 * 运行在独立线程中，避免阻塞主线程
 */
class TriggerProcessor : public QObject
{
    Q_OBJECT
    
public:
    explicit TriggerProcessor(QObject *parent = nullptr);
    ~TriggerProcessor();
    
public slots:
    /**
     * @brief 设置触发器使能状态
     * @param enabled true: 启用触发器, false: 禁用触发器
     */
    void setTriggerEnabled(bool enabled);
    
    /**
     * @brief 设置触发模式
     * @param mode 0: Auto（自动模式，总是显示波形）, 1: Normal（正常模式，只在触发时显示）
     */
    void setTriggerMode(int mode);
    
    /**
     * @brief 设置触发边沿
     * @param rising true: 上升沿触发, false: 下降沿触发
     */
    void setTriggerEdge(bool rising);
    
    /**
     * @brief 设置触发电平
     * @param level 触发电平值（单位：V）
     */
    void setTriggerLevel(double level);
    
    /**
     * @brief 处理接收到的波形数据
     * @param voltages 电压数据（单位：V）
     * @param times 时间戳数据（单位：微秒）
     * 
     * 根据当前触发设置处理数据：
     * - 如果触发器未启用，直接转发原始数据
     * - 如果触发器启用且为Auto模式，总是输出数据（找到触发点则对齐，否则输出原始数据）
     * - 如果触发器启用且为Normal模式，只有找到触发点才输出数据
     */
    void processWaveformData(const QVector<double> &voltages, const QVector<double> &times);
    
signals:
    /**
     * @brief 触发处理后的数据就绪信号
     * @param voltages 处理后的电压数据
     * @param times 处理后的时间戳数据
     * 
     * 发送给主窗口用于显示
     */
    void triggeredDataReady(const QVector<double> &voltages, const QVector<double> &times);
    
private:
    /**
     * @brief 在波形数据中查找触发点
     * @param voltages 电压数据
     * @return 触发点的索引，如果未找到返回-1
     */
    int findTriggerPoint(const QVector<double> &voltages);
    
    /**
     * @brief 截取以触发点为中心的波形数据
     * @param voltages 原始电压数据
     * @param times 原始时间戳数据
     * @param triggerIndex 触发点索引
     * @param outVoltages 输出的电压数据
     * @param outTimes 输出的时间戳数据
     */
    void extractTriggeredWaveform(
        const QVector<double> &voltages,
        const QVector<double> &times,
        int triggerIndex,
        QVector<double> &outVoltages,
        QVector<double> &outTimes
    );
    
private:
    bool triggerEnabled;      ///< 触发器是否启用
    int triggerMode;          ///< 触发模式 (0: Auto, 1: Normal)
    bool triggerEdge;         ///< 触发边沿 (true: 上升沿, false: 下降沿)
    double triggerLevel;      ///< 触发电平 (V)
    
    int expectedDataCount;    ///< 期望输出的数据点数（用于截取波形）
    
    // 触发保持相关
    qint64 lastTriggerTime;   ///< 上次触发的时间戳（微秒）
    qint64 holdoffTime;       ///< 触发保持时间（微秒），在此时间内不响应新触发
    bool isInHoldoff;         ///< 是否在保持期内
    
    // 数据缓冲
    QVector<double> dataBuffer;      ///< 数据缓冲区
    QVector<double> timeBuffer;      ///< 时间缓冲区
};

#endif // TRIGGER_PROCESSOR_H
