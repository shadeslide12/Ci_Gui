#ifndef PREPROCESSOR_RESIDUAL_PLOT_H
#define PREPROCESSOR_RESIDUAL_PLOT_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QVector>
QT_CHARTS_USE_NAMESPACE

class Residual_Plot:public QChart{
Q_OBJECT

public:
    explicit Residual_Plot();

    void updateResidualPlot(const QVector<double>& iteration,const QVector<double>& convergence1,const QVector<double>& convergence2);

private:
    QLineSeries* series_con1;
    QLineSeries* series_con2;
    QValueAxis* axisX;
    QValueAxis* axisY1;
    QValueAxis* axisY2;
    void setupResidualPlot();
};

#endif //PREPROCESSOR_RESIDUAL_PLOT_H
