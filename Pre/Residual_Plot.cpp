#include "Residual_Plot.h"
#include <QDebug>
QT_CHARTS_USE_NAMESPACE

Residual_Plot::Residual_Plot(QWidget *parent) :
        residualchart(new QChart),
        series_con1(new QLineSeries(this)),
        series_con2(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY1(new QValueAxis(this)),
        axisY2(new QValueAxis(this))
{
    autoScale = 1;
    maxIter = std::numeric_limits<int>::lowest();
    maxCon1 = std::numeric_limits<double>::lowest();
    maxCon2 = std::numeric_limits<double>::lowest();
    minCon1 = std::numeric_limits<double>::max();
    minCon2 = std::numeric_limits<double>::max();
    setupResidualPlot();
}


void Residual_Plot::setupResidualPlot() {
    this->setChart(residualchart);

    residualchart->addAxis(axisX,Qt::AlignBottom);
    residualchart->addAxis(axisY1,Qt::AlignLeft);
    residualchart->addAxis(axisY2,Qt::AlignRight);
    residualchart->addSeries(series_con1);
    residualchart->addSeries(series_con2);

    series_con1->attachAxis(axisX);
    series_con1->attachAxis(axisY1);
    series_con2->attachAxis(axisX);
    series_con2->attachAxis(axisY2);


    axisX->setRange(0,10);
    axisY1->setRange(-9,-6);
    axisY2->setRange(-12,-10.8);

    axisX->setTickCount(8);
    axisY1->setTickCount(6);
    axisY2->setTickCount(6);
    this->setChartStyle();
}

void Residual_Plot::updateResidualPlot(const int& iteration, const double& convergence1,
                                       const double& convergence2) {

    qDebug() << "Hello";
    qDebug() << convergence1;
    series_con1->append(iteration,convergence1);
    series_con2->append(iteration,convergence2);

    if(autoScale){
        maxIter = std::max(maxIter, iteration);
        maxCon1 = std::max(maxCon1, convergence1);
        maxCon2 = std::max(maxCon2, convergence2);
        minCon1 = std::min(maxCon2, convergence1);
        minCon2 = std::min(minCon2, convergence2);

        axisX->setRange(0,maxIter+5);
        axisY1->setRange(minCon1,maxCon1);
        axisY2->setRange(minCon2,maxCon2);
    }

    residualchart->update();
}

void Residual_Plot::setRangeX_Max(const QString &text_xMax) {
    xMax = text_xMax.toDouble();
    if(!autoScale && xMax > xMin ) {
        axisX->setRange(xMin, xMax);
    }
}

void Residual_Plot::setRangeX_Min(const QString &text_xMin) {
    xMin = text_xMin.toDouble();
    if(!autoScale && xMin >= 0) {
        axisX->setRange(xMin, xMax);
    }
}

void Residual_Plot::setRangeY1_Min(const QString &text_y1Min) {
    if(!autoScale) {
        y1Min = text_y1Min.toDouble();
        axisY1->setRange(y1Min, y1Max);
    }
}

void Residual_Plot::setRangeY1_Max(const QString &text_y1Max) {
    if(!autoScale) {
        y1Max = text_y1Max.toDouble();
        axisY1->setRange(y1Min, y1Max);
    }
}

void Residual_Plot::setAutoScaleMode() {
    autoScale = 1;
}

void Residual_Plot::setManualScaleMode() {
    autoScale = 0;
}

void Residual_Plot::setChartStyle() {

    QFont titleFont("Arial", 22, QFont::Bold);
    residualchart->setTitleFont(titleFont);
    residualchart->setTitle("Residual Curves");
    residualchart->setTitleBrush(Qt::darkCyan);

    QFont axisTitleFont("Arial", 16, QFont::Bold);  // 为坐标轴标题单独设置字体
    QFont axisLabelFont("Arial", 12);               // 为坐标轴标签单独设置字体

    axisX->setTitleFont(axisTitleFont);
    axisX->setLabelsFont(axisLabelFont);
    axisX->setTitleText("Iteration");

    axisY1->setTitleFont(axisTitleFont);
    axisY1->setLabelsFont(axisLabelFont);
    axisY1->setTitleText("N-S");
    axisY1->setTitleBrush(Qt::red);

    axisY2->setTitleFont(axisTitleFont);
    axisY2->setLabelsFont(axisLabelFont);
    axisY2->setTitleText("Turbulence");
    axisY2->setTitleBrush(Qt::darkGray);

    axisX->setGridLineVisible(0);

    residualchart->update();
}