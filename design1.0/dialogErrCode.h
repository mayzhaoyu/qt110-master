#pragma once

#include <QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "ui_dialogErrCode.h"

class dialogErrCode : public QDialog
{
	Q_OBJECT
	
	uint32_t code;
	QPushButton * closebutton;
	QVBoxLayout * layout;
	QTableWidget* errTable;
public:
	dialogErrCode(QWidget *parent = Q_NULLPTR);
	~dialogErrCode();
	void setCode(uint32_t errcode);

private:
	Ui::dialogErrCode ui;
};

