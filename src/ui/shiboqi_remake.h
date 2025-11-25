#ifndef SHIBOQI_REMAKE_H
#define SHIBOQI_REMAKE_H

#include <QMainWindow>
#include <QTimer>
#include <QEvent>
#include "qcustomplot.h"
#include "udp_receive.h"
#include "udp_send.h"
#include "data_processor.h"
#include "data_processor_thread.h"
#include "trigger_processor.h"
#include "trigger_processor_thread.h"
#include "UART_receive.h"
#include "spectrum_analyzer.h"
#include "waveform_sender_thread.h"
#include "PWMControllerQt.h"
#include "MusicPlayer.h"
#include <QSerialPortInfo>

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
     * @brief 采样参数推荐就绪的槽函数
     * @param recommendation 推荐的采样参数（包含分频比）
     * 
     * 自动设置下位机的分频比和采样点数
     */
    void onSamplingRecommendationReady(const SamplingRecommendation &recommendation);

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
     * @brief 手绘模式按钮切换槽函数
     * @param checked true表示开启手绘模式，false表示关闭手绘模式
     */
    void on_handDrawButton_toggled(bool checked);

    /**
     * @brief 清除绘制按钮点击槽函数
     */
    void on_clearDrawButton_clicked();

    /**
     * @brief 保存并发送按钮点击槽函数
     */
    void on_saveAndSendButton_clicked();

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

    /**
     * @brief 波形发送进度更新槽函数
     * @param current 当前已发送的数据包数
     * @param total 总数据包数
     */
    void onWaveformSendProgress(int current, int total);

    /**
     * @brief 波形发送完成槽函数
     * @param successCount 成功发送的数据包数
     * @param totalCount 总数据包数
     */
    void onWaveformSendCompleted(int successCount, int totalCount);

    /**
     * @brief 波形发送失败槽函数
     * @param errorMessage 错误信息
     */
    void onWaveformSendFailed(const QString &errorMessage);

    /**
     * @brief 频谱分析结果就绪槽函数
     * @param result 频谱分析结果
     */
    void onSpectrumReady(const SpectrumAnalysisResult &result);

    /**
     * @brief 触发处理后的数据就绪槽函数
     * @param voltages 处理后的电压数据
     * @param times 处理后的时间戳数据
     */
    void onTriggeredDataReady(const QVector<double> &voltages, const QVector<double> &times);

    /**
     * @brief 触发使能复选框切换槽函数
     * @param checked true表示启用触发，false表示禁用触发
     */
    void on_triggerEnableCheckBox_toggled(bool checked);

    /**
     * @brief 触发模式下拉框切换槽函数
     * @param index 0: Auto模式, 1: Normal模式
     */
    void on_triggerModeComboBox_currentIndexChanged(int index);

    /**
     * @brief 触发边沿下拉框切换槽函数
     * @param index 0: 上升沿, 1: 下降沿
     */
    void on_triggerEdgeComboBox_currentIndexChanged(int index);

    /**
     * @brief PWM串口刷新定时器槽函数
     */
    void refreshPWMSerialPorts();

    /**
     * @brief PWM串口打开/关闭按钮切换槽函数
     * @param checked true表示打开串口，false表示关闭串口
     */
    void on_pwmOpenSerialButton_toggled(bool checked);

    /**
     * @brief PWM加载音乐文件按钮槽函数
     */
    void on_pwmLoadMusicButton_clicked();

    /**
     * @brief PWM播放音乐按钮槽函数
     */
    void on_pwmPlayMusicButton_toggled(bool checked);

    /**
     * @brief PWM停止音乐按钮槽函数
     */
    void on_pwmStopMusicButton_clicked();

    /**
     * @brief 音乐播放器请求设置频率槽函数
     */
    void onMusicRequestFrequency(int frequency);

    /**
     * @brief 音乐播放进度更新槽函数
     */
    void onMusicProgressUpdated(int current, int total);

private:
    /**
     * @brief 将手绘点集合插值为1024点波形数据
     */
    void interpolateHandDrawnWaveform();
    
    /**
     * @brief 翻转Y轴数据（1023 - y）,使发送的波形和手绘的波形一致
     */
    void flipYAxisData();
    
    /**
     * @brief 发送手绘波形数据包（使用独立线程发送）
     */
    void sendHandDrawnWaveform();
    
    /**
     * @brief 初始化触发电平线
     */
    void setupTriggerLine();
    
    /**
     * @brief 更新触发电平线的位置
     * @param level 触发电平值（V）
     */
    void updateTriggerLine(double level);
    
    /**
     * @brief 处理示波器的鼠标按下事件
     */
    void handlePlotMousePress(QMouseEvent *event);
    
    /**
     * @brief 处理示波器的鼠标移动事件
     */
    void handlePlotMouseMove(QMouseEvent *event);
    
    /**
     * @brief 处理示波器的鼠标释放事件
     */
    void handlePlotMouseRelease(QMouseEvent *event);
    
    /**
     * @brief 更新PWM参数到下位机
     */
    void updatePWMParameters();
    
    /**
     * @brief 设置PWM频率(由音乐播放器调用)
     */
    void setPWMFrequencyForMusic(int frequency);
    
    /**
     * @brief 启用/禁用PWM控制界面(播放音乐时禁用)
     */
    void setPWMControlsEnabled(bool enabled);

private:
    Ui::shiboqi_remake *ui;      ///< UI界面指针
    UdpReceiver *udpReceiver;    ///< UDP接收器实例指针
    UdpSender *udpSender;        ///< UDP发送器实例指针
    bool errorDialogShown;       ///< 错误对话框显示标志，防止重复弹出
    DataProcessorThread *dataProcessorThread; ///< 数据处理线程（独立线程运行）
    DataProcessor *dataProcessor; ///< 波形数据处理器（运行在独立线程中）
    TriggerProcessorThread *triggerProcessorThread; ///< 触发处理线程（独立线程运行）
    TriggerProcessor *triggerProcessor; ///< 触发处理器（运行在独立线程中）

    // 示波器相关
    QCustomPlot *customPlot;     ///< 自定义绘图控件
    QTimer *updateTimer;         ///< 更新定时器
    
    // 降采样后的绘图数据（由 DataProcessor 提供）
    QVector<double> plotVoltages; ///< 用于绘图的电压数据
    QVector<double> plotTimes;    ///< 用于绘图的时间戳数据
    
    // 波形控制相关
    quint8 currentWaveformType;   ///< 当前波形类型 (0-3)
    
    // 手绘波形相关
    bool isHandDrawMode;          ///< 是否处于手绘模式
    bool isDrawing;               ///< 是否正在绘制
    QVector<QPointF> handDrawnPoints; ///< 手绘的点集合
    QVector<quint16> handDrawnWaveform; ///< 插值后的1024点波形数据(0-1023)
    WaveformSenderThread *waveformSenderThread; ///< 波形发送线程
    
    UARTReceiver *uartReceiver;   ///< UART接收器实例指针
    QTimer *portRefreshTimer;     ///< 定期刷新串口列表的定时器
    QString openPortName;         ///< 记录当前已打开的串口名称（便于在端口消失时处理）

    // 频谱分析多线程架构（与示波器共享 page_5 的 stackedWidget）
    QCustomPlot *customPlot_spectrum; ///< 频谱分析的绘图控件（在 stackedWidget 中）
    QThread *spectrumThread;           ///< 频谱分析专用线程
    SpectrumAnalyzer *spectrumAnalyzer; ///< 频谱分析器实例（运行在独立线程中）
    
    QTimer *spectrumLabelUpdateTimer;  ///< 频谱数据标签更新定时器（节流）
    SpectrumAnalysisResult lastSpectrumResult; ///< 缓存最新的频谱分析结果
    
    // 视图模式标志
    bool isSpectrumMode;               ///< true=频谱模式，false=示波器模式
    bool hasUserZoomed;                ///< 用户是否手动缩放过示波器（禁用自动缩放）
    
    // 触发电平可视化控制
    QCPItemStraightLine *triggerLine;  ///< 触发电平线
    QCPItemText *triggerLevelText;     ///< 触发电平文本标签
    double currentTriggerLevel;        ///< 当前触发电平值（V）
    bool isDraggingTrigger;            ///< 是否正在拖动触发线

    // PWM控制器相关
    PWMControllerQt *pwmController;    ///< PWM控制器实例指针
    QTimer *pwmPortRefreshTimer;       ///< PWM串口列表刷新定时器
    QString pwmOpenPortName;           ///< 当前PWM已打开的串口名称
    MusicPlayer *musicPlayer;          ///< 音乐播放器实例指针
    QString currentMusicFile;          ///< 当前加载的音乐文件路径
};
#endif // SHIBOQI_REMAKE_H
