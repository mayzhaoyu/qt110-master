#include "dialogErrorCode.h"

dialogErrorCode::dialogErrorCode(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	closebutton = new QPushButton(this);
	closebutton->setText(QStringLiteral("�ر�"));
	QObject::connect(closebutton, SIGNAL(clicked()), this, SLOT(close()));
	layout = new QVBoxLayout(this);
	layout->addWidget(closebutton);
}

dialogErrorCode::~dialogErrorCode()
{
}
