#include "plotlines.h"  
PlotLines::PlotLines(QWidget *parent) :
	QwtPlot(parent)
{
	setTitle(QStringLiteral("��������"));
	//---------���û���---------//  
	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	canvas->setPalette(Qt::white);
	canvas->setBorderRadius(10);
	setCanvas(canvas);
	plotLayout()->setAlignCanvasToScales(true);

	//-----------����x��y����ͷ�Χ--------------//  
	setAxisTitle(QwtPlot::yLeft, "Voltage");
	setAxisTitle(QwtPlot::xBottom, "X Axis");
	//setAxisScale(QwtPlot::yRight, 0.0, 4.0, 0.5);
	setAxisScale(QwtPlot::yLeft, 0.0, 5, 0.5); //0��4 0.5Ϊ�̶�
	setAxisScale(QwtPlot::xBottom, 0.0, 100, 5);  //0��105 5Ϊ�̶�

												  //----------------����դ����-------------------//  
	QwtPlotGrid *grid = new QwtPlotGrid;
	grid->enableX(true);					//����������  
	grid->enableY(true);
	grid->setMajorPen(Qt::black, 0, Qt::DotLine);
	//grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
	grid->attach(this);

	//�����Զ����ű����Σ�Ϊĳ��������ָ��һ���޸ĵı�����
	//setAxisLabelRotation(QwtPlot::yLeft, -30.0);
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

	//��������
	QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(this->canvas());
	//������ѡ������Ŵ��Ҽ���ԭ
	QwtPlotPanner *panner = new QwtPlotPanner(this->canvas());

	this->resize(500, 300);

	this->replot();

	setAutoReplot(true);//�����Զ��ػ����൱�ڸ��� 
}

PlotLines::PlotLines(QWidget *parent, QString& Title, float max_x, float max_y) : QwtPlot(parent)
{
	setTitle(Title);
	//---------���û���---------//  
	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	canvas->setPalette(Qt::white);
	canvas->setBorderRadius(10);
	setCanvas(canvas);
	plotLayout()->setAlignCanvasToScales(true);

	//-----------����x��y����ͷ�Χ--------------//  
	setAxisTitle(QwtPlot::yLeft, "Voltage");
	setAxisTitle(QwtPlot::xBottom, "X Axis");
	//setAxisScale(QwtPlot::yRight, 0.0, 4.0, 0.5);
	setAxisScale(QwtPlot::yLeft, 0.0, max_y, 0.5); //0��4 0.5Ϊ�̶�
	setAxisScale(QwtPlot::xBottom, 0.0, max_x, 5);  //0��105 5Ϊ�̶�

													//----------------����դ����-------------------//  
	QwtPlotGrid *grid = new QwtPlotGrid;
	grid->enableX(true);					//����������  
	grid->enableY(true);
	grid->setMajorPen(Qt::black, 0, Qt::DotLine);
	//grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
	grid->attach(this);

	//�����Զ����ű����Σ�Ϊĳ��������ָ��һ���޸ĵı�����
	//setAxisLabelRotation(QwtPlot::yLeft, -30.0);
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

	//��������
	QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(this->canvas());
	//����϶���������
	QwtPlotPanner *panner = new QwtPlotPanner(this->canvas());
	//������ѡ������Ŵ��Ҽ���ԭ
	QwtPlotZoomer* zoomer = new QwtPlotZoomer(this->canvas());
	zoomer->setRubberBandPen(QColor(Qt::black));
	zoomer->setTrackerPen(QColor(Qt::black));
	zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
	zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton);

	curve = new QwtPlotCurve("curve");		//��ʼ��curve

	this->resize(600, 400);

	this->replot();

	setAutoReplot(true);//�����Զ��ػ����൱�ڸ���  

}

PlotLines::~PlotLines()
{

}

void PlotLines::drawline1(QVector<QPointF> &points1)
{
	//-----------------��ʼ��ͼ----------------------//  
	// curve->setTitle( "�ŵ�"+QString( "%1 " ).arg( i+1));  ��ʽ���ַ������
	curve->setPen(Qt::blue, 2);//����������ɫ ��ϸ  
	curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);//�����⻬��  
	curve->setSamples(points1);
	curve->attach(this);

	//setAutoReplot(true);
}