#include "shiboqi_remake.h"
#include "ui_shiboqi_remake.h"
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <cmath>
#include <algorithm>
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include "siprefixticker.h"
#include <QOpenGLWidget>
#include <QSerialPortInfo>


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
    , dataProcessorThread(new DataProcessorThread(this)) // 创建数据处理线程
    , dataProcessor(nullptr) // 稍后从线程对象获取
    , currentWaveformType(0) // 初始化为锯齿波
    , isHandDrawMode(false)  // 初始化手绘模式为关闭
    , isDrawing(false)       // 初始化绘制状态为未绘制
    , waveformSenderThread(nullptr) // 初始化线程指针为空
    , uartReceiver(new UARTReceiver(this)) // 创建UART接收器对象
    , isOscilloscopePageActive(true)  // 初始页面为示波器
    , isSpectrumPageActive(false)     // 频谱页面初始未激活
    , hasUserZoomed(false)            // 初始未手动缩放，允许自动缩放
{
    ui->setupUi(this);

    // 启动数据处理线程
    dataProcessorThread->start();
    dataProcessor = dataProcessorThread->getProcessor();

    // 创建数据处理器并连接信号（跨线程信号连接，自动使用队列连接）
    // 修正：使用processWaveformData槽函数接收UDP数据
    connect(udpReceiver, &UdpReceiver::dataReceived, dataProcessor, &DataProcessor::processWaveformData);
    connect(dataProcessor, &DataProcessor::analysisReady, this, &shiboqi_remake::onAnalysisReady);
    connect(dataProcessor, &DataProcessor::downsampledDataReady, this, &shiboqi_remake::onDownsampledDataReady);
    
    qDebug() << "主窗口线程ID：" << QThread::currentThreadId();
    qDebug() << "DataProcessor 已在独立线程中运行，避免阻塞GUI";

    // 初始化示波器
    customPlot = ui->customPlot_2;

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
    
    // 设置更新定时器
    connect(updateTimer, &QTimer::timeout, this, &shiboqi_remake::updatePlot);
    updateTimer->start(50); // 20fps更新

    // 连接设置按钮的点击信号到槽函数
    connect(ui->setButton_4, &QPushButton::clicked, this, &shiboqi_remake::on_setButton_clicked);

    // 连接监听按钮的切换信号到槽函数
    connect(ui->listenButton_4, &QPushButton::toggled, this, &shiboqi_remake::on_listenButton_toggled);

    // 连接循环发送按钮的切换信号到槽函数
    connect(ui->loopSendButton_4, &QPushButton::toggled, this, &shiboqi_remake::on_loopSendButton_toggled);

    // 连接发送采集命令按钮的点击信号到槽函数
    connect(ui->restartButton_4, &QPushButton::clicked, this, &shiboqi_remake::on_restartButton_clicked);

    // 连接UDP绑定失败信号到错误处理槽函数
    connect(udpReceiver, &UdpReceiver::bindFailed, this, &shiboqi_remake::onUdpBindFailed);

    // 连接数据个数输入框的值变化信号，自动更新 UdpReceiver 的期望数据个数
    connect(ui->dataNumSpinBox_4, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
        udpReceiver->setExpectedDataCount(static_cast<quint32>(value));
        qDebug() << "示波器页面：数据个数已更新为" << value;
    });
    
    // 初始化时设置一次期望数据个数
    if (ui->dataNumSpinBox_4) {
        udpReceiver->setExpectedDataCount(static_cast<quint32>(ui->dataNumSpinBox_4->value()));
    }

    // --- 侧边栏导航按钮：切换不同页面（示波器 / DDS 设置 / 数字信号测量 / 频谱）
    
    // 示波器按钮
    connect(ui->navButton_oscilloscope, &QPushButton::clicked, this, [this]() {
        // 先设置页面激活状态，立即停止其他页面的更新
        isOscilloscopePageActive = true;
        isSpectrumPageActive = false;
        
        // 重置手动缩放标志，重新启用自动缩放
        hasUserZoomed = false;
        
        // 停止频谱数据标签更新定时器
        if (spectrumLabelUpdateTimer) spectrumLabelUpdateTimer->stop();
        
        ui->stackedWidget->setCurrentIndex(0); // 示波器 -> page_5
        // 取消其他按钮的选中状态
        ui->navButton_dds->setChecked(false);
        ui->navButton_digital->setChecked(false);
        ui->navButton_spectrum->setChecked(false);
        ui->navButton_oscilloscope->setChecked(true);
        
        // 启动 page_5 的更新定时器
        if (updateTimer) updateTimer->start(50);
        // 强制刷新 page_5 示波器的坐标轴标签
        if (customPlot) {
            customPlot->xAxis->setLabel("Time (us)");
            customPlot->yAxis->setLabel("Voltage (V)");
            
            // 修正X轴范围，确保零点在左下角
            auto xRange = customPlot->xAxis->range();
            if (xRange.lower < 0) {
                // 如果下界小于0，强制修正为从0开始
                double span = xRange.upper - xRange.lower;
                customPlot->xAxis->setRange(0.0, span);
            }
            
            customPlot->replot();
        }
    });
    
    // DDS设置按钮
    connect(ui->navButton_dds, &QPushButton::clicked, this, [this]() {
        // 先设置页面激活状态
        isOscilloscopePageActive = false;
        isSpectrumPageActive = false;
        
        ui->stackedWidget->setCurrentIndex(1); // DDS设置 -> page_6
        // 取消其他按钮的选中状态
        ui->navButton_oscilloscope->setChecked(false);
        ui->navButton_digital->setChecked(false);
        ui->navButton_spectrum->setChecked(false);
        ui->navButton_dds->setChecked(true);
        
        // 停止示波器更新定时器
        if (updateTimer) updateTimer->stop();
        
        // 保持手绘波形显示（不清空，确保切换回来时能看到）
        if (ui->boxingxianshi) {
            ui->boxingxianshi->replot();
        }
    });
    
    // 数字信号测量按钮
    connect(ui->navButton_digital, &QPushButton::clicked, this, [this]() {
        // 先设置页面激活状态，立即停止其他页面更新
        isOscilloscopePageActive = false;
        isSpectrumPageActive = false;
        
        ui->stackedWidget->setCurrentIndex(2); // 数字信号测量 -> page_7
        // 取消其他按钮的选中状态
        ui->navButton_oscilloscope->setChecked(false);
        ui->navButton_dds->setChecked(false);
        ui->navButton_spectrum->setChecked(false);
        ui->navButton_digital->setChecked(true);
        
        // 停止所有绘图更新定时器（非当前页面）
        if (updateTimer) updateTimer->stop();
    });
    
    // 频谱分析按钮
    connect(ui->navButton_spectrum, &QPushButton::clicked, this, [this]() {
        // 先设置页面激活状态，立即停止其他页面更新
        isOscilloscopePageActive = false;
        isSpectrumPageActive = true;
        
        ui->stackedWidget->setCurrentIndex(3); // 频谱 -> page_8
        // 取消其他按钮的选中状态
        ui->navButton_oscilloscope->setChecked(false);
        ui->navButton_dds->setChecked(false);
        ui->navButton_digital->setChecked(false);
        ui->navButton_spectrum->setChecked(true);
        
        // 停止 page_5 的更新定时器（page_8 通过信号更新，不需要定时刷新）
        if (updateTimer) updateTimer->stop();
        // 启动频谱数据标签更新定时器（减少跳动）
        if (spectrumLabelUpdateTimer) spectrumLabelUpdateTimer->start();
        
        // 强制刷新 page_8 频谱的坐标轴标签
        if (customPlot_page8) {
            customPlot_page8->xAxis->setLabel("Frequency (Hz)");
            customPlot_page8->yAxis->setLabel("Amplitude (V)");
            customPlot_page8->replot();
        }
    });

    // 初始化串口comboBox
    auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) ui->comboBox->addItem(info.portName());

    // 启动定时器每秒刷新串口列表
    portRefreshTimer = new QTimer(this);
    portRefreshTimer->setInterval(1000);
    connect(portRefreshTimer, &QTimer::timeout, this, &shiboqi_remake::refreshSerialPorts);
    portRefreshTimer->start();

    // 连接串口连接按钮的切换信号到槽函数
    connect(ui->pushButton_2, &QPushButton::toggled, this, &shiboqi_remake::on_pushButton_2_toggled);

    // 连接UART解析后信号到界面刷新槽（每200ms）
    connect(uartReceiver, &UARTReceiver::parsedDataReady, this, &shiboqi_remake::onParsedSerialData);

    // ===== 初始化 page_8 频谱页面（用于频谱显示，不包含示波器时域逻辑） =====
    customPlot_page8 = ui->customPlot_3;
    errorDialogShown_page8 = false;

    // 仅开启 OpenGL 加速并保留为绘图控件，但不添加时域 graph（频谱绘制在需要时创建）
    customPlot_page8->setOpenGl(true);
    customPlot_page8->setInteractions(QCP::iNone);  // 禁用所有交互，包括缩放

    // 连接 page_8 的按钮信号（保持功能不变）
    // connect(ui->setButton_5, &QPushButton::clicked, this, &shiboqi_remake::on_setButton_5_clicked);
    // connect(ui->listenButton_5, &QPushButton::toggled, this, &shiboqi_remake::on_listenButton_5_toggled);
    // connect(ui->loopSendButton_5, &QPushButton::toggled, this, &shiboqi_remake::on_loopSendButton_5_toggled);
    // connect(ui->restartButton_5, &QPushButton::clicked, this, &shiboqi_remake::on_restartButton_5_clicked);

    // 连接 dataProcessor 的分析结果（page_5 使用 onAnalysisReady）

    // ===== 初始化频谱分析器（多线程架构） =====
    spectrumThread = new QThread(this);
    spectrumAnalyzer = new SpectrumAnalyzer();
    spectrumAnalyzer->moveToThread(spectrumThread);
    spectrumThread->start();
    
    qDebug() << "频谱分析器已在独立线程中运行，避免FFT阻塞GUI";
    
    // 设置频谱分析器参数
    spectrumAnalyzer->setSampleRate(udpReceiver->getSampleRate());
    
    // 连接 UDP 数据到频谱分析器（跨线程，自动队列连接）
    connect(udpReceiver, &UdpReceiver::dataReceived, spectrumAnalyzer, &SpectrumAnalyzer::onDataReceived);
    
    // 连接频谱分析结果到 UI 更新槽（跨线程，自动队列连接）
    connect(spectrumAnalyzer, &SpectrumAnalyzer::spectrumReady, this, &shiboqi_remake::onSpectrumReady);
    
    // 初始化 page_5 到 page_8 的设置同步定时器（每 500ms 同步一次）
    settingsSyncTimer = new QTimer(this);
    settingsSyncTimer->setInterval(500);
    connect(settingsSyncTimer, &QTimer::timeout, this, &shiboqi_remake::syncSettingsToPage8);
    
    // 初始化频谱数据标签更新定时器（每 500ms 更新一次，减少跳动）
    spectrumLabelUpdateTimer = new QTimer(this);
    spectrumLabelUpdateTimer->setInterval(500);
    connect(spectrumLabelUpdateTimer, &QTimer::timeout, this, [this]() {
        if (isSpectrumPageActive && ui) {
            // 更新所有频谱数据标签
            if (ui->Frequency_in_3) {
                ui->Frequency_in_3->setText(QString("%1 Hz").arg(QString::number(lastSpectrumResult.dominantFrequency, 'f', 2)));
            }
            if (ui->Amplitude_in_3) {
                ui->Amplitude_in_3->setText(QString("%1 V").arg(QString::number(lastSpectrumResult.dominantAmplitude, 'f', 3)));
            }
            if (ui->label_snr_value) {
                ui->label_snr_value->setText(QString("%1 dB").arg(QString::number(lastSpectrumResult.snr, 'f', 1)));
            }
            if (ui->label_thd_value) {
                ui->label_thd_value->setText(QString("%1 %").arg(QString::number(lastSpectrumResult.thd, 'f', 2)));
            }
            if (ui->label_bandwidth_value) {
                double bw = lastSpectrumResult.bandwidth;
                QString bwText;
                if (bw >= 1e6) {
                    bwText = QString("%1 MHz").arg(QString::number(bw / 1e6, 'f', 2));
                } else if (bw >= 1e3) {
                    bwText = QString("%1 kHz").arg(QString::number(bw / 1e3, 'f', 2));
                } else {
                    bwText = QString("%1 Hz").arg(QString::number(bw, 'f', 1));
                }
                ui->label_bandwidth_value->setText(bwText);
            }
            if (ui->label_harmonics_value) {
                ui->label_harmonics_value->setText(QString::number(lastSpectrumResult.harmonicCount));
            }
        }
    });
    
    settingsSyncTimer->start();
    
    // ===== 初始化 DDS 手绘波形功能 (boxingxianshi) =====
    if (ui->boxingxianshi) {
        QCustomPlot *drawPlot = ui->boxingxianshi;
        
        // 设置基本属性
        drawPlot->setOpenGl(true);
        
        // 添加一个graph用于显示手绘轨迹
        drawPlot->addGraph();
        drawPlot->graph(0)->setPen(QPen(Qt::red, 2));
        
        // 设置坐标轴范围 (X: 0-1, Y: 0-1023)
        drawPlot->xAxis->setRange(0.0, 1.0);
        drawPlot->yAxis->setRange(0.0, 1023.0);
        drawPlot->xAxis->setLabel("Time (normalized)");
        drawPlot->yAxis->setLabel("Voltage (10-bit)");
        
        // 启用鼠标跟踪（以便在移动时也能捕获事件）
        drawPlot->setMouseTracking(true);
        
        // 禁用默认交互
        drawPlot->setInteractions(QCP::iNone);
        
        // 安装事件过滤器以捕获鼠标事件
        drawPlot->installEventFilter(this);
    }
}

/**
 * @brief 析构函数实现
 *
 * 释放UI界面资源。UdpReceiver实例由于设置了this为父对象，会自动被删除。
 */
shiboqi_remake::~shiboqi_remake()
{
    // 停止并清理数据处理线程（使用封装的stop方法）
    if (dataProcessorThread) {
        dataProcessorThread->stop();
    }
    
    // 停止并清理频谱分析线程
    if (spectrumThread) {
        spectrumThread->quit();
        spectrumThread->wait();
    }
    
    // 删除频谱分析器（在线程停止后）
    if (spectrumAnalyzer) {
        delete spectrumAnalyzer;
        spectrumAnalyzer = nullptr;
    }
    
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
    QString ipText = ui->ipLineEdit_4->text();

    // 获取用户选择的端口号
    quint16 port = ui->portSpinBox_4->value();

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
    QString targetIpText = ui->targetIpLineEdit_4->text();
    quint16 targetPort = ui->targetPortSpinBox_4->value();
    QHostAddress targetAddress(targetIpText);
    if (!targetAddress.isNull()) {
        udpSender->setTargetAddress(targetAddress, targetPort);
    }

    // 设置UDP发送器的数据个数、分频系数和通道（固定值）
    quint32 dataNum = ui->dataNumSpinBox_4->value();
    quint32 divider = 0;  // 固定为0
    quint8 channel = 1;   // 固定为通道1
    udpSender->setDataNum(dataNum);
    udpSender->setDivider(divider);
    udpSender->setChannel(channel);
    
    // ========== 新增：配置数据处理器的采样参数（智能低频支持）==========
    dataProcessor->setSamplingConfig(dataNum, udpReceiver->getSampleRate());
    
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
        
        // 获取分频系数并计算实际采样率
        quint32 divider = udpSender->getDivider();
        quint32 dataNum = udpSender->getDataNum();
        const double BASE_SAMPLE_RATE = 50000000.0; // 50MHz 基础采样率
        double actualSampleRate = BASE_SAMPLE_RATE / (divider+1);
        
        // 配置 UDP 接收器的采样率
        udpReceiver->setSampleRate(actualSampleRate);
        
        // 配置数据处理器的采样配置
        QMetaObject::invokeMethod(dataProcessor, "setSamplingConfig", Qt::QueuedConnection,
                                 Q_ARG(quint32, dataNum),
                                 Q_ARG(double, actualSampleRate));
        
        qDebug() << "启动监听 - 分频系数:" << divider 
                 << ", 数据个数:" << dataNum
                 << ", 实际采样率:" << actualSampleRate << "Hz";
        
        // 开始监听UDP数据
        udpSender->sendStopLoopCommand();

        udpReceiver->startListening();
        ui->listenButton_4->setText("停止监听");
        
        // 禁用设置按钮，防止在监听期间修改参数
        ui->setButton_4->setEnabled(false);
        ui->ipLineEdit_4->setEnabled(false);
        ui->portSpinBox_4->setEnabled(false);
        ui->targetIpLineEdit_4->setEnabled(false);
        ui->targetPortSpinBox_4->setEnabled(false);
        ui->dataNumSpinBox_4->setEnabled(false);
        // 注意：通道和分频系数输入框已删除，不再需要禁用
        
        // 同步 page_8 的监听按钮状态
        ui->listenButton_5->blockSignals(true);
        ui->listenButton_5->setChecked(true);
        ui->listenButton_5->setText("停止监听");
        ui->listenButton_5->blockSignals(false);
    } else {
        // 停止监听UDP数据
        udpSender->sendStopLoopCommand();
        udpReceiver->stopListening();
        
        // 线程安全的重置数据处理器（通过信号槽机制跨线程调用）
        QMetaObject::invokeMethod(dataProcessor, "reset", Qt::QueuedConnection);
        
        ui->listenButton_4->setText("开始监听");
        
        // 重新启用设置按钮和输入控件
        ui->setButton_4->setEnabled(true);
        ui->ipLineEdit_4->setEnabled(true);
        ui->portSpinBox_4->setEnabled(true);
        ui->targetIpLineEdit_4->setEnabled(true);
        ui->targetPortSpinBox_4->setEnabled(true);
        ui->dataNumSpinBox_4->setEnabled(true);
        // 注意：通道和分频系数输入框已删除，不再需要启用
        
        // 同步 page_8 的监听按钮状态
        ui->listenButton_5->blockSignals(true);
        ui->listenButton_5->setChecked(false);
        ui->listenButton_5->setText("开始监听");
        ui->listenButton_5->blockSignals(false);
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
        ui->listenButton_4->blockSignals(true);
        ui->listenButton_4->setChecked(false);
        ui->listenButton_4->setText("开始监听");
        ui->listenButton_4->blockSignals(false);
        
        // 同步 page_8 的监听按钮状态
        ui->listenButton_5->blockSignals(true);
        ui->listenButton_5->setChecked(false);
        ui->listenButton_5->setText("开始监听");
        ui->listenButton_5->blockSignals(false);

        // 重新启用设置控件，因为监听失败了
        ui->setButton_4->setEnabled(true);
        ui->ipLineEdit_4->setEnabled(true);
        ui->portSpinBox_4->setEnabled(true);
        ui->targetIpLineEdit_4->setEnabled(true);
        ui->targetPortSpinBox_4->setEnabled(true);
        ui->dataNumSpinBox_4->setEnabled(true);
        // 注意：通道和分频系数输入框已删除，不再需要启用

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
        ui->loopSendButton_4->setText("停止循环发送");
        
        // 同步 page_8 的循环发送按钮状态
        ui->loopSendButton_5->blockSignals(true);
        ui->loopSendButton_5->setChecked(true);
        ui->loopSendButton_5->setText("停止循环发送");
        ui->loopSendButton_5->blockSignals(false);
    } else {
        // 停止循环发送
        dataProcessor->reset();
        udpSender->sendStopLoopCommand();
        ui->loopSendButton_4->setText("循环发送");
        
        // 同步 page_8 的循环发送按钮状态
        ui->loopSendButton_5->blockSignals(true);
        ui->loopSendButton_5->setChecked(false);
        ui->loopSendButton_5->setText("循环发送");
        ui->loopSendButton_5->blockSignals(false);
    }
}

/**
 * @brief 发送采集命令按钮点击处理函数
 *
 * 发送重新启动采集命令。
 */
void shiboqi_remake::on_restartButton_clicked()
{   
    // 重置手动缩放标志，重新启用自动缩放
    hasUserZoomed = false;
    
    udpSender->sendRestartCommand();
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
    // LIFO队列模式：直接替换为最新数据（后进先出，丢弃旧数据）
    plotVoltages = voltages;
    plotTimes = times;
    
    qDebug() << "[波形队列] 收到最新数据：" << voltages.size() << "点（LIFO模式：自动丢弃旧数据）";
    
    // 仅在用户未手动缩放时自动缩放坐标轴到数据范围
    if (!hasUserZoomed && !plotVoltages.isEmpty() && !plotTimes.isEmpty()) {
        // 计算时间范围（使用调整后的时间，即从0开始）
        double minT = 0.0;  // 第一个点的时间为0
        double maxT = times.last() - times.first();  // 最后一个点相对于第一个点的时间
        
        // 不调整Y轴范围（保持用户设置的电压范围）
        
        // X轴：正常设置范围，但确保下界为0（零点固定在左下角）
        double tMargin = (maxT - minT) * 0.1;
        if (tMargin < 0.01) tMargin = 1.0;  // 防止范围过小时边距为0
        customPlot->xAxis->setRange(0.0, maxT + tMargin);  // 下界固定为0
    }
}

/**
 * @brief 更新波形图（使用降采样数据）
 *
 * 使用 DataProcessor 提供的降采样数据进行高效绘图
 * 波形起点固定在坐标原点(0,0)，不自动调整坐标轴范围
 */
void shiboqi_remake::updatePlot()
{
    // 性能优化：只在示波器页面激活时更新
    if (!isOscilloscopePageActive) {
        return;
    }
    
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
    
    // 重绘图表
    customPlot->replot();
}

/**
 * @brief 按因子缩放 Y 轴范围（保持0刻度在中心）
 *
 * @param plot 指定的 QCustomPlot
 * @param factor 缩放因子（<1 放大，>1 缩小）
 * @param pos 鼠标位置（当前实现未使用）
 * 
 * Y轴始终以0为中心对称缩放，确保0刻度线保持在屏幕中间
 */
void scaleYAxis(QCustomPlot *plot, double factor, const QPoint &/*pos*/) {
    auto range = plot->yAxis->range();
    // 计算当前范围相对于0的最大偏移（取上下边界绝对值的最大值）
    double maxOffset = qMax(qAbs(range.upper), qAbs(range.lower));
    // 按因子缩放偏移量
    double newMaxOffset = maxOffset * factor;
    // 设置对称范围：[-newMaxOffset, +newMaxOffset]
    plot->yAxis->setRange(-newMaxOffset, newMaxOffset);
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
    // ===== 处理 DDS 手绘波形的鼠标事件 =====
    if (obj == ui->boxingxianshi && isHandDrawMode) {
        QCustomPlot *drawPlot = ui->boxingxianshi;
        
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *me = static_cast<QMouseEvent *>(event);
            if (me->button() == Qt::LeftButton) {
                // 开始绘制
                isDrawing = true;
                handDrawnPoints.clear();
                
                // 将鼠标坐标转换为绘图坐标
                double x = drawPlot->xAxis->pixelToCoord(me->pos().x());
                double y = drawPlot->yAxis->pixelToCoord(me->pos().y());
                
                // 限制在有效范围内
                x = qBound(0.0, x, 1.0);
                y = qBound(0.0, y, 1023.0);
                
                handDrawnPoints.append(QPointF(x, y));
                return true;
            }
        } else if (event->type() == QEvent::MouseMove && isDrawing) {
            QMouseEvent *me = static_cast<QMouseEvent *>(event);
            
            // 将鼠标坐标转换为绘图坐标
            double x = drawPlot->xAxis->pixelToCoord(me->pos().x());
            double y = drawPlot->yAxis->pixelToCoord(me->pos().y());
            
            // 限制在有效范围内
            x = qBound(0.0, x, 1.0);
            y = qBound(0.0, y, 1023.0);
            
            handDrawnPoints.append(QPointF(x, y));
            
            // 实时更新显示
            QVector<double> xs, ys;
            for (const QPointF &p : handDrawnPoints) {
                xs.append(p.x());
                ys.append(p.y());
            }
            
            if (drawPlot->graphCount() > 0) {
                drawPlot->graph(0)->setData(xs, ys);
                drawPlot->replot();
            }
            
            return true;
        } else if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *me = static_cast<QMouseEvent *>(event);
            if (me->button() == Qt::LeftButton && isDrawing) {
                // 结束绘制
                isDrawing = false;
                qDebug() << "手绘波形已完成，共" << handDrawnPoints.size() << "个点，点击'保存并发送'按钮以发送波形";
                
                return true;
            }
        }
    }
    
    // 仅支持 page_5 (示波器) 的 customPlot 滚轮缩放
    // page_8 (频谱图) 不支持鼠标缩放
    QCustomPlot *targetPlot = nullptr;
    QVector<double> *targetTimes = nullptr;

    if (obj == customPlot && event->type() == QEvent::Wheel) {
        targetPlot = customPlot;
        targetTimes = &plotTimes;
    }

    if (targetPlot && event->type() == QEvent::Wheel) {
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
        if (targetTimes && !targetTimes->isEmpty()) {
            adjustedTimes = *targetTimes;
            double timeOffset = adjustedTimes.first();
            for (int i = 0; i < adjustedTimes.size(); ++i) {
                adjustedTimes[i] -= timeOffset;
            }
        }

        if (mods & Qt::ShiftModifier) {
            // Y轴缩放：无限制
            scaleYAxis(targetPlot, factor, we->position().toPoint());
        } else if (mods & Qt::ControlModifier) {
            // X轴缩放：有数据时限制范围，无数据时不限制
            if (!adjustedTimes.isEmpty()) {
                scaleXAxis(targetPlot, factor, we->position().toPoint(), adjustedTimes);
            } else {
                // 无数据时，使用简单的无限制缩放
                auto range = targetPlot->xAxis->range();
                double span = (range.upper - range.lower) * factor;
                double newLower = 0.0;
                double newUpper = newLower + span;
                targetPlot->xAxis->setRange(newLower, newUpper);
            }
        } else {
            // 同时缩放X和Y轴
            if (!adjustedTimes.isEmpty()) {
                scaleXAxis(targetPlot, factor, we->position().toPoint(), adjustedTimes);
            } else {
                // 无数据时，X轴使用简单的无限制缩放
                auto range = targetPlot->xAxis->range();
                double span = (range.upper - range.lower) * factor;
                double newLower = 0.0;
                double newUpper = newLower + span;
                targetPlot->xAxis->setRange(newLower, newUpper);
            }
            scaleYAxis(targetPlot, factor, we->position().toPoint());
        }

        // 如果是示波器页面的缩放，标记用户已手动缩放（禁用自动缩放）
        if (targetPlot == customPlot) {
            hasUserZoomed = true;
        }

        targetPlot->replot();
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
    ui->Frequency_in_2->setText(freqText);

    // amplitude (label_12 在 UI 中用于显示幅度)
    QString ampText = QString("%1 V").arg(QString::number(result.amplitude, 'f', 3));
    ui->Amplitude_in_2->setText(ampText);

    // peak-to-peak
    QString vppText = QString("%1 V").arg(QString::number(result.peakToPeak, 'f', 3));
    ui->VPP_in_2->setText(vppText);

    // Vmax
    QString vmaxText = QString("%1 V").arg(QString::number(result.maxValue, 'f', 3));
    ui->V_MAX_in_2->setText(vmaxText);
}

/**
 * @brief 波形切换按钮点击槽函数
 */
void shiboqi_remake::on_waveformSwitchButton_clicked()
{
    // 循环切换波形类型：0->1->2->3->0...
    currentWaveformType = (currentWaveformType + 1) % 4;
    
    // 设置波形类型并发送命令
    udpSender->setWaveformType(currentWaveformType);
    udpSender->sendWaveformCommand();
    
    // 更新右侧标签显示当前波形
    QString waveformNames[] = {"锯齿波", "正弦波", "方波", "三角波"};
    QString waveformEmojis[] = {"📐", "〰️", "▭", "🔺"};
    
    if (ui && ui->currentWaveformLabel) {
        ui->currentWaveformLabel->setText(
            QString("当前波形: %1 %2").arg(waveformEmojis[currentWaveformType]).arg(waveformNames[currentWaveformType])
        );
    }
    
    qDebug() << "切换到波形：" << waveformNames[currentWaveformType] << "(" << currentWaveformType << ")";
}

/**
 * @brief 频率加按钮点击槽函数
 */
void shiboqi_remake::on_frequencyUpButton_clicked()
{
    udpSender->sendFrequencyUpCommand();
    qDebug() << "发送频率增加命令";
}

/**
 * @brief 频率减按钮点击槽函数
 */
void shiboqi_remake::on_frequencyDownButton_clicked()
{
    udpSender->sendFrequencyDownCommand();
    qDebug() << "发送频率减少命令";
}

/**
 * @brief 幅度加按钮点击槽函数
 */
void shiboqi_remake::on_amplitudeUpButton_clicked()
{
    udpSender->sendAmplitudeUpCommand();
    qDebug() << "发送幅度增加命令";
}

/**
 * @brief 幅度减按钮点击槽函数
 */
void shiboqi_remake::on_amplitudeDownButton_clicked()
{
    udpSender->sendAmplitudeDownCommand();
    qDebug() << "发送幅度减少命令";
}

/**
 * @brief 串口连接按钮切换槽函数
 * @param checked true表示连接串口，false表示断开串口
 */
void shiboqi_remake::on_pushButton_2_toggled(bool checked)
{
    if (checked) {
        // 获取选中的串口名称
        QString portName = ui->comboBox->currentText();
        if (!portName.isEmpty()) {
            if (uartReceiver->openPort(portName, 115200)) {
                qDebug() << "串口" << portName << "连接成功";
            } else {
                qDebug() << "串口" << portName << "连接失败";
                // 连接失败时，将按钮状态设置为未按下
                ui->pushButton_2->blockSignals(true);
                ui->pushButton_2->setChecked(false);
                ui->pushButton_2->blockSignals(false);
            }
        }
    } else {
        // 断开串口连接
        uartReceiver->closePort();
        qDebug() << "串口连接已断开";
    }
}

/**
 * @brief 串口解析后数据到达槽函数
 */
void shiboqi_remake::onParsedSerialData(int duty, int highTime, int lowTime, double frequency)
{
    if (!ui) return;

    // 更新频率文本，保留0位小数（Hz）
    ui->pinglv_in->setText(QString("%1 Hz").arg(QString::number(frequency, 'f', 0)));

    // 占空比直接显示
    ui->zhankongbi_in->setText(QString::number(duty));

    // 高/低电平时间显示为 us
    ui->Hvolt_t_in->setText(QString("%1 us").arg(QString::number(highTime)));
    ui->Lvolt_t_in->setText(QString("%1 us").arg(QString::number(lowTime)));

    // 在 shuzixinhaoboxing 上绘制一周期数字波形（以高/低时间为微秒单位）
    if (ui->shuzixinhaoboxing) {
        QCustomPlot *plot = ui->shuzixinhaoboxing;

        // 计算周期（微秒）
        double period = static_cast<double>(highTime + lowTime);
        if (period <= 0.0) {
            // 清空数据
            if (plot->graphCount() > 0) plot->graph(0)->setData(QVector<double>(), QVector<double>());
            plot->replot();
        } else {
            // 构造阶跃波形点：0->highTime (高), highTime->period (低)
            QVector<double> xs, ys;
            // Start high at t=0
            xs << 0.0 << static_cast<double>(highTime) << static_cast<double>(highTime) << period;
            ys << 1.0 << 1.0 << 0.0 << 0.0;

            if (plot->graphCount() == 0) plot->addGraph();
            plot->graph(0)->setData(xs, ys);
            plot->graph(0)->setPen(QPen(Qt::green));
            plot->xAxis->setLabel("Time (us)");
            plot->yAxis->setLabel("Logic");
            plot->xAxis->setRange(0, period);
            plot->yAxis->setRange(-0.2, 1.2);
            plot->replot();
        }
    }
}

void shiboqi_remake::refreshSerialPorts()
{
    // 获取当前可用端口名集合
    QList<QString> names;
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) names.append(info.portName());

    // 保存当前选择
    QString current = ui->comboBox->currentText();

    // 如果下拉列表为空但现在有端口，或有变化，刷新整个列表
    bool changed = false;
    if (ui->comboBox->count() != names.size()) changed = true;
    else {
        for (int i = 0; i < names.size(); ++i) {
            if (ui->comboBox->itemText(i) != names.at(i)) { changed = true; break; }
        }
    }

    if (changed) {
        ui->comboBox->blockSignals(true);
        ui->comboBox->clear();
        for (const QString &n : names) ui->comboBox->addItem(n);
        // 恢复选择到之前的项（如果仍然存在）
        int idx = ui->comboBox->findText(current);
        if (idx >= 0) ui->comboBox->setCurrentIndex(idx);
        ui->comboBox->blockSignals(false);
    }

    // 如果当前已经打开的串口不再存在，则关闭串口并复位按钮
    if (!openPortName.isEmpty() && !names.contains(openPortName)) {
        // 关闭串口
        if (uartReceiver && uartReceiver->isOpen()) uartReceiver->closePort();
        openPortName.clear();
        // 将按钮设置为未按下状态（阻止信号以免递归）
        ui->pushButton_2->blockSignals(true);
        ui->pushButton_2->setChecked(false);
        ui->pushButton_2->blockSignals(false);
        qDebug() << "已移除打开的串口，已关闭连接";
    }
}

/**
 * @brief 设置按钮（页面8）点击处理函数
 *
 * 从 page_8 的 IP/端口和目标地址输入中读取用户设置，
 * 并把相应参数传递给 UDP 发送/接收器。
 * 同时将 dataNum 用于设置频谱分析器的目标点数。
 */
void shiboqi_remake::on_setButton_5_clicked()
{
    QString ipText = ui->ipLineEdit_5->text();
    quint16 port = ui->portSpinBox_5->value();
    QHostAddress address(ipText);

    if (address.isNull()) return;

    udpReceiver->setLocalAddress(address, port);

    QString targetIpText = ui->targetIpLineEdit_5->text();
    quint16 targetPort = ui->targetPortSpinBox_5->value();
    QHostAddress targetAddress(targetIpText);
    if (!targetAddress.isNull()) {
        udpSender->setTargetAddress(targetAddress, targetPort);
    }

    quint32 dataNum = ui->dataNumSpinBox_5->value();
    quint32 divider = 0;  // 固定为0
    quint8 channel = 1;   // 固定为通道1
    udpSender->setDataNum(dataNum);
    udpSender->setDivider(divider);
    udpSender->setChannel(channel);
    
    // ========== 新增：配置数据处理器的采样参数 ==========
    dataProcessor->setSamplingConfig(dataNum, udpReceiver->getSampleRate());
    
    udpSender->sendChannelSelectCommand();
    udpSender->sendDataNumCommand();
    udpSender->sendDividerCommand();

    // 设置频谱分析器的目标数据点数量
    if (spectrumAnalyzer) spectrumAnalyzer->setTargetDataCount(dataNum);
}

/**
 * @brief 监听按钮（页面8）切换处理函数
 *
 * 控制 page_8 的 UDP 监听启停：开始时调用 on_setButton_5_clicked()
 * 并重置频谱分析器；停止时停止接收并重置 UI 控件状态。
 */
void shiboqi_remake::on_listenButton_5_toggled(bool checked)
{
    if (checked) {
        on_setButton_5_clicked();
        
        // 获取分频系数并计算实际采样率
        quint32 divider = udpSender->getDivider();
        quint32 dataNum = udpSender->getDataNum();
        const double BASE_SAMPLE_RATE = 50000000.0; // 50MHz 基础采样率
        double actualSampleRate = BASE_SAMPLE_RATE / (divider+1);
        
        // 配置 UDP 接收器的采样率
        udpReceiver->setSampleRate(actualSampleRate);
        
        // 配置数据处理器的采样配置
        QMetaObject::invokeMethod(dataProcessor, "setSamplingConfig", Qt::QueuedConnection,
                                 Q_ARG(quint32, dataNum),
                                 Q_ARG(double, actualSampleRate));
        
        qDebug() << "启动监听(page_8) - 分频系数:" << divider 
                 << ", 数据个数:" << dataNum
                 << ", 实际采样率:" << actualSampleRate << "Hz";
        
        // 线程安全的频谱分析器reset调用
        if (spectrumAnalyzer) {
            QMetaObject::invokeMethod(spectrumAnalyzer, "reset", Qt::QueuedConnection);
        }
        udpSender->sendStopLoopCommand();
        udpReceiver->startListening();
        ui->listenButton_5->setText("停止监听");

        ui->setButton_5->setEnabled(false);
        ui->ipLineEdit_5->setEnabled(false);
        ui->portSpinBox_5->setEnabled(false);
        ui->targetIpLineEdit_5->setEnabled(false);
        ui->targetPortSpinBox_5->setEnabled(false);
        ui->dataNumSpinBox_5->setEnabled(false);
        // 注意：通道和分频系数输入框已删除，不再需要禁用
        
        // 同步 page_5 的监听按钮状态
        ui->listenButton_4->blockSignals(true);
        ui->listenButton_4->setChecked(true);
        ui->listenButton_4->setText("停止监听");
        ui->listenButton_4->blockSignals(false);
    } else {
        udpSender->sendStopLoopCommand();
        udpReceiver->stopListening();
        dataProcessor->reset();

        ui->listenButton_5->setText("开始监听");

        ui->setButton_5->setEnabled(true);
        ui->ipLineEdit_5->setEnabled(true);
        ui->portSpinBox_5->setEnabled(true);
        ui->targetIpLineEdit_5->setEnabled(true);
        ui->targetPortSpinBox_5->setEnabled(true);
        ui->dataNumSpinBox_5->setEnabled(true);
        // 注意：通道和分频系数输入框已删除，不再需要启用
        
        // 同步 page_5 的监听按钮状态
        ui->listenButton_4->blockSignals(true);
        ui->listenButton_4->setChecked(false);
        ui->listenButton_4->setText("开始监听");
        ui->listenButton_4->blockSignals(false);
    }
}

/**
 * @brief 循环发送按钮（页面8）切换处理函数
 *
 * 启动或停止设备的循环发送功能。
 */
void shiboqi_remake::on_loopSendButton_5_toggled(bool checked)
{
    if (checked) {
        udpSender->sendStartLoopCommand();
        ui->loopSendButton_5->setText("停止循环发送");
        
        // 同步 page_5 的循环发送按钮状态
        ui->loopSendButton_4->blockSignals(true);
        ui->loopSendButton_4->setChecked(true);
        ui->loopSendButton_4->setText("停止循环发送");
        ui->loopSendButton_4->blockSignals(false);
    } else {
        dataProcessor->reset();
        udpSender->sendStopLoopCommand();
        ui->loopSendButton_5->setText("循环发送");
        
        // 同步 page_5 的循环发送按钮状态
        ui->loopSendButton_4->blockSignals(true);
        ui->loopSendButton_4->setChecked(false);
        ui->loopSendButton_4->setText("循环发送");
        ui->loopSendButton_4->blockSignals(false);
    }
}

/**
 * @brief 发送重启采集命令（页面8）
 */
void shiboqi_remake::on_restartButton_5_clicked()
{
    udpSender->sendRestartCommand();
}

/**
 * @brief page_8 的 UDP 绑定失败处理（Doxygen 风格注释）
 *
 * 与 page_5 相同的行为：在短延时后显示错误对话框并重置监听按钮与控件状态。
 */
void shiboqi_remake::onUdpBindFailed_page8(const QString &errorString)
{
    if (errorDialogShown_page8) return;

    errorDialogShown_page8 = true;

    QTimer::singleShot(30, this, [this, errorString]() {
        QMessageBox::critical(this, "UDP绑定失败",
            QString("无法绑定到指定的IP地址和端口。\n\n错误详情：%1\n\n请检查：\n1. IP地址是否正确\n2. 网络连接是否正常\n3. 该IP地址是否存在于本机").arg(errorString),
            QMessageBox::Ok);

        ui->listenButton_5->blockSignals(true);
        ui->listenButton_5->setChecked(false);
        ui->listenButton_5->setText("开始监听");
        ui->listenButton_5->blockSignals(false);
        
        // 同步 page_5 的监听按钮状态
        ui->listenButton_4->blockSignals(true);
        ui->listenButton_4->setChecked(false);
        ui->listenButton_4->setText("开始监听");
        ui->listenButton_4->blockSignals(false);

        ui->setButton_5->setEnabled(true);
        ui->ipLineEdit_5->setEnabled(true);
        ui->portSpinBox_5->setEnabled(true);
        ui->targetIpLineEdit_5->setEnabled(true);
        ui->targetPortSpinBox_5->setEnabled(true);
        ui->dataNumSpinBox_5->setEnabled(true);
        // 注意：通道和分频系数输入框已删除，不再需要启用

        errorDialogShown_page8 = false;
    });
}

/**
 * @brief 频谱分析结果就绪槽函数
 */
void shiboqi_remake::onSpectrumReady(const SpectrumAnalysisResult &result)
{
    if (!ui) return;
    
    // 性能优化：只在频谱页面激活时更新显示
    if (!isSpectrumPageActive) {
        qDebug() << "频谱页面未激活，跳过显示更新（数据已接收）";
        return;
    }

    qDebug() << "收到频谱分析结果：主频率 =" << result.dominantFrequency << "Hz, 幅度 =" << result.dominantAmplitude << "V";

    // 缓存最新的频谱分析结果，由定时器定期更新标签（减少跳动）
    lastSpectrumResult = result;

    // 延时 30ms 后更新频谱图（保持高刷新率），但不更新数据标签
    // 使用 Qt::QueuedConnection 确保在主线程中执行，并且检查页面状态
    QTimer::singleShot(30, this, [this, result]() {
        // 再次检查UI指针和页面激活状态，防止切换页面后崩溃
        if (!ui || !customPlot_page8 || !isSpectrumPageActive) {
            qDebug() << "延时回调时页面已切换，取消频谱更新";
            return;
        }

        // 检查数据有效性
        if (result.frequencies.isEmpty() || result.amplitudes.isEmpty()) {
            qWarning() << "频谱数据为空，跳过绘制";
            return;
        }

        // 在 customPlot_page8 上绘制频谱图（快速刷新）
        if (customPlot_page8 && !result.frequencies.isEmpty()) {
            try {
                // 清空并重新设置图形
                customPlot_page8->clearGraphs();
                customPlot_page8->addGraph();
                
                if (customPlot_page8->graphCount() > 0 && customPlot_page8->graph(0)) {
                    customPlot_page8->graph(0)->setPen(QPen(Qt::red, 2));
                    customPlot_page8->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 50))); // 半透明填充

                    // 设置数据
                    customPlot_page8->graph(0)->setData(result.frequencies, result.amplitudes);

                    // 自动调整坐标轴范围
                    customPlot_page8->xAxis->setLabel("Frequency (Hz)");
                    customPlot_page8->yAxis->setLabel("Amplitude (V)");
                    customPlot_page8->xAxis->setRange(0, result.frequencies.last());
                    
                    // 安全获取最大值
                    auto maxIt = std::max_element(result.amplitudes.begin(), result.amplitudes.end());
                    if (maxIt != result.amplitudes.end()) {
                        customPlot_page8->yAxis->setRange(0, (*maxIt) * 1.1);
                    }

                    // 重绘
                    customPlot_page8->replot();

                    qDebug() << "频谱图已绘制，频率范围：0 -" << result.frequencies.last() << "Hz";
                }
            } catch (const std::exception &e) {
                qWarning() << "频谱绘制异常：" << e.what();
            } catch (...) {
                qWarning() << "频谱绘制未知异常";
            }
        }
    });
}

/**
 * @brief 同步 page_5 和 page_8 的设置参数（智能双向同步）
 * 
 * 逻辑：
 * - 如果当前在 page_5（示波器）：检查 page_5 界面参数是否与 UDP 模块一致
 *   - 不一致：说明用户刚在 page_5 修改，更新 UDP 模块和 page_8
 *   - 一致：不做任何操作，避免覆盖用户正在输入的内容
 * - 如果当前在 page_8（频谱）：检查 page_8 界面参数是否与 UDP 模块一致
 *   - 不一致：说明用户刚在 page_8 修改，更新 UDP 模块和 page_5
 *   - 一致：不做任何操作
 * - 如果在其他页面：同步 UDP 模块的参数到两个页面（确保一致性）
 */
void shiboqi_remake::syncSettingsToPage8()
{
    if (!ui || !udpReceiver || !udpSender) return;
    
    // 获取当前显示的页面索引
    // page_5 = 0 (示波器), page_6 = 1 (DDS), page_7 = 2 (数字信号), page_8 = 3 (频谱)
    int currentPageIndex = ui->stackedWidget->currentIndex();
    
    // 从 UDP 模块获取当前的实际参数
    QString udpLocalIp = udpReceiver->getLocalAddress().toString();
    quint16 udpLocalPort = udpReceiver->getPort();
    QString udpTargetIp = udpSender->getTargetAddress().toString();
    quint16 udpTargetPort = udpSender->getTargetPort();
    quint32 udpDataNum = udpSender->getDataNum();
    
    // 从 UI 获取当前显示的值
    QString uiIp4 = ui->ipLineEdit_4->text();
    QString uiIp5 = ui->ipLineEdit_5->text();
    quint16 uiPort4 = ui->portSpinBox_4->value();
    quint16 uiPort5 = ui->portSpinBox_5->value();
    QString uiTargetIp4 = ui->targetIpLineEdit_4->text();
    QString uiTargetIp5 = ui->targetIpLineEdit_5->text();
    quint16 uiTargetPort4 = ui->targetPortSpinBox_4->value();
    quint16 uiTargetPort5 = ui->targetPortSpinBox_5->value();
    quint32 uiDataNum4 = ui->dataNumSpinBox_4->value();
    quint32 uiDataNum5 = ui->dataNumSpinBox_5->value();
    
    if (currentPageIndex == 0) {
        // 当前在 page_5（示波器页面）
        // 检查 page_5 的参数是否与 UDP 模块不一致
        bool page5Changed = (uiIp4 != udpLocalIp) ||
                           (uiPort4 != udpLocalPort) ||
                           (uiTargetIp4 != udpTargetIp) ||
                           (uiTargetPort4 != udpTargetPort) ||
                           (uiDataNum4 != udpDataNum);
        
        if (page5Changed) {
            // page_5 有修改，更新 UDP 模块和 page_8
            
            // 1. 更新 UDP 接收器的本地地址和端口
            if (uiIp4 != udpLocalIp || uiPort4 != udpLocalPort) {
                udpReceiver->setLocalAddress(QHostAddress(uiIp4), uiPort4);
            }
            
            // 2. 更新 UDP 发送器的目标地址和端口
            if (uiTargetIp4 != udpTargetIp || uiTargetPort4 != udpTargetPort) {
                udpSender->setTargetAddress(QHostAddress(uiTargetIp4), uiTargetPort4);
            }
            
            // 3. 更新数据个数
            if (uiDataNum4 != udpDataNum) {
                udpSender->setDataNum(uiDataNum4);
            }
            
            // 4. 同步参数到 page_8
            ui->ipLineEdit_5->blockSignals(true);
            ui->ipLineEdit_5->setText(uiIp4);
            ui->ipLineEdit_5->blockSignals(false);
            
            ui->portSpinBox_5->blockSignals(true);
            ui->portSpinBox_5->setValue(uiPort4);
            ui->portSpinBox_5->blockSignals(false);
            
            ui->targetIpLineEdit_5->blockSignals(true);
            ui->targetIpLineEdit_5->setText(uiTargetIp4);
            ui->targetIpLineEdit_5->blockSignals(false);
            
            ui->targetPortSpinBox_5->blockSignals(true);
            ui->targetPortSpinBox_5->setValue(uiTargetPort4);
            ui->targetPortSpinBox_5->blockSignals(false);
            
            ui->dataNumSpinBox_5->blockSignals(true);
            ui->dataNumSpinBox_5->setValue(uiDataNum4);
            ui->dataNumSpinBox_5->blockSignals(false);
        }
        // 如果一致，不做任何操作，避免打断用户输入
        
    } else if (currentPageIndex == 3) {
        // 当前在 page_8（频谱页面）
        // 检查 page_8 的参数是否与 UDP 模块不一致
        bool page8Changed = (uiIp5 != udpLocalIp) ||
                           (uiPort5 != udpLocalPort) ||
                           (uiTargetIp5 != udpTargetIp) ||
                           (uiTargetPort5 != udpTargetPort) ||
                           (uiDataNum5 != udpDataNum);
        
        if (page8Changed) {
            // page_8 有修改，更新 UDP 模块和 page_5
            
            // 1. 更新 UDP 接收器的本地地址和端口
            if (uiIp5 != udpLocalIp || uiPort5 != udpLocalPort) {
                udpReceiver->setLocalAddress(QHostAddress(uiIp5), uiPort5);
            }
            
            // 2. 更新 UDP 发送器的目标地址和端口
            if (uiTargetIp5 != udpTargetIp || uiTargetPort5 != udpTargetPort) {
                udpSender->setTargetAddress(QHostAddress(uiTargetIp5), uiTargetPort5);
            }
            
            // 3. 更新数据个数
            if (uiDataNum5 != udpDataNum) {
                udpSender->setDataNum(uiDataNum5);
            }
            
            // 4. 同步参数到 page_5
            ui->ipLineEdit_4->blockSignals(true);
            ui->ipLineEdit_4->setText(uiIp5);
            ui->ipLineEdit_4->blockSignals(false);
            
            ui->portSpinBox_4->blockSignals(true);
            ui->portSpinBox_4->setValue(uiPort5);
            ui->portSpinBox_4->blockSignals(false);
            
            ui->targetIpLineEdit_4->blockSignals(true);
            ui->targetIpLineEdit_4->setText(uiTargetIp5);
            ui->targetIpLineEdit_4->blockSignals(false);
            
            ui->targetPortSpinBox_4->blockSignals(true);
            ui->targetPortSpinBox_4->setValue(uiTargetPort5);
            ui->targetPortSpinBox_4->blockSignals(false);
            
            ui->dataNumSpinBox_4->blockSignals(true);
            ui->dataNumSpinBox_4->setValue(uiDataNum5);
            ui->dataNumSpinBox_4->blockSignals(false);
        }
        // 如果一致，不做任何操作，避免打断用户输入
        
    } else {
        // 当前在其他页面（page_6 DDS 或 page_7 数字信号测量）
        // 从 UDP 模块同步参数到两个页面，确保显示一致
        ui->ipLineEdit_4->blockSignals(true);
        ui->ipLineEdit_4->setText(udpLocalIp);
        ui->ipLineEdit_4->blockSignals(false);
        
        ui->ipLineEdit_5->blockSignals(true);
        ui->ipLineEdit_5->setText(udpLocalIp);
        ui->ipLineEdit_5->blockSignals(false);
        
        ui->portSpinBox_4->blockSignals(true);
        ui->portSpinBox_4->setValue(udpLocalPort);
        ui->portSpinBox_4->blockSignals(false);
        
        ui->portSpinBox_5->blockSignals(true);
        ui->portSpinBox_5->setValue(udpLocalPort);
        ui->portSpinBox_5->blockSignals(false);
        
        ui->targetIpLineEdit_4->blockSignals(true);
        ui->targetIpLineEdit_4->setText(udpTargetIp);
        ui->targetIpLineEdit_4->blockSignals(false);
        
        ui->targetIpLineEdit_5->blockSignals(true);
        ui->targetIpLineEdit_5->setText(udpTargetIp);
        ui->targetIpLineEdit_5->blockSignals(false);
        
        ui->targetPortSpinBox_4->blockSignals(true);
        ui->targetPortSpinBox_4->setValue(udpTargetPort);
        ui->targetPortSpinBox_4->blockSignals(false);
        
        ui->targetPortSpinBox_5->blockSignals(true);
        ui->targetPortSpinBox_5->setValue(udpTargetPort);
        ui->targetPortSpinBox_5->blockSignals(false);
        
        ui->dataNumSpinBox_4->blockSignals(true);
        ui->dataNumSpinBox_4->setValue(udpDataNum);
        ui->dataNumSpinBox_4->blockSignals(false);
        
        ui->dataNumSpinBox_5->blockSignals(true);
        ui->dataNumSpinBox_5->setValue(udpDataNum);
        ui->dataNumSpinBox_5->blockSignals(false);
    }
}

// ==================== 手绘波形功能实现 ====================

/**
 * @brief 手绘模式按钮切换槽函数
 * @param checked true表示开启手绘模式，false表示关闭手绘模式
 */
void shiboqi_remake::on_handDrawButton_toggled(bool checked)
{
    isHandDrawMode = checked;
    
    if (checked) {
        qDebug() << "手绘模式已开启";
        
        // 禁用切换波形按钮
        if (ui->waveformSwitchButton) {
            ui->waveformSwitchButton->setEnabled(false);
        }
        
        // 更新标签显示为"手绘波形"
        if (ui->currentWaveformLabel) {
            ui->currentWaveformLabel->setText("当前波形: ✏️ 手绘波形");
        }
        
        // 清空之前的绘制
        if (ui->boxingxianshi && ui->boxingxianshi->graphCount() > 0) {
            ui->boxingxianshi->graph(0)->data()->clear();
            ui->boxingxianshi->replot();
        }
    } else {
        qDebug() << "手绘模式已关闭";
        isDrawing = false;
        
        // 启用切换波形按钮
        if (ui->waveformSwitchButton) {
            ui->waveformSwitchButton->setEnabled(true);
        }
        
        // 恢复显示当前波形类型
        QString waveformNames[] = {"锯齿波", "正弦波", "方波", "三角波"};
        QString waveformEmojis[] = {"📐", "〰️", "▭", "🔺"};
        if (ui->currentWaveformLabel && currentWaveformType < 4) {
            ui->currentWaveformLabel->setText(
                QString("当前波形: %1 %2").arg(waveformEmojis[currentWaveformType]).arg(waveformNames[currentWaveformType])
            );
        }
    }
}

/**
 * @brief 清除绘制按钮点击槽函数
 */
void shiboqi_remake::on_clearDrawButton_clicked()
{
    // 清空手绘点集合
    handDrawnPoints.clear();
    handDrawnWaveform.clear();
    
    // 清空显示
    if (ui->boxingxianshi && ui->boxingxianshi->graphCount() > 0) {
        ui->boxingxianshi->graph(0)->data()->clear();
        ui->boxingxianshi->replot();
    }
    
    qDebug() << "手绘波形已清除";
}

/**
 * @brief 保存并发送按钮点击槽函数
 */
void shiboqi_remake::on_saveAndSendButton_clicked()
{
    // 检查是否有足够的绘制点
    if (handDrawnPoints.size() < 2) {
        qDebug() << "绘制点不足，无法发送波形";
        return;
    }
    
    // 检查线程是否正在运行
    if (waveformSenderThread && waveformSenderThread->isRunning()) {
        qDebug() << "波形正在发送中，请等待...";
        return;
    }
    
    // 插值为1024点
    interpolateHandDrawnWaveform();
    
    // 翻转Y轴数据
    flipYAxisData();
    
    // 发送波形数据
    sendHandDrawnWaveform();
    
    qDebug() << "手绘波形已保存并开始发送";
}

/**
 * @brief 将手绘点集合插值为1024点波形数据
 * 
 * 参考 udp_test.py 的逻辑，将用户手绘的点插值为1024个采样点
 * 每个点的值范围为 0-1023 (10位)
 */
void shiboqi_remake::interpolateHandDrawnWaveform()
{
    handDrawnWaveform.clear();
    
    if (handDrawnPoints.size() < 2) {
        qWarning() << "手绘点数不足，无法插值";
        return;
    }
    
    // 按 x 坐标排序
    QVector<QPointF> sortedPoints = handDrawnPoints;
    std::sort(sortedPoints.begin(), sortedPoints.end(), 
              [](const QPointF &a, const QPointF &b) { return a.x() < b.x(); });
    
    const int NUM_SAMPLES = 1024;
    handDrawnWaveform.reserve(NUM_SAMPLES);
    
    // 线性插值生成1024个点
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        double targetX = double(i) / (NUM_SAMPLES - 1); // 0.0 到 1.0
        
        // 找到 targetX 左右两个点
        int leftIdx = 0;
        for (int j = 0; j < sortedPoints.size() - 1; ++j) {
            if (sortedPoints[j].x() <= targetX && targetX <= sortedPoints[j + 1].x()) {
                leftIdx = j;
                break;
            }
        }
        
        // 如果 targetX 超出范围，使用边界值
        if (targetX < sortedPoints.first().x()) {
            handDrawnWaveform.append(static_cast<quint16>(qBound(0.0, sortedPoints.first().y(), 1023.0)));
        } else if (targetX > sortedPoints.last().x()) {
            handDrawnWaveform.append(static_cast<quint16>(qBound(0.0, sortedPoints.last().y(), 1023.0)));
        } else {
            // 线性插值
            QPointF p1 = sortedPoints[leftIdx];
            QPointF p2 = sortedPoints[leftIdx + 1];
            
            double t = (targetX - p1.x()) / (p2.x() - p1.x());
            double y = p1.y() + t * (p2.y() - p1.y());
            
            handDrawnWaveform.append(static_cast<quint16>(qBound(0.0, y, 1023.0)));
        }
    }
    
    qDebug() << "插值完成，生成" << handDrawnWaveform.size() << "个采样点";
}

/**
 * @brief 翻转Y轴数据（1023 - y）
 * 
 * 由于绘图坐标系和实际显示坐标系Y轴方向相反，
 * 需要将所有Y坐标翻转，使发送的波形和手绘的波形一致
 */
void shiboqi_remake::flipYAxisData()
{
    for (int i = 0; i < handDrawnWaveform.size(); ++i) {
        handDrawnWaveform[i] = 1023 - handDrawnWaveform[i];
    }
    
    qDebug() << "Y轴数据已翻转";
}

/**
 * @brief 发送手绘波形数据包
 * 
 * 使用独立线程发送波形数据，避免阻塞主线程
 */
void shiboqi_remake::sendHandDrawnWaveform()
{
    if (handDrawnWaveform.size() != 1024) {
        qWarning() << "波形数据不是1024个点，无法发送";
        return;
    }

    // 如果之前的线程还在运行，先停止它
    if (waveformSenderThread && waveformSenderThread->isRunning()) {
        qDebug() << "正在发送波形，请等待上一次发送完成...";
        return;
    }

    // 获取目标地址和端口（从UdpSender获取，或使用默认值）
    QHostAddress targetAddress("192.168.0.2");
    quint16 targetPort = 5000;

    // TODO: 如果需要，可以从UI读取目标地址
    // targetAddress = QHostAddress(ui->targetIpLineEdit_4->text());
    // targetPort = ui->targetPortSpinBox_4->value();

    qDebug() << "创建波形发送线程...";
    
    // 创建新的发送线程
    waveformSenderThread = new WaveformSenderThread(
        handDrawnWaveform,
        targetAddress,
        targetPort,
        1,  // 1ms延迟
        this
    );

    // 连接线程信号
    connect(waveformSenderThread, &WaveformSenderThread::progressUpdated,
            this, &shiboqi_remake::onWaveformSendProgress);
    connect(waveformSenderThread, &WaveformSenderThread::sendingCompleted,
            this, &shiboqi_remake::onWaveformSendCompleted);
    connect(waveformSenderThread, &WaveformSenderThread::sendingFailed,
            this, &shiboqi_remake::onWaveformSendFailed);

    // 线程完成后自动清理
    connect(waveformSenderThread, &WaveformSenderThread::finished,
            waveformSenderThread, &QObject::deleteLater);

    // 在发送前切换波形类型为手绘波形（4）
    udpSender->setWaveformType(4);
    udpSender->sendWaveformCommand();

    // 启动线程
    waveformSenderThread->start();
    qDebug() << "波形发送线程已启动（异步发送）";
}

/**
 * @brief 波形发送进度更新槽函数
 */
void shiboqi_remake::onWaveformSendProgress(int current, int total)
{
    if (total <= 0) return;
    
    int percentage = (current * 100) / total;
    qDebug() << "波形发送进度：" << current << "/" << total << "(" << percentage << "%)";
    
    // 更新UI进度显示
    if (ui && ui->sendProgressLabel) {
        ui->sendProgressLabel->setText(QString("发送进度: %1%").arg(percentage));
        
        // 根据进度改变颜色
        if (percentage < 100) {
            ui->sendProgressLabel->setStyleSheet(
                "QLabel {"
                "    background-color: #fff3cd;"
                "    color: #856404;"
                "    border: 2px solid #ffc107;"
                "    border-radius: 8px;"
                "    padding: 8px;"
                "    font-size: 13px;"
                "    font-weight: 600;"
                "}"
            );
        }
    }
}

/**
 * @brief 波形发送完成槽函数
 */
void shiboqi_remake::onWaveformSendCompleted(int successCount, int totalCount)
{
    qDebug() << "✓ 波形发送完成！成功：" << successCount << "/" << totalCount;
    
    // 将线程指针置空（线程会通过deleteLater自动删除）
    waveformSenderThread = nullptr;
    
    // 更新进度为100%并显示成功状态
    if (ui && ui->sendProgressLabel) {
        ui->sendProgressLabel->setText("发送完成: 100% ✓");
        ui->sendProgressLabel->setStyleSheet(
            "QLabel {"
            "    background-color: #d4edda;"
            "    color: #155724;"
            "    border: 2px solid #28a745;"
            "    border-radius: 8px;"
            "    padding: 8px;"
            "    font-size: 13px;"
            "    font-weight: 600;"
            "}"
        );
        
        // 3秒后恢复默认样式
        QTimer::singleShot(3000, this, [this]() {
            if (ui && ui->sendProgressLabel) {
                ui->sendProgressLabel->setText("发送进度: 0%");
                ui->sendProgressLabel->setStyleSheet(
                    "QLabel {"
                    "    background-color: #e8f5e9;"
                    "    color: #27ae60;"
                    "    border: 2px solid #27ae60;"
                    "    border-radius: 8px;"
                    "    padding: 8px;"
                    "    font-size: 13px;"
                    "    font-weight: 600;"
                    "}"
                );
            }
        });
    }
    
    qDebug() << "✓ 波形发送完成！波形已保留，可重复发送或点击'清除绘制'清空";
    // TODO: 可以在UI上显示成功提示
}

/**
 * @brief 波形发送失败槽函数
 */
void shiboqi_remake::onWaveformSendFailed(const QString &errorMessage)
{
    qWarning() << "✗ 波形发送失败：" << errorMessage;
    
    // 将线程指针置空（线程会通过deleteLater自动删除）
    waveformSenderThread = nullptr;
    
    // 显示发送失败状态
    if (ui && ui->sendProgressLabel) {
        ui->sendProgressLabel->setText("发送失败 ✗");
        ui->sendProgressLabel->setStyleSheet(
            "QLabel {"
            "    background-color: #f8d7da;"
            "    color: #721c24;"
            "    border: 2px solid #dc3545;"
            "    border-radius: 8px;"
            "    padding: 8px;"
            "    font-size: 13px;"
            "    font-weight: 600;"
            "}"
        );
        
        // 3秒后恢复默认样式
        QTimer::singleShot(3000, this, [this]() {
            if (ui && ui->sendProgressLabel) {
                ui->sendProgressLabel->setText("发送进度: 0%");
                ui->sendProgressLabel->setStyleSheet(
                    "QLabel {"
                    "    background-color: #e8f5e9;"
                    "    color: #27ae60;"
                    "    border: 2px solid #27ae60;"
                    "    border-radius: 8px;"
                    "    padding: 8px;"
                    "    font-size: 13px;"
                    "    font-weight: 600;"
                    "}"
                );
            }
        });
    }
}
