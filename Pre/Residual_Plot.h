#ifndef PREPROCESSOR_RESIDUAL_PLOT_H
#define PREPROCESSOR_RESIDUAL_PLOT_H

#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QVector>
QT_CHARTS_USE_NAMESPACE

class Residual_Plot:public QChartView{
Q_OBJECT

public:
    explicit Residual_Plot(QWidget* parent= nullptr);
    ~Residual_Plot()=default;

    void updateResidualPlot(const QVector<double>& iteration,const QVector<double>& convergence1,const QVector<double>& convergence2);
    void setRangeX_Max(const QString &text_xMax);
    void setRangeX_Min(const QString &text_xMin);
    void setRangeY1_Min(const QString &text_y1Min);
    void setRangeY1_Max(const QString &text_yMax);
    void setAutoScaleMode();
    void setManualScaleMode();

    QChart* residualchart;
private:
    QLineSeries* series_con1;
    QLineSeries* series_con2;
    QValueAxis* axisX;
    QValueAxis* axisY1;
    QValueAxis* axisY2;

    double y1Min;
    double y1Max;
    double xMin;
    double xMax;

    bool autoScale;
    void setupResidualPlot();
};

#endif //PREPROCESSOR_RESIDUAL_PLOT_H
