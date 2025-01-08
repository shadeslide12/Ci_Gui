
#include "MonitorPlot.h"
#include <QLineSeries>
#include <QDebug>

MonitorPlot::MonitorPlot(QWidget *parent):
        CustomChartView(new QChart,parent),
        monitorchart(new QChart),
        inlet_pTotal(new QLineSeries(this)),
        inlet_tTotal(new QLineSeries(this)),
        inlet_vAxial(new QLineSeries(this)),
        inlet_vTheta(new QLineSeries(this)),
        inlet_pStatic(new QLineSeries(this)),
        inlet_mDot(new QLineSeries(this)),
        outlet_pTotal(new QLineSeries(this)),
        outlet_tTotal(new QLineSeries(this)),
        outlet_vAxial(new QLineSeries(this)),
        outlet_vTheta(new QLineSeries(this)),
        outlet_pStatic(new QLineSeries(this)),
        outlet_mDot(new QLineSeries(this)),
        perf_pRatio(new QLineSeries(this)),
        perf_tRatio(new QLineSeries(this)),
        perf_efficiency(new QLineSeries(this)),
        perf_turning(new QLineSeries(this)),
        perf_qInlet(new QLineSeries(this)),
        perf_qOutlet(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY(new QValueAxis(this))
{
    chartSeriesTable = {
            inlet_pTotal, inlet_tTotal, inlet_vAxial, inlet_vTheta, inlet_pStatic, inlet_mDot,
            outlet_pTotal, outlet_tTotal, outlet_vAxial, outlet_vTheta, outlet_pStatic, outlet_mDot,
            perf_pRatio, perf_tRatio, perf_efficiency, perf_turning, perf_qInlet, perf_qOutlet
    };

    maxRangeY = std::numeric_limits<double>::lowest();
    minRangeY = std::numeric_limits<double>::max();

    autoScale = 1;
    setupChart();
    initSeriesMap();
    initValueGetMap();
    this->hideSeries();

}

void MonitorPlot::setupChart() {
    this->setChart(monitorchart);

    monitorchart->addAxis(axisX, Qt::AlignBottom);
    monitorchart->addAxis(axisY, Qt::AlignLeft);

    inlet_pTotal->setName("Inlet pTotal");
    inlet_tTotal->setName("Inlet tTotal");
    inlet_vAxial->setName("Inlet vAxial");
    inlet_vTheta->setName("Inlet vTheta");
    inlet_pStatic->setName("Inlet pStatic");
    inlet_mDot->setName("Inlet mDot");

    outlet_pTotal->setName("Outlet pTotal");
    outlet_tTotal->setName("Outlet tTotal");
    outlet_vAxial->setName("Outlet vAxial");
    outlet_vTheta->setName("Outlet vTheta");
    outlet_pStatic->setName("Outlet pStatic");
    outlet_mDot->setName("Outlet mDot");

    perf_pRatio->setName("Perf pRatio");
    perf_tRatio->setName("Perf tRatio");
    perf_efficiency->setName("Efficiency");
    perf_turning->setName("Turning");
    perf_qInlet->setName("qInlet");
    perf_qOutlet->setName("qOutlet");

    monitorchart->addSeries(inlet_pTotal);
    monitorchart->addSeries(inlet_tTotal);
    monitorchart->addSeries(inlet_vAxial);
    monitorchart->addSeries(inlet_vTheta);
    monitorchart->addSeries(inlet_pStatic);
    monitorchart->addSeries(inlet_mDot);

    monitorchart->addSeries(outlet_pTotal);
    monitorchart->addSeries(outlet_tTotal);
    monitorchart->addSeries(outlet_vAxial);
    monitorchart->addSeries(outlet_vTheta);
    monitorchart->addSeries(outlet_pStatic);
    monitorchart->addSeries(outlet_mDot);

    monitorchart->addSeries(perf_pRatio);
    monitorchart->addSeries(perf_tRatio);
    monitorchart->addSeries(perf_efficiency);
    monitorchart->addSeries(perf_turning);
    monitorchart->addSeries(perf_qInlet);
    monitorchart->addSeries(perf_qOutlet);


    for(auto series : chartSeriesTable) {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    axisX->setRange(0,10);
    axisY->setRange(0,10);

    monitorchart->setAnimationOptions(QChart::SeriesAnimations);
    this->setChartStyle();
}

void MonitorPlot::updateMonitorChart(int iteration, const MonitorVariableTable &data) {
    inlet_pTotal->append(iteration, data.inlet.pTotal.last());
    inlet_tTotal->append(iteration, data.inlet.tTotal.last());
    inlet_vAxial->append(iteration, data.inlet.vAxial.last());
    inlet_vTheta->append(iteration, data.inlet.vTheta.last());
    inlet_pStatic->append(iteration, data.inlet.pStatic.last());
    inlet_mDot->append(iteration, data.inlet.mDot.last());

    outlet_pTotal->append(iteration, data.outlet.pTotal.last());
    outlet_tTotal->append(iteration, data.outlet.tTotal.last());
    outlet_vAxial->append(iteration, data.outlet.vAxial.last());
    outlet_vTheta->append(iteration, data.outlet.vTheta.last());
    outlet_pStatic->append(iteration, data.outlet.pStatic.last());
    outlet_mDot->append(iteration, data.outlet.mDot.last());

    perf_pRatio->append(iteration, data.perform.pRatio.last());
    perf_tRatio->append(iteration, data.perform.tRatio.last());
    perf_efficiency->append(iteration, data.perform.efficiency.last());
    perf_turning->append(iteration, data.perform.turning.last());
    perf_qInlet->append(iteration, data.perform.qInlet.last());
    perf_qOutlet->append(iteration, data.perform.qOutlet.last());

    if(!autoScale)
        return;
    if (iteration > axisX->max()) {
        axisX->setRange(0, iteration + 1);
    }
    updateRangeWithTimer(data);
}

void MonitorPlot::updateRangeWithTimer(const MonitorVariableTable &data) {
    for(const auto& var : seriesMap.keys()){
        if(seriesMap[var]-> isVisible()){
            double value = valueGetMap[var](data);
            minRangeY = std::min(minRangeY,value);
            maxRangeY = std::max(maxRangeY,value);
        }
    }
    double margin = (maxRangeY - minRangeY) * 0.05;
    axisY->setRange(minRangeY-margin,maxRangeY+margin);
}

void MonitorPlot::updateRangeOnVariableChange() {
    maxRangeY = std::numeric_limits<double>::lowest();
    minRangeY = std::numeric_limits<double>::max();
    for(const auto& series : seriesMap.values()) {
        if(series->isVisible() && (!series->points().isEmpty()) ) {
            const auto& points =series->points();
            for(const auto& point : points) {
                maxRangeY = std::max(maxRangeY, point.y());
                minRangeY = std::min(minRangeY, point.y());
            }
        }
    }
    double margin = (maxRangeY - minRangeY) * 0.05;
    axisY->setRange(minRangeY-margin,maxRangeY+margin);
}

void MonitorPlot::setRangeX_Max(const QString &text_xMax) {
    if(!autoScale) {
        maxRangeX = text_xMax.toDouble();
        axisX->setRange(minRangeX, maxRangeX);
    }
}

void MonitorPlot::setRangeX_Min(const QString &text_xMin) {
    if(!autoScale) {
        minRangeX = text_xMin.toDouble();
        axisX->setRange(minRangeX, maxRangeX);
    }
}

void MonitorPlot::setRangeY_Min(const QString &text_yMin) {
    if(!autoScale) {
        minRangeY = text_yMin.toDouble();
        axisY->setRange(minRangeY, maxRangeY);
    }
}

void MonitorPlot::setRangeY_Max(const QString &text_yMax) {
    if(!autoScale) {
        maxRangeY = text_yMax.toDouble();
        axisY->setRange(minRangeY, maxRangeY);
    }
}

void MonitorPlot::setAutoScaleMode() {
    autoScale = 1;
}

void MonitorPlot::setManualScaleMode() {
    autoScale = 0;
}

void MonitorPlot::setChartStyle() {
    QFont titleFont("Arial",16,QFont::Bold);
    monitorchart->setTitle("Monitor");
    monitorchart->setTitleFont(titleFont);

    QFont axisTitleFont("Arial", 12, QFont::Bold);
    QFont axisLabelFont("Arial", 12);
    axisX->setTitleText("Iteration");
    axisX->setTitleFont(axisTitleFont);
    axisX->setLabelsFont(axisLabelFont);
    axisX->setLabelFormat("%d");

    axisY->setTitleText("Value");
    axisY->setTitleFont(axisTitleFont);
    axisY->setLabelsFont(axisLabelFont);
    axisY->setTitleBrush(Qt::red);

    axisX->setTickCount(11);
    axisX->setMinorTickCount(4);
    axisY->setTickCount(8);
}

void MonitorPlot::hideSeries() {
    for(auto series : seriesMap.values()) {
        series->hide();
    }
}

void MonitorPlot::updateSeriesVisibility(const QStringList &selectedVariables) {
    this->hideSeries();

    for(const auto& var : selectedVariables){
        if(seriesMap.contains(var))
            seriesMap[var]->show();
    }
}

void MonitorPlot::initValueGetMap() {
    valueGetMap["pTotal(inlet)"] = [](const MonitorVariableTable& data) { return data.inlet.pTotal.last(); };
    valueGetMap["tTotal(inlet)"] = [](const MonitorVariableTable& data) { return data.inlet.tTotal.last(); };
    valueGetMap["vAxial(inlet)"] = [](const MonitorVariableTable& data) { return data.inlet.vAxial.last(); };
    valueGetMap["vTheta(inlet)"] = [](const MonitorVariableTable& data) { return data.inlet.vTheta.last(); };
    valueGetMap["pStatic(inlet)"] = [](const MonitorVariableTable& data) { return data.inlet.pStatic.last(); };
    valueGetMap["mDot(inlet)"] = [](const MonitorVariableTable& data) { return data.inlet.mDot.last(); };

    valueGetMap["pTotal(outlet)"] = [](const MonitorVariableTable& data) { return data.outlet.pTotal.last(); };
    valueGetMap["tTotal(outlet)"] = [](const MonitorVariableTable& data) { return data.outlet.tTotal.last(); };
    valueGetMap["vAxial(outlet)"] = [](const MonitorVariableTable& data) { return data.outlet.vAxial.last(); };
    valueGetMap["vTheta(outlet)"] = [](const MonitorVariableTable& data) { return data.outlet.vTheta.last(); };
    valueGetMap["pStatic(outlet)"] = [](const MonitorVariableTable& data) { return data.outlet.pStatic.last(); };
    valueGetMap["mDot(outlet)"] = [](const MonitorVariableTable& data) { return data.outlet.mDot.last(); };

    valueGetMap["pRatio"] = [](const MonitorVariableTable& data) { return data.perform.pRatio.last(); };
    valueGetMap["tRatio"] = [](const MonitorVariableTable& data) { return data.perform.tRatio.last(); };
    valueGetMap["efficiency"] = [](const MonitorVariableTable& data) { return data.perform.efficiency.last(); };
    valueGetMap["turning"] = [](const MonitorVariableTable& data) { return data.perform.turning.last(); };
    valueGetMap["qInlet"] = [](const MonitorVariableTable& data) { return data.perform.qInlet.last(); };
    valueGetMap["qOutlet"] = [](const MonitorVariableTable& data) { return data.perform.qOutlet.last(); };
}


void MonitorPlot::initSeriesMap() {
    seriesMap = {
            {"pTotal(inlet)", inlet_pTotal},
            {"tTotal(inlet)", inlet_tTotal},
            {"vAxial(inlet)", inlet_vAxial},
            {"vTheta(inlet)", inlet_vTheta},
            {"pStatic(inlet)", inlet_pStatic},
            {"mDot(inlet)", inlet_mDot},
            {"pTotal(outlet)", outlet_pTotal},
            {"tTotal(outlet)", outlet_tTotal},
            {"vAxial(outlet)", outlet_vAxial},
            {"vTheta(outlet)", outlet_vTheta},
            {"pStatic(outlet)", outlet_pStatic},
            {"mDot(outlet)", outlet_mDot},
            {"pRatio", perf_pRatio},
            {"tRatio", perf_tRatio},
            {"efficiency", perf_efficiency},
            {"turning", perf_turning},
            {"qInlet", perf_qInlet},
            {"qOutlet", perf_qOutlet}
    };
}

void MonitorPlot::clearSeries() {
    for(auto const& series : seriesMap )
        series->clear();
    axisX->setRange(0,10);
    axisY->setRange(0,10);
    maxRangeY = std::numeric_limits<double>::lowest();
    minRangeY = std::numeric_limits<double>::max();
    maxRangeX = 10;
    monitorchart->update();
}

