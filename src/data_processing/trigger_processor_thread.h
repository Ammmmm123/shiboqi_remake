#ifndef TRIGGER_PROCESSOR_THREAD_H
#define TRIGGER_PROCESSOR_THREAD_H

#include <QThread>
#include "trigger_processor.h"

/**
 * @brief 触发处理器线程类
 * 
 * 管理 TriggerProcessor 的独立线程
 * 负责线程的启动、停止和清理
 */
class TriggerProcessorThread : public QThread
{
    Q_OBJECT
    
public:
    explicit TriggerProcessorThread(QObject *parent = nullptr);
    ~TriggerProcessorThread();
    
    /**
     * @brief 获取触发处理器实例指针
     * @return TriggerProcessor 指针（运行在子线程中）
     */
    TriggerProcessor* getProcessor();
    
    /**
     * @brief 停止线程
     * 
     * 安全地停止线程，清理资源
     */
    void stop();
    
protected:
    /**
     * @brief 线程运行函数
     * 
     * 创建 TriggerProcessor 实例并启动事件循环
     */
    void run() override;
    
private:
    TriggerProcessor *processor;  ///< 触发处理器实例（在子线程中创建）
};

#endif // TRIGGER_PROCESSOR_THREAD_H
