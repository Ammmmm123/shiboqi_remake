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
    QStackedWidget *stackedWidget_2;
    QWidget *page_9;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *customPlot_spectrum;
    QHBoxLayout *horizontalLayout_9;
    QLabel *spectrum_freq_label;
    QLabel *label;
    QLabel *spectrum_amp_label;
    QLabel *label_2;
    QLabel *spectrum_second_freq_label;
    QLabel *label_3;
    QLabel *spectrum_second_amp_label;
    QLabel *label_4;
    QWidget *displayStackedWidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *customPlot_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *Frequency_4;
    QLabel *Frequency_4_in;
    QLabel *Amplitude_4;
    QLabel *Amplitude_4_in;
    QLabel *Vpp;
    QLabel *Vpp_in;
    QLabel *Vmax;
    QLabel *Vmax_in;
    QLabel *Vmin;
    QLabel *Vmin_in;
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

    void setupUi(QMainWindow *shiboqi_remake)
    {
        if (shiboqi_remake->objectName().isEmpty())
            shiboqi_remake->setObjectName(QString::fromUtf8("shiboqi_remake"));
        shiboqi_remake->resize(1182, 696);
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
        copyrightLabel1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        copyrightLabel1->setWordWrap(true);

        verticalLayout_sidebar->addWidget(copyrightLabel1);

        copyrightLabel2 = new QLabel(sidebarWidget);
        copyrightLabel2->setObjectName(QString::fromUtf8("copyrightLabel2"));
        copyrightLabel2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #ecf0f1;\n"
"    padding: 5px 10px;\n"
"    font-size: 11px;\n"
"}"));
        copyrightLabel2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
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
        stackedWidget_2 = new QStackedWidget(page_5);
        stackedWidget_2->setObjectName(QString::fromUtf8("stackedWidget_2"));
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        horizontalLayout_8 = new QHBoxLayout(page_9);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        customPlot_spectrum = new QCustomPlot(page_9);
        customPlot_spectrum->setObjectName(QString::fromUtf8("customPlot_spectrum"));

        verticalLayout_3->addWidget(customPlot_spectrum);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        spectrum_freq_label = new QLabel(page_9);
        spectrum_freq_label->setObjectName(QString::fromUtf8("spectrum_freq_label"));
        spectrum_freq_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_9->addWidget(spectrum_freq_label);

        label = new QLabel(page_9);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #e74c3c;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #fee;\n"
"    border: 1px solid #e74c3c;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_9->addWidget(label);

        spectrum_amp_label = new QLabel(page_9);
        spectrum_amp_label->setObjectName(QString::fromUtf8("spectrum_amp_label"));
        spectrum_amp_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_9->addWidget(spectrum_amp_label);

        label_2 = new QLabel(page_9);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #e74c3c;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #fee;\n"
"    border: 1px solid #e74c3c;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_9->addWidget(label_2);

        spectrum_second_freq_label = new QLabel(page_9);
        spectrum_second_freq_label->setObjectName(QString::fromUtf8("spectrum_second_freq_label"));
        spectrum_second_freq_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_9->addWidget(spectrum_second_freq_label);

        label_3 = new QLabel(page_9);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #e3f2fd;\n"
"    border: 1px solid #3498db;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_9->addWidget(label_3);

        spectrum_second_amp_label = new QLabel(page_9);
        spectrum_second_amp_label->setObjectName(QString::fromUtf8("spectrum_second_amp_label"));
        spectrum_second_amp_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_9->addWidget(spectrum_second_amp_label);

        label_4 = new QLabel(page_9);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3498db;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #e3f2fd;\n"
"    border: 1px solid #3498db;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_9->addWidget(label_4);


        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalLayout_3->setStretch(0, 3);

        horizontalLayout_8->addLayout(verticalLayout_3);

        stackedWidget_2->addWidget(page_9);
        displayStackedWidget = new QWidget();
        displayStackedWidget->setObjectName(QString::fromUtf8("displayStackedWidget"));
        horizontalLayout_6 = new QHBoxLayout(displayStackedWidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        customPlot_4 = new QCustomPlot(displayStackedWidget);
        customPlot_4->setObjectName(QString::fromUtf8("customPlot_4"));

        verticalLayout_2->addWidget(customPlot_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        Frequency_4 = new QLabel(displayStackedWidget);
        Frequency_4->setObjectName(QString::fromUtf8("Frequency_4"));
        Frequency_4->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Frequency_4);

        Frequency_4_in = new QLabel(displayStackedWidget);
        Frequency_4_in->setObjectName(QString::fromUtf8("Frequency_4_in"));
        Frequency_4_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #16a085;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #e8f5e9;\n"
"    border: 1px solid #16a085;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Frequency_4_in);

        Amplitude_4 = new QLabel(displayStackedWidget);
        Amplitude_4->setObjectName(QString::fromUtf8("Amplitude_4"));
        Amplitude_4->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Amplitude_4);

        Amplitude_4_in = new QLabel(displayStackedWidget);
        Amplitude_4_in->setObjectName(QString::fromUtf8("Amplitude_4_in"));
        Amplitude_4_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #16a085;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #e8f5e9;\n"
"    border: 1px solid #16a085;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Amplitude_4_in);

        Vpp = new QLabel(displayStackedWidget);
        Vpp->setObjectName(QString::fromUtf8("Vpp"));
        Vpp->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Vpp);

        Vpp_in = new QLabel(displayStackedWidget);
        Vpp_in->setObjectName(QString::fromUtf8("Vpp_in"));
        Vpp_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #16a085;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #e8f5e9;\n"
"    border: 1px solid #16a085;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Vpp_in);

        Vmax = new QLabel(displayStackedWidget);
        Vmax->setObjectName(QString::fromUtf8("Vmax"));
        Vmax->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Vmax);

        Vmax_in = new QLabel(displayStackedWidget);
        Vmax_in->setObjectName(QString::fromUtf8("Vmax_in"));
        Vmax_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #16a085;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #e8f5e9;\n"
"    border: 1px solid #16a085;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Vmax_in);

        Vmin = new QLabel(displayStackedWidget);
        Vmin->setObjectName(QString::fromUtf8("Vmin"));
        Vmin->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #2c3e50;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    padding: 4px 8px;\n"
"    background-color: #ecf0f1;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Vmin);

        Vmin_in = new QLabel(displayStackedWidget);
        Vmin_in->setObjectName(QString::fromUtf8("Vmin_in"));
        Vmin_in->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #16a085;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 4px 12px;\n"
"    background-color: #e8f5e9;\n"
"    border: 1px solid #16a085;\n"
"    border-radius: 4px;\n"
"}"));

        horizontalLayout_7->addWidget(Vmin_in);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalLayout_2->setStretch(0, 3);

        horizontalLayout_6->addLayout(verticalLayout_2);

        stackedWidget_2->addWidget(displayStackedWidget);

        horizontalLayout_26->addWidget(stackedWidget_2);

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
        portSpinBox_4->setMinimumSize(QSize(100, 32));
        portSpinBox_4->setLayoutDirection(Qt::LeftToRight);
        portSpinBox_4->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"    background-color: white;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 6px;\n"
"    padding: 5px 10px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QSpinBox:hover {\n"
"    border-color: #2980b9;\n"
"    background-color: #ecf8ff;\n"
"}\n"
"\n"
"QSpinBox:focus {\n"
"    border-color: #1abc9c;\n"
"    background-color: #e8f8f5;\n"
"}"));
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
        dataNumSpinBox_4->setMinimumSize(QSize(100, 32));
        dataNumSpinBox_4->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"    background-color: white;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 6px;\n"
"    padding: 5px 10px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QSpinBox:hover {\n"
"    border-color: #2980b9;\n"
"    background-color: #ecf8ff;\n"
"}\n"
"\n"
"QSpinBox:focus {\n"
"    border-color: #1abc9c;\n"
"    background-color: #e8f8f5;\n"
"}"));
        dataNumSpinBox_4->setFrame(true);
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
        targetPortSpinBox_4->setMinimumSize(QSize(100, 32));
        targetPortSpinBox_4->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"    background-color: white;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 6px;\n"
"    padding: 5px 10px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QSpinBox:hover {\n"
"    border-color: #2980b9;\n"
"    background-color: #ecf8ff;\n"
"}\n"
"\n"
"QSpinBox:focus {\n"
"    border-color: #1abc9c;\n"
"    background-color: #e8f8f5;\n"
"}"));
        targetPortSpinBox_4->setFrame(true);
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
        targetIpLineEdit_4->setMinimumSize(QSize(150, 32));
        targetIpLineEdit_4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 6px;\n"
"    padding: 5px 10px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border-color: #2980b9;\n"
"    background-color: #ecf8ff;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #1abc9c;\n"
"    background-color: #e8f8f5;\n"
"}"));

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
        ipLineEdit_4->setMinimumSize(QSize(150, 32));
        ipLineEdit_4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 6px;\n"
"    padding: 5px 10px;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border-color: #2980b9;\n"
"    background-color: #ecf8ff;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #1abc9c;\n"
"    background-color: #e8f8f5;\n"
"}"));

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

        verticalLayout_10->setStretch(3, 2);

        horizontalLayout_26->addWidget(groupBox);


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
        spectrum_freq_label->setText(QCoreApplication::translate("shiboqi_remake", "\344\270\273\351\242\221\347\216\207 \357\274\232", nullptr));
        label->setText(QCoreApplication::translate("shiboqi_remake", "0.00 Hz", nullptr));
        spectrum_amp_label->setText(QCoreApplication::translate("shiboqi_remake", "\344\270\273\345\271\205\345\272\246 \357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("shiboqi_remake", "0.000 V", nullptr));
        spectrum_second_freq_label->setText(QCoreApplication::translate("shiboqi_remake", "\346\254\241\351\242\221\347\216\207 \357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("shiboqi_remake", "0.00 Hz", nullptr));
        spectrum_second_amp_label->setText(QCoreApplication::translate("shiboqi_remake", "\346\254\241\345\271\205\345\272\246 \357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("shiboqi_remake", "0.000 V", nullptr));
        Frequency_4->setText(QCoreApplication::translate("shiboqi_remake", "\351\242\221\347\216\207 \357\274\232", nullptr));
        Frequency_4_in->setText(QCoreApplication::translate("shiboqi_remake", "0 Hz", nullptr));
        Amplitude_4->setText(QCoreApplication::translate("shiboqi_remake", "\345\271\205\345\272\246 \357\274\232", nullptr));
        Amplitude_4_in->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        Vpp->setText(QCoreApplication::translate("shiboqi_remake", "Vpp \357\274\232", nullptr));
        Vpp_in->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        Vmax->setText(QCoreApplication::translate("shiboqi_remake", "Vmax \357\274\232", nullptr));
        Vmax_in->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        Vmin->setText(QCoreApplication::translate("shiboqi_remake", "Vmin \357\274\232", nullptr));
        Vmin_in->setText(QCoreApplication::translate("shiboqi_remake", "0 V", nullptr));
        groupBox->setTitle(QCoreApplication::translate("shiboqi_remake", "UDP\350\256\276\347\275\256", nullptr));
        label_22->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_22->setText(QCoreApplication::translate("shiboqi_remake", " \347\253\257\345\217\243:", nullptr));
        label_25->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_25->setText(QCoreApplication::translate("shiboqi_remake", "\346\225\260\346\215\256\344\270\252\346\225\260:", nullptr));
        label_26->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_26->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207\347\253\257\345\217\243:", nullptr));
        label_27->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_27->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207IP\345\234\260\345\235\200:", nullptr));
        targetIpLineEdit_4->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.2", nullptr));
        label_28->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_28->setText(QCoreApplication::translate("shiboqi_remake", "\346\234\254\346\234\272IP\345\234\260\345\235\200:", nullptr));
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
    } // retranslateUi

};

namespace Ui {
    class shiboqi_remake: public Ui_shiboqi_remake {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHIBOQI_REMAKE_H
