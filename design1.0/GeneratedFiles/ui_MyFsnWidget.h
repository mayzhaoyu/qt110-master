/********************************************************************************
** Form generated from reading UI file 'MyFsnWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFSNWIDGET_H
#define UI_MYFSNWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyFsnWidget
{
public:

    void setupUi(QWidget *MyFsnWidget)
    {
        if (MyFsnWidget->objectName().isEmpty())
            MyFsnWidget->setObjectName(QStringLiteral("MyFsnWidget"));
        MyFsnWidget->resize(400, 300);

        retranslateUi(MyFsnWidget);

        QMetaObject::connectSlotsByName(MyFsnWidget);
    } // setupUi

    void retranslateUi(QWidget *MyFsnWidget)
    {
        MyFsnWidget->setWindowTitle(QApplication::translate("MyFsnWidget", "MyFsnWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyFsnWidget: public Ui_MyFsnWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFSNWIDGET_H
