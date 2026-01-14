
#ifndef QLIST_MONITORPLOT_H
#define QLIST_MONITORPLOT_H

#include <QChart>
#include <QChartView>
#include <QListWidget>
#include <QLineSeries>
#include <QValueAxis>
#include <QMap>
#include <functional>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDateTime>
#include <QRegExp>

#include "CustomChartView.h"
#include "DataStructure.h"
QT_CHARTS_USE_NAMESPACE

class MonitorPlot : public CustomChartView{
Q_OBJECT

public:
    explicit MonitorPlot(QWidget* parent = nullptr);
    ~MonitorPlot();

    void setRangeX_Max(const QString &text_xMax);
    void setRangeX_Min(const QString &text_xMin);
    void setRangeY_Min(const QString &text_yMin);
    void setRangeY_Max(const QString &text_yMax);

    void updateMonitorChart(int iteration, const MonitorVariableTable& data);
    void loadAllDataToChart(const MonitorVariableTable& data);  // 首次加载全部数据
    void hideSeries();
    void updateSeriesVisibility(const QStringList& selectedVariables);
    void updateRangeWithTimer(const MonitorVariableTable& data);
    void updateRangeOnVariableChange();
    void clearSeries();

    void setAutoScaleMode();
    void setManualScaleMode();
    void setChartStyle();
    
    // Dynamic series management
    void ensureSeriesExists(const QString& displayName);
    void updateAvailableVariables(const QStringList& variableNames);
    
    // Type 2 support (radial profile)
    void loadType2File(const QString& filePath);
    void updateType2Chart(const MonitorType2Data& data);
    void setType2Mode(bool enabled);
    bool isType2Mode() const { return type2Mode; }
    
    // File type detection
    static int detectMonitorFileType(const QString& filePath);

    QChart* monitorchart;
    QList<QString> displayVariableList;
    
    // Type 2 data
    MonitorType2Data type2Data;

private:
    //* Dynamic Series
    QMap<QString, QLineSeries*> seriesMap;
    
    //* Fixed perf series (kept for backward compatibility)
    QLineSeries* perf_pRatio;
    QLineSeries* perf_tRatio;
    QLineSeries* perf_efficiency;
    QLineSeries* perf_turning;
    QLineSeries* perf_qInlet;
    QLineSeries* perf_qOutlet;

    QValueAxis* axisX;
    QValueAxis* axisY;

    void initPerfSeries();
    void setupChart();
    
    bool autoScale;
    double maxRangeY;
    double minRangeY;
    double minRangeX;
    double maxRangeX;
    
    // Type 2 mode flag
    bool type2Mode;
    QString type2FilePath;
    QDateTime type2LastModified;
};


#endif //QLIST_MONITORPLOT_H
