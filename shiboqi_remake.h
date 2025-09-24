#ifndef SHIBOQI_REMAKE_H
#define SHIBOQI_REMAKE_H

#include <QMainWindow>
#include <QTimer>
#include <QEvent>
#include "qcustomplot-source/qcustomplot.h"
#include "udp_receive.h"
#include "udp_send.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class shiboqi_remake;
}
QT_END_NAMESPACE

/**
 * @brief shiboqi_remake类
 *
 * 主窗口类，继承自QMainWindow。
 * 提供UDP连接设置的图形界面，包括IP地址和端口输入控件。
 * 内部管理UdpReceiver实例来处理UDP数据接收。
 */
class shiboqi_remake : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针，默认为nullptr
     *
     * 初始化主窗口，创建UI界面和UdpReceiver实例，
     * 并连接按钮信号到相应的槽函数。
     */
    shiboqi_remake(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     *
     * 清理UI资源和UdpReceiver实例。
     */
    ~shiboqi_remake();

private slots:
    /**
     * @brief 设置按钮点击槽函数
     *
     * 当用户点击"设置UDP连接"按钮时调用。
     * 从UI控件获取IP地址和端口值，验证IP地址有效性，
     * 然后调用UdpReceiver的setLocalAddress方法设置连接参数。
     */
    void on_setButton_clicked();

    /**
     * @brief 监听按钮切换槽函数
     *
     * 当用户点击监听按钮时调用，根据按钮状态开始或停止UDP监听。
     * @param checked true表示开始监听，false表示停止监听
     */
    void on_listenButton_toggled(bool checked);

    /**
     * @brief 循环发送按钮切换槽函数
     *
     * 当用户点击循环发送按钮时调用，根据按钮状态开始或停止循环发送数据。
     * @param checked true表示开始循环发送，false表示停止循环发送
     */
    void on_loopSendButton_toggled(bool checked);

    /**
     * @brief 发送采集命令按钮点击槽函数
     *
     * 当用户点击发送采集命令按钮时调用，发送重新启动采集命令。
     */
    void on_restartButton_clicked();

    /**
     * @brief 数据接收槽函数
     *
     * 处理UDP接收到的数据，添加到缓冲池并触发更新。
     * @param voltages 电压值向量
     * @param times 时间向量
     */
    void onDataReceived(const QVector<double> &voltages, const QVector<double> &times);

    /**
     * @brief 更新波形图
     *
     * 从缓冲池获取数据并更新显示。
     */
    void updatePlot();

    /**
     * @brief 事件过滤器，用于处理自定义的滚轮缩放行为
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

    /**
     * @brief UDP绑定失败处理槽函数
     *
     * 当UDP套接字绑定失败时弹出错误提示对话框。
     * @param errorString UDP套接字返回的错误描述
     */
    void onUdpBindFailed(const QString &errorString);

private:
    Ui::shiboqi_remake *ui;      ///< UI界面指针
    UdpReceiver *udpReceiver;    ///< UDP接收器实例指针
    UdpSender *udpSender;        ///< UDP发送器实例指针
    bool errorDialogShown;       ///< 错误对话框显示标志，防止重复弹出

    // 示波器相关
    QCustomPlot *customPlot;     ///< 自定义绘图控件
    QQueue<QPointF> dataBuffer;  ///< 数据缓冲池，先入先出
    const int maxBufferSize = 10000; ///< 最大缓冲大小
    double lastVoltage = 0.0;   ///< 上一个电压值，用于变化检测
    const double changeThreshold = 0.01; ///< 变化阈值，小于此值则省略
    QTimer *updateTimer;         ///< 更新定时器
    // 流式绘图相关（最新点在 x=0，旧点向右移动）
    QVector<double> streamBuffer;   ///< 环形/流式缓冲：仅保存电压值，索引 0 为最新
    double streamMaxDuration = 1.0; ///< 流式显示的最长时长（秒），波形长度不超过此值
    double lastSampleInterval = 0.0; ///< 最近一次计算的采样间隔（秒），用于 x 轴位置计算
};
#endif // SHIBOQI_REMAKE_H
