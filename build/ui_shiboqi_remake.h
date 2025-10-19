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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
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
    QStackedWidget *stackedWidget;
    QWidget *page_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_26;
    QVBoxLayout *verticalLayout_9;
    QCustomPlot *customPlot_2;
    QHBoxLayout *horizontalLayout_27;
    QLabel *Frequency_2;
    QLabel *Frequency_in_2;
    QLabel *Amplitude_2;
    QLabel *Amplitude_in_2;
    QLabel *VPP_2;
    QLabel *VPP_in_2;
    QLabel *V_MAX_2;
    QLabel *V_MAX_in_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_22;
    QSpinBox *portSpinBox_4;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_23;
    QSpinBox *channelSpinBox_4;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_24;
    QSpinBox *dividerSpinBox_4;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_25;
    QSpinBox *dataNumSpinBox_4;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_26;
    QSpinBox *targetPortSpinBox_4;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_27;
    QLineEdit *targetIpLineEdit_4;
    QHBoxLayout *horizontalLayout_34;
    QLabel *label_28;
    QLineEdit *ipLineEdit_4;
    QPushButton *setButton_4;
    QPushButton *listenButton_4;
    QPushButton *loopSendButton_4;
    QPushButton *restartButton_4;
    QWidget *page_6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_36;
    QCustomPlot *boxingxianshi;
    QVBoxLayout *verticalLayout_12;
    QPushButton *waveformSwitchButton;
    QPushButton *frequencyUpButton;
    QPushButton *frequencyDownButton;
    QPushButton *amplitudeUpButton;
    QPushButton *amplitudeDownButton;
    QWidget *page_7;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_13;
    QCustomPlot *shuzixinhaoboxing;
    QHBoxLayout *horizontalLayout_37;
    QLabel *pinglv;
    QLabel *pinglv_in;
    QLabel *zhankongbi;
    QLabel *zhankongbi_in;
    QLabel *Hvolt_t;
    QLabel *Hvolt_t_in;
    QLabel *Lvolt_t;
    QLabel *Lvolt_t_in;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuDDS;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *shiboqi_remake)
    {
        if (shiboqi_remake->objectName().isEmpty())
            shiboqi_remake->setObjectName(QString::fromUtf8("shiboqi_remake"));
        shiboqi_remake->resize(1118, 644);
        centralwidget = new QWidget(shiboqi_remake);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_main = new QHBoxLayout(centralwidget);
        horizontalLayout_main->setSpacing(0);
        horizontalLayout_main->setObjectName(QString::fromUtf8("horizontalLayout_main"));
        horizontalLayout_main->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        horizontalLayoutWidget = new QWidget(page_5);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 1101, 581));
        horizontalLayout_26 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        customPlot_2 = new QCustomPlot(horizontalLayoutWidget);
        customPlot_2->setObjectName(QString::fromUtf8("customPlot_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customPlot_2->sizePolicy().hasHeightForWidth());
        customPlot_2->setSizePolicy(sizePolicy);

        verticalLayout_9->addWidget(customPlot_2);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(60, -1, -1, -1);
        Frequency_2 = new QLabel(horizontalLayoutWidget);
        Frequency_2->setObjectName(QString::fromUtf8("Frequency_2"));

        horizontalLayout_27->addWidget(Frequency_2, 0, Qt::AlignRight);

        Frequency_in_2 = new QLabel(horizontalLayoutWidget);
        Frequency_in_2->setObjectName(QString::fromUtf8("Frequency_in_2"));

        horizontalLayout_27->addWidget(Frequency_in_2, 0, Qt::AlignLeft);

        Amplitude_2 = new QLabel(horizontalLayoutWidget);
        Amplitude_2->setObjectName(QString::fromUtf8("Amplitude_2"));

        horizontalLayout_27->addWidget(Amplitude_2, 0, Qt::AlignRight);

        Amplitude_in_2 = new QLabel(horizontalLayoutWidget);
        Amplitude_in_2->setObjectName(QString::fromUtf8("Amplitude_in_2"));

        horizontalLayout_27->addWidget(Amplitude_in_2, 0, Qt::AlignLeft);

        VPP_2 = new QLabel(horizontalLayoutWidget);
        VPP_2->setObjectName(QString::fromUtf8("VPP_2"));

        horizontalLayout_27->addWidget(VPP_2, 0, Qt::AlignRight);

        VPP_in_2 = new QLabel(horizontalLayoutWidget);
        VPP_in_2->setObjectName(QString::fromUtf8("VPP_in_2"));

        horizontalLayout_27->addWidget(VPP_in_2, 0, Qt::AlignLeft);

        V_MAX_2 = new QLabel(horizontalLayoutWidget);
        V_MAX_2->setObjectName(QString::fromUtf8("V_MAX_2"));

        horizontalLayout_27->addWidget(V_MAX_2, 0, Qt::AlignRight);

        V_MAX_in_2 = new QLabel(horizontalLayoutWidget);
        V_MAX_in_2->setObjectName(QString::fromUtf8("V_MAX_in_2"));

        horizontalLayout_27->addWidget(V_MAX_in_2, 0, Qt::AlignLeft);


        verticalLayout_9->addLayout(horizontalLayout_27);

        verticalLayout_9->setStretch(0, 9);

        horizontalLayout_26->addLayout(verticalLayout_9);

        groupBox = new QGroupBox(horizontalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_10 = new QVBoxLayout(groupBox);
        verticalLayout_10->setSpacing(10);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(20);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_11->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(5);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(-1, -1, 30, -1);
        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setEnabled(true);
        sizePolicy.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy);
        label_22->setMinimumSize(QSize(144, 0));
        label_22->setMaximumSize(QSize(144, 16777215));
        label_22->setLineWidth(1);
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_28->addWidget(label_22);

        portSpinBox_4 = new QSpinBox(groupBox);
        portSpinBox_4->setObjectName(QString::fromUtf8("portSpinBox_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(portSpinBox_4->sizePolicy().hasHeightForWidth());
        portSpinBox_4->setSizePolicy(sizePolicy1);
        portSpinBox_4->setMinimumSize(QSize(80, 0));
        portSpinBox_4->setLayoutDirection(Qt::LeftToRight);
        portSpinBox_4->setStyleSheet(QString::fromUtf8("padding: 0px; margin-left: -0;"));
        portSpinBox_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        portSpinBox_4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        portSpinBox_4->setMinimum(1);
        portSpinBox_4->setMaximum(65535);
        portSpinBox_4->setValue(6102);

        horizontalLayout_28->addWidget(portSpinBox_4);


        verticalLayout_11->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(5);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(-1, -1, 30, -1);
        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_29->addWidget(label_23);

        channelSpinBox_4 = new QSpinBox(groupBox);
        channelSpinBox_4->setObjectName(QString::fromUtf8("channelSpinBox_4"));
        sizePolicy1.setHeightForWidth(channelSpinBox_4->sizePolicy().hasHeightForWidth());
        channelSpinBox_4->setSizePolicy(sizePolicy1);
        channelSpinBox_4->setMinimumSize(QSize(80, 0));
        channelSpinBox_4->setFrame(false);
        channelSpinBox_4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        channelSpinBox_4->setMinimum(0);
        channelSpinBox_4->setMaximum(2);
        channelSpinBox_4->setValue(0);

        horizontalLayout_29->addWidget(channelSpinBox_4);


        verticalLayout_11->addLayout(horizontalLayout_29);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(5);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(-1, -1, 30, -1);
        label_24 = new QLabel(groupBox);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_30->addWidget(label_24, 0, Qt::AlignVCenter);

        dividerSpinBox_4 = new QSpinBox(groupBox);
        dividerSpinBox_4->setObjectName(QString::fromUtf8("dividerSpinBox_4"));
        sizePolicy1.setHeightForWidth(dividerSpinBox_4->sizePolicy().hasHeightForWidth());
        dividerSpinBox_4->setSizePolicy(sizePolicy1);
        dividerSpinBox_4->setMinimumSize(QSize(80, 0));
        dividerSpinBox_4->setFrame(false);
        dividerSpinBox_4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dividerSpinBox_4->setMinimum(0);
        dividerSpinBox_4->setMaximum(1000000);
        dividerSpinBox_4->setValue(0);

        horizontalLayout_30->addWidget(dividerSpinBox_4);


        verticalLayout_11->addLayout(horizontalLayout_30);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(5);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        horizontalLayout_31->setContentsMargins(-1, -1, 30, -1);
        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_31->addWidget(label_25, 0, Qt::AlignVCenter);

        dataNumSpinBox_4 = new QSpinBox(groupBox);
        dataNumSpinBox_4->setObjectName(QString::fromUtf8("dataNumSpinBox_4"));
        sizePolicy1.setHeightForWidth(dataNumSpinBox_4->sizePolicy().hasHeightForWidth());
        dataNumSpinBox_4->setSizePolicy(sizePolicy1);
        dataNumSpinBox_4->setMinimumSize(QSize(80, 0));
        dataNumSpinBox_4->setFrame(false);
        dataNumSpinBox_4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dataNumSpinBox_4->setMinimum(1);
        dataNumSpinBox_4->setMaximum(1000000);
        dataNumSpinBox_4->setValue(1);

        horizontalLayout_31->addWidget(dataNumSpinBox_4);


        verticalLayout_11->addLayout(horizontalLayout_31);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(5);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        horizontalLayout_32->setContentsMargins(-1, -1, 30, -1);
        label_26 = new QLabel(groupBox);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_32->addWidget(label_26);

        targetPortSpinBox_4 = new QSpinBox(groupBox);
        targetPortSpinBox_4->setObjectName(QString::fromUtf8("targetPortSpinBox_4"));
        sizePolicy1.setHeightForWidth(targetPortSpinBox_4->sizePolicy().hasHeightForWidth());
        targetPortSpinBox_4->setSizePolicy(sizePolicy1);
        targetPortSpinBox_4->setMinimumSize(QSize(80, 0));
        targetPortSpinBox_4->setFrame(false);
        targetPortSpinBox_4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        targetPortSpinBox_4->setMinimum(1);
        targetPortSpinBox_4->setMaximum(65535);
        targetPortSpinBox_4->setValue(5000);

        horizontalLayout_32->addWidget(targetPortSpinBox_4);


        verticalLayout_11->addLayout(horizontalLayout_32);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(5);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        label_27 = new QLabel(groupBox);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_33->addWidget(label_27);

        targetIpLineEdit_4 = new QLineEdit(groupBox);
        targetIpLineEdit_4->setObjectName(QString::fromUtf8("targetIpLineEdit_4"));
        sizePolicy1.setHeightForWidth(targetIpLineEdit_4->sizePolicy().hasHeightForWidth());
        targetIpLineEdit_4->setSizePolicy(sizePolicy1);
        targetIpLineEdit_4->setMinimumSize(QSize(120, 0));

        horizontalLayout_33->addWidget(targetIpLineEdit_4);


        verticalLayout_11->addLayout(horizontalLayout_33);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(5);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        label_28 = new QLabel(groupBox);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_34->addWidget(label_28);

        ipLineEdit_4 = new QLineEdit(groupBox);
        ipLineEdit_4->setObjectName(QString::fromUtf8("ipLineEdit_4"));
        sizePolicy1.setHeightForWidth(ipLineEdit_4->sizePolicy().hasHeightForWidth());
        ipLineEdit_4->setSizePolicy(sizePolicy1);
        ipLineEdit_4->setMinimumSize(QSize(120, 0));

        horizontalLayout_34->addWidget(ipLineEdit_4);


        verticalLayout_11->addLayout(horizontalLayout_34);


        verticalLayout_10->addLayout(verticalLayout_11);

        setButton_4 = new QPushButton(groupBox);
        setButton_4->setObjectName(QString::fromUtf8("setButton_4"));

        verticalLayout_10->addWidget(setButton_4);

        listenButton_4 = new QPushButton(groupBox);
        listenButton_4->setObjectName(QString::fromUtf8("listenButton_4"));
        listenButton_4->setCheckable(true);

        verticalLayout_10->addWidget(listenButton_4);

        loopSendButton_4 = new QPushButton(groupBox);
        loopSendButton_4->setObjectName(QString::fromUtf8("loopSendButton_4"));
        loopSendButton_4->setCheckable(true);

        verticalLayout_10->addWidget(loopSendButton_4);

        restartButton_4 = new QPushButton(groupBox);
        restartButton_4->setObjectName(QString::fromUtf8("restartButton_4"));

        verticalLayout_10->addWidget(restartButton_4);

        verticalLayout_10->setStretch(2, 2);

        horizontalLayout_26->addWidget(groupBox);

        horizontalLayout_26->setStretch(0, 3);
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        horizontalLayoutWidget_2 = new QWidget(page_6);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(9, 9, 1101, 581));
        horizontalLayout_36 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        horizontalLayout_36->setContentsMargins(0, 0, 0, 0);
        boxingxianshi = new QCustomPlot(horizontalLayoutWidget_2);
        boxingxianshi->setObjectName(QString::fromUtf8("boxingxianshi"));

        horizontalLayout_36->addWidget(boxingxianshi);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        waveformSwitchButton = new QPushButton(horizontalLayoutWidget_2);
        waveformSwitchButton->setObjectName(QString::fromUtf8("waveformSwitchButton"));

        verticalLayout_12->addWidget(waveformSwitchButton);

        frequencyUpButton = new QPushButton(horizontalLayoutWidget_2);
        frequencyUpButton->setObjectName(QString::fromUtf8("frequencyUpButton"));

        verticalLayout_12->addWidget(frequencyUpButton);

        frequencyDownButton = new QPushButton(horizontalLayoutWidget_2);
        frequencyDownButton->setObjectName(QString::fromUtf8("frequencyDownButton"));

        verticalLayout_12->addWidget(frequencyDownButton);

        amplitudeUpButton = new QPushButton(horizontalLayoutWidget_2);
        amplitudeUpButton->setObjectName(QString::fromUtf8("amplitudeUpButton"));

        verticalLayout_12->addWidget(amplitudeUpButton);

        amplitudeDownButton = new QPushButton(horizontalLayoutWidget_2);
        amplitudeDownButton->setObjectName(QString::fromUtf8("amplitudeDownButton"));

        verticalLayout_12->addWidget(amplitudeDownButton);


        horizontalLayout_36->addLayout(verticalLayout_12);

        horizontalLayout_36->setStretch(0, 2);
        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        verticalLayoutWidget_2 = new QWidget(page_7);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(9, 9, 1091, 581));
        verticalLayout_13 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        shuzixinhaoboxing = new QCustomPlot(verticalLayoutWidget_2);
        shuzixinhaoboxing->setObjectName(QString::fromUtf8("shuzixinhaoboxing"));

        verticalLayout_13->addWidget(shuzixinhaoboxing);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        pinglv = new QLabel(verticalLayoutWidget_2);
        pinglv->setObjectName(QString::fromUtf8("pinglv"));

        horizontalLayout_37->addWidget(pinglv);

        pinglv_in = new QLabel(verticalLayoutWidget_2);
        pinglv_in->setObjectName(QString::fromUtf8("pinglv_in"));

        horizontalLayout_37->addWidget(pinglv_in);

        zhankongbi = new QLabel(verticalLayoutWidget_2);
        zhankongbi->setObjectName(QString::fromUtf8("zhankongbi"));

        horizontalLayout_37->addWidget(zhankongbi);

        zhankongbi_in = new QLabel(verticalLayoutWidget_2);
        zhankongbi_in->setObjectName(QString::fromUtf8("zhankongbi_in"));

        horizontalLayout_37->addWidget(zhankongbi_in);

        Hvolt_t = new QLabel(verticalLayoutWidget_2);
        Hvolt_t->setObjectName(QString::fromUtf8("Hvolt_t"));

        horizontalLayout_37->addWidget(Hvolt_t);

        Hvolt_t_in = new QLabel(verticalLayoutWidget_2);
        Hvolt_t_in->setObjectName(QString::fromUtf8("Hvolt_t_in"));

        horizontalLayout_37->addWidget(Hvolt_t_in);

        Lvolt_t = new QLabel(verticalLayoutWidget_2);
        Lvolt_t->setObjectName(QString::fromUtf8("Lvolt_t"));

        horizontalLayout_37->addWidget(Lvolt_t);

        Lvolt_t_in = new QLabel(verticalLayoutWidget_2);
        Lvolt_t_in->setObjectName(QString::fromUtf8("Lvolt_t_in"));

        horizontalLayout_37->addWidget(Lvolt_t_in);


        verticalLayout_13->addLayout(horizontalLayout_37);

        verticalLayout_13->setStretch(0, 3);
        stackedWidget->addWidget(page_7);

        horizontalLayout_main->addWidget(stackedWidget);

        shiboqi_remake->setCentralWidget(centralwidget);
        menubar = new QMenuBar(shiboqi_remake);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1118, 24));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuDDS = new QMenu(menubar);
        menuDDS->setObjectName(QString::fromUtf8("menuDDS"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        shiboqi_remake->setMenuBar(menubar);
        statusbar = new QStatusBar(shiboqi_remake);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        shiboqi_remake->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuDDS->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());

        retranslateUi(shiboqi_remake);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(shiboqi_remake);
    } // setupUi

    void retranslateUi(QMainWindow *shiboqi_remake)
    {
        shiboqi_remake->setWindowTitle(QCoreApplication::translate("shiboqi_remake", "shiboqi_remake", nullptr));
        Frequency_2->setText(QCoreApplication::translate("shiboqi_remake", "Frequency :", nullptr));
        Frequency_in_2->setText(QCoreApplication::translate("shiboqi_remake", "0 Hz", nullptr));
        Amplitude_2->setText(QCoreApplication::translate("shiboqi_remake", "Amplitude :", nullptr));
        Amplitude_in_2->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        VPP_2->setText(QCoreApplication::translate("shiboqi_remake", "vp-p :", nullptr));
        VPP_in_2->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        V_MAX_2->setText(QCoreApplication::translate("shiboqi_remake", "Vmax :", nullptr));
        V_MAX_in_2->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        groupBox->setTitle(QCoreApplication::translate("shiboqi_remake", "UDP\350\256\276\347\275\256", nullptr));
        label_22->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_22->setText(QCoreApplication::translate("shiboqi_remake", " \347\253\257\345\217\243:", nullptr));
        label_23->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_23->setText(QCoreApplication::translate("shiboqi_remake", "\351\200\232\351\201\223\351\200\211\346\213\251:", nullptr));
        channelSpinBox_4->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_24->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_24->setText(QCoreApplication::translate("shiboqi_remake", "\345\210\206\351\242\221\347\263\273\346\225\260:", nullptr));
        dividerSpinBox_4->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_25->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_25->setText(QCoreApplication::translate("shiboqi_remake", "\346\225\260\346\215\256\344\270\252\346\225\260:", nullptr));
        dataNumSpinBox_4->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_26->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_26->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207\347\253\257\345\217\243:", nullptr));
        targetPortSpinBox_4->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_27->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_27->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207IP\345\234\260\345\235\200:", nullptr));
        targetIpLineEdit_4->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        targetIpLineEdit_4->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.2", nullptr));
        label_28->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_28->setText(QCoreApplication::translate("shiboqi_remake", "\346\234\254\346\234\272IP\345\234\260\345\235\200:", nullptr));
        ipLineEdit_4->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        ipLineEdit_4->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.3", nullptr));
        setButton_4->setText(QCoreApplication::translate("shiboqi_remake", "\350\256\276\347\275\256UDP\350\277\236\346\216\245\345\217\202\346\225\260", nullptr));
        listenButton_4->setText(QCoreApplication::translate("shiboqi_remake", "\345\274\200\345\247\213\347\233\221\345\220\254", nullptr));
        loopSendButton_4->setText(QCoreApplication::translate("shiboqi_remake", "\345\276\252\347\216\257\345\217\221\351\200\201", nullptr));
        restartButton_4->setText(QCoreApplication::translate("shiboqi_remake", "\345\217\221\351\200\201\351\207\207\351\233\206\345\221\275\344\273\244", nullptr));
        waveformSwitchButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\210\207\346\215\242\346\263\242\345\275\242", nullptr));
        frequencyUpButton->setText(QCoreApplication::translate("shiboqi_remake", "\351\242\221\347\216\207+", nullptr));
        frequencyDownButton->setText(QCoreApplication::translate("shiboqi_remake", "\351\242\221\347\216\207-", nullptr));
        amplitudeUpButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\271\205\345\272\246+", nullptr));
        amplitudeDownButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\271\205\345\272\246-", nullptr));
        pinglv->setText(QCoreApplication::translate("shiboqi_remake", "\351\242\221\347\216\207\357\274\232", nullptr));
        pinglv_in->setText(QCoreApplication::translate("shiboqi_remake", "0 Hz", nullptr));
        zhankongbi->setText(QCoreApplication::translate("shiboqi_remake", "\345\215\240\347\251\272\346\257\224\357\274\232", nullptr));
        zhankongbi_in->setText(QCoreApplication::translate("shiboqi_remake", "0", nullptr));
        Hvolt_t->setText(QCoreApplication::translate("shiboqi_remake", "\351\253\230\347\224\265\345\271\263\346\227\266\351\227\264\357\274\232", nullptr));
        Hvolt_t_in->setText(QCoreApplication::translate("shiboqi_remake", "0 us", nullptr));
        Lvolt_t->setText(QCoreApplication::translate("shiboqi_remake", "\344\275\216\347\224\265\345\271\263\346\227\266\351\227\264\357\274\232", nullptr));
        Lvolt_t_in->setText(QCoreApplication::translate("shiboqi_remake", "0 us", nullptr));
        menu->setTitle(QCoreApplication::translate("shiboqi_remake", "\347\244\272\346\263\242\345\231\250", nullptr));
        menuDDS->setTitle(QCoreApplication::translate("shiboqi_remake", "DDS\350\256\276\347\275\256", nullptr));
        menu_2->setTitle(QCoreApplication::translate("shiboqi_remake", "\346\225\260\345\255\227\344\277\241\345\217\267\346\265\213\351\207\217", nullptr));
        menu_3->setTitle(QCoreApplication::translate("shiboqi_remake", "\351\242\221\350\260\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class shiboqi_remake: public Ui_shiboqi_remake {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHIBOQI_REMAKE_H
