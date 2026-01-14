//
// Created by Niko on 2024/12/31.
//

#include "plotManager.h"

PlotManager::PlotManager(QObject *parent)
    : QObject(parent)
    , residualPlot(nullptr)
    , monitorPlot(nullptr)
    , performPlot(nullptr){

}

void PlotManager::initializePlots(Residual_Plot* residualPlot,
                                MonitorPlot* monitorPlot,
                                Perform_Plot* performPlot) {
    this->residualPlot = residualPlot;
    this->monitorPlot = monitorPlot;
    this->performPlot = performPlot;

}

void PlotManager::clearPlotDataBeforeRunning() {
    if (residualPlot) {
        residualPlot->clearSeries();
    }

    if (monitorPlot) {
        monitorPlot->clearSeries();
    }

}

void PlotManager::setResidualRanges(const QString& xMin, const QString& xMax,
                                  const QString& y1Min, const QString& y1Max,
                                  const QString& y2Min, const QString& y2Max) {
    if (residualPlot) {
        residualPlot->setRangeX_Min(xMin);
        residualPlot->setRangeX_Max(xMax);
        residualPlot->setRangeY1_Min(y1Min);
        residualPlot->setRangeY1_Max(y1Max);
        residualPlot->setRangeY2_Min(y2Min);
        residualPlot->setRangeY2_Max(y2Max);
    }
}

void PlotManager::setMonitorRanges(const QString& xMin, const QString& xMax,
                                 const QString& yMin, const QString& yMax) {
    if (monitorPlot) {
        monitorPlot->setRangeX_Min(xMin);
        monitorPlot->setRangeX_Max(xMax);
        monitorPlot->setRangeY_Min(yMin);
        monitorPlot->setRangeY_Max(yMax);
    }
}

void PlotManager::setPerformanceRanges(const QString& xMin, const QString& xMax,
                                     const QString& yMin, const QString& yMax) {
    if (performPlot) {
        performPlot->setRangeX_Min(xMin);
        performPlot->setRangeX_Max(xMax);
        performPlot->setRangeY_Min(yMin);
        performPlot->setRangeY_Max(yMax);
    }
}

void PlotManager::refreshAllPlots(){
    residualPlot->update();
    monitorPlot->update();
    performPlot->update();
}