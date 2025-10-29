#ifndef DATA_PROCESSOR_THREAD_H
#define DATA_PROCESSOR_THREAD_H

#include <QThread>
#include "data_processor.h"

/**
 * @brief 数据处理线程类
 * 
 * 管理 DataProcessor 在独立线程中的运行
 * 避免数据处理阻塞GUI线程
 */
class DataProcessorThread : public QThread
{
    Q_OBJECT
    
public:
    explicit DataProcessorThread(QObject *parent = nullptr);
    ~DataProcessorThread();
    
    /**
     * @brief 获取数据处理器实例
     * @return DataProcessor指针（运行在本线程中）
     */
    DataProcessor* getProcessor();
    
    /**
     * @brief 停止线程
     */
    void stop();
    
protected:
    /**
     * @brief 线程运行函数
     */
    void run() override;
    
private:
    DataProcessor *processor;  ///< 数据处理器实例
};

#endif // DATA_PROCESSOR_THREAD_H
