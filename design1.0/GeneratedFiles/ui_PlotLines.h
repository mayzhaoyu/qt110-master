/********************************************************************************
** Form generated from reading UI file 'PlotLines.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTLINES_H
#define UI_PLOTLINES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <qwtplot.h>

QT_BEGIN_NAMESPACE

class Ui_PlotLines
{
public:

    void setupUi(QwtPlot *PlotLines)
    {
        if (PlotLines->objectName().isEmpty())
            PlotLines->setObjectName(QStringLiteral("PlotLines"));
        PlotLines->resize(400, 300);

        retranslateUi(PlotLines);

        QMetaObject::connectSlotsByName(PlotLines);
    } // setupUi

    void retranslateUi(QwtPlot *PlotLines)
    {
        PlotLines->setWindowTitle(QApplication::translate("PlotLines", "PlotLines", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlotLines: public Ui_PlotLines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTLINES_H
