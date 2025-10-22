#ifndef SHIBOQI_REMAKE_H
#define SHIBOQI_REMAKE_H

#include <QMainWindow>
#include <QTimer>
#include <QEvent>
#include "qcustomplot-source/qcustomplot.h"
#include "udp_receive.h"
#include "udp_send.h"
#include "data_processor.h"
#include "UART_receive.h"
#include "spectrum_analyzer.h"

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

    /**
     * @brief 分析结果就绪的槽（由 DataProcessor 发射）
     *
     * 留空以便用户自行实现处理逻辑。
     */
    void onAnalysisReady(const WaveformAnalysisResult &result);

    /**
     * @brief 降采样数据就绪的槽（用于绘图）
     * @param voltages 降采样后的电压数据
     * @param times 降采样后的时间戳（微秒）
     */
    void onDownsampledDataReady(const QVector<double> &voltages, const QVector<double> &times);

    /**
     * @brief 波形切换按钮点击槽函数
     */
    void on_waveformSwitchButton_clicked();

    /**
     * @brief 频率加按钮点击槽函数
     */
    void on_frequencyUpButton_clicked();

    /**
     * @brief 频率减按钮点击槽函数
     */
    void on_frequencyDownButton_clicked();

    /**
     * @brief 幅度加按钮点击槽函数
     */
    void on_amplitudeUpButton_clicked();

    /**
     * @brief 幅度减按钮点击槽函数
     */
    void on_amplitudeDownButton_clicked();

    /**
     * @brief 串口连接按钮切换槽函数
     * @param checked true表示连接串口，false表示断开串口
     */
    void on_pushButton_2_toggled(bool checked);
    /**
     * @brief 周期刷新可用串口列表（每秒）
     */
    void refreshSerialPorts();

    /**
     * @brief 串口解析后数据到达槽函数
     * @param duty 占空比
     * @param highTime 高电平时间（us）
     * @param lowTime 低电平时间（us）
     * @param frequency 频率（Hz）
     */
    void onParsedSerialData(int duty, int highTime, int lowTime, double frequency);

    // ===== page_8 频谱页面的槽函数（复制自page_5） =====
    void on_setButton_5_clicked();
    void on_listenButton_5_toggled(bool checked);
    void on_loopSendButton_5_toggled(bool checked);
    void on_restartButton_5_clicked();
    void onUdpBindFailed_page8(const QString &errorString);
    
    /**
     * @brief 频谱分析结果就绪槽函数
     * @param result 频谱分析结果
     */
    void onSpectrumReady(const SpectrumAnalysisResult &result);
    
    /**
     * @brief 同步 page_5 的设置参数到 page_8
     * 
     * 定期将 page_5 的 IP、端口、数据个数、分频系数、通道等参数同步到 page_8
     */
    void syncSettingsToPage8();

private:
    Ui::shiboqi_remake *ui;      ///< UI界面指针
    UdpReceiver *udpReceiver;    ///< UDP接收器实例指针
    UdpSender *udpSender;        ///< UDP发送器实例指针
    bool errorDialogShown;       ///< 错误对话框显示标志，防止重复弹出
    DataProcessor *dataProcessor; ///< 波形数据处理器

    // 示波器相关
    QCustomPlot *customPlot;     ///< 自定义绘图控件
    QTimer *updateTimer;         ///< 更新定时器
    
    // 降采样后的绘图数据（由 DataProcessor 提供）
    QVector<double> plotVoltages; ///< 用于绘图的电压数据
    QVector<double> plotTimes;    ///< 用于绘图的时间戳数据
    
    // 波形控制相关
    quint8 currentWaveformType;   ///< 当前波形类型 (0-3)
    UARTReceiver *uartReceiver;   ///< UART接收器实例指针
    QTimer *portRefreshTimer;     ///< 定期刷新串口列表的定时器
    QString openPortName;         ///< 记录当前已打开的串口名称（便于在端口消失时处理）

    // page_8 频谱页面相关（不包含时域示波器逻辑）
    QCustomPlot *customPlot_page8;     ///< page_8 的绘图控件（仅用于频谱显示）
    bool errorDialogShown_page8;       ///< page_8 的错误对话框标志
    SpectrumAnalyzer *spectrumAnalyzer; ///< 频谱分析器实例
    QTimer *settingsSyncTimer;         ///< page_5 到 page_8 的设置同步定时器
};
#endif // SHIBOQI_REMAKE_H
