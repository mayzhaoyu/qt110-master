#include "WavePage.h"
extern unsigned char buffer[512];
extern unsigned char buffer4[512];

//��һҳ����ȫ�ߵڶ�·�źţ������źţ���һ�ࣩ����ȫ�ߵ�һ·�źţ����Ⲩ���źţ������ࣩ
//�ڶ�ҳ�������氲ȫ��AD�źţ������źţ������ࣩ
//����ҳ����С���󣨲����źţ� ��С���ң������źţ�������Ϊ���ࣩ
//����ҳ���ߴ��󣶣����������źţ�����·��
//����ҳ���ߴ��󣱣����������źţ�����·��
//����ҳ�������ź�L3 �����ź�L2 �����ź�L1
//����ҳ�������ź�JSL �����ź�JSR
//�ڰ�ҳ�������ź�R1 �����ź�R2 �����ź�R3
//�ھ�ҳ��ӫ�ⷽ������ ӫ�ⷽ������ ӫ�ⷽ������ ӫ�ⷽ������

QString title[9][6] =
{
	QStringLiteral("��ȫ�ߵڶ�·�źţ������źţ�"),QStringLiteral("��ȫ�ߵ�һ·�źţ����Ⲩ���źţ�"),"","","","",
	QStringLiteral("�����氲ȫ��AD�źţ������źţ�"),"","","","","",
	QStringLiteral("��С���󣨲����źţ�"),QStringLiteral("��С���ң������źţ�"),"","","","",
	QStringLiteral("�ߴ���6"),QStringLiteral("�ߴ���5"),QStringLiteral("�ߴ���4"),QStringLiteral("�ߴ���3"),QStringLiteral("�ߴ���2"),QStringLiteral("�ߴ���1"),
	QStringLiteral("�ߴ���1"),QStringLiteral("�ߴ���2"),QStringLiteral("�ߴ���3"),QStringLiteral("�ߴ���4"),QStringLiteral("�ߴ���5"),QStringLiteral("�ߴ���6"),
	QStringLiteral("�����ź�L3"),QStringLiteral("�����ź�L2"),QStringLiteral("�����ź�L1"),"","","",
	QStringLiteral("�����ź�JSL"),QStringLiteral("�����ź�JSR"),"","","","",
	QStringLiteral("�����ź�R1"),QStringLiteral("�����ź�R2"),QStringLiteral("�����ź�R3"),"","","",
	QStringLiteral("ӫ�ⷽ������"),QStringLiteral("ӫ�ⷽ������"),QStringLiteral("ӫ�ⷽ������"),QStringLiteral("ӫ�ⷽ������"),"","",
};

WavePage::WavePage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}
WavePage::WavePage(QWidget *parent, int indexPage/*ҳ��*/, int Plotnum/*������*/) : QWidget(parent)
{
	IndexPage = indexPage;
	PlotNum = Plotnum;
	//points = new QPolygonF[PlotNum];
	//points[1];
	PlotTable = new PlotLines*[PlotNum];
	for (int i = 0; i < PlotNum; i++)
	{
		PlotTable[i] = new PlotLines(this, title[IndexPage - 1][i]/*"��һ·"*/, 100.0, 4.0);
	}

	if (PlotNum < 4)
	{
		GroupLayout1 = new QVBoxLayout(this);
		for (int i = 0; i < PlotNum; i++)
		{
			GroupLayout1->addWidget(PlotTable[i]);
		}
		return;
	}
	else
	{
		GridLayout1 = new QGridLayout(this);
		if ((PlotNum % 2) == 0)  //ż������
		{
			for (int i = 0; i < PlotNum; i++)
			{
				GridLayout1->addWidget(PlotTable[i], i / 2, i % 2);
			}
		}
		else		//���� �� ����  ��ʱû�в���������3�Ĳ��δ��� �˶κ�������ע��
		{
			for (int i = 0; i < PlotNum; i++)
			{
				GridLayout1->addWidget(PlotTable[i], i / 2, i % 2);
			}

		}
	}
}

/*WavePage::WavePage(QWidget *parent, int indexPage) : QWidget(parent)
{
	IndexPage = indexPage;

	if (IndexPage < 0 || IndexPage > 9)
	{
		return;
	}

	switch (IndexPage)
	{
	case 1:
		//��һҳ
		PlotArry[0] = new PlotLines(this, QStringLiteral("��һ·"), 100.0, 6.0);
		PlotArry[1] = new PlotLines(this, QStringLiteral("�ڶ�·"), 100.0, 6.0);

		GroupLayout1 = new QVBoxLayout(this);
		GroupLayout1->addWidget(PlotArry[0]);
		GroupLayout1->addWidget(PlotArry[1]);

		break;
	case 2:
		PlotArry[2] = new PlotLines(this, QStringLiteral("����·"), 100.0, 6.0);
		break;
	default:
		return;

	}

}*/

WavePage::~WavePage()
{

}

void WavePage::DrawWave(QPolygonF *points, int plotnum)
{
	if (plotnum != this->PlotNum)
		return;
	for (int i = 0; i < PlotNum; i++)
	{
		//ProcessData(&Points[i]);
		if (PlotTable[i] != NULL)
		{
			PlotTable[i]->drawline1(points[i]);
		}
		else
		{
			return;
		}
	}

}

//void WavePage::ProcessData(unsigned char*buff, QPolygonF *points)  //16��������===��29·�źŵĲ���·��
//{
//	IndexPage = ;
//}

/*void WavePage::Draw1(/*unsigned char*buffer)
{
	if (IndexPage != 1)
	{
		return;
	}

	int i;
	int datalength;
	unsigned char *p;

	QPolygonF points1;
	//QPolygonF *points1 = new QPolygonF[PlotNum];

	//��������

	for (i = 0; i < 512; i++)
	{
		if ((buffer[i] == 0xAA) && (buffer[i + 1] == 0x55) && (buffer[i + 6] == 0xD0) && (buffer[i + 7] == 0x01))
		{
			datalength = (int)buffer[i + 8];

			p = (unsigned char *)malloc(sizeof(char)*datalength);
			//OutputDataToTxt(&buffer[i + 9], datalength,"2.txt");
			memcpy(p, &buffer[i + 9], datalength);
			OutputDataToTxt(p, datalength, "1.txt");

			//���ݽ���
			int j; float Sum = 0;
			int L = datalength / 2;
			float *pData = (float *)malloc(sizeof(float)*L);

			for (j = 0; j < L; j++)
			{
				pData[j] = p[2 * j] + 16 * 16 * p[2 * j + 1];
				float a = pData[j];
				Sum += pData[j];
			}

			//��һ������
			for (j = 0; j < L; j++)
			{
				pData[j] = (pData[j] / Sum) * 100;
				//float a = pData[j];
			}

			//����ڵ�����QPointF(x,y)  

			double temp = 0;
			for (j = 0; j < L - 1; j++)
			{
				points1 << QPointF(temp, 3.3);
				temp += pData[j];
				points1 << QPointF(temp, 3.3);
				points1 << QPointF(temp, 0);
				temp += pData[j + 1];
				j++;
				points1 << QPointF(temp, 0);

			}

			points1 << QPointF(100.0, 3.3); //����β������

											//p1->SetTitleAndAxis(buffer[i + 7]);		//���ò���ͼ�ı���
			PlotArry[0]->drawline1(points1);					//��ʼ����ͼ��
			i += datalength; //ƫ��datalength���ֽ�
			free(p);
			free(pData);
		}
		//����ڶ�·����

		if ((buffer[i] == 0xAA) && (buffer[i + 1] == 0x55) && (buffer[i + 6] == 0xD0) && (buffer[i + 7] == 0x02))
		{
			datalength = (int)buffer[i + 8];

			p = (unsigned char *)malloc(sizeof(char)*datalength);
			//OutputDataToTxt(&buffer[i + 9], datalength,"2.txt");
			memcpy(p, &buffer[i + 9], datalength);
			OutputDataToTxt(p, datalength, "3.txt");

			//���ݽ���
			int j; float Sum = 0;

			float *pData = (float *)malloc(sizeof(float)*datalength);


			//�����j���͵�ƽ��Ӧ����Сֵ
			for (j = 0; j < datalength; j++)
			{
				pData[j] = (255.0 - (int)p[j]) * (3.300 / 255);
			}

			//����ڵ�����QPointF(x,y)  
			QPolygonF points2 = points1;

			double temp = 0; int l = 0;
			//�Ե͵�ƽ�������¸�ֵ��
			for (j = 0; j < datalength; j++)
			{
				//float a = points2[4 * j + 2].x;
				temp = (points2[4 * j + 2].x() + points2[4 * j + 3].x()) / 2;
				points2[4 * j + 2].setY(pData[j]);
				points2[4 * j + 3].setY(pData[j]);
				//(points2[4 * j + 2].x + points2[4 * j + 3].x) / 2
				points2[4 * j + 2].setX(temp);
				//points2[]
				points2[4 * j + 3].setX(temp);
			}
			//points1 << QPointF(100.0, 3.3);
			//p2->SetTitleAndAxis(buffer[i + 7]);
			//QwtSeriesData<QPointF> *series = 0;
			//PlotArry[1]->curve->NoCurve;
			//PlotArry[1]->curve->~QwtPlotCurve();
			PlotArry[1]->drawline1(points2);

			free(p);
			free(pData);
		}
	};

	//��ͼ
	//p1->drawline1();
	//p2->drawline1();
	//p3->drawline1();
}

void WavePage::Draw2(/*unsigned char* )
{
	int i;
	QPolygonF points6;
	int datalength = buffer4[1];

	unsigned char *pData = new unsigned char[datalength];
	float *DataFloat = new float[datalength];

	memcpy(pData, &buffer4[2], datalength);
	//p6->SetTitleAndAxis(buffer4[0]);

	//������ӳ�䵽 0~3.3v����
	for (i = 0; i < datalength; i++)
	{
		DataFloat[i] = (float)pData[i] * (3.3 / 255);
	}

	for (i = 0; i < datalength; i++)
	{
		points6 << QPointF(i, DataFloat[i]);
	}

	PlotArry[2]->drawline1(points6);
	delete pData;
	delete DataFloat;

}
*/