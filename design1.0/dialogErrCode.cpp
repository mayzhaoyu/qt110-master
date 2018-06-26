#include "dialogErrCode.h"

dialogErrCode::dialogErrCode(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	closebutton = new QPushButton(this);
	closebutton->setText(QStringLiteral("¹Ø±Õ"));
	QObject::connect(closebutton, SIGNAL(clicked()), this, SLOT(close()));
	layout = new QVBoxLayout(this);
	errTable=new  QTableWidget(0, 2);
	errTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//	errTable->setm
	QStringList header;
	header << QStringLiteral("´íÎó±àºÅ") << QStringLiteral("ÒâÒå");
	errTable->setHorizontalHeaderLabels(header);
	layout->addWidget(errTable);
	layout->addWidget(closebutton);
}

dialogErrCode::~dialogErrCode()
{
	delete closebutton;
	delete layout;
	//delete this;
}

void dialogErrCode::setCode(uint32_t errcode = 0) {
	uint32_t tempcode = errcode;
	code = errcode;
	setWindowTitle(QStringLiteral("´íÎóÂë") + QString("%1H").arg(code, 0, 16));
	int row = 0;
	uint32_t temp;
	Qt::ItemFlags flag = (Qt::ItemIsSelectable) | (Qt::ItemIsEnabled);
	for (int i = 0; i < errTable->rowCount(); i++) {
		for (int j = 0; j<errTable->colorCount(); j++)
			delete errTable->item(i, j);
	}
	errTable->reset();
	errTable->setRowCount(0);
	for (int i = 0; i < 32; i ++) {
		temp=(tempcode >> i) & 0x00000001;
		if (temp == 1) {
			errTable->insertRow(errTable->rowCount());
			errTable->setItem(row, 0, new QTableWidgetItem(QString("%1").arg(i, 0, 10)));
			//errTable->setItem(row, 0, new QTableWidgetItem("abc"));
			errTable->setItem(row, 1, new QTableWidgetItem(" "));
			errTable->item(row, 0)->setTextAlignment(Qt::AlignCenter);
			errTable->item(row, 1)->setTextAlignment(Qt::AlignCenter);
			errTable->item(row, 0)->setFlags(flag);
			errTable->item(row, 1)->setFlags(flag);
		
			row++;
			//errTable->item(row, 0)->setTextAlignment(Qt::AlignCenter);
		}
	}

}