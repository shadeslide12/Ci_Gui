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
    allSeries = {series_pratio, series_tratio, series_efficiency};
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

    axisX->setTitleText("Mass Flow Rate");
    axisY->setTitleText("Value");

    axisX->setRange(0,10);
    axisX->setTickCount(8);
    axisY->setTickCount(6);
}

void Perform_Plot::updateVisibility(int i) {
    for(auto const& series : allSeries)
        series->hide();

    if(i >= allSeries.size() )
        return;

    switch (i) {
        case 0:
            allSeries[0]->show();
            axisY->setTitleText("Pressure Ratio");
            break;
        case 1:
            allSeries[1]->show();
            axisY->setTitleText("Temperature Ratio");
            break;
        case 2:
            allSeries[2]->show();
            axisY->setTitleText("Efficiency");
            break;
        default:
            break;
    }

    currentVisibleLine = i ;
    this->autoRange();
}

void Perform_Plot::updateChart(MonitorVariableTable &monitorVariableTable) {
    double new_x = monitorVariableTable.outlet.mDot.last();

    bool need_sort = false;
    if (!series_pratio->points().isEmpty()) {
        qreal last_x = series_pratio->at(series_pratio->count() - 1).x();
        if (new_x < last_x) {
            need_sort = true;
        }
    }

    series_pratio->append(new_x, monitorVariableTable.perform.pRatio.last());
    series_tratio->append(new_x, monitorVariableTable.perform.tRatio.last());
    series_efficiency->append(new_x, monitorVariableTable.perform.efficiency.last());

    if (need_sort) {
        QVector<QPointF> points_pratio = series_pratio->pointsVector();
        QVector<QPointF> points_tratio = series_tratio->pointsVector();
        QVector<QPointF> points_efficiency = series_efficiency->pointsVector();

        std::sort(points_pratio.begin(), points_pratio.end(),
                  [](const QPointF &p1, const QPointF &p2) { return p1.x() < p2.x(); });
        std::sort(points_tratio.begin(), points_tratio.end(),
                  [](const QPointF &p1, const QPointF &p2) { return p1.x() < p2.x(); });
        std::sort(points_efficiency.begin(), points_efficiency.end(),
                  [](const QPointF &p1, const QPointF &p2) { return p1.x() < p2.x(); });

        series_pratio->replace(points_pratio);
        series_tratio->replace(points_tratio);
        series_efficiency->replace(points_efficiency);
    }

    this->autoRange();
}
void Perform_Plot::autoRange() {
    min_RangeY = std::numeric_limits<double>::max();
    max_RangeY = std::numeric_limits<double>::lowest();

    min_RangeX = std::numeric_limits<double>::max();
    max_RangeX = std::numeric_limits<double>::lowest();

    const QList<QPointF>& points =allSeries[currentVisibleLine]->points();

    for(auto const& point : points){
        double y = point.y();
        if(y < min_RangeY)
            min_RangeY = y;
        if(y > max_RangeY)
            max_RangeY = y;
        double x = point.x();
        if(x < min_RangeX)
            min_RangeX = x;
        if(x > max_RangeX)
            max_RangeX = x;
    }

    double margin = max_RangeY - min_RangeY;
    min_RangeY -= margin * 0.15;
    max_RangeY += margin * 0.15;

    axisY->setRange(min_RangeY,max_RangeY);

    double margin2 = max_RangeX - min_RangeX;
    min_RangeX -= margin2 * 0.15;
    max_RangeX += margin2 * 0.15;

    axisX->setRange(min_RangeX,max_RangeX);

}
