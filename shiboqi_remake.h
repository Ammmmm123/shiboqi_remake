#ifndef SHIBOQI_REMAKE_H
#define SHIBOQI_REMAKE_H

#include <QMainWindow>
#include "udp_receive.h"

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
     * @brief UDP绑定失败处理槽函数
     *
     * 当UDP套接字绑定失败时弹出错误提示对话框。
     * @param errorString UDP套接字返回的错误描述
     */
    void onUdpBindFailed(const QString &errorString);

private:
    Ui::shiboqi_remake *ui;      ///< UI界面指针
    UdpReceiver *udpReceiver;    ///< UDP接收器实例指针
    bool errorDialogShown;       ///< 错误对话框显示标志，防止重复弹出
};
#endif // SHIBOQI_REMAKE_H
