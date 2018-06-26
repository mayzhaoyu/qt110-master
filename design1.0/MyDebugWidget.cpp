#include "MyDebugWidget.h"
#include "myclass.h"
MyDebugWidget::MyDebugWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupWidget();

	//窗体内部的分布
	blankLayout = new QGridLayout(this);
	//blankLayout->addWidget(hostIpEdit, 0, 0, 1, 1, Qt::AlignHCenter);
	//blankLayout->addWidget(connectButton, 0, 1, 1, 1, Qt::AlignHCenter);
	blankLayout->addWidget(myin, 1, 0, 1, 1);
	blankLayout->addWidget(myout, 1, 1, 1, 1);
	blankLayout->addWidget(sendButton, 2, 0, 1, 1, Qt::AlignHCenter);
	blankLayout->addWidget(textClearButton, 2, 1, 1, 1, Qt::AlignHCenter);
	blankLayout->setMargin(25);
	blankLayout->setVerticalSpacing(0);
	blankLayout->setColumnStretch(0, 3);

	socket = NULL;
}

MyDebugWidget::~MyDebugWidget()
{
}


char styleSheet1[] = "QPushButton { background-color: rgb(128, 255, 0); \
							 color: rgb(255, 255, 255);border-style: none; } \
							QPushButton:hover { background-color: rgb(255, 50, 50); }\
							QPushButton:pressed { background-color: rgb(230, 0, 0); }";

char styleSheet2[] = "QPushButton { background-color: rgb(128, 255, 0); \
							 color: rgb(255, 255, 255);border-style: none; } \
							QPushButton:hover { background-color: rgb(0, 255, 0); }\
							QPushButton:pressed { background-color: rgb(0, 200, 0); }";


void MyDebugWidget::setupWidget() {

	QSizePolicy sizeFixed(QSizePolicy::Fixed, QSizePolicy::Fixed);
	//text edit
	myout = new QTextEdit();
	myout->setPlaceholderText(QStringLiteral("空白..."));
	myout->setSizePolicy(sizeFixed);
	myout->setReadOnly(true);
	QObject::connect(myout, SIGNAL(textChanged()), this, SLOT(autoScroll()));

	myin = new QTextEdit();
	myin->setPlaceholderText(QStringLiteral("请输入"));
	myin->setSizePolicy(sizeFixed);

	//hostIpEdit = new QComboBox();
	////hostIpEdit->setPlaceholderText(QStringLiteral("请输入服务器ip"));
	//hostIpEdit->setSizePolicy(sizeFixed);
	//hostIpEdit->setMaximumHeight(23);
	//hostIpEdit->setMinimumWidth(150);
	//hostIpEdit->setEditable(true);
	//hostIpList = new QListWidget();
	//hostIpList->setMouseTracking(true);
	//hostIpList->setFocusPolicy(Qt::NoFocus);
	//hostIpListItem = new QListWidgetItem(hostIpList);
	//hostIpListItem->setText("192.168.231.241");
	//hostIpList->setItemWidget(hostIpListItem, hostIpEdit);
	//hostIpEdit->setModel(hostIpList->model());

	//button
	sendButton = new QPushButton(this);
	sendButton->setText(QStringLiteral("发送"));
	sendButton->setMaximumWidth(50);
	sendButton->setMinimumHeight(30);

	textClearButton = new QPushButton(this);
	textClearButton->setText(QStringLiteral("清除"));
	textClearButton->setMaximumWidth(50);
	textClearButton->setMinimumHeight(30);

	/*connectButton = new QPushButton(this);
	connectButton->setText(QStringLiteral("连接网络"));
	connectButton->setMaximumWidth(50);
	connectButton->setMinimumHeight(30);*/

	QObject::connect(sendButton, SIGNAL(clicked()), this, SLOT(sendText()));
	connect(textClearButton, SIGNAL(clicked()), this, SLOT(clearText()));
	//connect(connectButton, SIGNAL(clicked()), parent(), SLOT(connectTCP()));
}


void MyDebugWidget::print(char * s) {
	myout->setText(myout->toPlainText() + QString::fromLocal8Bit(s));
	if(myout->toPlainText().length()>65535)
		myout->setText(QString::fromLocal8Bit(s));
}
void MyDebugWidget::print(QString  s) {
	myout->setText(myout->toPlainText() + s);
	if (myout->toPlainText().length()>65535)
		myout->setText(s);
}

void MyDebugWidget::print(char * s, uint32_t i) {
	myout->setText(myout->toPlainText() + QString().sprintf(s, i));
	if (myout->toPlainText().length()>65535)
		myout->setText(QString().sprintf(s, i));
}

void MyDebugWidget::print(char * fmt, QString  s) {
	myout->setText(myout->toPlainText() + (QString().sprintf(fmt, s)));
	if (myout->toPlainText().length()>65535)
		myout->setText((QString().sprintf(fmt, s)));
}









/*
发送按键对应的槽函数
*/
void MyDebugWidget::sendText() {
	QString str = myin->toPlainText();
	if (socket != 0) {
		myout->setText(myout->toPlainText() + str);
		myin->setText("");
		socket->write(str.toLatin1());
	}
	myin->setFocus();
}


/*
文本改变事件的槽函数
*/
void MyDebugWidget::autoScroll() {

	myout->moveCursor(QTextCursor::End);
}

/*
清除文本按键对应的槽函数
*/
void MyDebugWidget::clearText() {
	myout->setText("");
}


void MyDebugWidget::test() {
	this->close();
}