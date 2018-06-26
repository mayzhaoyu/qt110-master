/********************************************************************************
** Form generated from reading UI file 'cisDebugWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CISDEBUGWIDGET_H
#define UI_CISDEBUGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cisDebugWidget
{
public:

    void setupUi(QWidget *cisDebugWidget)
    {
        if (cisDebugWidget->objectName().isEmpty())
            cisDebugWidget->setObjectName(QStringLiteral("cisDebugWidget"));
        cisDebugWidget->resize(400, 300);

        retranslateUi(cisDebugWidget);

        QMetaObject::connectSlotsByName(cisDebugWidget);
    } // setupUi

    void retranslateUi(QWidget *cisDebugWidget)
    {
        cisDebugWidget->setWindowTitle(QApplication::translate("cisDebugWidget", "cisDebugWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class cisDebugWidget: public Ui_cisDebugWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CISDEBUGWIDGET_H
