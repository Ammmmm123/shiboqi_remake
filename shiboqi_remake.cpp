#include "shiboqi_remake.h"
#include "ui_shiboqi_remake.h"
#include <QMessageBox>
#include <QTimer>
#include <cmath>
#include <memory>
#include "siprefixticker.h"
#include <QOpenGLWidget>

/**
 * @brief 构造函数实现
 *
 * 创建主窗口，初始化UI界面和UDP接收器。
 * 设置窗口的父对象，并连接UI控件信号到相应的槽函数。
 *
/**
 * @brief 构造函数实现
 *
 * 创建主窗口，初始化UI界面和UDP接收器。
 * 设置窗口的父对象，并连接UI控件信号到相应的槽函数。
 *
 * @param parent 父窗口指针
 */
shiboqi_remake::shiboqi_remake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::shiboqi_remake)
    , udpReceiver(new UdpReceiver(this))
    , udpSender(new UdpSender(this))
    , errorDialogShown(false)
    , customPlot(nullptr)
    , updateTimer(new QTimer(this))
{
    ui->setupUi(this);
    /**
     * @brief 构造函数实现
     *
     * 创建主窗口，初始化UI界面和UDP接收器。
     * 设置窗口的父对象，并连接UI控件信号到相应的槽函数。
     *
     * @param parent 父窗口指针
     */

    // 初始化示波器
    customPlot = ui->customPlot;

    customPlot->setOpenGl(true);
    customPlot->addGraph(); // 添加一个图层
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // 设置线条颜色
    customPlot->xAxis->setLabel("Time (us)");
    customPlot->yAxis->setLabel("Voltage (V)");
    customPlot->xAxis->setRange(0, 1000); // 初始范围
    customPlot->yAxis->setRange(-5, 5);
    // 关闭默认拖拽/缩放交互，我们将通过事件过滤实现自定义行为
    customPlot->setInteractions(QCP::iNone);

    // 安装事件过滤器到 customPlot，用于捕获滚轮事件和修饰键组合
    customPlot->installEventFilter(this);

    // 将自定义 ticker 应用到 X 与 Y 轴
    auto xTicker = QSharedPointer<SIPrefixTicker>(new SIPrefixTicker("us"));
        auto yTicker = QSharedPointer<SIPrefixTicker>(new SIPrefixTicker("V"));
        customPlot->xAxis->setTicker(xTicker);
        customPlot->yAxis->setTicker(yTicker);

    // 当轴范围改变时，更新轴标签单位（例如 us->ms 等）
    connect(customPlot->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), this, [this, xTicker](const QCPRange &){
            QString unit = xTicker->unitLabel();
            customPlot->xAxis->setLabel(QString("Time (%1)").arg(unit));
        });

    connect(customPlot->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), this, [this, yTicker](const QCPRange &){
            QString unit = yTicker->unitLabel();
            // Ensure "V" label when prefix empty
            if (unit.isEmpty()) unit = QString("V");
            customPlot->yAxis->setLabel(QString("Voltage (%1)").arg(unit));
        });

    // 连接数据接收信号
    connect(udpReceiver, &UdpReceiver::dataReceived, this, &shiboqi_remake::onDataReceived);

    // 设置更新定时器
    connect(updateTimer, &QTimer::timeout, this, &shiboqi_remake::updatePlot);
    updateTimer->start(50); // 20fps更新

    // 连接设置按钮的点击信号到槽函数
    connect(ui->setButton, &QPushButton::clicked, this, &shiboqi_remake::on_setButton_clicked);

    // 连接监听按钮的切换信号到槽函数
    connect(ui->listenButton, &QPushButton::toggled, this, &shiboqi_remake::on_listenButton_toggled);

    // 连接循环发送按钮的切换信号到槽函数
    connect(ui->loopSendButton, &QPushButton::toggled, this, &shiboqi_remake::on_loopSendButton_toggled);

    // 连接发送采集命令按钮的点击信号到槽函数
    connect(ui->restartButton, &QPushButton::clicked, this, &shiboqi_remake::on_restartButton_clicked);

    // 连接UDP绑定失败信号到错误处理槽函数
    connect(udpReceiver, &UdpReceiver::bindFailed, this, &shiboqi_remake::onUdpBindFailed);
}

/**
 * @brief 析构函数实现
 *
 * 释放UI界面资源。UdpReceiver实例由于设置了this为父对象，会自动被删除。
 */
shiboqi_remake::~shiboqi_remake()
{
    delete ui;
}

/**
 * @brief 设置按钮点击处理函数
 *
 * 从IP地址输入框和端口选择框获取用户输入的值。
 * 验证IP地址的有效性，如果无效则直接返回。
 * 如果IP地址有效，则调用UDP接收器的setLocalAddress方法设置连接参数。
 *
 * 注意：此函数只设置连接参数，不启动监听。
 * 要开始接收UDP数据，需要另外调用udpReceiver->startListening()。
 */
void shiboqi_remake::on_setButton_clicked()
{
    // 获取用户输入的IP地址文本
    QString ipText = ui->ipLineEdit->text();

    // 获取用户选择的端口号
    quint16 port = ui->portSpinBox->value();

    // 将IP地址字符串转换为QHostAddress对象
    QHostAddress address(ipText);

    // 验证IP地址是否有效
    if (address.isNull()) {
        // IP地址无效，可以添加错误处理（如显示消息框）
        // 目前只是直接返回，不进行设置
        return;
    }

    // 设置UDP接收器的本地地址和端口
    udpReceiver->setLocalAddress(address, port);

    // 设置UDP发送器的目标地址和端口
    QString targetIpText = ui->targetIpLineEdit->text();
    quint16 targetPort = ui->targetPortSpinBox->value();
    QHostAddress targetAddress(targetIpText);
    if (!targetAddress.isNull()) {
        udpSender->setTargetAddress(targetAddress, targetPort);
    }

    // 设置UDP发送器的数据个数和分频系数
    quint32 dataNum = ui->dataNumSpinBox->value();
    quint32 divider = ui->dividerSpinBox->value();
    quint8 channel = ui->channelSpinBox->value();
    udpSender->setDataNum(dataNum);
    udpSender->setDivider(divider);
    udpSender->setChannel(channel);
}

/**
 * @brief 监听按钮切换处理函数
 *
 * 根据按钮的选中状态控制UDP监听的开始和停止。
 * 当按钮被选中时，开始UDP监听并改变按钮文本为"停止监听"，同时禁用设置控件；
 * 当取消选中时，停止监听并改变按钮文本为"开始监听"，重新启用设置控件。
 *
 * @param checked 按钮的选中状态，true为开始监听，false为停止监听
 */
void shiboqi_remake::on_listenButton_toggled(bool checked)
{
    if (checked) {
        // 开始监听UDP数据
        udpSender->sendStopLoopCommand();
        udpReceiver->startListening();
        ui->listenButton->setText("停止监听");
        
        // 禁用设置按钮，防止在监听期间修改参数
        ui->setButton->setEnabled(false);
        ui->ipLineEdit->setEnabled(false);
        ui->portSpinBox->setEnabled(false);
        ui->targetIpLineEdit->setEnabled(false);
        ui->targetPortSpinBox->setEnabled(false);
        ui->dataNumSpinBox->setEnabled(false);
        ui->dividerSpinBox->setEnabled(false);
        ui->channelSpinBox->setEnabled(false);
    } else {
        // 停止监听UDP数据
        udpSender->sendStopLoopCommand();
        udpReceiver->stopListening();
        ui->listenButton->setText("开始监听");
        
        // 重新启用设置按钮和输入控件
        ui->setButton->setEnabled(true);
        ui->ipLineEdit->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
        ui->targetIpLineEdit->setEnabled(true);
        ui->targetPortSpinBox->setEnabled(true);
        ui->dataNumSpinBox->setEnabled(true);
        ui->dividerSpinBox->setEnabled(true);
        ui->channelSpinBox->setEnabled(true);
    }
}

/**
 * @brief UDP绑定失败处理函数
 *
 * 当UDP套接字绑定失败时，经过短暂延时后弹出阻塞型的错误提示对话框。
 * 使用非阻塞延时确保UI状态正确更新后再显示错误信息。
 *
 * @param errorString UDP套接字返回的错误描述
 */
void shiboqi_remake::onUdpBindFailed(const QString &errorString)
{
    // 如果已经有错误对话框在显示，忽略这次调用
    if (errorDialogShown) {
        return;
    }

    errorDialogShown = true;

    // 非阻塞延时30ms后显示错误对话框，确保UI状态正确更新
    QTimer::singleShot(30, this, [this, errorString]() {
        // 弹出阻塞型的错误提示对话框
        QMessageBox::critical(this,
                             "UDP绑定失败",
                             QString("无法绑定到指定的IP地址和端口。\n\n错误详情：%1\n\n请检查：\n1. IP地址是否正确\n2. 网络连接是否正常\n3. 该IP地址是否存在于本机").arg(errorString),
                             QMessageBox::Ok);

        // 阻止信号发射，安全地重置按钮状态和文字
        ui->listenButton->blockSignals(true);
        ui->listenButton->setChecked(false);
        ui->listenButton->setText("开始监听");
        ui->listenButton->blockSignals(false);

        // 重新启用设置控件，因为监听失败了
        ui->setButton->setEnabled(true);
        ui->ipLineEdit->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
        ui->targetIpLineEdit->setEnabled(true);
        ui->targetPortSpinBox->setEnabled(true);
        ui->dataNumSpinBox->setEnabled(true);
        ui->dividerSpinBox->setEnabled(true);
        ui->channelSpinBox->setEnabled(true);

        // 重置标志位，允许下次显示错误对话框
        errorDialogShown = false;
    });
}

/**
 * @brief 循环发送按钮切换处理函数
 *
 * 根据按钮状态开始或停止循环发送UDP数据。
 * @param checked true表示开始循环发送，false表示停止循环发送
 */
void shiboqi_remake::on_loopSendButton_toggled(bool checked)
{
    if (checked) {
        // 开始循环发送
        udpSender->sendStartLoopCommand();
        ui->loopSendButton->setText("停止循环发送");
    } else {
        // 停止循环发送
        udpSender->sendStopLoopCommand();
        ui->loopSendButton->setText("循环发送");
    }
}

/**
 * @brief 发送采集命令按钮点击处理函数
 *
 * 发送重新启动采集命令。
 */
void shiboqi_remake::on_restartButton_clicked()
{
    udpSender->sendRestartCommand();
}

/**
 * @brief 数据接收槽函数
 *
 * 处理接收到的UDP数据，进行抽样和缓冲。
 * @param voltages 电压值向量
 * @param times 时间向量
 */
void shiboqi_remake::onDataReceived(const QVector<double> &voltages, const QVector<double> &times)
{
    // 从接收到的时间估算采样间隔（times 假定为微秒）
    double estimatedDtSec = 0.0;
    if (times.size() >= 2) {
        double sumDiff = 0.0;
        for (int i = 0; i < times.size() - 1; ++i) {
            sumDiff += (times[i+1] - times[i]);
        }
        double avgDiff = sumDiff / (times.size() - 1);
        // times are in microseconds in this project, convert to seconds
        estimatedDtSec = avgDiff * 1e-6;
        if (estimatedDtSec > 0) lastSampleInterval = estimatedDtSec;
    }

    // 将样本同时插入历史缓冲和流式缓冲。
    // 对于 streamBuffer，我们希望索引 0 存放最新样本，因此按顺序在前端插入（prepend）。
    for (int i = 0; i < voltages.size(); ++i) {
        double voltage = voltages[i];
        double time = times[i];

        // 检查波形变化幅度，若小于阈值则忽略该采样
        // if (qAbs(voltage - lastVoltage) < changeThreshold) {
        //     continue;
        // }
        // lastVoltage = voltage;

        // 历史 FIFO 缓冲（保持现有行为）
        dataBuffer.enqueue(QPointF(time, voltage));
        if (dataBuffer.size() > maxBufferSize) {
            dataBuffer.dequeue();
        }

        // 流式缓冲：将最新样本放到 index 0（队首）
        streamBuffer.prepend(voltage);
    }

    // 修剪流式缓冲，确保其表示的总时长不超过 streamMaxDuration（以秒为单位）
    if (lastSampleInterval > 0.0) {
        int maxSamples = qMax(1, int(streamMaxDuration / lastSampleInterval));
        while (streamBuffer.size() > maxSamples) {
            streamBuffer.removeLast();
        }
    } else {
        // 若未能估计出有效的采样间隔，使用 maxBufferSize 作为上限以避免无限增长
        while (streamBuffer.size() > maxBufferSize) {
            streamBuffer.removeLast();
        }
    }
}

/**
 * @brief 更新波形图
 *
 * 从缓冲池获取数据并更新显示。
 */
void shiboqi_remake::updatePlot()
{
    if (dataBuffer.isEmpty()) {
        return;
    }

    // 如果存在 streamBuffer 数据，按流式方式绘制：索引 0 为最新（x=0）
    if (!streamBuffer.isEmpty()) {
        QVector<double> xData, yData;

        // Determine delta in microseconds for plotting (axis uses microseconds)
        double dtSec = lastSampleInterval;
        if (dtSec <= 0.0) {
            // 回退：使用更新定时器间隔估算采样间隔
            dtSec = updateTimer->interval() / 1000.0;
        }
        double dtUs = dtSec * 1e6; // 将秒转换为微秒以匹配当前 X 轴单位

        int n = streamBuffer.size();
        xData.reserve(n);
        yData.reserve(n);
        for (int i = 0; i < n; ++i) {
            // 最新样本对应 x = 0，越旧的样本 x 值越大（向右延伸）
            xData.append(i * dtUs);
            yData.append(streamBuffer.at(i));
        }

        customPlot->graph(0)->setData(xData, yData);

        // 将 X 轴显示窗口固定为 streamMaxDuration（这里注释了 setRange，以保留轴自动缩放的灵活性）
        customPlot->replot();
        return;
    }

    // 否则回退到历史缓冲的绘制（保持原行为）
    QVector<double> xData, yData;
    for (const QPointF &point : dataBuffer) {
        xData.append(point.x());
        yData.append(point.y());
    }
    customPlot->graph(0)->setData(xData, yData);
    customPlot->replot();
}

/**
 * @brief 按因子缩放 Y 轴范围
 *
 * @param plot 指定的 QCustomPlot
 * @param factor 缩放因子（<1 放大，>1 缩小）
 * @param pos 鼠标位置（当前实现未使用）
 */
void scaleYAxis(QCustomPlot *plot, double factor, const QPoint &/*pos*/) {
    auto range = plot->yAxis->range();
    double center = (range.lower + range.upper) / 2.0;
    double half = (range.upper - range.lower) / 2.0 * factor;
    plot->yAxis->setRange(center - half, center + half);
}

/**
 * @brief 按因子缩放 X 轴，保持左边界为 0
 *
 * 该函数根据当前 X 轴范围计算新的跨度并将左边界固定为 0（或新下界为 0），
 * 以保持时间轴从 0 开始展示历史数据滚动窗口。
 * @param plot 指定的 QCustomPlot
 * @param factor 缩放因子
 * @param pos 鼠标位置（当前实现未使用）
 */
void scaleXAxis(QCustomPlot *plot, double factor, const QPoint &/*pos*/) {
    auto range = plot->xAxis->range();
    double lower = range.lower;
    double upper = range.upper;
    double span = (upper - lower) * factor;

    // 始终将左侧固定为0（确保程序启动时0位于左侧角落不会改变）
    double newLower = 0.0;
    double newUpper = newLower + span;
    // 若原始范围并非从0开始，也仍按保持0为左边缘的策略处理
    plot->xAxis->setRange(newLower, newUpper);
}

bool shiboqi_remake::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == customPlot && event->type() == QEvent::Wheel) {
        QWheelEvent *we = static_cast<QWheelEvent *>(event);
        QPoint numDegrees = we->angleDelta();
        if (numDegrees.isNull()) return true;

        // 计算缩放因子：滚轮向上放大（factor <1），向下缩小（factor >1）
        double steps = numDegrees.y() / 120.0; // 120 per step
        double factor = std::pow(0.9, steps); // 每步约10%变化

        // 根据修饰键决定缩放轴：Shift->Y, Ctrl->X, none->both
        Qt::KeyboardModifiers mods = we->modifiers();
        if (mods & Qt::ShiftModifier) {
            scaleYAxis(customPlot, factor, we->position().toPoint());
        } else if (mods & Qt::ControlModifier) {
            scaleXAxis(customPlot, factor, we->position().toPoint());
        } else {
            scaleXAxis(customPlot, factor, we->position().toPoint());
            scaleYAxis(customPlot, factor, we->position().toPoint());
        }

        customPlot->replot();
        return true; // 事件已处理
    }

    return QMainWindow::eventFilter(obj, event);
}