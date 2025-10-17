#include "shiboqi_remake.h"
#include "ui_shiboqi_remake.h"
#include <QMessageBox>
#include <QTimer>
#include <cmath>
#include <algorithm>
#include "siprefixticker.h"
#include <QOpenGLWidget>


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
    , dataProcessor(new DataProcessor(this)) // 创建数据处理器对象
{
    ui->setupUi(this);

    // 创建数据处理器并连接信号
    connect(udpReceiver, &UdpReceiver::dataReceived, dataProcessor, &DataProcessor::analyzeWaveform);
    connect(dataProcessor, &DataProcessor::analysisReady, this, &shiboqi_remake::onAnalysisReady);
    connect(dataProcessor, &DataProcessor::downsampledDataReady, this, &shiboqi_remake::onDownsampledDataReady);

    // 初始化示波器
    customPlot = ui->customPlot;

    customPlot->setOpenGl(true);
    qDebug()<<"opengle="<<customPlot->openGl();
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

    // 连接数据接收信号到本地槽函数（如果还需要其他处理）
    // connect(udpReceiver, &UdpReceiver::dataReceived, this, &shiboqi_remake::onDataReceived);
    
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
    udpSender->sendChannelSelectCommand(); // 发送通道选择命令
    udpSender->sendDataNumCommand(); // 发送数据个数设置命令
    udpSender->sendDividerCommand(); // 发送分频系数设置命令
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
        on_setButton_clicked();//预先设置参数
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
        
        // 重置数据处理器状态，清空累积的数据缓冲区
        dataProcessor->reset();
        
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
        dataProcessor->reset();
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
 * @brief 数据接收槽函数（已废弃 - 现在使用 DataProcessor 的降采样数据）
 *
 * 此函数保留用于兼容性，实际绘图数据由 onDownsampledDataReady 处理
 * @param voltages 电压值向量
 * @param times 时间向量
 */
void shiboqi_remake::onDataReceived(const QVector<double> &voltages, const QVector<double> &times)
{
    // 原始数据接收逻辑已移至 DataProcessor
    // 不再需要本地缓冲和抽样
    Q_UNUSED(voltages);
    Q_UNUSED(times);
}

/**
 * @brief 接收降采样后的数据用于绘图
 * @param voltages 降采样后的电压数据
 * @param times 降采样后的时间戳（微秒）
 * 
 * 由 DataProcessor 在完成分析和降采样后发射，直接用于高效绘图
 */
void shiboqi_remake::onDownsampledDataReady(const QVector<double> &voltages, const QVector<double> &times)
{
    // 保存降采样后的数据供绘图使用
    plotVoltages = voltages;
    plotTimes = times;
    
    // 可选：立即触发一次绘图更新（或等待定时器）
    // updatePlot();
}

/**
 * @brief 更新波形图（使用降采样数据）
 *
 * 使用 DataProcessor 提供的降采样数据进行高效绘图
 * 波形起点固定在坐标原点(0,0)，不自动调整坐标轴范围
 */
void shiboqi_remake::updatePlot()
{
    // 检查是否有有效的绘图数据
    if (plotVoltages.isEmpty() || plotTimes.isEmpty()) {
        return;
    }

    // 将时间戳平移，使第一个点的时间为0（波形从原点开始）
    QVector<double> adjustedTimes = plotTimes;
    if (!adjustedTimes.isEmpty()) {
        double timeOffset = adjustedTimes.first();
        for (int i = 0; i < adjustedTimes.size(); ++i) {
            adjustedTimes[i] -= timeOffset;
        }
    }
    
    // 使用调整后的时间数据绘图
    customPlot->graph(0)->setData(adjustedTimes, plotVoltages);
    
    // 不自动调整坐标轴范围，保持用户设置的范围
    // 注释掉 rescale() 调用
    // customPlot->xAxis->rescale();
    // customPlot->yAxis->rescale();
    
    // 重绘图表
    customPlot->replot();
}

/**
 * @brief 按因子缩放 Y 轴范围（无限制）
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
 * @brief 按因子缩放 X 轴，保持左边界为 0（限制在波形数据范围内）
 *
 * 该函数根据当前 X 轴范围计算新的跨度并将左边界固定为 0（或新下界为 0），
 * 以保持时间轴从 0 开始展示历史数据滚动窗口。
 * 缩放范围被限制在实际波形数据的时间范围内。
 * @param plot 指定的 QCustomPlot
 * @param factor 缩放因子
 * @param pos 鼠标位置（当前实现未使用）
 * @param plotTimes 当前波形的时间数据（已调整为从0开始），用于限制缩放范围
 */
void scaleXAxis(QCustomPlot *plot, double factor, const QPoint &/*pos*/, const QVector<double> &plotTimes) {
    // 如果没有数据，不进行缩放
    if (plotTimes.isEmpty()) {
        return;
    }
    
    // 计算数据的实际时间范围（已经是从0开始的调整后时间）
    double dataMin = 0.0; // 时间起点始终为0
    double dataMax = *std::max_element(plotTimes.begin(), plotTimes.end());
    
    // 添加2%的右边距
    double margin = (dataMax - dataMin) * 0.02;
    double limitMax = dataMax + margin;
    
    // 计算新的范围
    auto range = plot->xAxis->range();
    double span = (range.upper - range.lower) * factor;

    // 始终将左侧固定为0
    double newLower = 0.0;
    double newUpper = newLower + span;
    
    // 限制右边界不超过数据最大值
    if (newUpper > limitMax) {
        newUpper = limitMax;
    }
    
    // 确保最小显示范围（至少显示数据范围的5%）
    double minSpan = (dataMax - dataMin) * 0.05;
    if (newUpper - newLower < minSpan) {
        newUpper = newLower + minSpan;
        // 再次检查是否超出限制
        if (newUpper > limitMax) {
            newUpper = limitMax;
        }
    }
    
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
        
        // 如果有波形数据，计算调整后的时间数据（用于X轴缩放限制）
        QVector<double> adjustedTimes;
        if (!plotTimes.isEmpty()) {
            adjustedTimes = plotTimes;
            double timeOffset = adjustedTimes.first();
            for (int i = 0; i < adjustedTimes.size(); ++i) {
                adjustedTimes[i] -= timeOffset;
            }
        }

        if (mods & Qt::ShiftModifier) {
            // Y轴缩放：无限制
            scaleYAxis(customPlot, factor, we->position().toPoint());
        } else if (mods & Qt::ControlModifier) {
            // X轴缩放：有数据时限制范围，无数据时不限制
            if (!adjustedTimes.isEmpty()) {
                scaleXAxis(customPlot, factor, we->position().toPoint(), adjustedTimes);
            } else {
                // 无数据时，使用简单的无限制缩放
                auto range = customPlot->xAxis->range();
                double span = (range.upper - range.lower) * factor;
                double newLower = 0.0;
                double newUpper = newLower + span;
                customPlot->xAxis->setRange(newLower, newUpper);
            }
        } else {
            // 同时缩放X和Y轴
            if (!adjustedTimes.isEmpty()) {
                scaleXAxis(customPlot, factor, we->position().toPoint(), adjustedTimes);
            } else {
                // 无数据时，X轴使用简单的无限制缩放
                auto range = customPlot->xAxis->range();
                double span = (range.upper - range.lower) * factor;
                double newLower = 0.0;
                double newUpper = newLower + span;
                customPlot->xAxis->setRange(newLower, newUpper);
            }
            scaleYAxis(customPlot, factor, we->position().toPoint());
        }

        customPlot->replot();
        return true; // 事件已处理
    }

    return QMainWindow::eventFilter(obj, event);
}

/**
 * @brief 分析结果就绪槽（空实现，供用户自行填充）
 * @param result 波形分析结果
 */
void shiboqi_remake::onAnalysisReady(const WaveformAnalysisResult &result)
{
    // 更新UI上显示的分析结果（频率、幅度、峰峰值、最大值）
    // 频率：Hz，保留2位小数；幅度/峰峰值/最大值：V，保留3位小数
    if (!ui) return;

    // frequency
    QString freqText = QString("%1 Hz").arg(QString::number(result.frequency, 'f', 2));
    ui->Frequency_in->setText(freqText);

    // amplitude (label_12 在 UI 中用于显示幅度)
    QString ampText = QString("%1 V").arg(QString::number(result.amplitude, 'f', 3));
    ui->Amplitude_in->setText(ampText);

    // peak-to-peak
    QString vppText = QString("%1 V").arg(QString::number(result.peakToPeak, 'f', 3));
    ui->VPP_in->setText(vppText);

    // Vmax
    QString vmaxText = QString("%1 V").arg(QString::number(result.maxValue, 'f', 3));
    ui->V_MAX_in->setText(vmaxText);
}
