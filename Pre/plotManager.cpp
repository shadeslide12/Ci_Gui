//
// Created by Niko on 2024/12/31.
//

#include "PlotManager.h"

PlotManager::PlotManager(QObject *parent)
    : QObject(parent)
    , residualPlot(nullptr)
    , monitorPlot(nullptr)
    , performPlot(nullptr)
    , isResidualPlotVisible(false)
    , isMonitorPlotVisible(false)
    , isPerformancePlotVisible(false)
{
}

PlotManager::~PlotManager() {
    // Note: We don't delete the plot pointers here as they are owned by the UI
}

void PlotManager::initializePlots(Residual_Plot* residualPlot,
                                MonitorPlot* monitorPlot,
                                Perform_Plot* performPlot) {
    this->residualPlot = residualPlot;
    this->monitorPlot = monitorPlot;
    this->performPlot = performPlot;

}

void PlotManager::showResidualPlot(bool show) {
    if (residualPlot) {
        residualPlot->setVisible(show);
        isResidualPlotVisible = show;
    }
}

void PlotManager::showMonitorPlot(bool show) {
    if (monitorPlot) {
        monitorPlot->setVisible(show);
        isMonitorPlotVisible = show;
    }
}

void PlotManager::showPerformancePlot(bool show) {
    if (performPlot) {
        performPlot->setVisible(show);
        isPerformancePlotVisible = show;
    }
}

void PlotManager::updateMonitorSeriesVisibility(const QStringList& displayVariables) {
    if (monitorPlot) {
        monitorPlot->updateSeriesVisibility(displayVariables);
    }
}

void PlotManager::updateMonitorRangeOnVariableChange() {
    if (monitorPlot) {
        monitorPlot->updateRangeOnVariableChange();
    }
}

void PlotManager::updateResidualPlot(const int& iteration, const double& convergence1, const double& convergence2) {
    if (residualPlot && isResidualPlotVisible) {
        residualPlot->updateResidualPlot(iteration, convergence1, convergence2);
    }
}

void PlotManager::updateMonitorPlot(const MonitorVariableTable& data, int iteration) {
    if (monitorPlot && isMonitorPlotVisible) {
        monitorPlot->updateMonitorChart(iteration, data);
    }
}

void PlotManager::updatePerformancePlot(const MonitorVariableTable& data) {
    if (performPlot && isPerformancePlotVisible) {
        performPlot->updateChart(const_cast<MonitorVariableTable&>(data));  // const_cast needed due to Perform_Plot interface
    }
}



void PlotManager::clearPlotData() {
    if (residualPlot) {
        residualPlot->clearSeries();
    }

    if (monitorPlot) {
        monitorPlot->clearSeries();
    }

    if (performPlot) {
        performPlot->clearChartData();
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

void PlotManager::setAutoScale(bool enable) {
    if (residualPlot) {
        if (enable) {
            residualPlot->setAutoScaleMode();
        } else {
            residualPlot->setManualScaleMode();
        }
    }

    if (monitorPlot) {
        if (enable) {
            monitorPlot->setAutoScaleMode();
        } else {
            monitorPlot->setManualScaleMode();
        }
    }
}

void PlotManager::updateResidualHistory(const QString& name) {
    if (residualPlot) {
        residualPlot->updateDataHistory(name);
    }
}

void PlotManager::loadResidualHistory(const QString& name) {
    if (residualPlot) {
        residualPlot->loadHisotyData(name);
    }
}

void PlotManager::clearResidualHistory() {
    if (residualPlot) {
        residualPlot->clearHistory();
    }
}

QStringList PlotManager::getResidualHistoryNames() const {
    if (residualPlot) {
        return residualPlot->getHistoryName();
    }
    return QStringList();
}
