#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Util.h"
#include "PlotLines.h"
#include "ui_WavePage.h"

class WavePage : public QWidget
{
	Q_OBJECT

	int IndexPage = 1;

public:
	//PlotLines * PlotArry[29];	//29路波形 可以删掉
	int PlotNum;
	PlotLines **PlotTable;
	QVBoxLayout *GroupLayout1;
	QGridLayout *GridLayout1;
	//QPolygonF *points;
	WavePage(QWidget *parent = Q_NULLPTR);
	//WavePage(QWidget *parent, int);
	WavePage(QWidget *parent, int, int);
	~WavePage();

public slots:
	//void Draw1();
	//void Draw2();
	void DrawWave(QPolygonF *points, int plotnum);
	
private:
	Ui::WavePage ui;
};
