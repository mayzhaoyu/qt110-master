#include "debugWidget.h"
#include "myclass.h"

char styleSheet1[] = "QPushButton { background-color: rgb(128, 255, 0); \
							 color: rgb(255, 255, 255);border-style: none; } \
							QPushButton:hover { background-color: rgb(255, 50, 50); }\
							QPushButton:pressed { background-color: rgb(230, 0, 0); }";

char styleSheet2[] = "QPushButton { background-color: rgb(128, 255, 0); \
							 color: rgb(255, 255, 255);border-style: none; } \
							QPushButton:hover { background-color: rgb(0, 255, 0); }\
							QPushButton:pressed { background-color: rgb(0, 200, 0); }";



MyDebugWidget::MyDebugWidget(QWidget * p)
{
	this->QWidget::QWidget(p);//���û���Ĺ��캯��
	setupWidget();

	//�����ڲ��ķֲ�
	blankLayout = new QGridLayout(this);
	blankLayout->addWidget(hostIpEdit, 0, 0, 1, 1, Qt::AlignHCenter);
	blankLayout->addWidget(connectButton, 0, 1, 1, 1, Qt::AlignHCenter);
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

void MyDebugWidget::setupWidget() {

	QSizePolicy sizeFixed(QSizePolicy::Fixed, QSizePolicy::Fixed);
	//text edit
	myout = new QTextEdit();
	myout->setPlaceholderText(QStringLiteral("�հ�..."));
	myout->setSizePolicy(sizeFixed);
	myout->setReadOnly(true);
	QObject::connect(myout, SIGNAL(textChanged()), this, SLOT(autoScroll()));

	myin = new QTextEdit();
	myin->setPlaceholderText(QStringLiteral("������"));
	myin->setSizePolicy(sizeFixed);

	hostIpEdit = new QComboBox();
	//hostIpEdit->setPlaceholderText(QStringLiteral("�����������ip"));
	hostIpEdit->setSizePolicy(sizeFixed);
	hostIpEdit->setMaximumHeight(23);
	hostIpEdit->setMinimumWidth(150);
	hostIpEdit->setEditable(true);
	hostIpList = new QListWidget();
	hostIpList->setMouseTracking(true);
	hostIpList->setFocusPolicy(Qt::NoFocus);
	hostIpListItem = new QListWidgetItem(hostIpList);
	hostIpListItem->setText("192.168.231.241");
	hostIpList->setItemWidget(hostIpListItem, hostIpEdit);
	hostIpEdit->setModel(hostIpList->model());

	//button
	sendButton = new QPushButton(this);
	sendButton->setText(QStringLiteral("����"));
	sendButton->setMaximumWidth(50);
	sendButton->setMinimumHeight(30);

	textClearButton = new QPushButton(this);
	textClearButton->setText(QStringLiteral("���"));
	textClearButton->setMaximumWidth(50);
	textClearButton->setMinimumHeight(30);

	connectButton = new QPushButton(this);
	connectButton->setText(QStringLiteral("��������"));
	connectButton->setMaximumWidth(50);
	connectButton->setMinimumHeight(30);


	//QObject::connect(sendButton, SIGNAL(clicked()), this, SLOT(sendText()));
	connect(sendButton, SIGNAL(clicked()), this, SLOT(test()));
	connect(textClearButton, SIGNAL(clicked()), this, SLOT(clearText()));
	connect(connectButton, SIGNAL(clicked()), this, SLOT(connectTCP()));
}


void MyDebugWidget::print(char * s) {
	myout->setText(myout->toPlainText() + QString::fromLocal8Bit(s));
}
void MyDebugWidget::print(QString  s) {
	myout->setText(myout->toPlainText() + s);
}

void MyDebugWidget::print(char * s, uint32_t i) {
	myout->setText(myout->toPlainText() + QString().sprintf(s, i));
}

void MyDebugWidget::print(char * fmt, QString  s) {
	myout->setText(myout->toPlainText() + (QString().sprintf(fmt, s)));
}









/*
���Ͱ�����Ӧ�Ĳۺ���
*/
void MyDebugWidget::sendText() {
	print("123\n");return;
	QString str = myin->toPlainText();
	myout->setText(myout->toPlainText() + str);
	myin->setText("");
	socket->write(str.toLatin1());
	myin->setFocus();
}

/*
�ɹ�������TCP�������Ĳۺ��������ڴ�ӡ�ɹ��Լ���������
*/
void MyDebugWidget::connected() {
	myout->setText(myout->toPlainText() + QStringLiteral("���ӳɹ�\n"));
	socket->write("hello linux\n");
	connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyread()));
}

/*
�ı��ı��¼��Ĳۺ���
*/
void MyDebugWidget::autoScroll() {
	myout->moveCursor(QTextCursor::End);
}

/*
����ı�������Ӧ�Ĳۺ���
*/
void MyDebugWidget::clearText() {
	myout->setText("");
}

/*
���յ�TCP���ݵĲۺ���
*/
void MyDebugWidget::readyread()
{
	QByteArray arr = this->socket->readAll();
	//	print(QString().sprintf("I received %d char", arr.length()));

	//if (arr.length() < 10) {
	//	uint16_t checksum = *(uint16_t *)arr.data();
	//	uint32_t end = *(uint32_t *)(arr.data() + 2);
	//	print("%d\n", checksum);
	//	print("\n");
	//	print("0x%x\n", end);
	//}
	//else {

	//}

	print(arr);
}

/*
TCP����/�Ͽ���ť�Ĳۺ���
*/
void MyDebugWidget::connectTCP() {
	print("123\n");return;
	if (socket == NULL) {
		connectButton->setText(QStringLiteral("�Ͽ�����"));
		print("ip:" + hostIpListItem->text());
		socket = new QTcpSocket(this);
		socket->connectToHost(hostIpListItem->text(), 11910, QTcpSocket::ReadWrite);//80100
		QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected()));
		print("������������...\n");
	}
	else if (socket->isOpen()) {
		connectButton->setText(QStringLiteral("��������"));
		socket->disconnectFromHost();
		socket->waitForDisconnected(400);
		socket->close();
		print("�����ѶϿ�...\n");
		delete socket;
		socket = NULL;
	}
}


void MyDebugWidget::test() {
	this->close();
}
void MyClass::test() {
	debugWidget->print("�ر�");
	debugWidget->close();
}