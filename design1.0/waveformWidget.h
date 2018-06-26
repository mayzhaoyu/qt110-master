#pragma once

/*
=====================================================================================
        ���ι����� 
		���Ʋ���ģ��
		��һҳ����ȫ�ߵڶ�·�źţ������źţ���һ�ࣩ����ȫ�ߵ�һ·�źţ����Ⲩ���źţ������ࣩ
		�ڶ�ҳ�������氲ȫ��AD�źţ������źţ������ࣩ
		����ҳ����С���󣨲����źţ� ��С���ң������źţ�������Ϊ���ࣩ
		����ҳ���ߴ��󣶣����������źţ�����·��
		����ҳ���ߴ��󣱣����������źţ�����·��
		����ҳ�������ź�L3 �����ź�L2 �����ź�L1
		����ҳ�������ź�JSL �����ź�JSR
		�ڰ�ҳ�������ź�R1 �����ź�R2 �����ź�R3
		�ھ�ҳ��ӫ�ⷽ������ ӫ�ⷽ������ ӫ�ⷽ������ ӫ�ⷽ������
		��29 ·�����ź�
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
	//����ͨ�Ŷ���ı���
	QTcpSocket  **psocket;
	frameWriter WaveCmdWriter;

	QHBoxLayout * mainlayout;
	QVBoxLayout *BtnLayout;

	QPushButton *plotLineBtn;

	QListWidget *listwidget;
	QStackedWidget *stackWave;
	//WavePage **PageTable; ���ڸĽ�
	WavePage **PageTable;
	//QPolygonF **pointsTable; ���ڸĽ�
	//��һҳ���ھ�ҳ�Ĳ���·��
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
