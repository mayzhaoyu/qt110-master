#include "mytitlebar.h"
#include <QtGui/QMouseEvent>
//#include <QtGui/QApplication>

char styleSheetLabel[] = "QLabel {  color: rgb(120,120,120);border-style: none;  "
									" font: 10pt \"楷体\" ;} ";
myTitleBar::myTitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//setBaseSize(120, 50);
	resize(parent->width(), 40);
	setMaximumHeight(80);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setSizePolicy(sizePolicy);

	QPalette pal(palette());
	pal.setColor(QPalette::Window, QColor(204, 204, 191));//61, 62, 68
	setAutoFillBackground(true);
	setPalette(pal);

	logo = new QWidget(this);
	logo->setMinimumHeight(80);
	logo->setMinimumWidth(129);
	logo->setMaximumWidth(160);
	logo->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(251, 85, 78));
	logo->setPalette(pal);
	sizePolicy.setHorizontalStretch(1);
	logo->setSizePolicy(sizePolicy);

	logoText = new QLabel(logo);
	logoText->setText(QStringLiteral("V2.16"));
	logoLayout = new  QHBoxLayout(logo);
	logoLayout->addStretch();
	logoLayout->addWidget(logoText);
	logoLayout->addStretch();
	QFont ft;
	ft.setBold(true);
	//ft.setFamily(QStringLiteral("黑体"));
	ft.setPointSize(18);
	logoText->setFont(ft);
	pal.setColor(QPalette::WindowText, Qt::white);
	logoText->setPalette(pal);

	//标题栏的空白
	blank = new QWidget(this);
	blank->setMinimumHeight(80);
	blank->setMinimumWidth(129);
	blank->setAutoFillBackground(true);

	//QLinearGradient linear(QPointF(80, 80), QPointF(150, 150));
	//QLinearGradient linear(blank->rect().topLeft(), blank->rect().bottomRight());
	//QLinearGradient linear(QPoint(blank->rect().left()+80, blank->rect().top()), blank->rect().bottomRight());
	QLinearGradient linear(QPointF(0, 0), QPointF(700, 0));
	linear.setColorAt(1, QColor(204, 205, 191));
	linear.setColorAt(0.7, QColor(215, 217, 215));
	linear.setColorAt(0.4, QColor(193, 195, 198));
	linear.setColorAt(0.2, QColor(215, 217, 215));
	linear.setColorAt(0, QColor(185, 183, 176));
	pal.setBrush(backgroundRole(), QBrush(linear));
	//pal.setColor(QPalette::Window, QColor(204, 204, 191));

	blank->setPalette(pal);
	sizePolicy.setHorizontalStretch(5);
	blank->setSizePolicy(sizePolicy);

	layout = new QHBoxLayout(this);
	layout->addWidget(logo);
	layout->addWidget(blank);
	layout->setMargin(0);
	layout->setSpacing(0);

	//button
	QSizePolicy sizeFixed(QSizePolicy::Fixed, QSizePolicy::Fixed);
	//button

	//	CloseButt->setStyleSheet(styleSheet1);
	//构建最小化、最大化、关闭按钮  
	MinimazeButt = new QPushButton(this);
	MaximizeButt = new QPushButton(this);
	CloseButt = new QPushButton(this);
	//设置显示策略
	MinimazeButt->setSizePolicy(sizeFixed);
	MinimazeButt->setMinimumHeight(30);
	MinimazeButt->setMaximumWidth(45);
	MinimazeButt->setMinimumWidth(30);
	MaximizeButt->setSizePolicy(sizeFixed);
	MaximizeButt->setMinimumHeight(30);
	MaximizeButt->setMaximumWidth(45);
	MaximizeButt->setMinimumWidth(30);
	CloseButt->setSizePolicy(sizeFixed);
	CloseButt->setMinimumHeight(30);
	CloseButt->setMaximumWidth(45);
	CloseButt->setMinimumWidth(30);

	//获取最小化、关闭按钮图标  
	QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

	//MinimazeButt->setText(QStringLiteral("最小化"));
	//设置最小化、关闭按钮图标  
	MinimazeButt->setIcon(minPix);
	MinimazeButt->setToolTip(QStringLiteral("最小化"));
	MaximizeButt->setIcon(maxPix);
	MaximizeButt->setToolTip(QStringLiteral("最大化"));
	CloseButt->setIcon(closePix);
	CloseButt->setToolTip(QStringLiteral("关闭"));
	//设置最小化、关闭按钮的样式  
	MinimazeButt->setStyleSheet("QPushButton{background-color:transparent;border-style:non; }"
		"QPushButton:hover{background-color:rgb(220,220,220);}");
	MaximizeButt->setStyleSheet("QPushButton{background-color:transparent;border-style:non;}"
		"QPushButton:hover{background-color:rgb(220,220,220);}");
	CloseButt->setStyleSheet("QPushButton{background-color:transparent;border-style:non; }"
		"QPushButton:hover{background-color:rgb(220,220,220);}");
	
	//	MaximizeButt->setStyleSheet(styleSheet2);

	//connect(CloseButt, SIGNAL(clicked()), this, SLOT(test()));
	QObject::connect(CloseButt, SIGNAL(clicked()), this->parent(), SLOT(close()));
	QObject::connect(MaximizeButt, SIGNAL(clicked()), this->parent(), SLOT(showWindowSized()));
	QObject::connect(MinimazeButt, SIGNAL(clicked()), this->parent(), SLOT(showMinimized()));

	//ip
	ipLabel = new QLabel();
	ipLabel->setText(QStringLiteral("服务器地址"));
	ipLabel->setStyleSheet(styleSheetLabel);
	hostIpEdit = new QComboBox();
	hostIpEdit->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
	hostIpEdit->setMaximumHeight(23);
	hostIpEdit->setMinimumWidth(150);
	hostIpEdit->setEditable(true);
	hostIpList = new QListWidget();
	hostIpList->setFocusPolicy(Qt::NoFocus);

	ip = new string[MAXIPSIZE];
	ifstream file("ip.txt", ios::in | ios::binary); 
	if (!file.is_open()){
		ipNum = 1;
		ip = new string("192.168.231.142");
	}
	else {
		file >> ipNum;
		//ip = new string[ipNum];
		for (int i = 0;i < ipNum;i++) {
			file >> ip[i];
		}
	}
	file.close();

	//QFile qfile("ip.txt");
	//QString *qIp;
	//if (!qfile.isOpen()) {
	//	ipNum = 1;
	//	qIp = new QString("192.168.231.142");
	//}
	//else {
	//	QByteArray file_bytearr=qfile.readAll();
	//	file_bytearr.t
	//	ip = new string[ipNum];
	//	for (int i = 0; i < ipNum; i++) {
	//		file >> ip[i];
	//	}
	//}

	pHostIpListItem = new QListWidgetItem*[MAXIPSIZE];  
	//pHostIpListItem[]中元素10个 
	for (int i = 0; i < MAXIPSIZE; i++)
	{
		pHostIpListItem[i] = new QListWidgetItem(hostIpList);
	}

	for (int i = 0;i < ipNum;i++) {	
		//pHostIpListItem[i] = new QListWidgetItem(hostIpList);
		pHostIpListItem[i]->setText(ip[i].data());
	}
	hostIpList->setItemWidget(pHostIpListItem[0], hostIpEdit);
	//connect(hostIpEdit, SIGNAL(currenTextChanged(QString)), parent, SLOT(addip(QString)));

	//hostIpEdit->setCurrentText();
	hostIpEdit->setModel(hostIpList->model());
	//hostIpEdit->setFocusProxy(hostIpList);

	connectButton = new QPushButton(this);
	connectButton->setText(QStringLiteral("连接网络"));
	connectButton->setMaximumWidth(80);
	connectButton->setMinimumWidth(60);
	connectButton->setMinimumHeight(25);
	connectButton->setStyleSheet("QPushButton{background-color:white;color:rgb(120,120,120);border-radius:3px; border:0px groove gray; border-style:outset; }"
		"QPushButton:hover{background-color:white; color: red; font: 10pt \"黑体\"}");
	connect(connectButton, SIGNAL(clicked()), parent, SLOT(connectTCP()));
	
	connect(connectButton, SIGNAL(clicked()), this, SLOT(UpdateIpList()));

	//标题栏内空白的分布
	buttLayout = new QHBoxLayout(blank);		//new QHBoxLayout(blank)
	buttLayout->addWidget(ipLabel);
	buttLayout->addWidget(hostIpEdit);
	buttLayout->addWidget(connectButton);
	buttLayout->addStretch(1);
	
	buttLayout->addWidget(MinimazeButt);
	buttLayout->addWidget(MaximizeButt);
	buttLayout->addWidget(CloseButt);

	buttLayout->setContentsMargins(60, 0, 10, 0);
}

myTitleBar::~myTitleBar()
{
	//释放ip内存
	delete []ip;
}


void myTitleBar::UpdateIpList()
{
	QString a = hostIpEdit->currentText();
	string str = string((const char *)a.toLocal8Bit());  //Qstring转string对象

	int num = ipNum;
	int flag = 0;
	//统计ip.txt中与当前输入ip相同的个数
	for (int i = 0; i < ipNum; i++)
	{
		if (!str.compare(ip[i]))
			flag++;
	}
	//没有相同ip则添加ip到ip.txt中
	if (flag == 0)  
	{
		//非0 不相等
		ipNum++;
		//如果添加的ip数量大于10 则弹出提示信息并且将ipnum置为10
		if (ipNum > MAXIPSIZE)
		{
			QMessageBox::information(this, QStringLiteral("提示信息"), 
				QStringLiteral("IP数量已经达到最大值10，打开ip.txt删除多余的ip"));
			ipNum = MAXIPSIZE;
		}
		else
		{
			//添加ip到ip.txt中
			AddIp(str);
		}
	}

	//重新读取ip.txt
	ifstream file("ip.txt", ios::in | ios::binary);
	if (!file.is_open()) 
	{
		ipNum = 1;
		ip = new string("192.168.231.142");
	}
	else
	{
		file >> ipNum;
		//ip = new string[ipNum];
		for (int i = 0; i < ipNum; i++)
		{
			file >> ip[i];
		}
	}
	file.close();

	//更新pHostIpListItem
	for (int i = 0; i < ipNum; i++)
	{
		pHostIpListItem[i]->setText(ip[i].data());
	}
	hostIpList->setItemWidget(pHostIpListItem[0], hostIpEdit);

	hostIpEdit->setModel(hostIpList->model());
}

void myTitleBar::AddIp(string &ip) 
{

	//读取配置文件
	string *ipdata = new string[ipNum+1];
	ifstream filein("ip.txt", ios::binary | ios::in);
	for (int i = 0; i < ipNum;i++)
	{
		filein >> ipdata[i];
	}

	//更新ipnum
	ipdata[0] = to_string(ipNum);
	//插入新的ip
	ipdata[ipNum] = ip;
	filein.close();

	//更新ip.txt
	ofstream file("ip.txt", ios::out);
	if (!file.is_open())
	{
		ipNum = 1;
	}
	else
	{
		for (int i = 0; i < (ipNum + 1); i++)
		{
			file << ipdata[i]<<'\n';
		}
	}

	file.close();
	delete[]ipdata;
}


void myTitleBar::mousePressEvent(QMouseEvent *event)
{
	isMoving = true;
	movePosition = event->globalPos() - this->window()->pos();
	return QWidget::mousePressEvent(event);
}

void myTitleBar::mouseReleaseEvent(QMouseEvent *event) {
	isMoving = false;
}

void myTitleBar::mouseMoveEvent(QMouseEvent *event) {
	//鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？  
	//通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标  
	if (isMoving && (event->buttons() && Qt::LeftButton)//鼠标左键按下
		&& (event->globalPos() - movePosition).manhattanLength() > QApplication::startDragDistance())
	{
		this->window()->move(event->globalPos() - movePosition);
		movePosition = event->globalPos() - this->window()-> pos();
	}
	return QWidget::mouseMoveEvent(event);
}

void myTitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
	if (Qt::WindowState::WindowMaximized == window()->windowState())
		window()->setWindowState(Qt::WindowState::WindowNoState);
	else
		window()->setWindowState(Qt::WindowState::WindowMaximized);
	return QWidget::mouseDoubleClickEvent(event);
}



void myTitleBar::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	//QPainter painter(this);// 反走样
	//painter.setRenderHint(QPainter::Antialiasing, true);

	//// 设置渐变色
	//QLinearGradient linear(QPointF(80, 80), QPointF(150, 150));
	//linear.setColorAt(0, Qt::black);
	//linear.setColorAt(1, Qt::white);

	//// 设置显示模式
	////linear.setSpread(QGradient::PadSpread);

	//// 设置画笔颜色、宽度
	//painter.setPen(QPen(QColor(0, 160, 230), 2));

	//// 设置画刷填充
	//painter.setBrush(linear);

	//// 绘制椭圆
	//painter.drawRect(QRect(40, 0, 40, 60));

}

void myTitleBar::test() {
	close();
}
