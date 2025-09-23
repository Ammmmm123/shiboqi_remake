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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_shiboqi_remake
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_main;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ipLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *portSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *targetIpLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *targetPortSpinBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *dataNumSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *dividerSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *setButton;
    QPushButton *listenButton;
    QPushButton *loopSendButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *shiboqi_remake)
    {
        if (shiboqi_remake->objectName().isEmpty())
            shiboqi_remake->setObjectName(QString::fromUtf8("shiboqi_remake"));
        shiboqi_remake->resize(800, 600);
        centralwidget = new QWidget(shiboqi_remake);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_main = new QHBoxLayout(centralwidget);
        horizontalLayout_main->setObjectName(QString::fromUtf8("horizontalLayout_main"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_main->addItem(horizontalSpacer);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        ipLineEdit = new QLineEdit(groupBox);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ipLineEdit->sizePolicy().hasHeightForWidth());
        ipLineEdit->setSizePolicy(sizePolicy);
        ipLineEdit->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(ipLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(0, -1, 20, -1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(144, 0));
        label_2->setMaximumSize(QSize(144, 16777215));
        label_2->setLineWidth(1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        portSpinBox = new QSpinBox(groupBox);
        portSpinBox->setObjectName(QString::fromUtf8("portSpinBox"));
        sizePolicy.setHeightForWidth(portSpinBox->sizePolicy().hasHeightForWidth());
        portSpinBox->setSizePolicy(sizePolicy);
        portSpinBox->setMinimumSize(QSize(80, 0));
        portSpinBox->setLayoutDirection(Qt::LeftToRight);
        portSpinBox->setStyleSheet(QString::fromUtf8("padding: 0px; margin-left: -0;"));
        portSpinBox->setAlignment(Qt::AlignCenter);
        portSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        portSpinBox->setMinimum(1);
        portSpinBox->setMaximum(65535);
        portSpinBox->setValue(6102);

        horizontalLayout_2->addWidget(portSpinBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        targetIpLineEdit = new QLineEdit(groupBox);
        targetIpLineEdit->setObjectName(QString::fromUtf8("targetIpLineEdit"));
        sizePolicy.setHeightForWidth(targetIpLineEdit->sizePolicy().hasHeightForWidth());
        targetIpLineEdit->setSizePolicy(sizePolicy);
        targetIpLineEdit->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(targetIpLineEdit);


        horizontalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        targetPortSpinBox = new QSpinBox(groupBox);
        targetPortSpinBox->setObjectName(QString::fromUtf8("targetPortSpinBox"));
        sizePolicy.setHeightForWidth(targetPortSpinBox->sizePolicy().hasHeightForWidth());
        targetPortSpinBox->setSizePolicy(sizePolicy);
        targetPortSpinBox->setMinimumSize(QSize(80, 0));
        targetPortSpinBox->setFrame(false);
        targetPortSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        targetPortSpinBox->setMinimum(1);
        targetPortSpinBox->setMaximum(65535);
        targetPortSpinBox->setValue(5000);

        horizontalLayout_4->addWidget(targetPortSpinBox);


        horizontalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        dataNumSpinBox = new QSpinBox(groupBox);
        dataNumSpinBox->setObjectName(QString::fromUtf8("dataNumSpinBox"));
        sizePolicy.setHeightForWidth(dataNumSpinBox->sizePolicy().hasHeightForWidth());
        dataNumSpinBox->setSizePolicy(sizePolicy);
        dataNumSpinBox->setMinimumSize(QSize(80, 0));
        dataNumSpinBox->setFrame(false);
        dataNumSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dataNumSpinBox->setMinimum(1);
        dataNumSpinBox->setMaximum(1000000);
        dataNumSpinBox->setValue(1);

        horizontalLayout_5->addWidget(dataNumSpinBox);


        horizontalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        dividerSpinBox = new QSpinBox(groupBox);
        dividerSpinBox->setObjectName(QString::fromUtf8("dividerSpinBox"));
        sizePolicy.setHeightForWidth(dividerSpinBox->sizePolicy().hasHeightForWidth());
        dividerSpinBox->setSizePolicy(sizePolicy);
        dividerSpinBox->setMinimumSize(QSize(80, 0));
        dividerSpinBox->setFrame(false);
        dividerSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dividerSpinBox->setMinimum(0);
        dividerSpinBox->setMaximum(1000000);
        dividerSpinBox->setValue(0);

        horizontalLayout_6->addWidget(dividerSpinBox);


        horizontalLayout_2->addLayout(horizontalLayout_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 5);
        horizontalLayout_2->setStretch(1, 5);
        horizontalLayout_2->setStretch(2, 5);

        verticalLayout->addLayout(horizontalLayout_2);

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

        verticalLayout->setStretch(3, 2);

        horizontalLayout_main->addWidget(groupBox);

        horizontalLayout_main->setStretch(0, 4);
        horizontalLayout_main->setStretch(1, 1);
        shiboqi_remake->setCentralWidget(centralwidget);
        menubar = new QMenuBar(shiboqi_remake);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
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
        groupBox->setTitle(QCoreApplication::translate("shiboqi_remake", "UDP\350\256\276\347\275\256", nullptr));
        label->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label->setText(QCoreApplication::translate("shiboqi_remake", "\346\234\254\346\234\272IP\345\234\260\345\235\200:", nullptr));
        ipLineEdit->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        ipLineEdit->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.3", nullptr));
        label_2->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_2->setText(QCoreApplication::translate("shiboqi_remake", " \347\253\257\345\217\243:      ", nullptr));
        label_3->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_3->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207IP\345\234\260\345\235\200:", nullptr));
        targetIpLineEdit->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        targetIpLineEdit->setText(QCoreApplication::translate("shiboqi_remake", "192.168.0.2", nullptr));
        label_4->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_4->setText(QCoreApplication::translate("shiboqi_remake", "\347\233\256\346\240\207\347\253\257\345\217\243:", nullptr));
        targetPortSpinBox->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_5->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_5->setText(QCoreApplication::translate("shiboqi_remake", "\346\225\260\346\215\256\344\270\252\346\225\260:", nullptr));
        dataNumSpinBox->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        label_6->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "margin: 0px; padding: 0px;", nullptr));
        label_6->setText(QCoreApplication::translate("shiboqi_remake", "\345\210\206\351\242\221\347\263\273\346\225\260:", nullptr));
        dividerSpinBox->setStyleSheet(QCoreApplication::translate("shiboqi_remake", "padding: 0px;", nullptr));
        setButton->setText(QCoreApplication::translate("shiboqi_remake", "\350\256\276\347\275\256UDP\350\277\236\346\216\245\345\217\202\346\225\260", nullptr));
        listenButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\274\200\345\247\213\347\233\221\345\220\254", nullptr));
        loopSendButton->setText(QCoreApplication::translate("shiboqi_remake", "\345\276\252\347\216\257\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class shiboqi_remake: public Ui_shiboqi_remake {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHIBOQI_REMAKE_H
