#include "data_processor_thread.h"
#include <QDebug>
#include <QEventLoop>

/**
 * @brief 构造函数
 */
DataProcessorThread::DataProcessorThread(QObject *parent)
    : QThread(parent)
    , processor(new DataProcessor())  // 在构造函数中创建处理器
{
    // 将处理器移动到这个线程的事件循环中
    processor->moveToThread(this);

}

/**
 * @brief 析构函数
 */
DataProcessorThread::~DataProcessorThread()
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
 * @brief 获取数据处理器实例
 * @return DataProcessor指针
 */
DataProcessor* DataProcessorThread::getProcessor()
{
    // TODO: 返回处理器实例
    return processor;
}

/**
 * @brief 停止线程
 */
void DataProcessorThread::stop()
{
    // 请求线程退出
    quit();
    // 等待线程结束
    wait();

}

/**
 * @brief 线程运行函数
 */
void DataProcessorThread::run()
{

    
    // 进入事件循环，处理槽函数调用
    exec();
    

}
