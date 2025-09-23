/********************************************************************************
** Form generated from reading UI file 'shiboqi_remake.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHIBOQI_REMAKE_H
#define UI_SHIBOQI_REMAKE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_shiboqi_remake
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ipLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *portSpinBox;
    QPushButton *setButton;
    QPushButton *listenButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *shiboqi_remake)
    {
        if (shiboqi_remake->objectName().isEmpty())
            shiboqi_remake->setObjectName(QString::fromUtf8("shiboqi_remake"));
        shiboqi_remake->resize(800, 600);
        centralwidget = new QWidget(shiboqi_remake);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        ipLineEdit = new QLineEdit(centralwidget);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));

        horizontalLayout->addWidget(ipLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        portSpinBox = new QSpinBox(centralwidget);
        portSpinBox->setObjectName(QString::fromUtf8("portSpinBox"));
        portSpinBox->setMinimum(1);
        portSpinBox->setMaximum(65535);
        portSpinBox->setValue(6102);

        horizontalLayout_2->addWidget(portSpinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        setButton = new QPushButton(centralwidget);
        setButton->setObjectName(QString::fromUtf8("setButton"));

        verticalLayout->addWidget(setButton);

        listenButton = new QPushButton(centralwidget);
        listenButton->setObjectName(QString::fromUtf8("listenButton"));
        listenButton->setCheckable(true);

        verticalLayout->addWidget(listenButton);

        shiboqi_remake->setCentralWidget(centralwidget);
        menubar = new QMenuBar(shiboqi_remake);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        shiboqi_remake->setMenuBar(menubar);
        statusbar = new QStatusBar(shiboqi_remake);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        shiboqi_remake->setStatusBar(statusbar);

        retranslateUi(shiboqi_remake);

        QMetaObject::connectSlotsByName(shiboqi_remake);
    } // setupUi

    void retranslateUi(QMainWindow *shiboqi_remake)
    {
        shiboqi_remake->setWindowTitle(QCoreApplication::translate("shiboqi_remake", "shiboqi_remake", nullptr));
        label->setText(QCoreApplication::translate("shiboqi_remake", "\346\234\254\346\234\272IP\345\234\260\345\235\200:", nullptr));
        ipLineEdit->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.3", nullptr));
        label_2->setText(QCoreApplication::translate("shiboqi_remake", "\347\253\257\345\217\243:", nullptr));
        setButton->setText(QCoreApplication::translate("shiboqi_remake", "\350\256\276\347\275\256UDP\350\277\236\346\216\245\345\217\202\346\225\260", nullptr));
        listenButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\274\200\345\247\213\347\233\221\345\220\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class shiboqi_remake: public Ui_shiboqi_remake {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHIBOQI_REMAKE_H
