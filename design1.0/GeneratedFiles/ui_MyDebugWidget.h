/********************************************************************************
** Form generated from reading UI file 'MyDebugWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDEBUGWIDGET_H
#define UI_MYDEBUGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyDebugWidget
{
public:

    void setupUi(QWidget *MyDebugWidget)
    {
        if (MyDebugWidget->objectName().isEmpty())
            MyDebugWidget->setObjectName(QStringLiteral("MyDebugWidget"));
        MyDebugWidget->resize(400, 300);

        retranslateUi(MyDebugWidget);

        QMetaObject::connectSlotsByName(MyDebugWidget);
    } // setupUi

    void retranslateUi(QWidget *MyDebugWidget)
    {
        MyDebugWidget->setWindowTitle(QApplication::translate("MyDebugWidget", "MyDebugWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyDebugWidget: public Ui_MyDebugWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDEBUGWIDGET_H
