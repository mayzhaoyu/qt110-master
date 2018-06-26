/********************************************************************************
** Form generated from reading UI file 'mytitlebar.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTITLEBAR_H
#define UI_MYTITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myTitleBar
{
public:

    void setupUi(QWidget *myTitleBar)
    {
        if (myTitleBar->objectName().isEmpty())
            myTitleBar->setObjectName(QStringLiteral("myTitleBar"));
        myTitleBar->resize(400, 300);

        retranslateUi(myTitleBar);

        QMetaObject::connectSlotsByName(myTitleBar);
    } // setupUi

    void retranslateUi(QWidget *myTitleBar)
    {
        myTitleBar->setWindowTitle(QApplication::translate("myTitleBar", "myTitleBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class myTitleBar: public Ui_myTitleBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTITLEBAR_H
