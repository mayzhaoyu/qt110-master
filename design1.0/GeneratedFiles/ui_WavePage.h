/********************************************************************************
** Form generated from reading UI file 'WavePage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAVEPAGE_H
#define UI_WAVEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WavePage
{
public:

    void setupUi(QWidget *WavePage)
    {
        if (WavePage->objectName().isEmpty())
            WavePage->setObjectName(QStringLiteral("WavePage"));
        WavePage->resize(400, 300);

        retranslateUi(WavePage);

        QMetaObject::connectSlotsByName(WavePage);
    } // setupUi

    void retranslateUi(QWidget *WavePage)
    {
        WavePage->setWindowTitle(QApplication::translate("WavePage", "WavePage", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WavePage: public Ui_WavePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVEPAGE_H
