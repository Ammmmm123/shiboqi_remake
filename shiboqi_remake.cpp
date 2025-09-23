#include "shiboqi_remake.h"
#include "ui_shiboqi_remake.h"
#include <QMessageBox>
#include <QTimer>

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
    , errorDialogShown(false)
{
    ui->setupUi(this);

    // 连接设置按钮的点击信号到槽函数
    connect(ui->setButton, &QPushButton::clicked, this, &shiboqi_remake::on_setButton_clicked);

    // 连接监听按钮的切换信号到槽函数
    connect(ui->listenButton, &QPushButton::toggled, this, &shiboqi_remake::on_listenButton_toggled);

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
        udpReceiver->startListening();
        ui->listenButton->setText("停止监听");
        
        // 禁用设置按钮，防止在监听期间修改参数
        ui->setButton->setEnabled(false);
        ui->ipLineEdit->setEnabled(false);
        ui->portSpinBox->setEnabled(false);
    } else {
        // 停止监听UDP数据
        udpReceiver->stopListening();
        ui->listenButton->setText("开始监听");
        
        // 重新启用设置按钮和输入控件
        ui->setButton->setEnabled(true);
        ui->ipLineEdit->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
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

        // 重置标志位，允许下次显示错误对话框
        errorDialogShown = false;
    });
}