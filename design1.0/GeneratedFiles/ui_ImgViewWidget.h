/********************************************************************************
** Form generated from reading UI file 'ImgViewWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGVIEWWIDGET_H
#define UI_IMGVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImgViewWidget
{
public:

    void setupUi(QWidget *ImgViewWidget)
    {
        if (ImgViewWidget->objectName().isEmpty())
            ImgViewWidget->setObjectName(QStringLiteral("ImgViewWidget"));
        ImgViewWidget->resize(400, 300);

        retranslateUi(ImgViewWidget);

        QMetaObject::connectSlotsByName(ImgViewWidget);
    } // setupUi

    void retranslateUi(QWidget *ImgViewWidget)
    {
        ImgViewWidget->setWindowTitle(QApplication::translate("ImgViewWidget", "ImgViewWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImgViewWidget: public Ui_ImgViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGVIEWWIDGET_H
