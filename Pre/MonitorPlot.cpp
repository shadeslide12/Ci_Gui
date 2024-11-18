
#include "MonitorPlot.h"
#include <QLineSeries>
#include <QDebug>

MonitorPlot::MonitorPlot(QWidget *parent):
        monitorchart(new QChart),
        axisX(new QValueAxis(this)),
        axisY(new QValueAxis(this))
{
    yMin=0 ; yMax=10;
    xMin=0 ; xMax=10;
    autoScale = 1;
    setupChart();
}

void MonitorPlot::setupChart() {
    this->setChart(monitorchart);
    QLineSeries* defaultSeries = new QLineSeries(this);

    QFont titleFont("Arial",26,QFont::Bold);
    QColor titleColor(Qt::darkGray);
    monitorchart->setTitle("Monitor");
    monitorchart->setTitleFont(titleFont);
    monitorchart->setTitleBrush(titleColor);

    qDebug()<<"ok1";

    QFont axisFont;
    axisFont.setPointSize(12);
    axisX->setLabelsFont(axisFont);
    axisY->setLabelsFont(axisFont);
    QColor yColor(Qt::red);
    axisY->setTitleBrush(yColor);

    monitorchart->addAxis(axisX, Qt::AlignBottom);
    monitorchart->addAxis(axisY, Qt::AlignLeft);

    axisX->setTitleText("Iter");
    axisY->setTitleText("Value");

    defaultSeries->attachAxis(axisX);
    defaultSeries->attachAxis(axisY);

    axisX->setRange(xMin,xMax);
    axisY->setRange(yMin,yMax);
    qDebug()<<"ok2";

    monitorchart->addSeries(defaultSeries);
}

void MonitorPlot::updateChart(QList<int> &selectedColumns, QList<QListWidgetItem *> selectedItems,
                              QVector<QVector<double>> &data, QVector<int> &iteration)  {


    for (int i = 0; i < selectedColumns.size(); ++i) {
        QLineSeries *series = new QLineSeries();
        series->setName(selectedItems[i]->text());

        const QVector<double> &columnData = data[i];
        for (int j = 0; j < columnData.size(); ++j) {
            series->append(iteration[j], columnData[j]);
        }

        monitorchart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    if(!iteration.isEmpty() && autoScale){
        double cal_yMin = std::numeric_limits<double>::max();
        double cal_yMax = std::numeric_limits<double>::lowest();

        int maxIter = *std::max_element(iteration.begin(), iteration.end());

        for(const auto& columnData: data){
            double temp_yMin = *std::min_element(columnData.begin(), columnData.end());
            double temp_yMax = *std::max_element(columnData.begin(), columnData.end());

            cal_yMin = std::min(cal_yMin,temp_yMin);
            cal_yMax = std::max(cal_yMax,temp_yMax);
        }

        axisY->setRange(cal_yMin,cal_yMax);
        axisX->setRange(0,maxIter);
    }


}

void MonitorPlot::setRangeX_Max(const QString &text_xMax) {
    if(!autoScale) {
        xMax = text_xMax.toDouble();
        axisX->setRange(xMin, xMax);
    }
}

void MonitorPlot::setRangeX_Min(const QString &text_xMin) {
    if(!autoScale) {
        xMin = text_xMin.toDouble();
        axisX->setRange(xMin, xMax);
    }
}

void MonitorPlot::setRangeY_Min(const QString &text_yMin) {
    if(!autoScale) {
        yMin = text_yMin.toDouble();
        axisY->setRange(yMin, yMax);
    }
}

void MonitorPlot::setRangeY_Max(const QString &text_yMax) {
    if(!autoScale) {
        yMax = text_yMax.toDouble();
        axisY->setRange(yMin, yMax);
    }
}

void MonitorPlot::setAutoScaleMode() {
    autoScale = 1;
}

void MonitorPlot::setManualScaleMode() {
    autoScale = 0;
}