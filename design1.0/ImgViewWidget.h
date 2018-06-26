#pragma once

#include <QWidget>
#include "ui_ImgViewWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
class ImgViewWidget : public QWidget
{
	Q_OBJECT

public:
	ImgViewWidget(QWidget *parent = Q_NULLPTR);
	~ImgViewWidget();
	QImage FrontRGBImg;
	QImage FrontIRImg;
	QImage BackRGBImg;
	QImage BackIRImg;

	QPushButton *GetImgBtn;
	QPushButton *SaveImgBtn;

	QLabel *FrontRGBImgLb;
	QLabel *FrontIRImgLb;
	QLabel *BackRGBImgLb;
	QLabel *BackIRImgLb;
		 
public slots:
	void updateImg(uint8_t*, int);
private:
	Ui::ImgViewWidget ui;
};
