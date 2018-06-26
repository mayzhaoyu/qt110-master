/************************************************************************************
** Class ：myclass
** Date: 2018/5/9
** Description：
** 1 绘制主界面UI，相关变量、信号声明以及槽函数实现
** 2 划分功能模块 目前三个功能模块对应的类 
** ==================================================
**	模块名           类名
** ==================================================
** 网络调试模块     MyDebugWidget Qtnetwork(TCP协议)
** 算法模块			MyFsnWidget
** CIS校正模块	     cisDebugWidget
** 
** 3 冠字号比对，网络通信流程
** 点击连接网络按钮，连接网络(mytitle类 连接button)==>连接TCP（myclass类connectTCP函数）
** ==>设置数据监听（myclass类connect函数）==>若检测到有数据上传，则在readyread函数里面接收数据，
** 解析出冠字号比对指令，发送更新信号 billPkg，调用更新UItable函数updateTable
**
** ... ...
****************************************************************************************/

#ifndef MYCLASS_H
#define MYCLASS_H

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
#include "MyDebugWidget.h"
#include "MyFsnWidget.h"
#include "cisDebugWidget.h"
#include "fsnMsg.h"
#include "decodeFrame.h"

#include "waveformWidget.h"
#include "ImgViewWidget.h"
QT_BEGIN_NAMESPACE

#include "mytitlebar.h"

//QTcpSocket * socket;   //接收数据的套接字

QString &fomatData(QByteArray &arr);
class MyClass : public QWidget
{
	Q_OBJECT
	QListWidgetItem * currentItem;
public:
	MyClass(QWidget *parent = 0);
	~MyClass();

public:
	//title and window
	myTitleBar* titleBar;
	QWidget * window;
	QWidget * function;
	QWidget * blank;
	QVBoxLayout *mainLayout;
	QHBoxLayout *windowLayout;


	MyDebugWidget * debugWidget;
	MyFsnWidget * fsnWidget;
	cisDebugWidget * cisWidget;
	waveformWidget *waveWidget;
	ImgViewWidget *imgviewWidget;

	QWidget * tmpwidget;

	//guide
	QListWidget* guideList;
	QListWidgetItem * debugListItem;
	QListWidgetItem * fsnListItem;
	QListWidgetItem * cisListItem;
	QListWidgetItem * waveListItem;
	QListWidgetItem * imgListItem;

	//layout
	QStackedLayout *stackLayout;
	QHBoxLayout *textLayout;
	QVBoxLayout * guideLayout;

	QTcpSocket * socket;   //接收数据的套接字

	decodeFrame de_frame;
	frameWriter frame_writer;

	//bool RecvAll = true;  //是否接受完毕标志位

private:
	Ui::MyClassClass ui;
	void setupLayout();
	void processsBuf(QByteArray& qarray);
	void carryOutCmd(netFrame & frame);
public slots:
	void showWindowSized();
	void guidItemChanged(QListWidgetItem* item);
	//void connectTcp(QString ip);
	void connectTCP();
	//void disconnectTcp();
	void connected();
	void readyread();
	void debugPrint(QString str);
//信号
signals:
	void fsnPkg(const TCP_FSN_Msg* msg);
	void fsnPkg(const TCP_FSN_Msg_Sml* msg);
	void billPkg(billInf& msg);
	void debug(QString str);
	//发送波形数据的信号
	void wavePkg(uint8_t *msg, int size);
	void ImgPkg(uint8_t *msg, int size);
};

#endif // MYCLASS_H


