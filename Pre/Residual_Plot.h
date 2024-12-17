#ifndef PREPROCESSOR_RESIDUAL_PLOT_H
#define PREPROCESSOR_RESIDUAL_PLOT_H

#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QVector>
#include "CustomChartView.h"
QT_CHARTS_USE_NAMESPACE

struct ResidualData{
    QVector<QPointF> con1_data;
    QVector<QPointF> con2_data;
};


class Residual_Plot:public CustomChartView{
Q_OBJECT

public:
    explicit Residual_Plot(QWidget* parent= nullptr);
    ~Residual_Plot()=default;

    void updateResidualPlot(const int& iteration,const double& convergence1,const double& convergence2);
    void setRangeX_Max(const QString &text_xMax);
    void setRangeX_Min(const QString &text_xMin);
    void setRangeY1_Min(const QString &text_y1Min);
    void setRangeY1_Max(const QString &text_yMax);
    void setAutoScaleMode();
    void setManualScaleMode();
    void setChartStyle();
    void clearSeries();
    void updateDataHistory(const QString& name);
    void loadHisotyData(const QString& name);
    QStringList getHistoryName() const;
    void clearHistory();

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

    int maxIter;
    double maxCon1;
    double minCon1;
    double maxCon2;
    double minCon2;

    QMap<QString,ResidualData> residualHistory;
    bool autoScale;
    void setupResidualPlot();
};

#endif //PREPROCESSOR_RESIDUAL_PLOT_H
