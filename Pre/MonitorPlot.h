
#ifndef QLIST_MONITORPLOT_H
#define QLIST_MONITORPLOT_H

#include <QChart>
#include <QChartView>
#include <QListWidget>
#include <QLineSeries>
#include <QValueAxis>
#include <functional>

#include "CustomChartView.h"
#include "DataStructure.h"
QT_CHARTS_USE_NAMESPACE

using ValueGetter = std::function<double(const MonitorVariableTable& data)>;

class MonitorPlot : public CustomChartView{
Q_OBJECT

public:
    explicit MonitorPlot(QWidget* parent = nullptr);
    ~MonitorPlot()=default;

    void setRangeX_Max(const QString &text_xMax);
    void setRangeX_Min(const QString &text_xMin);
    void setRangeY_Min(const QString &text_yMin);
    void setRangeY_Max(const QString &text_yMax);

    void updateChart(int iteration, const MonitorVariableTable& data);
    void hideSeries();
    void updateSeriesVisibility(const QStringList& selectedVariables);
    void updateRangeWithTimer(const MonitorVariableTable& data);
    void updateRangeOnVariableChange();
    void clearSeries();

    void setAutoScaleMode();
    void setManualScaleMode();
    void setChartStyle();

    QChart* monitorchart;

private:
    QMap<QString, QLineSeries*> seriesMap;
    QMap<QString, ValueGetter> valueGetMap;

    QList<QLineSeries* > chartSeriesTable;
    QLineSeries* inlet_pTotal;
    QLineSeries* inlet_tTotal;
    QLineSeries* inlet_vAxial;
    QLineSeries* inlet_vTheta;
    QLineSeries* inlet_pStatic;
    QLineSeries* inlet_mDot;

    QLineSeries* outlet_pTotal;
    QLineSeries* outlet_tTotal;
    QLineSeries* outlet_vAxial;
    QLineSeries* outlet_vTheta;
    QLineSeries* outlet_pStatic;
    QLineSeries* outlet_mDot;

    QLineSeries* perf_pRatio;
    QLineSeries* perf_tRatio;
    QLineSeries* perf_efficiency;
    QLineSeries* perf_turning;
    QLineSeries* perf_qInlet;
    QLineSeries* perf_qOutlet;

    QValueAxis* axisX;
    QValueAxis* axisY;

    void initSeriesMap();
    void initValueGetMap();
    bool autoScale;
    double maxRangeY;
    double minRangeY;
    double minRangeX;
    double maxRangeX;

    void setupChart();

};


#endif //QLIST_MONITORPLOT_H
