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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_shiboqi_remake
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_main;
    QWidget *sidebarWidget;
    QVBoxLayout *verticalLayout_sidebar;
    QLabel *titleLabel;
    QLabel *menuLabel;
    QPushButton *navButton_oscilloscope;
    QPushButton *navButton_dds;
    QPushButton *navButton_digital;
    QPushButton *navButton_spectrum;
    QSpacerItem *verticalSpacer;
    QLabel *copyrightLabel1;
    QLabel *copyrightLabel2;
    QStackedWidget *stackedWidget;
    QWidget *page_5;
    QHBoxLayout *horizontalLayout_3;
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
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_36;
    QCustomPlot *boxingxianshi;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_dds_title;
    QPushButton *waveformSwitchButton;
    QPushButton *handDrawButton;
    QPushButton *clearDrawButton;
    QPushButton *saveAndSendButton;
    QLabel *label_separator1;
    QPushButton *frequencyUpButton;
    QPushButton *frequencyDownButton;
    QPushButton *amplitudeUpButton;
    QPushButton *amplitudeDownButton;
    QLabel *label_separator2;
    QLabel *currentWaveformLabel;
    QLabel *sendProgressLabel;
    QSpacerItem *verticalSpacer_dds;
    QWidget *page_7;
    QHBoxLayout *horizontalLayout_5;
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
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QWidget *page_8;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_35;
    QVBoxLayout *verticalLayout_14;
    QCustomPlot *customPlot_3;
    QHBoxLayout *horizontalLayout_38;
    QLabel *Frequency_3;
    QLabel *Frequency_in_3;
    QLabel *Amplitude_3;
    QLabel *Amplitude_in_3;
    QLabel *label_snr;
    QLabel *label_snr_value;
    QHBoxLayout *horizontalLayout_spectrum_info2;
    QLabel *label_thd;
    QLabel *label_thd_value;
    QLabel *label_bandwidth;
    QLabel *label_bandwidth_value;
    QLabel *label_harmonics;
    QLabel *label_harmonics_value;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_15;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_29;
    QSpinBox *portSpinBox_5;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_32;
    QSpinBox *dataNumSpinBox_5;
    QHBoxLayout *horizontalLayout_43;
    QLabel *label_33;
    QSpinBox *targetPortSpinBox_5;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_34;
    QLineEdit *targetIpLineEdit_5;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_35;
    QLineEdit *ipLineEdit_5;
    QPushButton *setButton_5;
    QPushButton *listenButton_5;
    QPushButton *loopSendButton_5;
    QPushButton *restartButton_5;

    void setupUi(QMainWindow *shiboqi_remake)
    {
        if (shiboqi_remake->objectName().isEmpty())
            shiboqi_remake->setObjectName(QString::fromUtf8("shiboqi_remake"));
        shiboqi_remake->resize(1116, 696);
        centralwidget = new QWidget(shiboqi_remake);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_main = new QHBoxLayout(centralwidget);
        horizontalLayout_main->setSpacing(0);
        horizontalLayout_main->setObjectName(QString::fromUtf8("horizontalLayout_main"));
        horizontalLayout_main->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_main->setContentsMargins(0, 0, 0, 0);
        sidebarWidget = new QWidget(centralwidget);
        sidebarWidget->setObjectName(QString::fromUtf8("sidebarWidget"));
        sidebarWidget->setMinimumSize(QSize(200, 0));
        sidebarWidget->setMaximumSize(QSize(200, 16777215));
        sidebarWidget->setStyleSheet(QString::fromUtf8("QWidget#sidebarWidget {\n"
"    background-color: #2c3e50;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: transparent;\n"
"    color: #ecf0f1;\n"
"    text-align: left;\n"
"    padding: 15px 20px;\n"
"    border: none;\n"
"    border-left: 3px solid transparent;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #34495e;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #34495e;\n"
"    border-left: 3px solid #3498db;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #95a5a6;\n"
"    padding: 10px 20px;\n"
"    font-size: 12px;\n"
"}"));
        verticalLayout_sidebar = new QVBoxLayout(sidebarWidget);
        verticalLayout_sidebar->setSpacing(0);
        verticalLayout_sidebar->setObjectName(QString::fromUtf8("verticalLayout_sidebar"));
        verticalLayout_sidebar->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(sidebarWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMinimumSize(QSize(0, 60));
        titleLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #1a252f;\n"
"    color: #3498db;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    padding: 20px;\n"
"}"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_sidebar->addWidget(titleLabel);

        menuLabel = new QLabel(sidebarWidget);
        menuLabel->setObjectName(QString::fromUtf8("menuLabel"));

        verticalLayout_sidebar->addWidget(menuLabel);

        navButton_oscilloscope = new QPushButton(sidebarWidget);
        navButton_oscilloscope->setObjectName(QString::fromUtf8("navButton_oscilloscope"));
        navButton_oscilloscope->setCheckable(true);
        navButton_oscilloscope->setChecked(true);

        verticalLayout_sidebar->addWidget(navButton_oscilloscope);

        navButton_dds = new QPushButton(sidebarWidget);
        navButton_dds->setObjectName(QString::fromUtf8("navButton_dds"));
        navButton_dds->setCheckable(true);

        verticalLayout_sidebar->addWidget(navButton_dds);

        navButton_digital = new QPushButton(sidebarWidget);
        navButton_digital->setObjectName(QString::fromUtf8("navButton_digital"));
        navButton_digital->setCheckable(true);

        verticalLayout_sidebar->addWidget(navButton_digital);

        navButton_spectrum = new QPushButton(sidebarWidget);
        navButton_spectrum->setObjectName(QString::fromUtf8("navButton_spectrum"));
        navButton_spectrum->setCheckable(true);

        verticalLayout_sidebar->addWidget(navButton_spectrum);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_sidebar->addItem(verticalSpacer);

        copyrightLabel1 = new QLabel(sidebarWidget);
        copyrightLabel1->setObjectName(QString::fromUtf8("copyrightLabel1"));
        copyrightLabel1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #ecf0f1;\n"
"    padding: 5px 10px;\n"
"    font-size: 11px;\n"
"}"));
        copyrightLabel1->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        copyrightLabel1->setWordWrap(true);

        verticalLayout_sidebar->addWidget(copyrightLabel1);

        copyrightLabel2 = new QLabel(sidebarWidget);
        copyrightLabel2->setObjectName(QString::fromUtf8("copyrightLabel2"));
        copyrightLabel2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #ecf0f1;\n"
"    padding: 5px 10px;\n"
"    font-size: 11px;\n"
"}"));
        copyrightLabel2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        copyrightLabel2->setWordWrap(true);

        verticalLayout_sidebar->addWidget(copyrightLabel2);


        horizontalLayout_main->addWidget(sidebarWidget);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setLayoutDirection(Qt::LeftToRight);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout_3 = new QHBoxLayout(page_5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        customPlot_2 = new QCustomPlot(page_5);
        customPlot_2->setObjectName(QString::fromUtf8("customPlot_2"));
        sizePolicy.setHeightForWidth(customPlot_2->sizePolicy().hasHeightForWidth());
        customPlot_2->setSizePolicy(sizePolicy);

        verticalLayout_9->addWidget(customPlot_2);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(60, -1, -1, -1);
        Frequency_2 = new QLabel(page_5);
        Frequency_2->setObjectName(QString::fromUtf8("Frequency_2"));
        Frequency_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_27->addWidget(Frequency_2, 0, Qt::AlignRight);

        Frequency_in_2 = new QLabel(page_5);
        Frequency_in_2->setObjectName(QString::fromUtf8("Frequency_in_2"));
        Frequency_in_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_27->addWidget(Frequency_in_2, 0, Qt::AlignLeft);

        Amplitude_2 = new QLabel(page_5);
        Amplitude_2->setObjectName(QString::fromUtf8("Amplitude_2"));
        Amplitude_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_27->addWidget(Amplitude_2, 0, Qt::AlignRight);

        Amplitude_in_2 = new QLabel(page_5);
        Amplitude_in_2->setObjectName(QString::fromUtf8("Amplitude_in_2"));
        Amplitude_in_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_27->addWidget(Amplitude_in_2, 0, Qt::AlignLeft);

        VPP_2 = new QLabel(page_5);
        VPP_2->setObjectName(QString::fromUtf8("VPP_2"));
        VPP_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_27->addWidget(VPP_2, 0, Qt::AlignRight);

        VPP_in_2 = new QLabel(page_5);
        VPP_in_2->setObjectName(QString::fromUtf8("VPP_in_2"));
        VPP_in_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_27->addWidget(VPP_in_2, 0, Qt::AlignLeft);

        V_MAX_2 = new QLabel(page_5);
        V_MAX_2->setObjectName(QString::fromUtf8("V_MAX_2"));
        V_MAX_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_27->addWidget(V_MAX_2, 0, Qt::AlignRight);

        V_MAX_in_2 = new QLabel(page_5);
        V_MAX_in_2->setObjectName(QString::fromUtf8("V_MAX_in_2"));
        V_MAX_in_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_27->addWidget(V_MAX_in_2, 0, Qt::AlignLeft);


        verticalLayout_9->addLayout(horizontalLayout_27);

        verticalLayout_9->setStretch(0, 9);

        horizontalLayout_26->addLayout(verticalLayout_9);

        groupBox = new QGroupBox(page_5);
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
        dataNumSpinBox_4->setMaximum(2147483647);
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
        setButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #21618c;\n"
"}"));

        verticalLayout_10->addWidget(setButton_4);

        listenButton_4 = new QPushButton(groupBox);
        listenButton_4->setObjectName(QString::fromUtf8("listenButton_4"));
        listenButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #27ae60;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #229954;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1e8449;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #e74c3c;\n"
"}\n"
"\n"
"QPushButton:checked:hover {\n"
"    background-color: #c0392b;\n"
"}"));
        listenButton_4->setCheckable(true);

        verticalLayout_10->addWidget(listenButton_4);

        loopSendButton_4 = new QPushButton(groupBox);
        loopSendButton_4->setObjectName(QString::fromUtf8("loopSendButton_4"));
        loopSendButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #f39c12;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #e67e22;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #d35400;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #e74c3c;\n"
"}\n"
"\n"
"QPushButton:checked:hover {\n"
"    background-color: #c0392b;\n"
"}"));
        loopSendButton_4->setCheckable(true);

        verticalLayout_10->addWidget(loopSendButton_4);

        restartButton_4 = new QPushButton(groupBox);
        restartButton_4->setObjectName(QString::fromUtf8("restartButton_4"));
        restartButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #9b59b6;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #8e44ad;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7d3c98;\n"
"}"));

        verticalLayout_10->addWidget(restartButton_4);

        verticalLayout_10->setStretch(2, 2);

        horizontalLayout_26->addWidget(groupBox);

        horizontalLayout_26->setStretch(0, 3);

        horizontalLayout_3->addLayout(horizontalLayout_26);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        horizontalLayout_4 = new QHBoxLayout(page_6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        boxingxianshi = new QCustomPlot(page_6);
        boxingxianshi->setObjectName(QString::fromUtf8("boxingxianshi"));
        boxingxianshi->setStyleSheet(QString::fromUtf8("QCustomPlot {\n"
"    border: 2px solid #34495e;\n"
"    border-radius: 10px;\n"
"    background-color: white;\n"
"}"));

        horizontalLayout_36->addWidget(boxingxianshi);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(10);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(10, 10, 10, 10);
        label_dds_title = new QLabel(page_6);
        label_dds_title->setObjectName(QString::fromUtf8("label_dds_title"));
        label_dds_title->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    color: #2c3e50;\n"
"    padding: 5px;\n"
"}"));
        label_dds_title->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_dds_title);

        waveformSwitchButton = new QPushButton(page_6);
        waveformSwitchButton->setObjectName(QString::fromUtf8("waveformSwitchButton"));
        waveformSwitchButton->setMinimumSize(QSize(0, 45));
        waveformSwitchButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #21618c;\n"
"}"));

        verticalLayout_12->addWidget(waveformSwitchButton);

        handDrawButton = new QPushButton(page_6);
        handDrawButton->setObjectName(QString::fromUtf8("handDrawButton"));
        handDrawButton->setMinimumSize(QSize(0, 45));
        handDrawButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #e74c3c;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #a93226;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #27ae60;\n"
"}\n"
"\n"
"QPushButton:checked:hover {\n"
"    background-color: #229954;\n"
"}"));
        handDrawButton->setCheckable(true);

        verticalLayout_12->addWidget(handDrawButton);

        clearDrawButton = new QPushButton(page_6);
        clearDrawButton->setObjectName(QString::fromUtf8("clearDrawButton"));
        clearDrawButton->setMinimumSize(QSize(0, 40));
        clearDrawButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #95a5a6;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #7f8c8d;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #66727a;\n"
"}"));

        verticalLayout_12->addWidget(clearDrawButton);

        saveAndSendButton = new QPushButton(page_6);
        saveAndSendButton->setObjectName(QString::fromUtf8("saveAndSendButton"));
        saveAndSendButton->setMinimumSize(QSize(0, 45));
        saveAndSendButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #9b59b6;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #8e44ad;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7d3c98;\n"
"}"));

        verticalLayout_12->addWidget(saveAndSendButton);

        label_separator1 = new QLabel(page_6);
        label_separator1->setObjectName(QString::fromUtf8("label_separator1"));
        label_separator1->setMinimumSize(QSize(0, 20));
        label_separator1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #bdc3c7;\n"
"    max-height: 2px;\n"
"}"));

        verticalLayout_12->addWidget(label_separator1);

        frequencyUpButton = new QPushButton(page_6);
        frequencyUpButton->setObjectName(QString::fromUtf8("frequencyUpButton"));
        frequencyUpButton->setMinimumSize(QSize(0, 40));
        frequencyUpButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #16a085;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #138d75;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #117a65;\n"
"}"));

        verticalLayout_12->addWidget(frequencyUpButton);

        frequencyDownButton = new QPushButton(page_6);
        frequencyDownButton->setObjectName(QString::fromUtf8("frequencyDownButton"));
        frequencyDownButton->setMinimumSize(QSize(0, 40));
        frequencyDownButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #16a085;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #138d75;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #117a65;\n"
"}"));

        verticalLayout_12->addWidget(frequencyDownButton);

        amplitudeUpButton = new QPushButton(page_6);
        amplitudeUpButton->setObjectName(QString::fromUtf8("amplitudeUpButton"));
        amplitudeUpButton->setMinimumSize(QSize(0, 40));
        amplitudeUpButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #f39c12;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #e67e22;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #d35400;\n"
"}"));

        verticalLayout_12->addWidget(amplitudeUpButton);

        amplitudeDownButton = new QPushButton(page_6);
        amplitudeDownButton->setObjectName(QString::fromUtf8("amplitudeDownButton"));
        amplitudeDownButton->setMinimumSize(QSize(0, 40));
        amplitudeDownButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #f39c12;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #e67e22;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #d35400;\n"
"}"));

        verticalLayout_12->addWidget(amplitudeDownButton);

        label_separator2 = new QLabel(page_6);
        label_separator2->setObjectName(QString::fromUtf8("label_separator2"));
        label_separator2->setMinimumSize(QSize(0, 2));
        label_separator2->setMaximumSize(QSize(16777215, 2));
        label_separator2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #bdc3c7;\n"
"    margin: 10px 0px;\n"
"}"));

        verticalLayout_12->addWidget(label_separator2);

        currentWaveformLabel = new QLabel(page_6);
        currentWaveformLabel->setObjectName(QString::fromUtf8("currentWaveformLabel"));
        currentWaveformLabel->setMinimumSize(QSize(0, 50));
        currentWaveformLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #ecf0f1;\n"
"    color: #2c3e50;\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"}"));
        currentWaveformLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(currentWaveformLabel);

        sendProgressLabel = new QLabel(page_6);
        sendProgressLabel->setObjectName(QString::fromUtf8("sendProgressLabel"));
        sendProgressLabel->setMinimumSize(QSize(0, 40));
        sendProgressLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #e8f5e9;\n"
"    color: #27ae60;\n"
"    border: 2px solid #27ae60;\n"
"    border-radius: 8px;\n"
"    padding: 8px;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"}"));
        sendProgressLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(sendProgressLabel);

        verticalSpacer_dds = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_dds);


        horizontalLayout_36->addLayout(verticalLayout_12);

        horizontalLayout_36->setStretch(0, 3);

        horizontalLayout_4->addLayout(horizontalLayout_36);

        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        horizontalLayout_5 = new QHBoxLayout(page_7);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        shuzixinhaoboxing = new QCustomPlot(page_7);
        shuzixinhaoboxing->setObjectName(QString::fromUtf8("shuzixinhaoboxing"));

        verticalLayout_13->addWidget(shuzixinhaoboxing);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        pinglv = new QLabel(page_7);
        pinglv->setObjectName(QString::fromUtf8("pinglv"));
        pinglv->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_37->addWidget(pinglv);

        pinglv_in = new QLabel(page_7);
        pinglv_in->setObjectName(QString::fromUtf8("pinglv_in"));
        pinglv_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_37->addWidget(pinglv_in);

        zhankongbi = new QLabel(page_7);
        zhankongbi->setObjectName(QString::fromUtf8("zhankongbi"));
        zhankongbi->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_37->addWidget(zhankongbi);

        zhankongbi_in = new QLabel(page_7);
        zhankongbi_in->setObjectName(QString::fromUtf8("zhankongbi_in"));
        zhankongbi_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_37->addWidget(zhankongbi_in);

        Hvolt_t = new QLabel(page_7);
        Hvolt_t->setObjectName(QString::fromUtf8("Hvolt_t"));
        Hvolt_t->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_37->addWidget(Hvolt_t);

        Hvolt_t_in = new QLabel(page_7);
        Hvolt_t_in->setObjectName(QString::fromUtf8("Hvolt_t_in"));
        Hvolt_t_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_37->addWidget(Hvolt_t_in);

        Lvolt_t = new QLabel(page_7);
        Lvolt_t->setObjectName(QString::fromUtf8("Lvolt_t"));
        Lvolt_t->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_37->addWidget(Lvolt_t);

        Lvolt_t_in = new QLabel(page_7);
        Lvolt_t_in->setObjectName(QString::fromUtf8("Lvolt_t_in"));
        Lvolt_t_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_37->addWidget(Lvolt_t_in);


        verticalLayout_13->addLayout(horizontalLayout_37);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(50);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(50, -1, 50, -1);
        pushButton_2 = new QPushButton(page_7);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 45));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #27ae60;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #229954;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1e8449;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #e74c3c;\n"
"}\n"
"\n"
"QPushButton:checked:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"\n"
"QPushButton:checked:pressed {\n"
"    background-color: #a93226;\n"
"}"));
        pushButton_2->setCheckable(true);
        pushButton_2->setAutoDefault(false);
        pushButton_2->setFlat(false);

        horizontalLayout_2->addWidget(pushButton_2);

        comboBox = new QComboBox(page_7);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 45));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: white;\n"
"    color: #2c3e50;\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 8px;\n"
"    padding: 8px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border-color: #3498db;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border-color: #3498db;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 30px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: none;\n"
"    border-left: 5px solid transparent;\n"
"    border-right: 5px solid transparent;\n"
"    border-top: 6px solid #2c3e50;\n"
"    margin-right: 8px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    background-color: white;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 6px;\n"
"    selection-background-color: #3498db;\n"
"    selection-color: white;\n"
"    padding: 5px;\n"
"}"));

        horizontalLayout_2->addWidget(comboBox);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_13->addLayout(horizontalLayout_2);

        verticalLayout_13->setStretch(0, 3);

        horizontalLayout_5->addLayout(verticalLayout_13);

        stackedWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        horizontalLayout = new QHBoxLayout(page_8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        customPlot_3 = new QCustomPlot(page_8);
        customPlot_3->setObjectName(QString::fromUtf8("customPlot_3"));
        sizePolicy.setHeightForWidth(customPlot_3->sizePolicy().hasHeightForWidth());
        customPlot_3->setSizePolicy(sizePolicy);

        verticalLayout_14->addWidget(customPlot_3);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(15);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        horizontalLayout_38->setContentsMargins(20, -1, 20, -1);
        Frequency_3 = new QLabel(page_8);
        Frequency_3->setObjectName(QString::fromUtf8("Frequency_3"));
        Frequency_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_38->addWidget(Frequency_3, 0, Qt::AlignRight);

        Frequency_in_3 = new QLabel(page_8);
        Frequency_in_3->setObjectName(QString::fromUtf8("Frequency_in_3"));
        Frequency_in_3->setMinimumSize(QSize(100, 0));
        Frequency_in_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_38->addWidget(Frequency_in_3, 0, Qt::AlignLeft);

        Amplitude_3 = new QLabel(page_8);
        Amplitude_3->setObjectName(QString::fromUtf8("Amplitude_3"));
        Amplitude_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_38->addWidget(Amplitude_3, 0, Qt::AlignRight);

        Amplitude_in_3 = new QLabel(page_8);
        Amplitude_in_3->setObjectName(QString::fromUtf8("Amplitude_in_3"));
        Amplitude_in_3->setMinimumSize(QSize(80, 0));
        Amplitude_in_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_38->addWidget(Amplitude_in_3, 0, Qt::AlignLeft);

        label_snr = new QLabel(page_8);
        label_snr->setObjectName(QString::fromUtf8("label_snr"));
        label_snr->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_38->addWidget(label_snr, 0, Qt::AlignRight);

        label_snr_value = new QLabel(page_8);
        label_snr_value->setObjectName(QString::fromUtf8("label_snr_value"));
        label_snr_value->setMinimumSize(QSize(80, 0));
        label_snr_value->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #27ae60;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_38->addWidget(label_snr_value, 0, Qt::AlignLeft);


        verticalLayout_14->addLayout(horizontalLayout_38);

        horizontalLayout_spectrum_info2 = new QHBoxLayout();
        horizontalLayout_spectrum_info2->setSpacing(15);
        horizontalLayout_spectrum_info2->setObjectName(QString::fromUtf8("horizontalLayout_spectrum_info2"));
        horizontalLayout_spectrum_info2->setContentsMargins(20, -1, 20, -1);
        label_thd = new QLabel(page_8);
        label_thd->setObjectName(QString::fromUtf8("label_thd"));
        label_thd->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_spectrum_info2->addWidget(label_thd, 0, Qt::AlignRight);

        label_thd_value = new QLabel(page_8);
        label_thd_value->setObjectName(QString::fromUtf8("label_thd_value"));
        label_thd_value->setMinimumSize(QSize(100, 0));
        label_thd_value->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #e67e22;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_spectrum_info2->addWidget(label_thd_value, 0, Qt::AlignLeft);

        label_bandwidth = new QLabel(page_8);
        label_bandwidth->setObjectName(QString::fromUtf8("label_bandwidth"));
        label_bandwidth->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_spectrum_info2->addWidget(label_bandwidth, 0, Qt::AlignRight);

        label_bandwidth_value = new QLabel(page_8);
        label_bandwidth_value->setObjectName(QString::fromUtf8("label_bandwidth_value"));
        label_bandwidth_value->setMinimumSize(QSize(80, 0));
        label_bandwidth_value->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #9b59b6;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_spectrum_info2->addWidget(label_bandwidth_value, 0, Qt::AlignLeft);

        label_harmonics = new QLabel(page_8);
        label_harmonics->setObjectName(QString::fromUtf8("label_harmonics"));
        label_harmonics->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_spectrum_info2->addWidget(label_harmonics, 0, Qt::AlignRight);

        label_harmonics_value = new QLabel(page_8);
        label_harmonics_value->setObjectName(QString::fromUtf8("label_harmonics_value"));
        label_harmonics_value->setMinimumSize(QSize(80, 0));
        label_harmonics_value->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #e74c3c;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 2px 5px;\n"
"}"));

        horizontalLayout_spectrum_info2->addWidget(label_harmonics_value, 0, Qt::AlignLeft);


        verticalLayout_14->addLayout(horizontalLayout_spectrum_info2);

        verticalLayout_14->setStretch(0, 9);

        horizontalLayout_35->addLayout(verticalLayout_14);

        groupBox_2 = new QGroupBox(page_8);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_15 = new QVBoxLayout(groupBox_2);
        verticalLayout_15->setSpacing(10);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(20);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_16->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(5);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        horizontalLayout_39->setContentsMargins(-1, -1, 30, -1);
        label_29 = new QLabel(groupBox_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setEnabled(true);
        sizePolicy.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy);
        label_29->setMinimumSize(QSize(144, 0));
        label_29->setMaximumSize(QSize(144, 16777215));
        label_29->setLineWidth(1);
        label_29->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_39->addWidget(label_29);

        portSpinBox_5 = new QSpinBox(groupBox_2);
        portSpinBox_5->setObjectName(QString::fromUtf8("portSpinBox_5"));
        sizePolicy1.setHeightForWidth(portSpinBox_5->sizePolicy().hasHeightForWidth());
        portSpinBox_5->setSizePolicy(sizePolicy1);
        portSpinBox_5->setMinimumSize(QSize(80, 0));
        portSpinBox_5->setLayoutDirection(Qt::LeftToRight);
        portSpinBox_5->setStyleSheet(QString::fromUtf8("padding: 0px; margin-left: -0;"));
        portSpinBox_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        portSpinBox_5->setButtonSymbols(QAbstractSpinBox::NoButtons);
        portSpinBox_5->setMinimum(1);
        portSpinBox_5->setMaximum(65535);
        portSpinBox_5->setValue(6102);

        horizontalLayout_39->addWidget(portSpinBox_5);


        verticalLayout_16->addLayout(horizontalLayout_39);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setSpacing(5);
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        horizontalLayout_42->setContentsMargins(-1, -1, 30, -1);
        label_32 = new QLabel(groupBox_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_42->addWidget(label_32, 0, Qt::AlignVCenter);

        dataNumSpinBox_5 = new QSpinBox(groupBox_2);
        dataNumSpinBox_5->setObjectName(QString::fromUtf8("dataNumSpinBox_5"));
        sizePolicy1.setHeightForWidth(dataNumSpinBox_5->sizePolicy().hasHeightForWidth());
        dataNumSpinBox_5->setSizePolicy(sizePolicy1);
        dataNumSpinBox_5->setMinimumSize(QSize(80, 0));
        dataNumSpinBox_5->setFrame(false);
        dataNumSpinBox_5->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dataNumSpinBox_5->setMinimum(1);
        dataNumSpinBox_5->setMaximum(2147483647);
        dataNumSpinBox_5->setValue(1);

        horizontalLayout_42->addWidget(dataNumSpinBox_5);


        verticalLayout_16->addLayout(horizontalLayout_42);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(5);
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        horizontalLayout_43->setContentsMargins(-1, -1, 30, -1);
        label_33 = new QLabel(groupBox_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_43->addWidget(label_33);

        targetPortSpinBox_5 = new QSpinBox(groupBox_2);
        targetPortSpinBox_5->setObjectName(QString::fromUtf8("targetPortSpinBox_5"));
        sizePolicy1.setHeightForWidth(targetPortSpinBox_5->sizePolicy().hasHeightForWidth());
        targetPortSpinBox_5->setSizePolicy(sizePolicy1);
        targetPortSpinBox_5->setMinimumSize(QSize(80, 0));
        targetPortSpinBox_5->setFrame(false);
        targetPortSpinBox_5->setButtonSymbols(QAbstractSpinBox::NoButtons);
        targetPortSpinBox_5->setMinimum(1);
        targetPortSpinBox_5->setMaximum(65535);
        targetPortSpinBox_5->setValue(5000);

        horizontalLayout_43->addWidget(targetPortSpinBox_5);


        verticalLayout_16->addLayout(horizontalLayout_43);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(5);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        label_34 = new QLabel(groupBox_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_44->addWidget(label_34);

        targetIpLineEdit_5 = new QLineEdit(groupBox_2);
        targetIpLineEdit_5->setObjectName(QString::fromUtf8("targetIpLineEdit_5"));
        sizePolicy1.setHeightForWidth(targetIpLineEdit_5->sizePolicy().hasHeightForWidth());
        targetIpLineEdit_5->setSizePolicy(sizePolicy1);
        targetIpLineEdit_5->setMinimumSize(QSize(120, 0));

        horizontalLayout_44->addWidget(targetIpLineEdit_5);


        verticalLayout_16->addLayout(horizontalLayout_44);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(5);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        label_35 = new QLabel(groupBox_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_45->addWidget(label_35);

        ipLineEdit_5 = new QLineEdit(groupBox_2);
        ipLineEdit_5->setObjectName(QString::fromUtf8("ipLineEdit_5"));
        sizePolicy1.setHeightForWidth(ipLineEdit_5->sizePolicy().hasHeightForWidth());
        ipLineEdit_5->setSizePolicy(sizePolicy1);
        ipLineEdit_5->setMinimumSize(QSize(120, 0));

        horizontalLayout_45->addWidget(ipLineEdit_5);


        verticalLayout_16->addLayout(horizontalLayout_45);


        verticalLayout_15->addLayout(verticalLayout_16);

        setButton_5 = new QPushButton(groupBox_2);
        setButton_5->setObjectName(QString::fromUtf8("setButton_5"));
        setButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #21618c;\n"
"}"));

        verticalLayout_15->addWidget(setButton_5);

        listenButton_5 = new QPushButton(groupBox_2);
        listenButton_5->setObjectName(QString::fromUtf8("listenButton_5"));
        listenButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #27ae60;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #229954;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1e8449;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #e74c3c;\n"
"}\n"
"\n"
"QPushButton:checked:hover {\n"
"    background-color: #c0392b;\n"
"}"));
        listenButton_5->setCheckable(true);

        verticalLayout_15->addWidget(listenButton_5);

        loopSendButton_5 = new QPushButton(groupBox_2);
        loopSendButton_5->setObjectName(QString::fromUtf8("loopSendButton_5"));
        loopSendButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #f39c12;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #e67e22;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #d35400;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #e74c3c;\n"
"}\n"
"\n"
"QPushButton:checked:hover {\n"
"    background-color: #c0392b;\n"
"}"));
        loopSendButton_5->setCheckable(true);

        verticalLayout_15->addWidget(loopSendButton_5);

        restartButton_5 = new QPushButton(groupBox_2);
        restartButton_5->setObjectName(QString::fromUtf8("restartButton_5"));
        restartButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #9b59b6;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #8e44ad;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7d3c98;\n"
"}"));

        verticalLayout_15->addWidget(restartButton_5);

        verticalLayout_15->setStretch(2, 2);

        horizontalLayout_35->addWidget(groupBox_2);

        horizontalLayout_35->setStretch(0, 3);

        horizontalLayout->addLayout(horizontalLayout_35);

        stackedWidget->addWidget(page_8);

        horizontalLayout_main->addWidget(stackedWidget);

        horizontalLayout_main->setStretch(1, 1);
        shiboqi_remake->setCentralWidget(centralwidget);

        retranslateUi(shiboqi_remake);

        stackedWidget->setCurrentIndex(0);
        pushButton_2->setDefault(false);


        QMetaObject::connectSlotsByName(shiboqi_remake);
    } // setupUi

    void retranslateUi(QMainWindow *shiboqi_remake)
    {
        shiboqi_remake->setWindowTitle(QCoreApplication::translate("shiboqi_remake", "shiboqi_remake", nullptr));
        titleLabel->setText(QCoreApplication::translate("shiboqi_remake", "\345\244\232\345\212\237\350\203\275\350\260\203\350\257\225\345\231\250", nullptr));
        menuLabel->setText(QCoreApplication::translate("shiboqi_remake", "\345\212\237\350\203\275\350\217\234\345\215\225", nullptr));
        navButton_oscilloscope->setText(QCoreApplication::translate("shiboqi_remake", "  \360\237\223\212  \347\244\272\346\263\242\345\231\250", nullptr));
        navButton_dds->setText(QCoreApplication::translate("shiboqi_remake", "  \360\237\216\233\357\270\217  DDS\350\256\276\347\275\256", nullptr));
        navButton_digital->setText(QCoreApplication::translate("shiboqi_remake", "  \360\237\223\241  \346\225\260\345\255\227\344\277\241\345\217\267", nullptr));
        navButton_spectrum->setText(QCoreApplication::translate("shiboqi_remake", "  \360\237\223\210  \351\242\221\350\260\261\345\210\206\346\236\220", nullptr));
        copyrightLabel1->setText(QCoreApplication::translate("shiboqi_remake", "\345\207\272\345\223\201\346\226\271\357\274\232\344\272\272\345\226\204\350\242\253\344\272\272\346\254\272\357\274\214\351\251\254\345\226\204\351\251\254\345\230\211\347\245\272\351\230\237", nullptr));
        copyrightLabel2->setText(QCoreApplication::translate("shiboqi_remake", "\345\215\227\344\272\254\345\255\235\351\231\265\345\215\253\351\236\255\347\202\256\345\216\202\347\240\224\345\217\221\344\270\255\345\277\203", nullptr));
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
        label_dds_title->setText(QCoreApplication::translate("shiboqi_remake", "\346\263\242\345\275\242\346\216\247\345\210\266", nullptr));
        waveformSwitchButton->setText(QCoreApplication::translate("shiboqi_remake", "\360\237\224\204 \345\210\207\346\215\242\346\263\242\345\275\242", nullptr));
        handDrawButton->setText(QCoreApplication::translate("shiboqi_remake", "\342\234\217\357\270\217 \346\211\213\347\273\230\346\250\241\345\274\217", nullptr));
        clearDrawButton->setText(QCoreApplication::translate("shiboqi_remake", "\360\237\227\221\357\270\217 \346\270\205\351\231\244\347\273\230\345\210\266", nullptr));
        saveAndSendButton->setText(QCoreApplication::translate("shiboqi_remake", "\360\237\222\276 \344\277\235\345\255\230\345\271\266\345\217\221\351\200\201", nullptr));
        label_separator1->setText(QString());
        frequencyUpButton->setText(QCoreApplication::translate("shiboqi_remake", "\342\254\206\357\270\217 \351\242\221\347\216\207+", nullptr));
        frequencyDownButton->setText(QCoreApplication::translate("shiboqi_remake", "\342\254\207\357\270\217 \351\242\221\347\216\207-", nullptr));
        amplitudeUpButton->setText(QCoreApplication::translate("shiboqi_remake", "\342\254\206\357\270\217 \345\271\205\345\272\246+", nullptr));
        amplitudeDownButton->setText(QCoreApplication::translate("shiboqi_remake", "\342\254\207\357\270\217 \345\271\205\345\272\246-", nullptr));
        label_separator2->setText(QString());
        currentWaveformLabel->setText(QCoreApplication::translate("shiboqi_remake", "\345\275\223\345\211\215\346\263\242\345\275\242: \351\224\257\351\275\277\346\263\242", nullptr));
        sendProgressLabel->setText(QCoreApplication::translate("shiboqi_remake", "\345\217\221\351\200\201\350\277\233\345\272\246: 0%", nullptr));
        pinglv->setText(QCoreApplication::translate("shiboqi_remake", "\351\242\221\347\216\207\357\274\232", nullptr));
        pinglv_in->setText(QCoreApplication::translate("shiboqi_remake", "0 Hz", nullptr));
        zhankongbi->setText(QCoreApplication::translate("shiboqi_remake", "\345\215\240\347\251\272\346\257\224\357\274\232", nullptr));
        zhankongbi_in->setText(QCoreApplication::translate("shiboqi_remake", "0", nullptr));
        Hvolt_t->setText(QCoreApplication::translate("shiboqi_remake", "\351\253\230\347\224\265\345\271\263\346\227\266\351\227\264\357\274\232", nullptr));
        Hvolt_t_in->setText(QCoreApplication::translate("shiboqi_remake", "0 us", nullptr));
        Lvolt_t->setText(QCoreApplication::translate("shiboqi_remake", "\344\275\216\347\224\265\345\271\263\346\227\266\351\227\264\357\274\232", nullptr));
        Lvolt_t_in->setText(QCoreApplication::translate("shiboqi_remake", "0 us", nullptr));
        pushButton_2->setText(QCoreApplication::translate("shiboqi_remake", "\360\237\224\214 \345\274\200\345\220\257\350\277\236\346\216\245", nullptr));
        Frequency_3->setText(QCoreApplication::translate("shiboqi_remake", "\344\270\273\351\242\221\347\216\207:", nullptr));
        Frequency_in_3->setText(QCoreApplication::translate("shiboqi_remake", "0 Hz", nullptr));
        Amplitude_3->setText(QCoreApplication::translate("shiboqi_remake", "\345\271\205\345\272\246:", nullptr));
        Amplitude_in_3->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        label_snr->setText(QCoreApplication::translate("shiboqi_remake", "SNR:", nullptr));
        label_snr_value->setText(QCoreApplication::translate("shiboqi_remake", "0 dB", nullptr));
        label_thd->setText(QCoreApplication::translate("shiboqi_remake", "THD:", nullptr));
        label_thd_value->setText(QCoreApplication::translate("shiboqi_remake", "0 %", nullptr));
        label_bandwidth->setText(QCoreApplication::translate("shiboqi_remake", "\345\270\246\345\256\275:", nullptr));
        label_bandwidth_value->setText(QCoreApplication::translate("shiboqi_remake", "0 Hz", nullptr));
        label_harmonics->setText(QCoreApplication::translate("shiboqi_remake", "\350\260\220\346\263\242\346\225\260:", nullptr));
        label_harmonics_value->setText(QCoreApplication::translate("shiboqi_remake", "0", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("shiboqi_remake", "UDP\350\256\276\347\275\256", nullptr));
        label_29->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_29->setText(QCoreApplication::translate("shiboqi_remake", " \347\253\257\345\217\243:", nullptr));
        label_32->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_32->setText(QCoreApplication::translate("shiboqi_remake", "\346\225\260\346\215\256\344\270\252\346\225\260:", nullptr));
        dataNumSpinBox_5->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_33->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_33->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207\347\253\257\345\217\243:", nullptr));
        targetPortSpinBox_5->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_34->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_34->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207IP\345\234\260\345\235\200:", nullptr));
        targetIpLineEdit_5->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        targetIpLineEdit_5->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.2", nullptr));
        label_35->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_35->setText(QCoreApplication::translate("shiboqi_remake", "\346\234\254\346\234\272IP\345\234\260\345\235\200:", nullptr));
        ipLineEdit_5->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        ipLineEdit_5->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.3", nullptr));
        setButton_5->setText(QCoreApplication::translate("shiboqi_remake", "\350\256\276\347\275\256UDP\350\277\236\346\216\245\345\217\202\346\225\260", nullptr));
        listenButton_5->setText(QCoreApplication::translate("shiboqi_remake", "\345\274\200\345\247\213\347\233\221\345\220\254", nullptr));
        loopSendButton_5->setText(QCoreApplication::translate("shiboqi_remake", "\345\276\252\347\216\257\345\217\221\351\200\201", nullptr));
        restartButton_5->setText(QCoreApplication::translate("shiboqi_remake", "\345\217\221\351\200\201\351\207\207\351\233\206\345\221\275\344\273\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class shiboqi_remake: public Ui_shiboqi_remake {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHIBOQI_REMAKE_H
