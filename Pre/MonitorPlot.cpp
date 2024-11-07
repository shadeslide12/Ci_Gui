
#include "MonitorPlot.h"
#include <QLineSeries>
#include <QDebug>

MonitorPlot::MonitorPlot(QWidget *parent):
        monitorChart(new QChart),
        axisX(new QValueAxis(this)),
        axisY(new QValueAxis(this))
{
    yMin=0 ; yMax=10;
    xMin=0 ; xMax=10;
    setupChart();
}

void MonitorPlot::setupChart() {
    this->setChart(monitorChart);
    QLineSeries* defaultSeries = new QLineSeries(this);

    QFont titleFont("Arial",26,QFont::Bold);
    QColor titleColor(Qt::darkGray);
    monitorChart->setTitle("Monitor");
    monitorChart->setTitleFont(titleFont);
    monitorChart->setTitleBrush(titleColor);

    qDebug()<<"ok1";

    QFont axisFont;
    axisFont.setPointSize(12);
    axisX->setLabelsFont(axisFont);
    axisY->setLabelsFont(axisFont);
    QColor yColor(Qt::red);
    axisY->setTitleBrush(yColor);

    monitorChart->addAxis(axisX,Qt::AlignBottom);
    monitorChart->addAxis(axisY,Qt::AlignLeft);

    axisX->setTitleText("Iter");
    axisY->setTitleText("Value");

    defaultSeries->attachAxis(axisX);
    defaultSeries->attachAxis(axisY);

    axisX->setRange(xMin,xMax);
    axisY->setRange(yMin,yMax);
    qDebug()<<"ok2";

    monitorChart->addSeries(defaultSeries);
}

void MonitorPlot::updateChart(QList<int> &selectedColumns, QList<QListWidgetItem *> selectedItems,
                              QVector<QVector<double>> &data, QVector<int> &iteration)  {
    for (int i = 0; i < selectedColumns.size(); ++i) {
        QLineSeries *series = new QLineSeries();
        series->setName(selectedItems[i]->text());


        for (int j = 0; j < data[0].size(); ++j) {
            series->append(iteration[j], data[i][j]);
        }

        monitorChart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }


}

void MonitorPlot::setRangeX_Max(const QString &text_xMax) {
    xMax = text_xMax.toDouble();
    axisX->setRange(xMin,xMax);
}

void MonitorPlot::setRangeX_Min(const QString &text_xMin) {
    xMin = text_xMin.toDouble();
    axisX->setRange(xMin,xMax);
}

void MonitorPlot::setRangeY_Min(const QString &text_yMin) {
    yMin = text_yMin.toDouble();
    axisX->setRange(yMin,yMax);
}

void MonitorPlot::setRangeY_Max(const QString &text_yMax) {
    yMax = text_yMax.toDouble();
    axisY->setRange(yMin,yMax);
}