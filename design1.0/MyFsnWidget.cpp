#include "MyFsnWidget.h"

#include <QFile>
static const char verTable[][5] = { "1990","1999","2005","2015" };
static const char tfTable[][7] = {"false","true","broken","old" };

MyFsnWidget::MyFsnWidget(QWidget *parent, QTcpSocket **psocket)
	: QWidget(parent) , GZHCmdWriter(psocket)
{
	ui.setupUi(this);
	setAutoFillBackground(true);

	fsnTable = new QTableWidget(0,9);

	this->psocket = psocket;
	//gzh_list = new list<gzh>();
	gzh_list = new list<QString>();
	//

	//GZHCmdWriter = new frameWriter(&socket);

	//表格
	fsnTable->setWindowTitle("QTableWidget & Item");
	fsnTable->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	//fsnTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(fsnTable, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(openDialog(QTableWidgetItem*)));
	connect(fsnTable, SIGNAL(cellClicked(int,int)), this, SLOT(mark(int,int)));
	connect(fsnTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(popMenu(QPoint)));
//	fsnTable->setMaximumWidth(width());
	//fsnTable->resize(350, 200);  //设置表格  
	QStringList header;
	header << QStringLiteral("面额") << QStringLiteral("版本") << QStringLiteral("方向") << QStringLiteral("长度")<< QStringLiteral("宽度") << QStringLiteral("错误码") << QStringLiteral("保留字") << QStringLiteral("冠字号") << QStringLiteral("抠图");
	fsnTable->setHorizontalHeaderLabels(header);
	for (int i = 0; i < 8; i++) {
		fsnTable->setColumnWidth(i, 90);
	}
	fsnTable->setColumnWidth(8, 134);
	//fsnTable->setFont(QFont("Monospace"));
	fsnTable->setFont(QFont("Consolas"));


	//按钮
	ClearBtn = new QPushButton(this);
	ClearBtn->setText(QStringLiteral("清空"));
	connect(ClearBtn, SIGNAL(clicked()), this, SLOT(ClearBtnClicked()));

	CompareBtn = new QPushButton(this);
	CompareBtn->setText(QStringLiteral("比对"));
	connect(CompareBtn, SIGNAL(clicked()), this, SLOT(CompareBtnClicked()));

	SaveTempBtn=new QPushButton(this);
	SaveTempBtn->setText(QStringLiteral("保存模板"));
	connect(SaveTempBtn, SIGNAL(clicked()), this, SLOT(SaveTempBtnClicked()));

	connect(this, SIGNAL(debug(QString)), parent, SLOT(debugPrint(QString)));

	SendGZHCmdBtn = new QPushButton(this);
	SendGZHCmdBtn->setText(QStringLiteral("发送指令"));
	connect(SendGZHCmdBtn, SIGNAL(clicked()), this, SLOT(SendGZHCmd()));

	//connect(this,SIGNAL(), GZHCmdWriter,)
	//layout
	layout = new QGridLayout(this);
	layout->addWidget(fsnTable,0,0,1,4);
	layout->addWidget(ClearBtn,1,0,1,1);
	layout->addWidget(CompareBtn, 1, 1, 1, 1);
	layout->addWidget(SaveTempBtn, 1, 2, 1, 1);
	layout->addWidget(SendGZHCmdBtn, 1, 3, 1, 1);
	layout->setContentsMargins(20, 10, 20, 10);

	dialog_errcode = new dialogErrCode(this);
	dialog_errcode->setModal(true);


	//右键菜单
	//检测鼠标右键
	//connect(fsnTable, SIGNAL(contextMenuEvent(QContextMenuEvent *)), this, SLOT(popMenu(QContextMenuEvent*)));//检测鼠标右键

	//初始化变量

	max_length=0;  max_length_index=0;
	min_length=65535; min_length_index=0;
	max_width=0; max_width_index=0;
	min_width=65535; min_width_index=0;
}

MyFsnWidget::~MyFsnWidget()
{
}


void MyFsnWidget::ClearBtnClicked() 
{//clear
	for (int i = 0;i < fsnTable->rowCount();i++) {
		for(int j=0;j<fsnTable->colorCount();j++)
			delete fsnTable->item(i, j);
	}
	fsnTable->reset();
	fsnTable->setRowCount(0);
	max_length = 0;  max_length_index = 0;
	min_length = 65535; min_length_index = 0;
	max_width = 0; max_width_index = 0;
	min_width = 65535; min_width_index = 0;
}

void MyFsnWidget::SaveTempBtnClicked() {
	
	//QFile file("GZH.txt");
	//file.open(QIODevice::WriteOnly);
	//for (int i = 0; i < fsnTable->rowCount(); i++) {
	//	file.write(QString("[%1] ").arg(i+1, 3, 10).toLatin1());
	//	file.write(fsnTable->item(i, 6)->text().toLatin1());
	//	file.write("\n");
	//}
	//file.close();
	gzh_list->clear();
	for (int i = 0; i < fsnTable->rowCount(); i++) 
	{
		//gzh_list->insert(gzh_list->begin(), *(gzh*)fsnTable->item(i,6)->text().toLatin1().data());
		gzh_list->insert(gzh_list->begin(), fsnTable->item(i, 7)->text());
	//	emit debug(fsnTable->item(i, 6)->text());
	}
}

void MyFsnWidget::setChecked(int row, QColor color) {
	for (int i = 0; i < fsnTable->columnCount() - 1; i++) {
		fsnTable->item(row, i)->setTextColor(Qt::white);
		fsnTable->item(row, i)->setBackgroundColor(color);
	}
}
bool strCompare(QString& str1, QString& str2) 
{
	bool temp = true;
	for (int i = 0; i < str1.length(); i++) {
		if (str1.at(i) != str2.at(i)) {
			temp = false;
		}
	}
	return temp;
}

bool MyFsnWidget::compareGzh(QString& str) 
{
	int res = 0;
	for (list<QString>::iterator iter = gzh_list->begin(); iter != gzh_list->end(); ++iter)
	{
	//	emit debug(*iter);
	//	emit debug(str);
		//if( strCompare(*iter,str) ){
		if (*iter == str) {
			res = 1;
		}
	}
	if (res == 1)
		return true;
	else
		return false;
}
void MyFsnWidget::CompareBtnClicked() {
	for (int i = 0; i < fsnTable->rowCount(); i++) {
		if (compareGzh(fsnTable->item(i, 7)->text()))
			setChecked(i, QColor(91, 140, 71));//green
		else {
			setChecked(i, QColor(251, 85, 78));//red
		}
	}

}


void MyFsnWidget::setItemColor(int row,int col, itemType type){
	QColor color;
	QColor background;
	if (type == itemType::nomal) {
		color = Qt::black;
		background= Qt::white;
	}
	if (type == itemType::min) {
		color = Qt::white;
		background = QColor(128,255,128);
	}
	if (type == itemType::max) {
		color = Qt::white;
		background = Qt::green;
	}
	if (type == itemType::red) {
		color = Qt::white;
		background = QColor(251, 85, 78);
	}
	if ((col==5)&&(type == itemType::nomal)) {
		color = QColor(251, 85, 78);
		background = Qt::white;
	}
	fsnTable->item(row, col)->setTextColor(color);
	fsnTable->item(row, col)->setBackgroundColor(background);
}

void MyFsnWidget::updateTable(billInf& msg)  //一张钱就要发送一个数据包，也就是说要调用一次这个函数更新表
{
	QString str;
	int length = msg.moneyResult.length;
	int width = msg.moneyResult.width;
	fsnTable->insertRow(fsnTable->rowCount());
	Qt::ItemFlags flag = (Qt::ItemIsSelectable) | (Qt::ItemIsEnabled);
	int row = fsnTable->rowCount() - 1;
	fsnTable->setRowHeight(row, 25);
	//面额
	str = QString("%1").arg(msg.moneyResult.money, 0, 10);
	fsnTable->setItem(row, 0, new QTableWidgetItem(str));
	fsnTable->item(row, 0)->setTextAlignment(Qt::AlignCenter);
	fsnTable->item(row, 0)->setFlags(flag);
	//版本
	str = QString("%1").arg(msg.moneyResult.edition, 0, 10);
	fsnTable->setItem(row, 1, new QTableWidgetItem(str));
	fsnTable->item(row, 1)->setTextAlignment(Qt::AlignCenter);
	fsnTable->item(row, 1)->setFlags(flag);
	//方向
	str = QString("%1").arg(msg.moneyResult.direction, 0, 10);
	fsnTable->setItem(row, 2, new QTableWidgetItem(str));
	fsnTable->item(row, 2)->setTextAlignment(Qt::AlignCenter);
	fsnTable->item(row, 2)->setFlags(flag);
	//长度
	str = QString("%1").arg(length, 0, 10);
	fsnTable->setItem(row, 3, new QTableWidgetItem(str));
	fsnTable->item(row, 3)->setTextAlignment(Qt::AlignCenter);
	fsnTable->item(row, 3)->setFlags(flag);
	if (min_length >length) {
		min_length = length;
		if ( max_length_index == min_length_index) {
			setItemColor(min_length_index, 3, itemType::max);
		}
		else {
			setItemColor(min_length_index, 3, itemType::nomal);
		}
		setItemColor(row, 3, itemType::min);
		
		min_length_index = row;
	}
	if (max_length < length) {
		max_length = length;
		if (max_length_index== min_length_index){
			setItemColor(max_length_index, 3, itemType::min);
		}
		else {
			setItemColor(max_length_index, 3, itemType::nomal);
		}
		setItemColor(row, 3, itemType::max);
		max_length_index = row;
	}
	//宽度
	str = QString("%1").arg(width, 0, 10);
	fsnTable->setItem(row, 4, new QTableWidgetItem(str));
	fsnTable->item(row, 4)->setTextAlignment(Qt::AlignCenter);
	fsnTable->item(row, 4)->setFlags(flag);

	if (min_width >width) {
		min_width = width;
		if (max_width_index == min_width_index) {
			setItemColor(min_width_index, 4, itemType::max);
		}
		else {
			setItemColor(min_width_index, 4, itemType::nomal);
		}
		setItemColor(row, 4, itemType::min);

		min_width_index = row;
	}
	if (max_width < width) {
		max_width = width;
		if (max_width_index == min_width_index) {
			setItemColor(max_width_index, 4, itemType::min);
		}
		else {
			setItemColor(max_width_index, 4, itemType::nomal);
		}
		setItemColor(row, 4, itemType::max);
		max_width_index = row;
	}

	//错误码
	str = QString("%1").arg(msg.moneyResult.isTrue,8,16,QChar('0'));
	fsnTable->setItem(row, 5, new QTableWidgetItem(str));
	fsnTable->item(row, 5)->setTextAlignment(Qt::AlignCenter);
	fsnTable->item(row, 5)->setFlags(flag);
	if (msg.moneyResult.isTrue != 0)
		fsnTable->item(row, 5)->setTextColor(QColor(251, 85, 78));
	//保留字
	str = QString("%1").arg(msg.moneyResult.reserved, 0, 10);
	fsnTable->setItem(row, 6, new QTableWidgetItem(str));
	fsnTable->item(row, 6)->setTextAlignment(Qt::AlignCenter);
	fsnTable->item(row, 6)->setFlags(flag);
	//冠字号
	str = "";
	for (int i = 0; i < strlen(msg.moneyResult.GZHresult); i++) {
		str += msg.moneyResult.GZHresult[i];
	}
	fsnTable->setItem(row, 7, new QTableWidgetItem(str));
	fsnTable->item(row, 7)->setTextAlignment(Qt::AlignCenter);
	//imgr
	QImage img= QImage((const unsigned char*)(msg.GZHImage),134, 25,134,QImage::Format_Grayscale8);
	QLabel *label = new QLabel("");
	label->setPixmap(QPixmap::fromImage(img).scaled(QSize(134, 25)));
//	label->setPixmap(QPixmap::fromImage(img));
	fsnTable->setCellWidget(row, 8, label);

	/*if (list_on == 1)
		gzh_list->insert(gzh_list->begin(), *(gzh*)msg.moneyResult.GZHresult);*/
	fsnTable->scrollToBottom();
}

void MyFsnWidget::openDialog(QTableWidgetItem* tiem) {
	if (tiem->column() == 5) {
	
	//	if(dialog_errcode!=NULL)
	//		delete dialog_errcode;
	
		dialog_errcode->setCode(tiem->text().toUInt(0, 16));
		dialog_errcode->show();

	}
}
/*
槽函数----单击表项
*/
void MyFsnWidget::mark(int row, int col) {

}

/*
槽函数----右键菜单选项
*/
void MyFsnWidget::mark() {
	QTableWidgetItem* curItem = fsnTable->currentItem();
	if (curItem->column() == 8) return;
	setItemColor(curItem->row(), curItem->column(), itemType::red);
}

void MyFsnWidget::unmark() {
	QTableWidgetItem* curItem = fsnTable->currentItem();
	if (curItem->column() == 8) return;
	setItemColor(curItem->row(), curItem->column(), itemType::nomal);
}
void MyFsnWidget::allmark() {
	QTableWidgetItem* curItem = fsnTable->currentItem();
	QString text = curItem->text();
	for (int i = 0; i < fsnTable->rowCount(); i++) {
		if (fsnTable->item(i, curItem->column())->text().compare(text)==0) {
			setItemColor(i, curItem->column(), itemType::red);
		}
	}
}
void MyFsnWidget::allunmark() {
	QTableWidgetItem* curItem = fsnTable->currentItem();
	QString text = curItem->text();
	for (int i = 0; i < fsnTable->rowCount(); i++) {
		if (fsnTable->item(i, curItem->column())->text() == text) {
			setItemColor(i, curItem->column(), itemType::nomal);
		}
	}
}

void MyFsnWidget::clearmark() {
	for (int i = 0; i < fsnTable->rowCount(); i++) {
		for (int j = 0; j < 8; j++) {
			setItemColor(i, j, itemType::nomal);
		}
	}
}

/*
槽函数----右击表项弹出菜单
*/
void MyFsnWidget::popMenu(QPoint point) {
	QTableWidgetItem* curItem = fsnTable->currentItem();  //获取当前被点击的节点
	if (curItem == NULL)return;   //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
	
	RowNum = curItem->row();
	
	QAction markItem(QString::fromLocal8Bit("标记该项"), this);//
	QAction unmarkItem(QString::fromLocal8Bit("取消该项标记"), this);//
	QAction markAllItem(QString::fromLocal8Bit("搜索并标记该值"), this);
	QAction unmarkAllItem(QString::fromLocal8Bit("取消该值的标记"), this);
	QAction clearmarkItem(QString::fromLocal8Bit("清除所有标记"), this);
	QAction saveImgItem(QString::fromLocal8Bit("保存标记对应的图片"), this);
					
	connect(&markItem, SIGNAL(triggered()), this, SLOT(mark()));
	connect(&unmarkItem, SIGNAL(triggered()), this, SLOT(unmark()));
	connect(&markAllItem, SIGNAL(triggered()), this, SLOT(allmark()));
	connect(&unmarkAllItem, SIGNAL(triggered()), this, SLOT(allunmark()));
	connect(&clearmarkItem, SIGNAL(triggered()), this, SLOT(clearmark()));
	connect(&saveImgItem, SIGNAL(triggered()), this, SLOT(SaveImgmark()));

	QMenu menu(fsnTable);
	menu.addAction(&markItem);
	menu.addAction(&unmarkItem);
	menu.addAction(&markAllItem);
	menu.addAction(&unmarkAllItem);
	menu.addAction(&clearmarkItem);
	menu.addAction(&saveImgItem);
	menu.exec(QCursor::pos());  //在当前鼠标位置显示
}

void MyFsnWidget::SaveImgmark()
{
	//int x = point.x();
	uint16_t num = fsnTable->rowCount()-RowNum;
	GZHCmdWriter.frame.data[0] = num;
	GZHCmdWriter.frame.data[1] = num/256;
	GZHCmdWriter.frame.data[2] = RowNum+1;
	GZHCmdWriter.frame.data[3] = (RowNum+1)/256;
	GZHCmdWriter.frame.cmd = (uint16_t)3 * 256;
	GZHCmdWriter.frame.cmd += 4;
	GZHCmdWriter.frame.msg_length = (uint32_t)4;
	GZHCmdWriter.send();
}

void MyFsnWidget::SendGZHCmd()
{
	GZHCmdWriter.command((unsigned char)00, (unsigned char)00);
}

/*
for(int i=0;i<25;i++){
for(int j=0;j<134;j++){
record.GZHImage[134*i+j]=j*0.9;
}
*/


