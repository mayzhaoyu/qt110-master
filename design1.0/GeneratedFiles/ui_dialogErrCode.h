/********************************************************************************
** Form generated from reading UI file 'dialogErrCode.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGERRCODE_H
#define UI_DIALOGERRCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_dialogErrCode
{
public:

    void setupUi(QDialog *dialogErrCode)
    {
        if (dialogErrCode->objectName().isEmpty())
            dialogErrCode->setObjectName(QStringLiteral("dialogErrCode"));
        dialogErrCode->resize(400, 300);

        retranslateUi(dialogErrCode);

        QMetaObject::connectSlotsByName(dialogErrCode);
    } // setupUi

    void retranslateUi(QDialog *dialogErrCode)
    {
        dialogErrCode->setWindowTitle(QApplication::translate("dialogErrCode", "dialogErrCode", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dialogErrCode: public Ui_dialogErrCode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGERRCODE_H
