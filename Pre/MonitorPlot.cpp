
#include "MonitorPlot.h"
#include <QLineSeries>
#include <QDebug>
#include <cmath>

MonitorPlot::MonitorPlot(QWidget *parent):
        CustomChartView(new QChart, parent),
        monitorchart(new QChart),
        perf_pRatio(new QLineSeries(this)),
        perf_tRatio(new QLineSeries(this)),
        perf_efficiency(new QLineSeries(this)),
        perf_turning(new QLineSeries(this)),
        perf_qInlet(new QLineSeries(this)),
        perf_qOutlet(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY(new QValueAxis(this)),
        type2Mode(false)
{
    maxRangeY = std::numeric_limits<double>::lowest();
    minRangeY = std::numeric_limits<double>::max();

    autoScale = 1;
    setupChart();
    initPerfSeries();
    this->hideSeries();
}

MonitorPlot::~MonitorPlot() {
    // seriesMap entries are owned by the chart, no need to delete
}

void MonitorPlot::setupChart() {
    this->setChart(monitorchart);

    monitorchart->addAxis(axisX, Qt::AlignBottom);
    monitorchart->addAxis(axisY, Qt::AlignLeft);

    axisX->setRange(0, 10);
    axisY->setRange(0, 10);

    monitorchart->setAnimationOptions(QChart::SeriesAnimations);
    this->setChartStyle();
}

void MonitorPlot::initPerfSeries() {
    // Initialize fixed perf series
    perf_pRatio->setName("pRatio");
    perf_tRatio->setName("tRatio");
    perf_efficiency->setName("efficiency");
    perf_turning->setName("turning");
    perf_qInlet->setName("qInlet");
    perf_qOutlet->setName("qOutlet");

    monitorchart->addSeries(perf_pRatio);
    monitorchart->addSeries(perf_tRatio);
    monitorchart->addSeries(perf_efficiency);
    monitorchart->addSeries(perf_turning);
    monitorchart->addSeries(perf_qInlet);
    monitorchart->addSeries(perf_qOutlet);

    perf_pRatio->attachAxis(axisX);
    perf_pRatio->attachAxis(axisY);
    perf_tRatio->attachAxis(axisX);
    perf_tRatio->attachAxis(axisY);
    perf_efficiency->attachAxis(axisX);
    perf_efficiency->attachAxis(axisY);
    perf_turning->attachAxis(axisX);
    perf_turning->attachAxis(axisY);
    perf_qInlet->attachAxis(axisX);
    perf_qInlet->attachAxis(axisY);
    perf_qOutlet->attachAxis(axisX);
    perf_qOutlet->attachAxis(axisY);

    // Add to seriesMap
    seriesMap["pRatio"] = perf_pRatio;
    seriesMap["tRatio"] = perf_tRatio;
    seriesMap["efficiency"] = perf_efficiency;
    seriesMap["turning"] = perf_turning;
    seriesMap["qInlet"] = perf_qInlet;
    seriesMap["qOutlet"] = perf_qOutlet;
}

void MonitorPlot::ensureSeriesExists(const QString& displayName) {
    if (!seriesMap.contains(displayName)) {
        QLineSeries* series = new QLineSeries(this);
        series->setName(displayName);
        monitorchart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        seriesMap[displayName] = series;
        series->hide();
        qDebug() << "Created new series:" << displayName;
    }
}

void MonitorPlot::updateAvailableVariables(const QStringList& variableNames) {
    // Clear existing dynamic series data when switching files
    for (auto* series : seriesMap.values()) {
        series->clear();
    }
    
    // Ensure series exist for all variables
    for (const QString& name : variableNames) {
        ensureSeriesExists(name);
    }
}

void MonitorPlot::updateMonitorChart(int iteration, const MonitorVariableTable &data) {
    // Check if this is a bulk load (series is empty but data has multiple points)
    bool isBulkLoad = false;
    for (const MonitorFileData& mon : data.monitors) {
        for (const QString& varName : mon.variableNames) {
            if (seriesMap.contains(varName) && seriesMap[varName]->count() == 0) {
                if (mon.data.contains(varName) && mon.data[varName].size() > 1) {
                    isBulkLoad = true;
                    break;
                }
            }
        }
        if (isBulkLoad) break;
    }
    
    if (isBulkLoad) {
        // Bulk load: add all existing data points
        loadAllDataToChart(data);
    } else {
        // Incremental update: add only the last point
        for (const MonitorFileData& mon : data.monitors) {
            for (const QString& varName : mon.variableNames) {
                ensureSeriesExists(varName);
                
                if (mon.data.contains(varName) && !mon.data[varName].isEmpty()) {
                    double val = mon.data[varName].last();
                    // Skip NaN and Infinity values
                    if (!std::isnan(val) && !std::isinf(val)) {
                        seriesMap[varName]->append(iteration, val);
                    }
                }
            }
        }

        // Update fixed perf data
        if (!data.perform.pRatio.isEmpty()) {
            perf_pRatio->append(iteration, data.perform.pRatio.last());
            perf_tRatio->append(iteration, data.perform.tRatio.last());
            perf_efficiency->append(iteration, data.perform.efficiency.last());
            perf_turning->append(iteration, data.perform.turning.last());
            perf_qInlet->append(iteration, data.perform.qInlet.last());
            perf_qOutlet->append(iteration, data.perform.qOutlet.last());
        }
    }

    if (!autoScale)
        return;
    if (iteration > axisX->max()) {
        axisX->setRange(0, iteration + 1);
    }
    updateRangeWithTimer(data);
}

void MonitorPlot::loadAllDataToChart(const MonitorVariableTable &data) {
    // Clear existing series data first
    for (auto* series : seriesMap.values()) {
        series->clear();
    }
    
    // Load all data points for dynamic monitors
    for (const MonitorFileData& mon : data.monitors) {
        for (const QString& varName : mon.variableNames) {
            ensureSeriesExists(varName);
            
            if (mon.data.contains(varName)) {
                const QVector<double>& values = mon.data[varName];
                QLineSeries* series = seriesMap[varName];
                for (int i = 0; i < values.size(); ++i) {
                    double val = values[i];
                    // Skip NaN and Infinity values
                    if (!std::isnan(val) && !std::isinf(val)) {
                        series->append(i + 1, val);  // iteration starts from 1
                    }
                }
            }
        }
    }
    
    // Load all perf data
    int perfSize = data.perform.pRatio.size();
    for (int i = 0; i < perfSize; ++i) {
        perf_pRatio->append(i + 1, data.perform.pRatio[i]);
        perf_tRatio->append(i + 1, data.perform.tRatio[i]);
        perf_efficiency->append(i + 1, data.perform.efficiency[i]);
        perf_turning->append(i + 1, data.perform.turning[i]);
        perf_qInlet->append(i + 1, data.perform.qInlet[i]);
        perf_qOutlet->append(i + 1, data.perform.qOutlet[i]);
    }
    
    // Update X axis range
    int maxIter = 0;
    for (const MonitorFileData& mon : data.monitors) {
        for (const auto& varData : mon.data) {
            maxIter = qMax(maxIter, varData.size());
        }
    }
    maxIter = qMax(maxIter, perfSize);
    
    if (maxIter > 0) {
        axisX->setRange(0, maxIter + 1);
    }
    
    qDebug() << "Bulk loaded" << maxIter << "data points to chart";
}

void MonitorPlot::updateRangeWithTimer(const MonitorVariableTable &data) {
    Q_UNUSED(data);
    // Update Y range based on visible series
    for (const auto& series : seriesMap.values()) {
        if (series->isVisible() && !series->points().isEmpty()) {
            double value = series->points().last().y();
            minRangeY = std::min(minRangeY, value);
            maxRangeY = std::max(maxRangeY, value);
        }
    }
    double margin = (maxRangeY - minRangeY) * 0.05;
    if (margin < 0.001) margin = 1.0; // Prevent zero margin
    axisY->setRange(minRangeY - margin, maxRangeY + margin);
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

void MonitorPlot::clearSeries() {
    for (auto const& series : seriesMap.values()) {
        series->clear();
    }
    axisX->setRange(0, 10);
    axisY->setRange(0, 10);
    maxRangeY = std::numeric_limits<double>::lowest();
    minRangeY = std::numeric_limits<double>::max();
    maxRangeX = 10;
    monitorchart->update();
}

// ============== Type 2 Support ==============

int MonitorPlot::detectMonitorFileType(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;
    }
    
    QTextStream in(&file);
    QString line1 = in.readLine().trimmed();
    file.close();
    
    // Type 2: 第一行是 "N 4" 或 "N 4 0"（纯数字，不以 # 开头）
    if (!line1.startsWith("#")) {
        QStringList parts = line1.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
        if (parts.size() >= 2) {
            bool ok1, ok2;
            parts[0].toInt(&ok1);
            parts[1].toInt(&ok2);
            if (ok1 && ok2) {
                return 2;  // Type 2
            }
        }
    }
    
    // 其他类型: 从 "# monitor type X" 解析
    if (line1.startsWith("#")) {
        QRegExp rx("monitor\\s+type\\s+(\\d+)");
        if (rx.indexIn(line1) != -1) {
            return rx.cap(1).toInt();
        }
    }
    
    return 1;  // 默认 Type 1
}

void MonitorPlot::setType2Mode(bool enabled) {
    type2Mode = enabled;
    
    if (type2Mode) {
        // Type 2 模式: X 轴为半径
        axisX->setTitleText("Radius");
        axisX->setLabelFormat("%.4f");
        monitorchart->setTitle("Monitor");
    } else {
        // 普通模式: X 轴为迭代次数
        axisX->setTitleText("Iteration");
        axisX->setLabelFormat("%d");
        monitorchart->setTitle("Monitor");
    }
}

void MonitorPlot::loadType2File(const QString& filePath) {
    // 检查文件是否更新
    QFileInfo fileInfo(filePath);
    if (filePath == type2FilePath && fileInfo.lastModified() == type2LastModified) {
        return;  // 文件未更新，跳过
    }
    
    type2FilePath = filePath;
    type2LastModified = fileInfo.lastModified();
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open Type 2 file:" << filePath;
        return;
    }
    
    QTextStream in(&file);
    
    // 读取第一行: N 4 [0]
    QString line1 = in.readLine();
    QStringList parts = line1.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
    int N = parts[0].toInt();
    
    type2Data.clear();
    type2Data.radialPoints = N;
    
    // 提取文件标识
    QString fileName = QFileInfo(filePath).fileName();
    QRegExp rx1("mon_([^.]+)\\.dat");
    QRegExp rx2("([^.]+)\\.dat");
    if (rx1.indexIn(fileName) != -1) {
        type2Data.identifier = rx1.cap(1);
    } else if (rx2.indexIn(fileName) != -1) {
        type2Data.identifier = rx2.cap(1);
    }
    
    // 按块读取数据
    QVector<QVector<double>> blocks;
    QVector<double> currentBlock;
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            // 空行 = 块结束
            if (!currentBlock.isEmpty()) {
                blocks.append(currentBlock);
                currentBlock.clear();
            }
        } else {
            currentBlock.append(line.toDouble());
        }
    }
    // 处理最后一个块（如果文件末尾没有空行）
    if (!currentBlock.isEmpty()) {
        blocks.append(currentBlock);
    }
    
    file.close();
    
    type2Data.numBlocks = blocks.size();
    
    // 按固定顺序分配
    if (blocks.size() >= 1) type2Data.r = blocks[0];
    if (blocks.size() >= 2) type2Data.rho = blocks[1];
    if (blocks.size() >= 3) type2Data.u = blocks[2];
    if (blocks.size() >= 4) type2Data.v = blocks[3];
    if (blocks.size() >= 5) type2Data.w = blocks[4];
    if (blocks.size() >= 6) type2Data.p = blocks[5];
    
    // 剩余的都是湍流变量
    for (int i = 6; i < blocks.size(); ++i) {
        type2Data.turbVars.append(blocks[i]);
    }
    
    qDebug() << "Loaded Type 2 file:" << fileName 
             << "N=" << N 
             << "Blocks=" << type2Data.numBlocks
             << "Variables:" << type2Data.getAvailableVariables();
    
    // 切换到 Type 2 模式并更新图表
    setType2Mode(true);
    
    // 为 Type 2 变量创建 series
    QStringList displayNames = type2Data.getDisplayNames();
    for (const QString& name : displayNames) {
        ensureSeriesExists(name);
    }
    
    // 更新图表数据
    updateType2Chart(type2Data);
}

void MonitorPlot::updateType2Chart(const MonitorType2Data& data) {
    if (data.r.isEmpty()) {
        qDebug() << "Type 2 data is empty";
        return;
    }
    
    // 清空所有 series 数据
    for (auto* series : seriesMap.values()) {
        series->clear();
    }
    
    // 获取可用变量
    QStringList vars = data.getAvailableVariables();
    
    // 填充数据：X 轴为半径 r
    for (const QString& varName : vars) {
        QString displayName = data.getDisplayName(varName);
        const QVector<double>* varData = data.getVariableData(varName);
        
        if (varData && seriesMap.contains(displayName)) {
            QLineSeries* series = seriesMap[displayName];
            for (int i = 0; i < data.r.size() && i < varData->size(); ++i) {
                series->append(data.r[i], (*varData)[i]);
            }
        }
    }
    
    // 自动调整坐标轴范围
    if (autoScale && !data.r.isEmpty()) {
        double minR = *std::min_element(data.r.begin(), data.r.end());
        double maxR = *std::max_element(data.r.begin(), data.r.end());
        double marginR = (maxR - minR) * 0.02;
        axisX->setRange(minR - marginR, maxR + marginR);
        
        // Y 轴范围根据可见 series 调整
        updateRangeOnVariableChange();
    }
}

