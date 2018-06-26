#include "waveformWidget.h"

waveformWidget::waveformWidget(QWidget *parent, QTcpSocket **psocket)
	: QWidget(parent), WaveCmdWriter(psocket)
{
	ui.setupUi(this);

	plotLineBtn = new QPushButton(QStringLiteral("��������"));

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

	//QPolygonF **pointsTable; ���ڸĽ�
	//��һҳ���ھ�ҳ�Ĳ���·��
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
	listwidget->insertItem(0, QStringLiteral("��һҳ"));
	listwidget->insertItem(1, QStringLiteral("�ڶ�ҳ"));
	listwidget->insertItem(2, QStringLiteral("����ҳ"));
	listwidget->insertItem(3, QStringLiteral("����ҳ"));
	listwidget->insertItem(4, QStringLiteral("����ҳ"));
	listwidget->insertItem(5, QStringLiteral("����ҳ"));
	listwidget->insertItem(6, QStringLiteral("����ҳ"));
	listwidget->insertItem(7, QStringLiteral("�ڰ�ҳ"));
	listwidget->insertItem(8, QStringLiteral("�ھ�ҳ"));
	

	//stackWave->setCurrentIndex(1);
	//�������
	BtnLayout = new QVBoxLayout;
	BtnLayout->addWidget(listwidget);
	BtnLayout->addWidget(plotLineBtn);

	//���岼��
	mainlayout = new QHBoxLayout(this);
    mainlayout->addLayout(BtnLayout);
	mainlayout->addWidget(stackWave); 
	
	connect(plotLineBtn, SIGNAL(clicked()), this, SLOT(sendGetWaveData()));   //����ָ��
	//�����ź� �����ź� Я������ �����ź� ��������
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
	//��29·���η�Ϊ9�࣬Page1->PlotNum; ÿһ·

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
	//��һ������
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

	//����ڵ�����QPointF(x,y)  

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

	points1[0] << QPointF(100.0, 3.3); //����β������
	free(p);
	free(pData);

	index = index + datalength + 3;


	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	p = (unsigned char *)malloc(sizeof(char)*datalength);
	//OutputDataToTxt(&buffer[i + 9], datalength,"2.txt");
	memcpy(p, &buffer[index + 3], datalength);
	OutputDataToTxt(p, datalength, "2.txt");

	//���ݽ���

	pData = (float *)malloc(sizeof(float)*datalength);

	//�����j���͵�ƽ��Ӧ����Сֵ
	for (j = 0; j < datalength; j++)
	{
		pData[j] = (255.0 - (int)p[j]) * (3.300 / 255);
	}

	//����ڵ�����QPointF(x,y)  
	points1[1] = points1[0];

	temp = 0;
	//�Ե͵�ƽ�������¸�ֵ��
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

void waveformWidget::PathPageType2(uint8_t * buffer,int & index)  //�����ನ��
{
	//����·
	int datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];
	index = index + datalength + 3;
}

void waveformWidget::PathPageType3(uint8_t * buffer,int & index)
{
	//����ҳ ����·
	int datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	unsigned char *pData = new unsigned char[datalength];
	float *DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	OutputDataToTxt(pData, datalength, "4.txt");
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ����·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	// ����ҳ ����·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ����·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ �ڰ�·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ �ھ�·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮһ·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ��·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ��·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ��·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ��·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ��·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ��·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ��·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��ʮ��·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//����ҳ ��20·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��7ҳ ��21·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��7ҳ ��22·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��8ҳ ��23·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��8ҳ ��24·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��8ҳ ��25·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��9ҳ ��26·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��9ҳ ��27·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��9ҳ ��28·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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

	//��9ҳ ��29·
	datalength = buffer[index + 1] + 16 * 16 * buffer[index + 2];

	pData = new unsigned char[datalength];
	DataFloat = new float[datalength];

	memcpy(pData, &buffer[index + 3], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
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
	//����Ľ�
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
