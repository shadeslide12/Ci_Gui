//
// Created by Niko on 2024/12/31.
//

#ifndef PREPROCESSOR_PLOTMANAGER_H
#define PREPROCESSOR_PLOTMANAGER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>
#include "DataStructure.h"
#include "Residual_Plot.h"
#include "MonitorPlot.h"
#include "Perform_Plot.h"

class PlotManager : public QObject {
Q_OBJECT

public:
    explicit PlotManager(QObject* parent = nullptr);
    ~PlotManager() = default;

    void initializePlots(Residual_Plot* residualPlot,
                         MonitorPlot* monitorPlot,
                         Perform_Plot* performPlot);

    void clearPlotDataBeforeRunning();
    void refreshAllPlots();

    void setResidualRanges(const QString& xMin, const QString& xMax,
                           const QString& y1Min, const QString& y1Max,
                           const QString& y2Min, const QString& y2Max);
    void setMonitorRanges(const QString& xMin, const QString& xMax,
                          const QString& yMin, const QString& yMax);
    void setPerformanceRanges(const QString& xMin, const QString& xMax,
                              const QString& yMin, const QString& yMax);
    void setAutoScale(bool enable);

    void updateResidualHistory(const QString& name);
    void loadResidualHistory(const QString& name);
    void clearResidualHistory();
    QStringList getResidualHistoryNames() const;

    void exportPerformancePlot();


    void updateResidualPlot(const int& iteration, const double& convergence1, const double& convergence2);
    void updateMonitorPlot(const MonitorVariableTable& data, int iteration);
    void updatePerformancePlot(const MonitorVariableTable& data);

private:
    Residual_Plot* residualPlot;
    MonitorPlot* monitorPlot;
    Perform_Plot* performPlot;

};

#endif //PREPROCESSOR_PLOTMANAGER_H
