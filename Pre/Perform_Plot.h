#ifndef PREPROCESSOR_PERFORM_PLOT_H
#define PREPROCESSOR_PERFORM_PLOT_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include "DataStructure.h"

QT_CHARTS_USE_NAMESPACE

class Perform_Plot: public QChart{
Q_OBJECT

public:
    explicit Perform_Plot(QWidget* parent= nullptr);
    void updateVisibility(int i);
    void updateChart( MonitorVariableTable& monitorVariableTable);

private:
    QList<QLineSeries* > allSeries;
    QLineSeries* series_pratio;
    QLineSeries* series_tratio;
    QLineSeries* series_efficiency;
    QValueAxis* axisX;
    QValueAxis* axisY;

    QVector<double> pressureList;
    int currentVisibleLine = 0;
    double min_RangeY;
    double max_RangeY;
    double max_RangeX;
    double min_RangeX;

    void setupPerformPlot();
    void autoRange();
    void hideAllSeries();

};

#endif //PREPROCESSOR_PERFORM_PLOT_H
