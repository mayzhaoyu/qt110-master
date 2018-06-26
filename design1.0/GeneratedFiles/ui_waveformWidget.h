/********************************************************************************
** Form generated from reading UI file 'waveformWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAVEFORMWIDGET_H
#define UI_WAVEFORMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_waveformWidget
{
public:

    void setupUi(QWidget *waveformWidget)
    {
        if (waveformWidget->objectName().isEmpty())
            waveformWidget->setObjectName(QStringLiteral("waveformWidget"));
        waveformWidget->resize(400, 300);

        retranslateUi(waveformWidget);

        QMetaObject::connectSlotsByName(waveformWidget);
    } // setupUi

    void retranslateUi(QWidget *waveformWidget)
    {
        waveformWidget->setWindowTitle(QApplication::translate("waveformWidget", "waveformWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class waveformWidget: public Ui_waveformWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVEFORMWIDGET_H
