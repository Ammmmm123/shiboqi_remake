#include "trigger_processor.h"
#include <QDebug>
#include <algorithm>

/**
 * @brief 构造函数
 */
TriggerProcessor::TriggerProcessor(QObject *parent)
    : QObject(parent)
    , triggerEnabled(false)
    , triggerMode(0)  // Auto
    , triggerEdge(true)  // 上升沿
    , triggerLevel(0.0)
    , expectedDataCount(1500)  // 默认1500个点
    , lastTriggerTime(0)
    , holdoffTime(50000)  // 50ms保持时间，防止同一周期重复触发
    , isInHoldoff(false)
{
}

/**
 * @brief 析构函数
 */
TriggerProcessor::~TriggerProcessor()
{
}

/**
 * @brief 设置触发器使能状态
 */
void TriggerProcessor::setTriggerEnabled(bool enabled)
{
    triggerEnabled = enabled;

}

/**
 * @brief 设置触发模式
 */
void TriggerProcessor::setTriggerMode(int mode)
{
    triggerMode = mode;
    QString modeStr = (mode == 0) ? "Auto" : "Normal";
    
    // 模式改变时清空缓冲区，立即响应新模式
    dataBuffer.clear();
    timeBuffer.clear();
    isInHoldoff = false;
}

/**
 * @brief 设置触发边沿
 */
void TriggerProcessor::setTriggerEdge(bool rising)
{
    triggerEdge = rising;
    QString edgeStr = rising ? "上升沿" : "下降沿";
    
    // 边沿改变时清空缓冲区，立即响应新边沿
    dataBuffer.clear();
    timeBuffer.clear();
    isInHoldoff = false;
}

/**
 * @brief 设置触发电平
 */
void TriggerProcessor::setTriggerLevel(double level)
{
    triggerLevel = level;
    
    // 电平改变时清空缓冲区，立即响应新电平
    dataBuffer.clear();
    timeBuffer.clear();
    isInHoldoff = false;
}

/**
 * @brief 处理接收到的波形数据
 */
void TriggerProcessor::processWaveformData(const QVector<double> &voltages, const QVector<double> &times)
{
    // 检查数据有效性
    if (voltages.isEmpty() || times.isEmpty() || voltages.size() != times.size()) {
        return;
    }
    
    // 如果触发器未启用，直接转发原始数据
    if (!triggerEnabled) {
        emit triggeredDataReady(voltages, times);
        return;
    }
    
    // ========== 触发器已启用，开始处理 ==========
    
    // 将新数据追加到缓冲区
    dataBuffer.append(voltages);
    timeBuffer.append(times);
    
    // 限制缓冲区大小，避免内存无限增长（保留最近3倍的期望数据量）
    int maxBufferSize = expectedDataCount * 2;
    if (dataBuffer.size() > maxBufferSize) {
        int removeCount = dataBuffer.size() - maxBufferSize;
        dataBuffer.remove(0, removeCount);
        timeBuffer.remove(0, removeCount);
    }
    
    // 检查是否还在触发保持期内
    if (isInHoldoff && !timeBuffer.isEmpty()) {
        qint64 currentTime = timeBuffer.last();
        if (currentTime - lastTriggerTime >= holdoffTime) {
            isInHoldoff = false;  // 保持期结束
        } else {
            // 还在保持期内，不处理触发
            return;
        }
    }
    
    // 查找触发点
    int triggerIndex = findTriggerPoint(dataBuffer);
    
    if (triggerIndex != -1) {
        // 找到触发点
        
        // 检查是否有足够的数据来截取完整波形
        // 需要触发点后有足够的数据（至少3/4的期望数据量）
        int requiredPointsAfterTrigger = expectedDataCount * 3 / 4;
        int availablePointsAfterTrigger = dataBuffer.size() - triggerIndex;
        
        if (availablePointsAfterTrigger >= requiredPointsAfterTrigger) {
            // 有足够数据，可以触发
            QVector<double> outVoltages;
            QVector<double> outTimes;
            extractTriggeredWaveform(dataBuffer, timeBuffer, triggerIndex, outVoltages, outTimes);
            
            // 发送触发后的数据
            emit triggeredDataReady(outVoltages, outTimes);
            
            // 记录触发时间，进入保持期
            if (!timeBuffer.isEmpty()) {
                lastTriggerTime = timeBuffer[triggerIndex];
                isInHoldoff = true;
            }
            
            // 清空缓冲区，准备接收新数据
            dataBuffer.clear();
            timeBuffer.clear();
        }
        // 如果数据不够，继续积累
        
    } else {
        // 未找到触发点
        if (triggerMode == 0) {
            // Auto模式：如果缓冲区数据足够多但还没找到触发点，强制触发
            if (dataBuffer.size() >= expectedDataCount * 2) {
                // 强制输出最新的数据
                QVector<double> outVoltages;
                QVector<double> outTimes;
                
                int startIdx = dataBuffer.size() - expectedDataCount;
                if (startIdx < 0) startIdx = 0;
                
                for (int i = startIdx; i < dataBuffer.size(); ++i) {
                    outVoltages.append(dataBuffer[i]);
                    outTimes.append(timeBuffer[i]);
                }
                
                emit triggeredDataReady(outVoltages, outTimes);
                
                // 清空部分缓冲区
                dataBuffer.clear();
                timeBuffer.clear();
            }
        } else {
            // Normal模式：没找到触发点，继续等待
            // 但如果缓冲区太大，清理一部分旧数据
            if (dataBuffer.size() > maxBufferSize) {
                int keepSize = maxBufferSize / 2;
                int removeCount = dataBuffer.size() - keepSize;
                dataBuffer.remove(0, removeCount);
                timeBuffer.remove(0, removeCount);
            }
        }
    }
}

/**
 * @brief 在波形数据中查找触发点
 * 
 * 触发原理：
 * - 上升沿触发：信号从低于触发电平上升到高于或等于触发电平
 * - 下降沿触发：信号从高于触发电平下降到低于或等于触发电平
 */
int TriggerProcessor::findTriggerPoint(const QVector<double> &voltages)
{
    if (voltages.size() < 2) {
        return -1;
    }
    
    // 遍历数据，查找满足触发条件的点
    for (int i = 1; i < voltages.size(); ++i) {
        double prevValue = voltages[i - 1];
        double currValue = voltages[i];
        
        if (triggerEdge) {
            // 上升沿触发：信号从低于触发电平越过到高于或等于触发电平
            // 条件：前一个点 < 触发电平 && 当前点 >= 触发电平
            if (prevValue < triggerLevel && currValue >= triggerLevel) {

                return i;
            }
        } else {
            // 下降沿触发：信号从高于触发电平越过到低于或等于触发电平
            // 条件：前一个点 > 触发电平 && 当前点 <= 触发电平
            if (prevValue > triggerLevel && currValue <= triggerLevel) {

                return i;
            }
        }
    }
    
    // 未找到触发点 - 说明信号没有穿越触发电平
    return -1;
}

/**
 * @brief 截取以触发点为中心的波形数据
 */
void TriggerProcessor::extractTriggeredWaveform(
    const QVector<double> &voltages,
    const QVector<double> &times,
    int triggerIndex,
    QVector<double> &outVoltages,
    QVector<double> &outTimes)
{
    // 计算截取范围：让触发点位于波形的前1/4位置
    // 这样可以看到触发前的一小段波形和触发后的大部分波形
    int preTriggerPoints = expectedDataCount / 4;
    int startIndex = triggerIndex - preTriggerPoints;
    
    // 确保起始索引不越界
    if (startIndex < 0) {
        startIndex = 0;
    }
    
    // 计算结束索引
    int endIndex = startIndex + expectedDataCount;
    
    // 如果数据不够，调整范围
    if (endIndex > voltages.size()) {
        endIndex = voltages.size();
        startIndex = endIndex - expectedDataCount;
        if (startIndex < 0) {
            startIndex = 0;
        }
    }
    
    // 截取数据
    int actualCount = endIndex - startIndex;
    outVoltages.reserve(actualCount);
    outTimes.reserve(actualCount);
    
    for (int i = startIndex; i < endIndex; ++i) {
        outVoltages.append(voltages[i]);
        outTimes.append(times[i]);
    }
    

}
