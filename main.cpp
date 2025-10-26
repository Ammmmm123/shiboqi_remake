#include "shiboqi_remake.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 设置应用程序名称
    a.setApplicationName("FPGA多功能调试仪");
    a.setApplicationDisplayName("FPGA多功能调试仪");
    
    // 设置应用程序图标
    a.setWindowIcon(QIcon(":/tubiao.ico"));
    
    shiboqi_remake w;
    w.setWindowTitle("FPGA多功能调试仪");
    w.show();
    return a.exec();
}
