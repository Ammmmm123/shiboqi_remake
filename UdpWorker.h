#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QVector>
#include <QTimer>

class UdpWorker : public QObject
{
    Q_OBJECT
public:
    explicit UdpWorker(quint16 listenPort = 6102, QObject *parent = nullptr);
    ~UdpWorker();

public slots:
    // 在主线程或通过 queued connection 设置要绑定的本地地址与端口
    void setLocalAddress(const QString &address, quint16 port);
    void start();
    void stop();

signals:
    void batchReady(const QVector<double> &voltages, const QVector<double> &times);
    // 当 bind 失败时告知主线程以便显示错误
    void bindFailed(const QString &errorString);
    // 与 UdpReceiver 保持一致的超量程信号
    void overRangeDetected(bool channel1OTR, bool channel2OTR, int sampleIndex);

private slots:
    void onReadyRead();
    void flushIfNeeded();

private:
    quint16 m_listenPort;
    QString m_listenAddressStr; // 保存为字符串，thread-safe 通过 queued invoke 设置
    QUdpSocket *m_socket = nullptr;
    QVector<double> m_bufVoltages;
    QVector<double> m_bufTimes;
    QTimer *m_flushTimer = nullptr;
    const int m_batchSize = 1024;
    const int m_flushMs = 25;
    bool m_running = false;
    // ADC / timing state (copied from UdpReceiver)
    const int ADC_DATA_WIDTH = 10;
    const double VOL_RANGE = 5.0;
    double sampleRate = 50000000.0; // Hz
    double LSB = 0.0;
    int sampleIndex = 0;
};

#endif // UDPWORKER_H
