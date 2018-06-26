#pragma once

#include <QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include "ui_dialogErrorCode.h"

class dialogErrorCode : public QWidget
{
	Q_OBJECT
		
	QPushButton * closebutton;
	QVBoxLayout * layout;
public:
	dialogErrorCode(QWidget *parent = Q_NULLPTR);
	~dialogErrorCode();

private:
	Ui::dialogErrorCode ui;
};
