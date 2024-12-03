#ifndef PREPROCESSOR_PERFORM_PLOT_H
#define PREPROCESSOR_PERFORM_PLOT_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
QT_CHARTS_USE_NAMESPACE

class Perform_Plot: public QChart{
Q_OBJECT

public:
    explicit Perform_Plot(QWidget* parent= nullptr);
private:
    QLineSeries* series_pratio;
    QLineSeries* series_tratio;
    QLineSeries* series_efficiency;
    QValueAxis* axisX;
    QValueAxis* axisY;

    void setupPerformPlot();

};

#endif //PREPROCESSOR_PERFORM_PLOT_H
