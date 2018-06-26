/********************************************************************************
** Form generated from reading UI file 'dialogErrorCode.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGERRORCODE_H
#define UI_DIALOGERRORCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialogErrorCode
{
public:

    void setupUi(QWidget *dialogErrorCode)
    {
        if (dialogErrorCode->objectName().isEmpty())
            dialogErrorCode->setObjectName(QStringLiteral("dialogErrorCode"));
        dialogErrorCode->resize(400, 300);

        retranslateUi(dialogErrorCode);

        QMetaObject::connectSlotsByName(dialogErrorCode);
    } // setupUi

    void retranslateUi(QWidget *dialogErrorCode)
    {
        dialogErrorCode->setWindowTitle(QApplication::translate("dialogErrorCode", "dialogErrorCode", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dialogErrorCode: public Ui_dialogErrorCode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGERRORCODE_H
