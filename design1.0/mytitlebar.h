#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QPainter>
#include "GeneratedFiles/ui_mytitlebar.h"
#include <QtWidgets/QWidget>
#include "ui_myclass.h"
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QTNetwork/Qtnetwork>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedLayout>

#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <fstream>
using namespace std;

class myTitleBar : public QWidget
{
	Q_OBJECT

public:
	myTitleBar(QWidget *parent = 0);
	~myTitleBar();
	QWidget * logo;
	QWidget * blank;
	QLabel * logoText;

	QHBoxLayout *layout;
	QHBoxLayout *logoLayout;

	//title button
	QPushButton *CloseButt;
	QPushButton *MaximizeButt;
	QPushButton *MinimazeButt;

	//net
	QLabel * ipLabel;
	QComboBox  *hostIpEdit;
	QListWidget *hostIpList;
	QListWidgetItem **pHostIpListItem;
	QPushButton *connectButton;
	int ipNum;
	string *ip;
	#define MAXIPSIZE 10
	QHBoxLayout *buttLayout;
private:
	Ui::myTitleBar ui;
	bool isMoving;
	QPoint movePosition;
	void paintEvent(QPaintEvent *event);
	void AddIp(string &ip);
protected:
	// 重写按下鼠标事件
	virtual void mousePressEvent(QMouseEvent *event);
	//重写移动鼠标事件
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
	void test();
	//void addip(QString ip);
	void UpdateIpList();
};

#endif // MYTITLEBAR_H
