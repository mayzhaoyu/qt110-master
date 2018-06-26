#include "WavePage.h"
extern unsigned char buffer[512];
extern unsigned char buffer4[512];

//第一页：安全线第二路信号（脉冲信号）（一类）；安全线第一路信号（特殊波型信号）（二类）
//第二页：１５版安全线AD信号（波形信号）（三类）
//第三页：中小磁左（波形信号） 中小磁右（波形信号）（以下为四类）
//第四页：边磁左６－１（波形信号／共六路）
//第五页：边磁左１－６（波形信号／共六路）
//第六页：红外信号L3 红外信号L2 红外信号L1
//第七页：红外信号JSL 红外信号JSR
//第八页：红外信号R1 红外信号R2 红外信号R3
//第九页：荧光方窗左上 荧光方窗右下 荧光方窗右上 荧光方窗右下

QString title[9][6] =
{
	QStringLiteral("安全线第二路信号（脉冲信号）"),QStringLiteral("安全线第一路信号（特殊波型信号）"),"","","","",
	QStringLiteral("１５版安全线AD信号（波形信号）"),"","","","","",
	QStringLiteral("中小磁左（波形信号）"),QStringLiteral("中小磁右（波形信号）"),"","","","",
	QStringLiteral("边磁左6"),QStringLiteral("边磁左5"),QStringLiteral("边磁左4"),QStringLiteral("边磁左3"),QStringLiteral("边磁左2"),QStringLiteral("边磁左1"),
	QStringLiteral("边磁左1"),QStringLiteral("边磁左2"),QStringLiteral("边磁左3"),QStringLiteral("边磁左4"),QStringLiteral("边磁左5"),QStringLiteral("边磁左6"),
	QStringLiteral("红外信号L3"),QStringLiteral("红外信号L2"),QStringLiteral("红外信号L1"),"","","",
	QStringLiteral("红外信号JSL"),QStringLiteral("红外信号JSR"),"","","","",
	QStringLiteral("红外信号R1"),QStringLiteral("红外信号R2"),QStringLiteral("红外信号R3"),"","","",
	QStringLiteral("荧光方窗左上"),QStringLiteral("荧光方窗右下"),QStringLiteral("荧光方窗右上"),QStringLiteral("荧光方窗左下"),"","",
};

WavePage::WavePage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}
WavePage::WavePage(QWidget *parent, int indexPage/*页码*/, int Plotnum/*波形数*/) : QWidget(parent)
{
	IndexPage = indexPage;
	PlotNum = Plotnum;
	//points = new QPolygonF[PlotNum];
	//points[1];
	PlotTable = new PlotLines*[PlotNum];
	for (int i = 0; i < PlotNum; i++)
	{
		PlotTable[i] = new PlotLines(this, title[IndexPage - 1][i]/*"第一路"*/, 100.0, 4.0);
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
		if ((PlotNum % 2) == 0)  //偶数布局
		{
			for (int i = 0; i < PlotNum; i++)
			{
				GridLayout1->addWidget(PlotTable[i], i / 2, i % 2);
			}
		}
		else		//奇数 的 布局  暂时没有波形数大于3的波形窗口 此段函数可以注释
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
		//第一页
		PlotArry[0] = new PlotLines(this, QStringLiteral("第一路"), 100.0, 6.0);
		PlotArry[1] = new PlotLines(this, QStringLiteral("第二路"), 100.0, 6.0);

		GroupLayout1 = new QVBoxLayout(this);
		GroupLayout1->addWidget(PlotArry[0]);
		GroupLayout1->addWidget(PlotArry[1]);

		break;
	case 2:
		PlotArry[2] = new PlotLines(this, QStringLiteral("第三路"), 100.0, 6.0);
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

//void WavePage::ProcessData(unsigned char*buff, QPolygonF *points)  //16进制数据===》29路信号的波形路径
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

	//解析数据

	for (i = 0; i < 512; i++)
	{
		if ((buffer[i] == 0xAA) && (buffer[i + 1] == 0x55) && (buffer[i + 6] == 0xD0) && (buffer[i + 7] == 0x01))
		{
			datalength = (int)buffer[i + 8];

			p = (unsigned char *)malloc(sizeof(char)*datalength);
			//OutputDataToTxt(&buffer[i + 9], datalength,"2.txt");
			memcpy(p, &buffer[i + 9], datalength);
			OutputDataToTxt(p, datalength, "1.txt");

			//数据解析
			int j; float Sum = 0;
			int L = datalength / 2;
			float *pData = (float *)malloc(sizeof(float)*L);

			for (j = 0; j < L; j++)
			{
				pData[j] = p[2 * j] + 16 * 16 * p[2 * j + 1];
				float a = pData[j];
				Sum += pData[j];
			}

			//归一化处理
			for (j = 0; j < L; j++)
			{
				pData[j] = (pData[j] / Sum) * 100;
				//float a = pData[j];
			}

			//输入节点数据QPointF(x,y)  

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

			points1 << QPointF(100.0, 3.3); //波形尾部处理

											//p1->SetTitleAndAxis(buffer[i + 7]);		//设置波形图的标题
			PlotArry[0]->drawline1(points1);					//开始绘制图像
			i += datalength; //偏移datalength个字节
			free(p);
			free(pData);
		}
		//处理第二路波形

		if ((buffer[i] == 0xAA) && (buffer[i + 1] == 0x55) && (buffer[i + 6] == 0xD0) && (buffer[i + 7] == 0x02))
		{
			datalength = (int)buffer[i + 8];

			p = (unsigned char *)malloc(sizeof(char)*datalength);
			//OutputDataToTxt(&buffer[i + 9], datalength,"2.txt");
			memcpy(p, &buffer[i + 9], datalength);
			OutputDataToTxt(p, datalength, "3.txt");

			//数据解析
			int j; float Sum = 0;

			float *pData = (float *)malloc(sizeof(float)*datalength);


			//计算第j个低电平对应的最小值
			for (j = 0; j < datalength; j++)
			{
				pData[j] = (255.0 - (int)p[j]) * (3.300 / 255);
			}

			//输入节点数据QPointF(x,y)  
			QPolygonF points2 = points1;

			double temp = 0; int l = 0;
			//对低电平波形重新赋值点
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

	//画图
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

	//将数据映射到 0~3.3v区间
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