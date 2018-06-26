#pragma once

/*
=====================================================================================
        波形共四类 
		绘制波形模块
		第一页：安全线第二路信号（脉冲信号）（一类）；安全线第一路信号（特殊波型信号）（二类）
		第二页：１５版安全线AD信号（波形信号）（三类）
		第三页：中小磁左（波形信号） 中小磁右（波形信号）（以下为四类）
		第四页：边磁左６－１（波形信号／共六路）
		第五页：边磁左１－６（波形信号／共六路）
		第六页：红外信号L3 红外信号L2 红外信号L1
		第七页：红外信号JSL 红外信号JSR
		第八页：红外信号R1 红外信号R2 红外信号R3
		第九页：荧光方窗左上 荧光方窗右下 荧光方窗右上 荧光方窗右下
		共29 路波形信号
=====================================================================================
*/

#include <QWidget>
#include "ui_waveformWidget.h"

#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QListWidget>

#include "PlotLines.h"
#include "WavePage.h"
#include "frameWriter.h"
//#include "WavePage5.h"


class waveformWidget : public QWidget
{
	Q_OBJECT

public:

	waveformWidget(QWidget *parent = Q_NULLPTR, QTcpSocket **psocket = 0);
	~waveformWidget();
	void BufferToPath(uint8_t *buffer,int size);
	void PathPageType1(uint8_t * buffer,int &index);  //???
	void PathPageType2(uint8_t * buffer,int &index);
	void PathPageType3(uint8_t * buffer,int &index);
	void clearPoints();
	//void PathPage4(int &index);

public:
	//网络通信定义的变量
	QTcpSocket  **psocket;
	frameWriter WaveCmdWriter;

	QHBoxLayout * mainlayout;
	QVBoxLayout *BtnLayout;

	QPushButton *plotLineBtn;

	QListWidget *listwidget;
	QStackedWidget *stackWave;
	//WavePage **PageTable; 后期改进
	WavePage **PageTable;
	//QPolygonF **pointsTable; 后期改进
	//第一页到第九页的波形路径
	QPolygonF *points1;
	QPolygonF *points2;
	QPolygonF *points3;
	QPolygonF *points4;
	QPolygonF *points5;
	QPolygonF *points6;
	QPolygonF *points7;
	QPolygonF *points8;
	QPolygonF *points9;

	int PlotNumber[9] = { 2,1,2,6,6,3,2,3,4 };
signals:
	//void signalEmit();
public slots:
	void updateWave(uint8_t *buffer,int size);
	void sendGetWaveData();
private:
	Ui::waveformWidget ui;
};
