#include "cisDebugWidget.h"

char optTreeStyleSheet[] = "QListWidget { background-color: qlineargradient(x1: 0, y1 : 0, x2 : 0, y2 : 1,"
"stop:0 rgb(204,205, 191),stop:0.4 rgb(215, 217, 215), stop:1   rgb(185, 183, 176)); "
"color: black;border-style: none; "
" font: 11pt \"MS Shell Dlg 2\" ; "
" }"
"QListWidget::item {min-height: 40px;border-style: none;}"
/*"QListWidget::item:selected{background-color:rgb(0, 196, 170);}"
"QListWidget::item:selected:active{background-color:rgb(0, 196, 170);}"*/
"QListWidget::item:hover{color:rgb(0, 0, 0); background-color:rgb(190, 196, 170); }";



//qlineargradient(x1: 0, y1 : 0, x2 : 0, y2 : 1,
//	stop : 0 #1B2534, stop: 0.4 #010101,
//	stop: 0.5 #000101, stop: 1.0 #1F2B3C)
cisDebugWidget::cisDebugWidget(QWidget *parent, QTcpSocket **psocket)
	: QWidget(parent), frame_writer(psocket)
{
	ui.setupUi(this);
	this->psocket = psocket;
	wind = new QWidget(this);
	optList = new QListWidget(this);


	QStringList* sl = new QStringList();
	sl->append(QStringLiteral("校正"));
	sl->append(QStringLiteral("清除校正系数"));

	optList->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding));
	optList->setMaximumWidth(150);
	optList->setStyleSheet(optTreeStyleSheet);
	optList->addItems(*sl);
	optList->setFocusPolicy(Qt::NoFocus);
	for (int i = 0; i < optList->count(); i++) {
		optList->item(i)->setTextAlignment(Qt::AlignCenter);
	}
	delete sl;
	
	
	h_layout = new QHBoxLayout(this);
	h_layout->addWidget(wind);
	h_layout->addWidget(optList);
	h_layout->setMargin(0);
//	connect(optList, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked_optlist(QModelIndex)));
}

cisDebugWidget::~cisDebugWidget()
{
}

void cisDebugWidget::fix_capButtonClicked(){
	cisTextEdit->setText(fix_cap_button->text());
	frame_writer.cmdFix(0x01);
}

void cisDebugWidget::fix_saveButtonClicked(){
	cisTextEdit->setText(fix_save_button->text());
	frame_writer.cmdFix(0x05);
}

void cisDebugWidget::fix_applyButtonClicked(){
	cisTextEdit->setText(fix_apply_button->text());
	frame_writer.cmdFix(0x03);
}

void cisDebugWidget::fix_readButtonClicked(){
	cisTextEdit->setText(fix_read_button->text());
	frame_writer.cmdFix(0x04);
}

void cisDebugWidget::fix_clearButtonClicked(){
	cisTextEdit->setText(fix_clear_button->text());
	frame_writer.cmdFix(0x06);
}

void cisDebugWidget::fix_getimgButtonClicked(){
	cisTextEdit->setText(fix_getimg_button->text());
	frame_writer.cmdFix(0x02);
}


void cisDebugWidget::on_clicked_optlist(QModelIndex modelIndex) {

	
}