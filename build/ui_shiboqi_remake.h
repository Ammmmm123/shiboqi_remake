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
#include <QtWidgets/QGroupBox>
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
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_shiboqi_remake
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_main;
    QVBoxLayout *verticalLayout_5;
    QCustomPlot *customPlot;
    QHBoxLayout *horizontalLayout_9;
    QLabel *Frequency;
    QLabel *Frequency_in;
    QLabel *Amplitude;
    QLabel *Amplitude_in;
    QLabel *VPP;
    QLabel *VPP_in;
    QLabel *V_MAX;
    QLabel *V_MAX_in;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QSpinBox *portSpinBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSpinBox *channelSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *dividerSpinBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *dataNumSpinBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *targetPortSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *targetIpLineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ipLineEdit;
    QPushButton *setButton;
    QPushButton *listenButton;
    QPushButton *loopSendButton;
    QPushButton *restartButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *shiboqi_remake)
    {
        if (shiboqi_remake->objectName().isEmpty())
            shiboqi_remake->setObjectName(QString::fromUtf8("shiboqi_remake"));
        shiboqi_remake->resize(1100, 599);
        centralwidget = new QWidget(shiboqi_remake);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_main = new QHBoxLayout(centralwidget);
        horizontalLayout_main->setObjectName(QString::fromUtf8("horizontalLayout_main"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(customPlot);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(60, -1, -1, -1);
        Frequency = new QLabel(centralwidget);
        Frequency->setObjectName(QString::fromUtf8("Frequency"));

        horizontalLayout_9->addWidget(Frequency, 0, Qt::AlignRight);

        Frequency_in = new QLabel(centralwidget);
        Frequency_in->setObjectName(QString::fromUtf8("Frequency_in"));

        horizontalLayout_9->addWidget(Frequency_in, 0, Qt::AlignLeft);

        Amplitude = new QLabel(centralwidget);
        Amplitude->setObjectName(QString::fromUtf8("Amplitude"));

        horizontalLayout_9->addWidget(Amplitude, 0, Qt::AlignRight);

        Amplitude_in = new QLabel(centralwidget);
        Amplitude_in->setObjectName(QString::fromUtf8("Amplitude_in"));

        horizontalLayout_9->addWidget(Amplitude_in, 0, Qt::AlignLeft);

        VPP = new QLabel(centralwidget);
        VPP->setObjectName(QString::fromUtf8("VPP"));

        horizontalLayout_9->addWidget(VPP, 0, Qt::AlignRight);

        VPP_in = new QLabel(centralwidget);
        VPP_in->setObjectName(QString::fromUtf8("VPP_in"));

        horizontalLayout_9->addWidget(VPP_in, 0, Qt::AlignLeft);

        V_MAX = new QLabel(centralwidget);
        V_MAX->setObjectName(QString::fromUtf8("V_MAX"));

        horizontalLayout_9->addWidget(V_MAX, 0, Qt::AlignRight);

        V_MAX_in = new QLabel(centralwidget);
        V_MAX_in->setObjectName(QString::fromUtf8("V_MAX_in"));

        horizontalLayout_9->addWidget(V_MAX_in, 0, Qt::AlignLeft);


        verticalLayout_5->addLayout(horizontalLayout_9);

        verticalLayout_5->setStretch(0, 9);

        horizontalLayout_main->addLayout(verticalLayout_5);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(5);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, 30, -1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(144, 0));
        label_2->setMaximumSize(QSize(144, 16777215));
        label_2->setLineWidth(1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_2);

        portSpinBox = new QSpinBox(groupBox);
        portSpinBox->setObjectName(QString::fromUtf8("portSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(portSpinBox->sizePolicy().hasHeightForWidth());
        portSpinBox->setSizePolicy(sizePolicy1);
        portSpinBox->setMinimumSize(QSize(80, 0));
        portSpinBox->setLayoutDirection(Qt::LeftToRight);
        portSpinBox->setStyleSheet(QString::fromUtf8("padding: 0px; margin-left: -0;"));
        portSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        portSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        portSpinBox->setMinimum(1);
        portSpinBox->setMaximum(65535);
        portSpinBox->setValue(6102);

        horizontalLayout_8->addWidget(portSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(5);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, -1, 30, -1);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_7);

        channelSpinBox = new QSpinBox(groupBox);
        channelSpinBox->setObjectName(QString::fromUtf8("channelSpinBox"));
        sizePolicy1.setHeightForWidth(channelSpinBox->sizePolicy().hasHeightForWidth());
        channelSpinBox->setSizePolicy(sizePolicy1);
        channelSpinBox->setMinimumSize(QSize(80, 0));
        channelSpinBox->setFrame(false);
        channelSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        channelSpinBox->setMinimum(0);
        channelSpinBox->setMaximum(2);
        channelSpinBox->setValue(0);

        horizontalLayout_7->addWidget(channelSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, -1, 30, -1);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_6, 0, Qt::AlignVCenter);

        dividerSpinBox = new QSpinBox(groupBox);
        dividerSpinBox->setObjectName(QString::fromUtf8("dividerSpinBox"));
        sizePolicy1.setHeightForWidth(dividerSpinBox->sizePolicy().hasHeightForWidth());
        dividerSpinBox->setSizePolicy(sizePolicy1);
        dividerSpinBox->setMinimumSize(QSize(80, 0));
        dividerSpinBox->setFrame(false);
        dividerSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dividerSpinBox->setMinimum(0);
        dividerSpinBox->setMaximum(1000000);
        dividerSpinBox->setValue(0);

        horizontalLayout_6->addWidget(dividerSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, 30, -1);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_5, 0, Qt::AlignVCenter);

        dataNumSpinBox = new QSpinBox(groupBox);
        dataNumSpinBox->setObjectName(QString::fromUtf8("dataNumSpinBox"));
        sizePolicy1.setHeightForWidth(dataNumSpinBox->sizePolicy().hasHeightForWidth());
        dataNumSpinBox->setSizePolicy(sizePolicy1);
        dataNumSpinBox->setMinimumSize(QSize(80, 0));
        dataNumSpinBox->setFrame(false);
        dataNumSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dataNumSpinBox->setMinimum(1);
        dataNumSpinBox->setMaximum(1000000);
        dataNumSpinBox->setValue(1);

        horizontalLayout_5->addWidget(dataNumSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(5);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 30, -1);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_4);

        targetPortSpinBox = new QSpinBox(groupBox);
        targetPortSpinBox->setObjectName(QString::fromUtf8("targetPortSpinBox"));
        sizePolicy1.setHeightForWidth(targetPortSpinBox->sizePolicy().hasHeightForWidth());
        targetPortSpinBox->setSizePolicy(sizePolicy1);
        targetPortSpinBox->setMinimumSize(QSize(80, 0));
        targetPortSpinBox->setFrame(false);
        targetPortSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        targetPortSpinBox->setMinimum(1);
        targetPortSpinBox->setMaximum(65535);
        targetPortSpinBox->setValue(5000);

        horizontalLayout_4->addWidget(targetPortSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        targetIpLineEdit = new QLineEdit(groupBox);
        targetIpLineEdit->setObjectName(QString::fromUtf8("targetIpLineEdit"));
        sizePolicy1.setHeightForWidth(targetIpLineEdit->sizePolicy().hasHeightForWidth());
        targetIpLineEdit->setSizePolicy(sizePolicy1);
        targetIpLineEdit->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(targetIpLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        ipLineEdit = new QLineEdit(groupBox);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));
        sizePolicy1.setHeightForWidth(ipLineEdit->sizePolicy().hasHeightForWidth());
        ipLineEdit->setSizePolicy(sizePolicy1);
        ipLineEdit->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(ipLineEdit);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(verticalLayout_2);

        setButton = new QPushButton(groupBox);
        setButton->setObjectName(QString::fromUtf8("setButton"));

        verticalLayout->addWidget(setButton);

        listenButton = new QPushButton(groupBox);
        listenButton->setObjectName(QString::fromUtf8("listenButton"));
        listenButton->setCheckable(true);

        verticalLayout->addWidget(listenButton);

        loopSendButton = new QPushButton(groupBox);
        loopSendButton->setObjectName(QString::fromUtf8("loopSendButton"));
        loopSendButton->setCheckable(true);

        verticalLayout->addWidget(loopSendButton);

        restartButton = new QPushButton(groupBox);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));

        verticalLayout->addWidget(restartButton);

        verticalLayout->setStretch(2, 2);

        horizontalLayout_main->addWidget(groupBox);

        horizontalLayout_main->setStretch(0, 3);
        horizontalLayout_main->setStretch(1, 1);
        shiboqi_remake->setCentralWidget(centralwidget);
        menubar = new QMenuBar(shiboqi_remake);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1100, 24));
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
        Frequency->setText(QCoreApplication::translate("shiboqi_remake", "Frequency :", nullptr));
        Frequency_in->setText(QCoreApplication::translate("shiboqi_remake", "0 Hz", nullptr));
        Amplitude->setText(QCoreApplication::translate("shiboqi_remake", "Amplitude :", nullptr));
        Amplitude_in->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        VPP->setText(QCoreApplication::translate("shiboqi_remake", "vp-p :", nullptr));
        VPP_in->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        V_MAX->setText(QCoreApplication::translate("shiboqi_remake", "Vmax :", nullptr));
        V_MAX_in->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        groupBox->setTitle(QCoreApplication::translate("shiboqi_remake", "UDP\350\256\276\347\275\256", nullptr));
        label_2->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_2->setText(QCoreApplication::translate("shiboqi_remake", " \347\253\257\345\217\243:", nullptr));
        label_7->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_7->setText(QCoreApplication::translate("shiboqi_remake", "\351\200\232\351\201\223\351\200\211\346\213\251:", nullptr));
        channelSpinBox->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_6->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_6->setText(QCoreApplication::translate("shiboqi_remake", "\345\210\206\351\242\221\347\263\273\346\225\260:", nullptr));
        dividerSpinBox->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_5->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_5->setText(QCoreApplication::translate("shiboqi_remake", "\346\225\260\346\215\256\344\270\252\346\225\260:", nullptr));
        dataNumSpinBox->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_4->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_4->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207\347\253\257\345\217\243:", nullptr));
        targetPortSpinBox->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_3->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_3->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207IP\345\234\260\345\235\200:", nullptr));
        targetIpLineEdit->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        targetIpLineEdit->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.2", nullptr));
        label->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label->setText(QCoreApplication::translate("shiboqi_remake", "\346\234\254\346\234\272IP\345\234\260\345\235\200:", nullptr));
        ipLineEdit->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        ipLineEdit->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.3", nullptr));
        setButton->setText(QCoreApplication::translate("shiboqi_remake", "\350\256\276\347\275\256UDP\350\277\236\346\216\245\345\217\202\346\225\260", nullptr));
        listenButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\274\200\345\247\213\347\233\221\345\220\254", nullptr));
        loopSendButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\276\252\347\216\257\345\217\221\351\200\201", nullptr));
        restartButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\217\221\351\200\201\351\207\207\351\233\206\345\221\275\344\273\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class shiboqi_remake: public Ui_shiboqi_remake {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHIBOQI_REMAKE_H
