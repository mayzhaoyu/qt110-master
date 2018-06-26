#include "waveformWidget.h"

waveformWidget::waveformWidget(QWidget *parent, QTcpSocket **psocket)
	: QWidget(parent), WaveCmdWriter(psocket)
{
	ui.setupUi(this);

	plotLineBtn = new QPushButton(QStringLiteral("绘制曲线"));

	stackWave = new QStackedWidget(this);
	
	this->psocket = psocket;	
	
	PageTable = new WavePage*[9];
	for (int i = 0; i < 9; i++)
	{
		PageTable[i] = new WavePage(this, i + 1, PlotNumber[i]);
	}

	points1 = new QPolygonF[PlotNumber[0]];
	points2 = new QPolygonF[PlotNumber[1]];
	points3 = new QPolygonF[PlotNumber[2]];
	points4 = new QPolygonF[PlotNumber[3]];
	points5 = new QPolygonF[PlotNumber[4]];
	points6 = new QPolygonF[PlotNumber[5]];
	points7 = new QPolygonF[PlotNumber[6]];
	points8 = new QPolygonF[PlotNumber[7]];
	points9 = new QPolygonF[PlotNumber[8]];

	//QPolygonF **pointsTable; 后期改进
	//第一页到第九页的波形路径
	//QPolygonF **pointsTable;
	//pointsTable = new QPolygonF*[9];
	//for (int i = 0; i < 9; i++)
	//{
	//	pointsTable[i] = new QPolygonF[PlotNumber[i]];
	//}

	for (int i = 0; i < 9; i++)
	{
		stackWave->addWidget(PageTable[i]);
	}

	/*stackWave->addWidget(Page1);
	stackWave->addWidget(Page2);*/

	listwidget = new QListWidget(this);
	listwidget->setMaximumWidth(80);
	listwidget->insertItem(0, QStringLiteral("第一页"));
	listwidget->insertItem(1, QStringLiteral("第二页"));
	listwidget->insertItem(2, QStringLiteral("第三页"));
	listwidget->insertItem(3, QStringLiteral("第四页"));
	listwidget->insertItem(4, QStringLiteral("第五页"));
	listwidget->insertItem(5, QStringLiteral("第六页"));
	listwidget->insertItem(6, QStringLiteral("第七页"));
	listwidget->insertItem(7, QStringLiteral("第八页"));
	listwidget->insertItem(8, QStringLiteral("第九页"));
	

	//stackWave->setCurrentIndex(1);
	//布局设计
	BtnLayout = new QVBoxLayout;
	BtnLayout->addWidget(listwidget);
	BtnLayout->addWidget(plotLineBtn);

	//整体布局
	mainlayout = new QHBoxLayout(this);
    mainlayout->addLayout(BtnLayout);
	mainlayout->addWidget(stackWave); 
	
	connect(plotLineBtn, SIGNAL(clicked()), this, SLOT(sendGetWaveData()));   //发送指令
	//连接信号 发送信号 携带数据 接受信号 解析数据
	//connect(WavePageOnebtn,SIGNAL(clicked()),stackWave, SLOT(setCurrentIndex(0)));
	//connect(plotLineBtn, SIGNAL(clicked()), wavepageOne, SLOT(draw1()));
	//connect(plotLineBtn, SIGNAL(clicked()), wavepageTwo, SLOT(draw2()));
	connect(listwidget, SIGNAL(currentRowChanged(int)), stackWave, SLOT(setCurrentIndex(int)));
}

waveformWidget::~waveformWidget()
{
	delete []points1;  delete[]points6;
	delete []points2;  delete[]points7;
	delete[]points3;   delete[]points8;
	delete[]points4;   delete[]points9;
	delete[]points5;
	
}

void waveformWidget::BufferToPath(uint8_t * buffer, int size)
{
	OutputDataToTxt(buffer, size, "buffer.txt");
	int index = 0;
	PathPageType1(buffer,index);

	PathPageType2(buffer, index);

	PathPageType3(buffer, index);
	/*PathPageType3(buffer, index);
	PathPageType3(buffer, index);
	PathPageType3(buffer, index);
	PathPageType3(buffer, index);
	PathPageType3(buffer, index);
	PathPageType3(buffer, index);*/
	
}

void waveformWidget::PathPageType1(uint8_t * buffer,int & index)
{
	int datalength;
	//将29路波形分为9类，Page1->PlotNum; 每一路

	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];
	unsigned char *p = (unsigned char *)malloc(sizeof(char)*datalength);

	memcpy(p, &buffer[index + 3], datalength);

	OutputDataToTxt(p, datalength, "1.txt");

	int j; float Sum = 0;
	int L;
	if (datalength % 2 == 1)
	{
		L = (datalength + 1) / 2;
	}
	else
	{
		L = datalength / 2;
	}

	float *pData = (float *)malloc(sizeof(float)*L);
	//归一化处理
	for (j = 0; j < L; j++)
	{
		pData[j] = p[2 * j] + 16 * 16 * p[2 * j + 1];
		float a = pData[j];
		Sum += pData[j];
	}

	for (j = 0; j < L; j++)
	{
		pData[j] = (pData[j] / Sum) * 100;
		//float a = pData[j];
	}

	//输入节点数据QPointF(x,y)  

	double temp = 0;
	for (j = 0; j < L - 1; j++)
	{
		points1[0] << QPointF(temp, 3.3);
		temp += pData[j];
		points1[0] << QPointF(temp, 3.3);
		points1[0] << QPointF(temp, 0);
		temp += pData[j + 1];
		j++;
		points1[0] << QPointF(temp, 0);

	}

	points1[0] << QPointF(100.0, 3.3); //波形尾部处理
	free(p);
	free(pData);

	index = index + datalength + 3;


	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	p = (unsigned char *)malloc(sizeof(char)*datalength);
	//OutputDataToTxt(&buffer[i + 9], datalength,"2.txt");
	memcpy(p, &buffer[index + 3], datalength);
	OutputDataToTxt(p, datalength, "2.txt");

	//数据解析

	pData = (float *)malloc(sizeof(float)*datalength);

	//计算第j个低电平对应的最小值
	for (j = 0; j < datalength; j++)
	{
		pData[j] = (255.0 - (int)p[j]) * (3.300 / 255);
	}

	//输入节点数据QPointF(x,y)  
	points1[1] = points1[0];

	temp = 0;
	//对低电平波形重新赋值点
	for (j = 0; j < datalength; j++)
	{
		//float a = points2[4 * j + 2].x;
		temp = (points1[1][4 * j + 2].x() + points1[1][4 * j + 3].x()) / 2;
		points1[1][4 * j + 2].setY(pData[j]);
		points1[1][4 * j + 3].setY(pData[j]);
		//(points2[4 * j + 2].x + points2[4 * j + 3].x) / 2
		points1[1][4 * j + 2].setX(temp);
		//points2[]
		points1[1][4 * j + 3].setX(temp);
	}
	//points1 << QPointF(100.0, 3.3);
	//p2->SetTitleAndAxis(buffer[i + 7]);
	//p2->drawline1(points2);
	index = index + datalength + 3;
	free(p);
	free(pData);
}

void waveformWidget::PathPageType2(uint8_t * buffer,int & index)  //第三类波形
{
	//第三路
	int datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];
	index = index + datalength + 3;
}

void waveformWidget::PathPageType3(uint8_t * buffer,int & index)
{
	//第三页 第四路
	int datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	unsigned char *pData = new unsigned char[datalength];
	float *DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	OutputDataToTxt(pData, datalength, "4.txt");
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points3[0] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第三页 第五路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points3[1] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	// 第四页 第六路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points4[0] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第四页 第七路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points4[1] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第四页 第八路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points4[2] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第四页 第九路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points4[3] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第四页 第十路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points4[4] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第四页 第十一路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points4[5] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第五页 第十二路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points5[0] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第五页 第十三路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points5[1] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第五页 第十四路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points5[2] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第五页 第十五路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points5[3] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第五页 第十六路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points5[4] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第五页 第十七路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points5[5] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第六页 第十八路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points6[0] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第六页 第十九路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points6[1] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第六页 第20路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points6[2] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第7页 第21路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points7[0] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第7页 第22路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points7[1] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第8页 第23路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points8[0] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第8页 第24路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points8[1] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第8页 第25路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points8[2] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第9页 第26路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points9[0] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第9页 第27路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points9[1] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第9页 第28路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points9[2] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

	//第9页 第29路
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//将数据映射到 0~3.3v区间
	for (int i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (int i = 0; i < datalength; i++)
	{
		points9[3] << QPointF(i, DataFloat[i]);
	}
	index = index + datalength + 3;
	delete pData;
	delete DataFloat;

}

void waveformWidget::clearPoints()
{
	//后面改进
	for (int i = 0; i < PlotNumber[0]; i++)
	{
		points1[i].clear();
	}
	for (int i = 0; i < PlotNumber[1]; i++)
	{
		points2[i].clear();
	}
	for (int i = 0; i < PlotNumber[2]; i++)
	{
		points3[i].clear();
	}
	for (int i = 0; i < PlotNumber[3]; i++)
	{
		points4[i].clear();
	}
	for (int i = 0; i < PlotNumber[4]; i++)
	{
		points5[i].clear();
	}
	for (int i = 0; i < PlotNumber[5]; i++)
	{
		points6[i].clear();
	}
	for (int i = 0; i < PlotNumber[6]; i++)
	{
		points7[i].clear();
	}
	for (int i = 0; i < PlotNumber[7]; i++)
	{
		points8[i].clear();
	}
	for (int i = 0; i < PlotNumber[8]; i++)
	{
		points9[i].clear();
	}
}



void waveformWidget::sendGetWaveData()
{
	WaveCmdWriter.command((unsigned char)04, (unsigned char)00);
}

void waveformWidget::updateWave(uint8_t *buffer,int size)
{

	BufferToPath(buffer,size);

	PageTable[0]->DrawWave(points1, PageTable[0]->PlotNum);
	PageTable[1]->DrawWave(points2, PageTable[1]->PlotNum);
	PageTable[2]->DrawWave(points3, PageTable[2]->PlotNum);
	PageTable[3]->DrawWave(points4, PageTable[3]->PlotNum);
	PageTable[4]->DrawWave(points5, PageTable[4]->PlotNum);
	PageTable[5]->DrawWave(points6, PageTable[5]->PlotNum);
	PageTable[6]->DrawWave(points7, PageTable[6]->PlotNum);
	PageTable[7]->DrawWave(points8, PageTable[7]->PlotNum); 
	PageTable[8]->DrawWave(points9, PageTable[8]->PlotNum);

	clearPoints();

	//PageTable[1]->DrawWave(points22, PageTable[1]->PlotNum);

}
