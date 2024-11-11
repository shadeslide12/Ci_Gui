
#ifndef QLIST_MONITORPLOT_H
#define QLIST_MONITORPLOT_H

#include <QChart>
#include <QChartView>
#include <QListWidget>
#include <QLineSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

class MonitorPlot : public QChartView{
Q_OBJECT

public:
    explicit MonitorPlot(QWidget* parent = nullptr);
    ~MonitorPlot()=default;

    void setRangeX_Max(const QString &text_xMax);
    void setRangeX_Min(const QString &text_xMin);
    void setRangeY_Min(const QString &text_yMin);
    void setRangeY_Max(const QString &text_yMax);
    void updateChart(QList<int>& selectedColumns,
                     QList<QListWidgetItem*> selectedItems,
                     QVector<QVector<double>>& data,
                     QVector<int>& iteration);
    void setAutoScaleMode();
    void setManualScaleMode();

    QChart* monitorchart;

private:
    QValueAxis* axisX;
    QValueAxis* axisY;
    bool autoScale;
    double yMin;
    double yMax;
    double xMin;
    double xMax;

    void setupChart();

};


#endif //QLIST_MONITORPLOT_H
