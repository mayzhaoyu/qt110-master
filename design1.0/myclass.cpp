#include "myclass.h"
/*


*/
char guideStyleSheet[] = "QListWidget { background-color: rgb(61, 74, 83); "
										"color: rgb(255, 255, 255);border-style: none;  "
										" font: 14pt \"新宋体\" ; "
										" }"
						"QListWidget::Item {min-height: 80px;border-left-color: rgb(255, 255, 255)}"
						"QListWidget::item:selected{color:rgb(251, 85, 78);border-style: none;  }"
						"QListWidget::item:hover{background: rgb(80, 90, 100);color:rgb(176, 233, 72);  }";

MyClass::MyClass(QWidget *parent)
	: QWidget(parent), frame_writer(&socket)
{
	ui.setupUi(this);	//整个窗体
	setWindowIcon(QIcon("icon/money.ico"));
	setMinimumSize(1100, 1100*0.618+30);
	setWindowFlags(Qt::FramelessWindowHint | windowFlags());
	titleBar = new myTitleBar(this); //自定义标题栏
	
    //network
	socket = NULL;

	//主窗体
	window = new QWidget(this);		
	window->resize(width(), height() - titleBar->height());
	QPalette pal(palette());
	pal.setColor(QPalette::Window, QColor(255, 255, 255));//61, 62, 68
	window->setAutoFillBackground(true);
	window->setPalette(pal);

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setSizePolicy(sizePolicy);

	//正文区
	blank = new QWidget(window);
	sizePolicy.setHorizontalStretch(5);
	blank->setSizePolicy(sizePolicy);
	blank->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(254, 255, 255));
	blank->setPalette(pal);

	debugWidget = new MyDebugWidget(this);	//右侧的空白区，内容区域
	sizePolicy.setHorizontalStretch(5);
	debugWidget->setSizePolicy(sizePolicy);
	debugWidget->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(254, 255, 255));
	debugWidget->setPalette(pal);

	//导航栏
	function = new QWidget(window);	//左侧的功能选择区
	function->setMaximumWidth(160);
	function->setMinimumWidth(160);
	sizePolicy.setHorizontalStretch(1);
	function->setSizePolicy(sizePolicy);
	function->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(61, 74, 83));
	function->setPalette(pal);
	//导航栏内容
	guideLayout =new QVBoxLayout(function);
	guideList = new QListWidget;
	debugListItem = new QListWidgetItem(QStringLiteral("通信与调试"), guideList);
	debugListItem->setTextAlignment(Qt::AlignCenter);

	fsnListItem = new QListWidgetItem(QStringLiteral("算法调试"), guideList);
	fsnListItem->setTextAlignment(Qt::AlignCenter);

	cisListItem = new QListWidgetItem(QStringLiteral("CIS调试"), guideList);
	cisListItem->setTextAlignment(Qt::AlignCenter);

	waveListItem = new QListWidgetItem(QStringLiteral("波形显示"), guideList);
	waveListItem->setTextAlignment(Qt::AlignCenter);

	imgListItem = new QListWidgetItem(QStringLiteral("图像预览"), guideList);
	imgListItem->setTextAlignment(Qt::AlignCenter);
	
	//cisListItem->setTextAlignment(Qt::AlignCenter);
	guideList->insertItem(1, debugListItem);
	guideList->insertItem(2, fsnListItem);
	guideList->insertItem(3, cisListItem);
	guideList->insertItem(4, waveListItem);
	guideList->insertItem(5, imgListItem);

	guideList->setItemSelected(debugListItem, true);//设置默认选项
	guideList->setStyleSheet(guideStyleSheet);
	guideList->setFocusPolicy(Qt::NoFocus);
	currentItem = debugListItem;	//同步默认选项
	connect(guideList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(guidItemChanged(QListWidgetItem*)));
	guideLayout->addWidget(guideList);
	guideLayout->setMargin(0);

    setupLayout();

	/*connect(this, SIGNAL(fsnPkg(const TCP_FSN_Msg*)), fsnWidget, SLOT(updateTable(const TCP_FSN_Msg*)));
	connect(this, SIGNAL(fsnPkg(const TCP_FSN_Msg_Sml*)), fsnWidget, SLOT(updateTable(const TCP_FSN_Msg_Sml*)));*/
	connect(this, SIGNAL(billPkg(billInf&)), fsnWidget, SLOT(updateTable(billInf&)));
	connect(this, SIGNAL(wavePkg(uint8_t* , int)), waveWidget, SLOT(updateWave(uint8_t*,int)));
	connect(this, SIGNAL(ImgPkg(uint8_t*,int)), imgviewWidget, SLOT(updateImg(uint8_t*, int)));

	//debugWidget->print("%d",sizeof(MoneyResult));
	//billInf bill;
	//bill.moneyResult.width = 100;
	//emit billPkg(billInf());
	//emit billPkg(bill);
	//emit billPkg(billInf(50));
	//emit billPkg(billInf(20));
}

MyClass::~MyClass()
{

}


void MyClass::setupLayout() {

	mainLayout = new QVBoxLayout(this);		//布局整体：标题栏与主窗口
	windowLayout = new QHBoxLayout(window); //布局主窗口：导航栏与正文窗
	stackLayout = new QStackedLayout(blank);

	//设置标题栏与窗口结构
	mainLayout->setMargin(0);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(titleBar);
	mainLayout->addWidget(window);

	windowLayout->addWidget(function);
	windowLayout->addWidget(blank);
	windowLayout->setMargin(0);
	windowLayout->setSpacing(0);

	//tmpwidget = new QWidget();
	//tmpwidget->setAutoFillBackground(true);
	//QPalette pal(palette());
	//pal.setColor(QPalette::Window, QColor(0, 255, 255));
	//tmpwidget->setPalette(pal);

	fsnWidget = new MyFsnWidget(this, &socket);
	cisWidget= new cisDebugWidget(this,&socket);
	waveWidget = new waveformWidget(this, &socket);
	imgviewWidget = new ImgViewWidget(this);

	stackLayout->addWidget(debugWidget);
	stackLayout->addWidget(fsnWidget);
	stackLayout->addWidget(cisWidget);
	stackLayout->addWidget(waveWidget);
	stackLayout->addWidget(imgviewWidget);

}









/*
最大化按键对应的槽函数
*/
void MyClass::showWindowSized() {
	if (Qt::WindowState::WindowMaximized == this->windowState())
		this->setWindowState(Qt::WindowState::WindowNoState);
	else
		this->setWindowState(Qt::WindowState::WindowMaximized);
}

/*
导航栏选项改变-槽函数
*/
void MyClass::guidItemChanged(QListWidgetItem* item) {
	if (item != currentItem) {//自检
		currentItem = item;
		//debugWidget-> print(QStringLiteral("\"") + item->text() + QStringLiteral("\"选项\n"));
		if (debugListItem == item) {
			stackLayout->setCurrentWidget(debugWidget);
		}
		if (fsnListItem == item) {
			stackLayout->setCurrentWidget(fsnWidget);
		}
		if (cisListItem == item) {
			stackLayout->setCurrentWidget(cisWidget);
		}
		if (waveListItem == item)
		{
			//切换界面就发送指令 0400
			//frame_writer.command((unsigned char)04, (unsigned char)00); 
			stackLayout->setCurrentWidget(waveWidget);
		}
		if (imgListItem == item)
		{
			//获取 四张图像 06 00
			frame_writer.command((unsigned char)06, (unsigned char)00);

			stackLayout->setCurrentWidget(imgviewWidget);

			//int i;
			//FILE *fp = fopen("data5.txt", "w");
			////	for (i = 0; i < size; i++)
			////	{
			////		fprintf(fp, "%x ", buffer[i]);
			////	}
			////	fclose(fp);

			////QImage img = QImage((const unsigned char*)(buffer), 1440, 1968, QImage::Format_Grayscale8);
			////FrontRGBImgLb->setPixmap(QPixmap::fromImage(img).scaled(QSize(1440, 1968)));
			////bool a = img.save("1.bmp");
			////int t = size;

			////显示图片
			//QImage img1;
			//img1.load("test.jpg");
			//for (int i = 0; i < 1968; i++)
			//{
			//	uchar *line = img1.scanLine(i);
			//	for (int j = 0; j < 1440; j++) {
			//		fprintf(fp, "%x ", line[j]);
			//	}
			//}
			//fclose(fp);

			////img1.save("2.bmp");
		}
	}
}


/*
处理数据
*/
void MyClass::processsBuf(QByteArray& qarray) {
	//print(QString().sprintf("receive %d char", qarray.length()));

}
/*
TCP连接/断开按钮的槽函数
*/
void MyClass::connectTCP() 
{
	if (socket == NULL) 
	{
		titleBar->connectButton->setText(QStringLiteral("断开网络"));
		debugWidget->print("ip:" + titleBar->hostIpEdit->currentText());
		debugWidget->print("正在连接网络...\n");
		//emit connectNet(hostIpListItem->text());
		socket = new QTcpSocket(this);
		socket->connectToHost(titleBar->hostIpEdit->currentText(), 11910, QTcpSocket::ReadWrite);//80100
		QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	}
	else if (socket->isOpen()) {
		titleBar->hostIpEdit->setEditable(true);
		titleBar->hostIpEdit->setDisabled(false);

		titleBar->hostIpEdit->setFocusPolicy(Qt::StrongFocus);
		titleBar->connectButton->setText(QStringLiteral("连接网络"));
		socket->disconnectFromHost();
		socket->waitForDisconnected(400);
		socket->close();
		//emit disconnectNet();
		debugWidget->print("网络已断开...\n");
		delete socket;
		socket = NULL;
	}
}

/*
成功连接上TCP服务器的槽函数：用于打印成功以及后续操作
*/
void MyClass::connected() {
	//debugWidget->myout->setText(myout->toPlainText() + QStringLiteral("连接成功\n"));
	debugWidget->print("连接成功\n");

	titleBar->hostIpEdit->setEditable(false);
	titleBar->hostIpEdit->setDisabled(true);
	titleBar->hostIpEdit->setFocusPolicy(Qt::NoFocus);
	de_frame.clear();
//	titleBar->addip(titleBar->hostIpEdit->currentText());
	socket->write("hello linux\n");
	connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyread()));
	//connect(socket, SIGNAL(readyRead()), this, SLOT(readyread()));
}


/*
接收到TCP数据的槽函数

*/
void MyClass::readyread()
{
	static int size = 0;
	QByteArray arr = this->socket->readAll();  //读取服务器数据
	
	size += arr.size();
	//debugWidget->print("size:%d\n", size);
	de_frame.inputs((arr.data()), arr.size());

	qDebug("RECV=%d", size);
	while (!de_frame.isEmpty()) {
		if (de_frame.decode() == 0) {
			/*	if((de_frame.getFrame().cmd>>8)==0x00)
			emit billPkg(*(billInf*)(uint8_t *)(de_frame.getFrame().data));
			if ((de_frame.getFrame().cmd >> 8) == 0x02) {
			debugWidget->print("0x%x\n", de_frame.getFrame().cmd);
			frame_writer.cmdFix(0x01);
			}
			if ((de_frame.getFrame().cmd >> 8) == 0xa0) {
			titleBar->hostIpEdit->setEditable(true);
			titleBar->hostIpEdit->setDisabled(false);
			titleBar->hostIpEdit->setFocusPolicy(Qt::StrongFocus);
			titleBar->connectButton->setText(QStringLiteral("连接网络"));
			socket->disconnectFromHost();
			socket->waitForDisconnected(400);
			socket->close();
			debugWidget->print("网络已断开...\n");
			delete socket;
			socket = NULL;
			}*/

			//debugWidget->print("cmd:%x\n", de_frame.getFrame().cmd);
			carryOutCmd(de_frame.getFrame());
		}
		else {

		}
	}
}

//void MyClass::readyread()
//{
//	QByteArray arr = this->socket->readAll();  //读取服务器数据
//	//QByteArray arr = socket->readAll();  //读取服务器数据
//	
//	//recv_all = false;
//	//if( 
//	//if(RecvAll)
//	de_frame.inputs((arr.data()), arr.size()) ;
//
//	while (!de_frame.isEmpty()) {
//		if (de_frame.decode() == 0) {
//		/*	if((de_frame.getFrame().cmd>>8)==0x00)
//				emit billPkg(*(billInf*)(uint8_t *)(de_frame.getFrame().data));
//			if ((de_frame.getFrame().cmd >> 8) == 0x02) {
//				debugWidget->print("0x%x\n", de_frame.getFrame().cmd);
//				frame_writer.cmdFix(0x01);
//			}
//			if ((de_frame.getFrame().cmd >> 8) == 0xa0) {
//				titleBar->hostIpEdit->setEditable(true);
//				titleBar->hostIpEdit->setDisabled(false);
//				titleBar->hostIpEdit->setFocusPolicy(Qt::StrongFocus);
//				titleBar->connectButton->setText(QStringLiteral("连接网络"));
//				socket->disconnectFromHost();
//				socket->waitForDisconnected(400);
//				socket->close();
//				debugWidget->print("网络已断开...\n");
//				delete socket;
//				socket = NULL;
//			}*/
//
//			carryOutCmd(de_frame.getFrame());
//		}
//		else {
//
//		}
//	}
//}


void MyClass::carryOutCmd(netFrame & frame) {
	switch (frame.cmd >> 8) {
	case CMD_BILLINF:
		//emit wavePkg((uint8_t *)de_frame.getFrame().data);
		//debugWidget->print();
		//debugWidget->print("cmd2:%x\n", de_frame.getFrame().cmd);
		//emit billPkg(*(billInf*)(uint8_t *)(de_frame.getFrame().data));    //??
		emit billPkg(*(billInf*)(uint8_t *)(frame.data));    //??

		break;
	case CMD_FPGA:
		break;
	case CMD_FIX:

		break;
	case CMD_IMG:

		emit ImgPkg(de_frame.pDataImg, de_frame.getFrame().msg_length);
		break; 
	case CMD_WAVE:
		emit wavePkg((uint8_t *)de_frame.getFrame().data, de_frame.getFrame().msg_length);
		break;
	case CMD_CLOSENET:
		titleBar->hostIpEdit->setEditable(true);
		titleBar->hostIpEdit->setDisabled(false);
		titleBar->hostIpEdit->setFocusPolicy(Qt::StrongFocus);
		titleBar->connectButton->setText(QStringLiteral("连接网络"));
		socket->disconnectFromHost();
		socket->waitForDisconnected(400);
		socket->close();
		debugWidget->print("网络已断开...\n");
		delete socket;
		socket = NULL;
		break;
	default:
		break;

	}
}

void MyClass::debugPrint(QString str) {
	debugWidget->print(str+"\n");
}

QString str = "";
QString &fomatData(QByteArray &arr) {
	str.clear();
	for (int i = 0; i < arr.length(); i++) {
		if (i % 10 == 0) {
			str += "[";
			str += QString("%1").arg(i / 10, 2, 10, QLatin1Char('0'));
			str += "]:";
		}
		str += QString("%1").arg((unsigned char)arr.at(i), 2, 16, QLatin1Char('0'));
		str += " ";
		if (i % 10 == 9)
			str += "\n";
	}
	return str;
}