/*
	Class : MyFsnWidget
	Description: 

*/
#pragma once

#include <QWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QColumnView>
#include <QIcon>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPicture>
#include <QMenu>
#include <QContextMenuEvent>
#include <queue>
#include <iostream>
#include <fstream>

#include "fsnMsg.h"
#include "GeneratedFiles/ui_MyFsnWidget.h"
#include "dialogErrCode.h"
#include "frameWriter.h"

using namespace std;
//extern QTcpSocket * socket;   //接收数据的套接字

typedef struct {
	uint8_t gzhtable[12];
}gzh;

typedef enum {
	nomal = 1,
	error,
	max,
	min,
	red,
	green,
	gray
}itemType;

class MyFsnWidget : public QWidget
{
	Q_OBJECT

public:

	QTableWidget* fsnTable;
	QColumnView* columnview;
	QGridLayout * layout;

	QPushButton *ClearBtn;
	QPushButton *CompareBtn;
	QPushButton *SaveTempBtn;
	QPushButton *SendGZHCmdBtn;

	dialogErrCode * dialog_errcode;

	QTcpSocket **psocket;
	frameWriter GZHCmdWriter;
	//QTcpSocket *socket1 = new QTcpSocket(this);
public:
	//MyFsnWidget(QWidget *parent = Q_NULLPTR);
	MyFsnWidget(QWidget *parent = Q_NULLPTR, QTcpSocket **psocket = 0);
	~MyFsnWidget();

	//list<gzh> *gzh_list;
	list<QString> *gzh_list;
	int list_on;
	int RowNum;
private:
	Ui::MyFsnWidget ui;
	void setChecked(int row,QColor color);
	bool compareGzh(QString& str);
	void setItemColor(int row, int col, itemType type);
	int max_length; int max_length_index;   //	标记最大宽度 最大长度
	int min_length; int min_length_index;
	int max_width; int max_width_index;
	int min_width; int min_width_index;

public slots:
	void ClearBtnClicked();
	void CompareBtnClicked();
	void SaveTempBtnClicked();
//	void updateTable(const TCP_FSN_Msg * msg);
//	void updateTable(const TCP_FSN_Msg_Sml * msg);
	void updateTable(billInf& msg);
	void SendGZHCmd();  //发送信号给图像板

	void openDialog(QTableWidgetItem*);
	void mark(int, int);
	void mark();
	void unmark();
	void allmark();
	void allunmark();
	void clearmark();
	void popMenu(QPoint point);
	void SaveImgmark();
	//信号
signals:
	void fsnPkg(const TCP_FSN_Msg* msg);
	void fsnPkg(const TCP_FSN_Msg_Sml* msg);
	void billPkg(billInf& msg);
	void debug(QString str);
};
