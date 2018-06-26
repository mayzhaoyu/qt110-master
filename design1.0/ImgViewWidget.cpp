#include "ImgViewWidget.h"
//#include "highgui.hpp"

ImgViewWidget::ImgViewWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	FrontRGBImg = QImage("Qt.png");
	FrontIRImg = QImage("Qt.png");
	BackRGBImg = QImage("Qt.png");
	BackIRImg = QImage("Qt.png");

	QLabel *FrontRGBImgLbtxt = new QLabel(QStringLiteral("彩色正面"));
	QLabel *FrontIRImgLbtxt = new QLabel(QStringLiteral("红外正面"));
	QLabel *BackRGBImgLbtxt = new QLabel(QStringLiteral("彩色背面"));
	QLabel *BackIRImgLbtxt = new QLabel(QStringLiteral("彩色背面"));

	GetImgBtn = new QPushButton(QStringLiteral("获取图像"));
	SaveImgBtn = new QPushButton(QStringLiteral("保存图像"));

	FrontRGBImgLb = new QLabel(this);
	//FrontRGBImgLb->setPixmap(QPixmap::fromImage(FrontRGBImg).scaled(QSize(200, 200)));
	FrontIRImgLb = new QLabel(this);
	FrontIRImgLb->setPixmap(QPixmap::fromImage(FrontRGBImg).scaled(QSize(200, 200)));
	BackRGBImgLb = new QLabel(this);
	BackRGBImgLb->setPixmap(QPixmap::fromImage(FrontRGBImg).scaled(QSize(200, 200)));
	BackIRImgLb = new QLabel(this);
	BackIRImgLb->setPixmap(QPixmap::fromImage(FrontRGBImg).scaled(QSize(200, 200)));

	QGridLayout *QGLayout = new QGridLayout(this);
	QGLayout->addWidget(FrontRGBImgLb,0,0);
	QGLayout->addWidget(FrontIRImgLb, 0, 1);
	QGLayout->addWidget(FrontRGBImgLbtxt, 1, 0);
	QGLayout->addWidget(FrontIRImgLbtxt, 1, 1);
	QGLayout->addWidget(BackRGBImgLb, 2, 0);
	QGLayout->addWidget(BackIRImgLb, 2, 1);
	QGLayout->addWidget(BackRGBImgLbtxt, 3, 0);
	QGLayout->addWidget(BackIRImgLbtxt, 3, 1);
	QGLayout->addWidget(GetImgBtn, 4, 0);
	QGLayout->addWidget(SaveImgBtn, 4, 1);

	QGLayout->setContentsMargins(20, 10, 20, 10);

	//label->setPixmap();

	/*QImage img = QImage((const unsigned char*)(msg.GZHImage), 134, 25, 134, QImage::Format_Grayscale8);
	QLabel *label = new QLabel("");
	label->setPixmap(QPixmap::fromImage(img).scaled(QSize(134, 25)));*/
}

ImgViewWidget::~ImgViewWidget()
{
}
void ImgViewWidget::updateImg(uint8_t *buffer, int size)
{
	//更新图片
	int t = size;

	//解析图片数据
	int i;
	FILE *fp = fopen("data7.txt", "w");
	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%x ", buffer[i]);
	}
	fclose(fp);

	//opencv保存图片

	//QImage img = QImage((const unsigned char*)(buffer), 1440, 1968, QImage::Format_Grayscale8);
	//FrontRGBImgLb->setPixmap(QPixmap::fromImage(img).scaled(QSize(1440, 1968)));
	//bool a = img.save("1.bmp");
	//int t = size;

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

	QImage img = QImage((const unsigned char*)(buffer), 1440, 1968, 1440,QImage::Format_Grayscale8);
	/*QImage img(1440, 1968, QImage::Format_Grayscale8);
	for (int i = 0; i < 1968; i++)
	{
		uchar *line = img.scanLine(i);
		for (int j = 0; j < 1440; j++) 
		{
			*line++ = *buffer++;
			
		}
		
	}*/
	qDebug("%d,%d,%d,%d", buffer[0], buffer[1], buffer[2], buffer[3]);

	img.save("1.bmp");
}
