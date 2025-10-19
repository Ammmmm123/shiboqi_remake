/********************************************************************************
** Form generated from reading UI file 'ddsqt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DDSQT_H
#define UI_DDSQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ddsqt
{
public:

    void setupUi(QDialog *ddsqt)
    {
        if (ddsqt->objectName().isEmpty())
            ddsqt->setObjectName(QString::fromUtf8("ddsqt"));
        ddsqt->resize(1007, 596);

        retranslateUi(ddsqt);

        QMetaObject::connectSlotsByName(ddsqt);
    } // setupUi

    void retranslateUi(QDialog *ddsqt)
    {
        ddsqt->setWindowTitle(QCoreApplication::translate("ddsqt", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ddsqt: public Ui_ddsqt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DDSQT_H
