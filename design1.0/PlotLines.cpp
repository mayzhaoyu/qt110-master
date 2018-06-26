#include "plotlines.h"  
PlotLines::PlotLines(QWidget *parent) :
	QwtPlot(parent)
{
	setTitle(QStringLiteral("绘制曲线"));
	//---------设置画布---------//  
	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	canvas->setPalette(Qt::white);
	canvas->setBorderRadius(10);
	setCanvas(canvas);
	plotLayout()->setAlignCanvasToScales(true);

	//-----------设置x，y坐标和范围--------------//  
	setAxisTitle(QwtPlot::yLeft, "Voltage");
	setAxisTitle(QwtPlot::xBottom, "X Axis");
	//setAxisScale(QwtPlot::yRight, 0.0, 4.0, 0.5);
	setAxisScale(QwtPlot::yLeft, 0.0, 5, 0.5); //0到4 0.5为刻度
	setAxisScale(QwtPlot::xBottom, 0.0, 100, 5);  //0到105 5为刻度

												  //----------------设置栅格线-------------------//  
	QwtPlotGrid *grid = new QwtPlotGrid;
	grid->enableX(true);					//设置网格线  
	grid->enableY(true);
	grid->setMajorPen(Qt::black, 0, Qt::DotLine);
	//grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
	grid->attach(this);

	//禁用自动缩放比例次，为某个坐标轴指定一个修改的比例尺
	//setAxisLabelRotation(QwtPlot::yLeft, -30.0);
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

	//滚轮缩放
	QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(this->canvas());
	//鼠标左键选择区域放大、右键复原
	QwtPlotPanner *panner = new QwtPlotPanner(this->canvas());

	this->resize(500, 300);

	this->replot();

	setAutoReplot(true);//设置自动重画，相当于更新 
}

PlotLines::PlotLines(QWidget *parent, QString& Title, float max_x, float max_y) : QwtPlot(parent)
{
	setTitle(Title);
	//---------设置画布---------//  
	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	canvas->setPalette(Qt::white);
	canvas->setBorderRadius(10);
	setCanvas(canvas);
	plotLayout()->setAlignCanvasToScales(true);

	//-----------设置x，y坐标和范围--------------//  
	setAxisTitle(QwtPlot::yLeft, "Voltage");
	setAxisTitle(QwtPlot::xBottom, "X Axis");
	//setAxisScale(QwtPlot::yRight, 0.0, 4.0, 0.5);
	setAxisScale(QwtPlot::yLeft, 0.0, max_y, 0.5); //0到4 0.5为刻度
	setAxisScale(QwtPlot::xBottom, 0.0, max_x, 5);  //0到105 5为刻度

													//----------------设置栅格线-------------------//  
	QwtPlotGrid *grid = new QwtPlotGrid;
	grid->enableX(true);					//设置网格线  
	grid->enableY(true);
	grid->setMajorPen(Qt::black, 0, Qt::DotLine);
	//grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
	grid->attach(this);

	//禁用自动缩放比例次，为某个坐标轴指定一个修改的比例尺
	//setAxisLabelRotation(QwtPlot::yLeft, -30.0);
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

	//滚轮缩放
	QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(this->canvas());
	//鼠标拖动画布功能
	QwtPlotPanner *panner = new QwtPlotPanner(this->canvas());
	//鼠标左键选择区域放大、右键复原
	QwtPlotZoomer* zoomer = new QwtPlotZoomer(this->canvas());
	zoomer->setRubberBandPen(QColor(Qt::black));
	zoomer->setTrackerPen(QColor(Qt::black));
	zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
	zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton);

	curve = new QwtPlotCurve("curve");		//初始化curve

	this->resize(600, 400);

	this->replot();

	setAutoReplot(true);//设置自动重画，相当于更新  

}

PlotLines::~PlotLines()
{

}

void PlotLines::drawline1(QVector<QPointF> &points1)
{
	//-----------------开始画图----------------------//  
	// curve->setTitle( "信道"+QString( "%1 " ).arg( i+1));  格式化字符串输出
	curve->setPen(Qt::blue, 2);//设置曲线颜色 粗细  
	curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);//线条光滑化  
	curve->setSamples(points1);
	curve->attach(this);

	//setAutoReplot(true);
}