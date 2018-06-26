/************************************************************************************
** Class ��myclass
** Date: 2018/5/9
** Description��
** 1 ����������UI����ر������ź������Լ��ۺ���ʵ��
** 2 ���ֹ���ģ�� Ŀǰ��������ģ���Ӧ���� 
** ==================================================
**	ģ����           ����
** ==================================================
** �������ģ��     MyDebugWidget Qtnetwork(TCPЭ��)
** �㷨ģ��			MyFsnWidget
** CISУ��ģ��	     cisDebugWidget
** 
** 3 ���ֺűȶԣ�����ͨ������
** ����������簴ť����������(mytitle�� ����button)==>����TCP��myclass��connectTCP������
** ==>�������ݼ�����myclass��connect������==>����⵽�������ϴ�������readyread��������������ݣ�
** ���������ֺűȶ�ָ����͸����ź� billPkg�����ø���UItable����updateTable
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

//QTcpSocket * socket;   //�������ݵ��׽���

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

	QTcpSocket * socket;   //�������ݵ��׽���

	decodeFrame de_frame;
	frameWriter frame_writer;

	//bool RecvAll = true;  //�Ƿ������ϱ�־λ

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
//�ź�
signals:
	void fsnPkg(const TCP_FSN_Msg* msg);
	void fsnPkg(const TCP_FSN_Msg_Sml* msg);
	void billPkg(billInf& msg);
	void debug(QString str);
	//���Ͳ������ݵ��ź�
	void wavePkg(uint8_t *msg, int size);
	void ImgPkg(uint8_t *msg, int size);
};

#endif // MYCLASS_H


