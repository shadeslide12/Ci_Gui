#include "Perform_Plot.h"



QT_CHARTS_USE_NAMESPACE

Perform_Plot::Perform_Plot(QWidget *parent) :
        QChart(),series_pratio(new QLineSeries(this)),
        series_tratio(new QLineSeries(this)),
        series_efficiency(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY(new QValueAxis(this))
{
    setupPerformPlot();
}


void Perform_Plot::setupPerformPlot()  {
    QFont titleFont("Arial",22,QFont::Bold);
    QColor titleColor(Qt::darkCyan);
    setTitle("Performance Curves");
    setTitleFont(titleFont);
    setTitleBrush(titleColor);

    QFont axisFont;
    axisFont.setPointSize(16);
    axisX->setLabelsFont(axisFont);
    axisY->setLabelsFont(axisFont);
    QColor yColor(Qt::red);
    axisY->setTitleBrush(yColor);

    addAxis(axisX,Qt::AlignBottom);
    addAxis(axisY,Qt::AlignLeft);
    addSeries(series_pratio);
    addSeries(series_tratio);
    addSeries(series_efficiency);

    series_pratio->attachAxis(axisX);
    series_pratio->attachAxis(axisY);
    series_tratio->attachAxis(axisX);
    series_tratio->attachAxis(axisY);
    series_efficiency->attachAxis(axisY);
    series_efficiency->attachAxis(axisY);

    axisX->setTitleText("Run Number");
    axisY->setTitleText("Value");

    axisX->setRange(0,10);
    axisX->setTickCount(8);
    axisY->setTickCount(6);
}

