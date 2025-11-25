#include "trigger_processor_thread.h"
#include <QDebug>

/**
 * @brief 构造函数
 */
TriggerProcessorThread::TriggerProcessorThread(QObject *parent)
    : QThread(parent)
    , processor(new TriggerProcessor())  // 在构造函数中创建处理器
{
    // 将处理器移动到这个线程的事件循环中
    processor->moveToThread(this);
}

/**
 * @brief 析构函数
 */
TriggerProcessorThread::~TriggerProcessorThread()
{
    // 停止线程
    if (isRunning()) {
        quit();
        wait();
    }
    
    // 删除处理器
    if (processor) {
        delete processor;
        processor = nullptr;
    }
}

/**
 * @brief 获取触发处理器实例指针
 */
TriggerProcessor* TriggerProcessorThread::getProcessor()
{
    return processor;
}

/**
 * @brief 停止线程
 */
void TriggerProcessorThread::stop()
{
    // 请求线程退出
    quit();
    // 等待线程结束
    wait();
}

/**
 * @brief 线程运行函数
 */
void TriggerProcessorThread::run()
{
    // 进入事件循环，处理槽函数调用
    exec();
}
