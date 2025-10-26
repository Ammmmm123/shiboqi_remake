#ifndef WAVEFORM_SENDER_THREAD_H
#define WAVEFORM_SENDER_THREAD_H

#include <QThread>
#include <QVector>
#include <QHostAddress>
#include <QUdpSocket>

/**
 * @brief 波形发送线程类
 * 
 * 在独立线程中发送手绘波形数据，避免阻塞主线程
 */
class WaveformSenderThread : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param waveformData 1024个采样点的波形数据 (0-1023)
     * @param targetAddr 目标IP地址
     * @param targetPort 目标端口
     * @param delayMs 每个数据包发送间隔（毫秒）
     * @param parent 父对象指针
     */
    WaveformSenderThread(const QVector<quint16> &waveformData,
                         const QHostAddress &targetAddr,
                         quint16 targetPort,
                         int delayMs = 1,
                         QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~WaveformSenderThread();

signals:
    /**
     * @brief 发送进度信号
     * @param current 当前已发送的数据包数
     * @param total 总数据包数
     */
    void progressUpdated(int current, int total);

    /**
     * @brief 发送完成信号
     * @param successCount 成功发送的数据包数
     * @param totalCount 总数据包数
     */
    void sendingCompleted(int successCount, int totalCount);

    /**
     * @brief 发送失败信号
     * @param errorMessage 错误信息
     */
    void sendingFailed(const QString &errorMessage);

protected:
    /**
     * @brief 线程运行函数
     */
    void run() override;

private:
    /**
     * @brief 构建UDP波形数据包
     * @param voltageValue 10位电压值 (0-1023)
     * @return 8字节数据包
     */
    QByteArray buildWaveformPacket(quint16 voltageValue);

    QVector<quint16> m_waveformData;  ///< 波形数据
    QHostAddress m_targetAddress;      ///< 目标地址
    quint16 m_targetPort;              ///< 目标端口
    int m_delayMs;                     ///< 发送延迟（毫秒）
};

#endif // WAVEFORM_SENDER_THREAD_H
