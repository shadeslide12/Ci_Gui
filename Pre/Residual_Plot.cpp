#include "Residual_Plot.h"
#include <QDebug>
QT_CHARTS_USE_NAMESPACE

Residual_Plot::Residual_Plot(QWidget *parent) :
        CustomChartView(new QChart,parent),
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
    series_con1->setName("Convergence:N-S");
    series_con2->setName("Convergence:Turbulence");
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
    axisY1->setRange(-10,10);
    axisY2->setRange(-10,-10);

    this->setChartStyle();
}

void Residual_Plot::updateResidualPlot(const int& iteration, const double& convergence1,
                                       const double& convergence2) {


    series_con1->append(iteration,convergence1);
    series_con2->append(iteration,convergence2);

    if(autoScale){
        maxIter = std::max(maxIter, iteration);
        maxCon1 = std::max(maxCon1, convergence1);
        maxCon2 = std::max(maxCon2, convergence2);
        minCon1 = std::min(minCon1, convergence1);
        minCon2 = std::min(minCon2, convergence2);

        axisX->setRange(0,maxIter+2);
        double margin1 = (maxCon1 - minCon1) * 0.05;
        axisY1->setRange(minCon1-margin1,maxCon1+margin1);
        double margin2 = (maxCon2 - minCon2) * 0.05;
        axisY2->setRange(minCon2-margin2,maxCon2+margin2);
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

void Residual_Plot::setRangeY2_Min(const QString &text_y2Min) {
    if(!autoScale) {
        y2Min = text_y2Min.toDouble();
        axisY2->setRange(y2Min, y2Max);
    }
}

void Residual_Plot::setRangeY2_Max(const QString &text_y2Max) {
    if(!autoScale) {
        y2Max = text_y2Max.toDouble();
        axisY2->setRange(y2Min, y2Max);
    }
}

void Residual_Plot::setAutoScaleMode() {
    autoScale = 1;
}

void Residual_Plot::setManualScaleMode() {
    autoScale = 0;
}

void Residual_Plot::setChartStyle() {

    QFont titleFont("Arial", 16, QFont::Bold);
    residualchart->setTitleFont(titleFont);
    residualchart->setTitle("Residual Curves");

    QFont axisTitleFont("Arial", 12, QFont::Bold);
    QFont axisLabelFont("Arial", 12);

    axisX->setTitleFont(axisTitleFont);
    axisX->setLabelsFont(axisLabelFont);
    axisX->setTitleText("Iteration");
    axisX->setLabelFormat("%d");

    axisY1->setTitleFont(axisTitleFont);
    axisY1->setLabelsFont(axisLabelFont);
    axisY1->setTitleText("N-S");
    axisY1->setTitleBrush(Qt::red);

    axisY2->setTitleFont(axisTitleFont);
    axisY2->setLabelsFont(axisLabelFont);
    axisY2->setTitleText("Turbulence");
    axisY2->setTitleBrush(Qt::darkGray);

//    axisX->setGridLineVisible(0);
    axisX->setTickCount(11);
    axisX->setMinorTickCount(4);
    axisY1->setTickCount(8);
    axisY2->setTickCount(8);

    QList<QColor> colors = {
            QColor("#FF6B6B"),QColor("#4ECDC4")
    };
    series_con1->setPen(QPen(colors[0],2 ));
    series_con2->setPen(QPen(colors[1],2 ));
//    QString gridColor = "#404040";
//    axisX->setGridLineColor(QColor(gridColor));
//    axisY1->setGridLineColor(QColor(gridColor));
//    axisY2->setGridLineColor(QColor(gridColor));

    residualchart->update();
}

void Residual_Plot::clearSeries() {
    series_con1->clear();
    series_con2->clear();

    axisX->setRange(0,10);
    axisY1->setRange(-10,10);
    axisY2->setRange(-10,-10);
    maxCon1 = std::numeric_limits<double>::lowest();
    maxCon2 = std::numeric_limits<double>::lowest();
    minCon1 = std::numeric_limits<double>::max();
    minCon2 = std::numeric_limits<double>::max();
    maxIter = 10 ;
    residualchart->update();
}

void Residual_Plot::updateDataHistory(const QString& name) {
    if(series_con1->points().isEmpty())
        return;
    ResidualData data ;
    data.con1_data =series_con1->points().toVector();
    data.con2_data =series_con2->points().toVector();
    residualHistory[name] = data;
}

void Residual_Plot::clearHistory() {
    residualHistory.clear();
}

QStringList Residual_Plot::getHistoryName() const {
    return residualHistory.keys();
}

void Residual_Plot::loadHisotyData(const QString &name) {
    if(!residualHistory.contains(name) )
        return;

    const auto& data = residualHistory[name];
    series_con1->clear();
    series_con2->clear();
    double min_con1_y1 = std::numeric_limits<double>::max();
    double min_con2_y2 = std::numeric_limits<double>::max();
    double max_con1_y1 = std::numeric_limits<double>::lowest();
    double max_con2_y2 = std::numeric_limits<double>::lowest();
    double min_series_x = 0 ;
    double max_series_x = 1 ;
    for(const auto& point : data.con1_data) {
        series_con1->append(point);
        min_con1_y1 = std::min(min_con1_y1,point.y());
        max_con1_y1 = std::max(max_con1_y1,point.y());
        max_series_x = std::max(max_series_x,point.x());
    }
    for(auto const& point : data.con2_data) {
        series_con2->append(point);
        min_con2_y2 = std::min(min_con2_y2,point.y());
        max_con2_y2 = std::max(max_con2_y2,point.y());
    }
    axisX->setRange(min_series_x,max_series_x);
    axisY1->setRange(min_con1_y1,max_con1_y1);
    axisY2->setRange(min_con2_y2,max_con2_y2);
}


