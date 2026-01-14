#include "RadialProfilePlot.h"
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

RadialProfilePlot::RadialProfilePlot(QWidget* parent)
    : QWidget(parent)
    , autoScale(true)
    , minRangeX(0), maxRangeX(1)
    , minRangeY(0), maxRangeY(1)
{
    setupUI();
    setupChart();
}

RadialProfilePlot::~RadialProfilePlot() {
    for (auto* series : seriesMap.values()) {
        delete series;
    }
    seriesMap.clear();
}

void RadialProfilePlot::setupUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // Left panel - controls (fixed width like other tabs)
    controlPanel = new QWidget();
    controlPanel->setFixedWidth(350);
    QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);
    controlLayout->setContentsMargins(10, 10, 10, 10);
    controlLayout->setSpacing(10);
    
    // File selection button
    selectFileBtn = new QPushButton("Select Profile File");
    controlLayout->addWidget(selectFileBtn);
    
    // File path label
    filePathLabel = new QLabel("No file selected");
    filePathLabel->setWordWrap(true);
    filePathLabel->setStyleSheet("color: gray; font-size: 9px;");
    controlLayout->addWidget(filePathLabel);
    
    // Variable list label
    QLabel* varLabel = new QLabel("Variable List:");
    controlLayout->addWidget(varLabel);
    
    // Variable list
    variableList = new QListWidget();
    variableList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    controlLayout->addWidget(variableList, 1);  // stretch factor 1
    
    // Scale buttons
    autoScaleBtn = new QPushButton("AutoScale");
    manualScaleBtn = new QPushButton("ManualScale");
    QHBoxLayout* scaleLayout = new QHBoxLayout();
    scaleLayout->addWidget(autoScaleBtn);
    scaleLayout->addWidget(manualScaleBtn);
    controlLayout->addLayout(scaleLayout);
    
    // Range controls
    QLabel* rangeXLabel = new QLabel("Range X:");
    controlLayout->addWidget(rangeXLabel);
    
    QHBoxLayout* rangeXLayout = new QHBoxLayout();
    rangeXLayout->addWidget(new QLabel("Min"));
    xMinEdit = new QLineEdit();
    xMinEdit->setEnabled(false);
    rangeXLayout->addWidget(xMinEdit);
    rangeXLayout->addWidget(new QLabel("Max"));
    xMaxEdit = new QLineEdit();
    xMaxEdit->setEnabled(false);
    rangeXLayout->addWidget(xMaxEdit);
    controlLayout->addLayout(rangeXLayout);
    
    QLabel* rangeYLabel = new QLabel("Range Y:");
    controlLayout->addWidget(rangeYLabel);
    
    QHBoxLayout* rangeYLayout = new QHBoxLayout();
    rangeYLayout->addWidget(new QLabel("Min"));
    yMinEdit = new QLineEdit();
    yMinEdit->setEnabled(false);
    rangeYLayout->addWidget(yMinEdit);
    rangeYLayout->addWidget(new QLabel("Max"));
    yMaxEdit = new QLineEdit();
    yMaxEdit->setEnabled(false);
    rangeYLayout->addWidget(yMaxEdit);
    controlLayout->addLayout(rangeYLayout);
    
    // Right panel - chart
    chart = new QChart();
    chartView = new CustomChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    mainLayout->addWidget(controlPanel);
    mainLayout->addWidget(chartView, 1);  // stretch factor 1 for chart
    
    // Connections
    connect(selectFileBtn, &QPushButton::clicked, this, &RadialProfilePlot::onSelectFile);
    connect(variableList, &QListWidget::itemSelectionChanged, this, &RadialProfilePlot::onVariableSelectionChanged);
    connect(autoScaleBtn, &QPushButton::clicked, this, &RadialProfilePlot::onAutoScale);
    connect(manualScaleBtn, &QPushButton::clicked, this, &RadialProfilePlot::onManualScale);
    connect(xMinEdit, &QLineEdit::editingFinished, [this]() { setRangeX_Min(xMinEdit->text()); });
    connect(xMaxEdit, &QLineEdit::editingFinished, [this]() { setRangeX_Max(xMaxEdit->text()); });
    connect(yMinEdit, &QLineEdit::editingFinished, [this]() { setRangeY_Min(yMinEdit->text()); });
    connect(yMaxEdit, &QLineEdit::editingFinished, [this]() { setRangeY_Max(yMaxEdit->text()); });
}

void RadialProfilePlot::setupChart() {
    QFont titleFont("Arial", 16, QFont::Bold);
    chart->setTitle("Radial Profile");
    chart->setTitleFont(titleFont);
    
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    
    QFont axisTitleFont("Arial", 12, QFont::Bold);
    QFont axisLabelFont("Arial", 12);
    
    axisX->setTitleText("Radius (r)");
    axisX->setTitleFont(axisTitleFont);
    axisX->setLabelsFont(axisLabelFont);
    
    axisY->setTitleText("Value");
    axisY->setTitleFont(axisTitleFont);
    axisY->setLabelsFont(axisLabelFont);
    axisY->setTitleBrush(Qt::red);
    
    // Match MonitorPlot tick settings
    axisX->setTickCount(11);
    axisX->setMinorTickCount(4);
    axisY->setTickCount(8);
    
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    axisX->setRange(0, 1);
    axisY->setRange(0, 1);
}

void RadialProfilePlot::onSelectFile() {
    QString filePath = QFileDialog::getOpenFileName(this,
        "Select Radial Profile File", "", "Monitor Files (mon*.dat);;All Files (*)");
    
    if (filePath.isEmpty()) {
        return;
    }
    
    if (loadFile(filePath)) {
        filePathLabel->setText(QFileInfo(filePath).fileName());
        filePathLabel->setToolTip(filePath);
    }
}

bool RadialProfilePlot::loadFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return false;
    }
    
    QTextStream in(&file);
    
    // Read first line: N numBlocks [optional]
    // Type 2 format: first line is "N numBlocks" (e.g., "89 4")
    QString line1 = in.readLine();
    QStringList parts = line1.trimmed().split(QRegExp("\\s+"), Qt::SkipEmptyParts);
    if (parts.size() < 1) {
        qDebug() << "Invalid Type 2 header format";
        file.close();
        return false;
    }
    
    int N = parts[0].toInt();
    
    profileData.clear();
    profileData.radialPoints = N;
    
    // Extract file identifier from filename
    QString fileName = QFileInfo(filePath).fileName();
    QRegExp rx1("mon_([^.]+)\\.dat");
    QRegExp rx2("([^.]+)\\.dat");
    if (rx1.indexIn(fileName) != -1) {
        profileData.identifier = rx1.cap(1);
    } else if (rx2.indexIn(fileName) != -1) {
        profileData.identifier = rx2.cap(1);
    }
    
    // Read data blocks separated by empty lines
    QVector<QVector<double>> blocks;
    QVector<double> currentBlock;
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            // Empty line = block end
            if (!currentBlock.isEmpty()) {
                blocks.append(currentBlock);
                currentBlock.clear();
            }
        } else {
            currentBlock.append(line.toDouble());
        }
    }
    // Handle last block (if file doesn't end with empty line)
    if (!currentBlock.isEmpty()) {
        blocks.append(currentBlock);
    }
    
    file.close();
    
    profileData.numBlocks = blocks.size();
    
    // Assign blocks to variables in order: r, rho, u, v, w, p, turb...
    if (blocks.size() >= 1) profileData.r = blocks[0];
    if (blocks.size() >= 2) profileData.rho = blocks[1];
    if (blocks.size() >= 3) profileData.u = blocks[2];
    if (blocks.size() >= 4) profileData.v = blocks[3];
    if (blocks.size() >= 5) profileData.w = blocks[4];
    if (blocks.size() >= 6) profileData.p = blocks[5];
    
    // Remaining blocks are turbulence variables
    for (int i = 6; i < blocks.size(); ++i) {
        profileData.turbVars.append(blocks[i]);
    }
    
    currentFilePath = filePath;
    
    // Update variable list
    variableList->clear();
    QStringList vars = profileData.getAvailableVariables();
    for (const QString& var : vars) {
        variableList->addItem(var);
    }
    
    // Create series for each variable
    for (const QString& var : vars) {
        ensureSeriesExists(var);
    }
    
    // Update chart with data
    updateChart();
    
    qDebug() << "Loaded Type 2 file:" << filePath 
             << "N=" << profileData.radialPoints << "Blocks=" << profileData.numBlocks
             << "Variables:" << vars;
    
    return true;
}

void RadialProfilePlot::ensureSeriesExists(const QString& varName) {
    if (!seriesMap.contains(varName)) {
        QLineSeries* series = new QLineSeries();
        series->setName(varName);
        series->setVisible(false);
        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        seriesMap[varName] = series;
    }
}

void RadialProfilePlot::updateChart() {
    if (profileData.r.isEmpty()) return;
    
    const QVector<double>& r = profileData.r;
    
    // Fill series with data
    QStringList vars = profileData.getAvailableVariables();
    for (const QString& varName : vars) {
        if (!seriesMap.contains(varName)) continue;
        
        QLineSeries* series = seriesMap[varName];
        series->clear();
        
        const QVector<double>* data = profileData.getVariableData(varName);
        if (data && data->size() == r.size()) {
            for (int i = 0; i < r.size(); ++i) {
                series->append(r[i], (*data)[i]);
            }
        }
    }
    
    if (autoScale) {
        autoRange();
    }
}

void RadialProfilePlot::onVariableSelectionChanged() {
    QStringList selectedVars;
    for (auto* item : variableList->selectedItems()) {
        selectedVars << item->text();
    }
    updateSeriesVisibility(selectedVars);
    
    if (autoScale && !selectedVars.isEmpty()) {
        autoRange();
    }
}

void RadialProfilePlot::updateSeriesVisibility(const QStringList& selectedVariables) {
    for (auto it = seriesMap.begin(); it != seriesMap.end(); ++it) {
        it.value()->setVisible(selectedVariables.contains(it.key()));
    }
}

void RadialProfilePlot::autoRange() {
    if (profileData.r.isEmpty()) return;
    
    // X range from radius data
    minRangeX = *std::min_element(profileData.r.begin(), profileData.r.end());
    maxRangeX = *std::max_element(profileData.r.begin(), profileData.r.end());
    
    // Y range from selected variables
    minRangeY = std::numeric_limits<double>::max();
    maxRangeY = std::numeric_limits<double>::lowest();
    
    for (auto* item : variableList->selectedItems()) {
        QString varName = item->text();
        const QVector<double>* data = profileData.getVariableData(varName);
        if (data) {
            for (double val : *data) {
                minRangeY = qMin(minRangeY, val);
                maxRangeY = qMax(maxRangeY, val);
            }
        }
    }
    
    // Add margins
    double xMargin = (maxRangeX - minRangeX) * 0.05;
    double yMargin = (maxRangeY - minRangeY) * 0.1;
    
    if (xMargin < 1e-10) xMargin = 0.1;
    if (yMargin < 1e-10) yMargin = 0.1;
    
    axisX->setRange(minRangeX - xMargin, maxRangeX + xMargin);
    axisY->setRange(minRangeY - yMargin, maxRangeY + yMargin);
}

void RadialProfilePlot::onAutoScale() {
    autoScale = true;
    xMinEdit->setEnabled(false);
    xMaxEdit->setEnabled(false);
    yMinEdit->setEnabled(false);
    yMaxEdit->setEnabled(false);
    autoRange();
}

void RadialProfilePlot::onManualScale() {
    autoScale = false;
    xMinEdit->setEnabled(true);
    xMaxEdit->setEnabled(true);
    yMinEdit->setEnabled(true);
    yMaxEdit->setEnabled(true);
    
    xMinEdit->setText(QString::number(axisX->min()));
    xMaxEdit->setText(QString::number(axisX->max()));
    yMinEdit->setText(QString::number(axisY->min()));
    yMaxEdit->setText(QString::number(axisY->max()));
}

void RadialProfilePlot::setRangeX_Min(const QString& text) {
    minRangeX = text.toDouble();
    axisX->setRange(minRangeX, maxRangeX);
}

void RadialProfilePlot::setRangeX_Max(const QString& text) {
    maxRangeX = text.toDouble();
    axisX->setRange(minRangeX, maxRangeX);
}

void RadialProfilePlot::setRangeY_Min(const QString& text) {
    minRangeY = text.toDouble();
    axisY->setRange(minRangeY, maxRangeY);
}

void RadialProfilePlot::setRangeY_Max(const QString& text) {
    maxRangeY = text.toDouble();
    axisY->setRange(minRangeY, maxRangeY);
}

QStringList RadialProfilePlot::getAvailableVariables() const {
    return profileData.getAvailableVariables();
}
