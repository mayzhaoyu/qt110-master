#pragma once

#define QWT_DLL

#include "qwt_plot.h"
#include <qwt_plot_layout.h>  
#include <qwt_plot_canvas.h>  
#include <qwt_plot_renderer.h>  
#include <qwt_plot_grid.h>  
#include <qwt_plot_histogram.h>  
#include <qwt_plot_curve.h>  
#include <qwt_plot_zoomer.h>  
#include <qwt_plot_panner.h>  
#include <qwt_plot_magnifier.h>  

#include <qwt_legend.h>  
#include <qwt_legend_label.h>  
#include <qwt_column_symbol.h>  
#include <qwt_series_data.h>  
#include <qpen.h>  
#include <qwt_symbol.h>  
#include <qwt_picker_machine.h>  
#include <QFileDialog>
#include <QString>
//Êý¾Ý²âÊÔ

class PlotLines : public QwtPlot
{
	Q_OBJECT      //

	int maxX;
	int maxY;
	QString name;

public:
	QwtPlotCurve * curve;
	PlotLines(QWidget *parent = 0);
	PlotLines(QWidget *, QString&, float max_x = 0, float max_y = 0);
	~PlotLines();
public slots:

	void drawline1(QVector<QPointF> &points1);
};