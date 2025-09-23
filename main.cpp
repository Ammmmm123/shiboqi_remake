#include "shiboqi_remake.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    shiboqi_remake w;
    w.show();
    return a.exec();
}
