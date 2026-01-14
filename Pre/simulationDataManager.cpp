//
// Created by Niko on 2024/12/31.
//

#include "simulationDataManager.h"
#include <limits>
#include <cmath>

SimulationDataManager::SimulationDataManager(QObject* parent)
    : QObject(parent)
{
    initializePositions();
    // Initialize with default monitor files (will be updated from config)
    monitorFilePaths << "./mon_inlet.dat" << "./mon_outlet.dat";
    perfFile.setFileName("./mon_perf.dat");
    residualDataFile.setFileName("./hist.dat");
}

SimulationDataManager::~SimulationDataManager() {
    closeFiles();
    // Clean up dynamically allocated monitor files
    for (QFile* file : monitorFiles) {
        delete file;
    }
    monitorFiles.clear();
}

void SimulationDataManager::initializePositions() {
    monfilePositionTable.clear();
    lastResFilePos = 0;
    perfFilePos = 0;
}

void SimulationDataManager::setFilePaths(const QString& perfPath, const QString& residualPath) {
    perfFile.setFileName(perfPath);
    residualDataFile.setFileName(residualPath);
}

void SimulationDataManager::updateMonitorFilePaths(const QStringList& newMonitorFilePaths) {
    // Save current data to cache before switching
    for (int i = 0; i < monitorFilePaths.size() && i < monitorVariableTable.monitors.size(); ++i) {
        QString path = monitorFilePaths[i];
        monitorDataCache[path] = monitorVariableTable.monitors[i];
        if (i < monfilePositionTable.size()) {
            monitorPositionCache[path] = monfilePositionTable[i];
        }
    }
    
    // Close and delete old files
    for (QFile* file : monitorFiles) {
        if (file->isOpen()) file->close();
        delete file;
    }
    monitorFiles.clear();
    monfilePositionTable.clear();
    monitorVariableTable.monitors.clear();
    
    // Update paths
    monitorFilePaths = newMonitorFilePaths;
    
    // Create new file objects
    for (int i = 0; i < monitorFilePaths.size(); ++i) {
        QString path = monitorFilePaths[i];
        QFile* file = new QFile(path);
        monitorFiles.append(file);
        
        // Check if we have cached data for this file
        if (monitorDataCache.contains(path)) {
            // Restore from cache
            monitorVariableTable.monitors.append(monitorDataCache[path]);
            monfilePositionTable.append(monitorPositionCache.value(path, 0));
            qDebug() << "Restored cached data for:" << path 
                     << "with" << monitorDataCache[path].data.size() << "variables";
        } else {
            // New file - create empty entry
            monfilePositionTable.append(0);
            MonitorFileData monData;
            monitorVariableTable.monitors.append(monData);
            
            // Parse header for new file
            parseMonitorFileHeader(i);
            
            // Load all existing data from file (首次加载全部数据)
            loadAllExistingData(i);
        }
    }
    
    qDebug() << "Updated monitor file paths:" << monitorFilePaths;
    
    // Emit signal to update chart with loaded data
    if (!monitorVariableTable.monitors.isEmpty()) {
        int lastIter = 0;
        // Find the last iteration from loaded data
        for (const auto& mon : monitorVariableTable.monitors) {
            for (const auto& varData : mon.data) {
                if (!varData.isEmpty()) {
                    lastIter = qMax(lastIter, varData.size());
                }
            }
        }
        if (lastIter > 0) {
            emit monitorDataUpdated(lastIter, monitorVariableTable);
        }
    }
}

int SimulationDataManager::parseMonitorType(const QString& headerLine) {
    // Parse: "# monitor type  3 on boundary    1"
    QRegExp rx("monitor\\s+type\\s+(\\d+)");
    if (rx.indexIn(headerLine) != -1) {
        return rx.cap(1).toInt();
    }
    return 1; // Default to Type 1
}

bool SimulationDataManager::isType4File(int fileIndex) {
    // Use the already-created QFile pointer instead of creating a new one
    if (fileIndex >= monitorFiles.size()) return false;
    
    QFile* file = monitorFiles[fileIndex];
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "isType4File: Failed to open file:" << monitorFilePaths[fileIndex];
        return false;
    }
    
    QTextStream in(file);
    QString line1 = in.readLine();
    file->close();
    
    // Type 4 starts with "# stage performance data"
    bool isType4 = line1.contains("stage performance data", Qt::CaseInsensitive);
    qDebug() << "isType4File:" << monitorFilePaths[fileIndex] << "Line1:" << line1.left(50) << "IsType4:" << isType4;
    return isType4;
}

double SimulationDataManager::parseType4Value(const QString& valueStr) {
    // Handle special values: "***********", "Infinity", "-Infinity"
    QString trimmed = valueStr.trimmed();
    
    if (trimmed.contains("*") || trimmed.isEmpty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (trimmed.compare("Infinity", Qt::CaseInsensitive) == 0 ||
        trimmed.compare("inf", Qt::CaseInsensitive) == 0) {
        return std::numeric_limits<double>::infinity();
    }
    if (trimmed.compare("-Infinity", Qt::CaseInsensitive) == 0 ||
        trimmed.compare("-inf", Qt::CaseInsensitive) == 0) {
        return -std::numeric_limits<double>::infinity();
    }
    
    bool ok;
    double val = trimmed.toDouble(&ok);
    return ok ? val : std::numeric_limits<double>::quiet_NaN();
}

void SimulationDataManager::parseMonitorFileHeader(int fileIndex) {
    if (fileIndex >= monitorFiles.size()) return;
    
    QString filePath = monitorFilePaths[fileIndex];
    MonitorFileData& monData = monitorVariableTable.monitors[fileIndex];
    
    // Check if this is a Type 4 file
    if (isType4File(fileIndex)) {
        parseType4Header(fileIndex);
        return;
    }
    
    // Standard Type 1/3/5 parsing
    QFile* file = monitorFiles[fileIndex];
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for header parsing:" << filePath;
        return;
    }
    
    QTextStream in(file);
    
    // Read first line: # monitor type X on boundary Y
    QString line1 = in.readLine();
    int monType = parseMonitorType(line1);
    monData.monitorType = monType;
    monData.headerLines = 2;
    
    // Read second line: # Iter Var1 Var2 ...
    QString line2 = in.readLine();
    if (line2.startsWith("#")) {
        QStringList vars = line2.mid(1).trimmed().split(QRegExp("\\s+"), Qt::SkipEmptyParts);
        // Skip "Iter" (first column)
        for (int i = 1; i < vars.size(); ++i) {
            monData.variableNames.append(vars[i]);
            // Initialize data vector for this variable
            monData.data[vars[i]] = QVector<double>();
        }
    }
    
    file->close();
    
    qDebug() << "Parsed monitor file" << fileIndex << ":" 
             << "Type" << monType 
             << "Variables:" << monData.variableNames;
}

void SimulationDataManager::parseType4Header(int fileIndex) {
    if (fileIndex >= monitorFiles.size()) return;
    
    QString filePath = monitorFilePaths[fileIndex];
    MonitorFileData& monData = monitorVariableTable.monitors[fileIndex];
    
    QFile* file = monitorFiles[fileIndex];
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open Type 4 file for header parsing:" << filePath;
        return;
    }
    
    QTextStream in(file);
    
    // Type 4 has 7 header lines
    // Line 1: # stage performance data from inlet boundary X to exit boundary Y
    // Line 2: # using mass averaging
    // Line 3: # power is sum of that of X wall boundaries
    // Line 4: #
    // Line 5: #        Inlet       <--Specific_Work-->     ...
    // Line 6: #       Capacity     d(Htot)       power     ... (Variable names)
    // Line 7: # Iter     (SI)        (SI)        (SI)      ... (Units)
    
    monData.monitorType = 4;
    monData.headerLines = 7;
    
    // Skip first 5 lines
    for (int i = 0; i < 5; ++i) {
        in.readLine();
    }
    
    // Line 6 contains actual variable names
    QString line6 = in.readLine();
    qDebug() << "Type 4 Line 6 (variables):" << line6;
    
    // Parse variable names from line 6
    // Format: "#       Capacity     d(Htot)       power     d(Htot)       power      del_H0    Reaction       Va          mass        work        flag"
    QStringList vars = line6.mid(1).trimmed().split(QRegExp("\\s+"), Qt::SkipEmptyParts);
    
    // Track duplicate names and add suffix
    QMap<QString, int> nameCount;
    for (const QString& var : vars) {
        QString cleanVar = var;
        // Clean up variable names: remove parentheses content like d(Htot) -> dHtot
        cleanVar.replace("(", "").replace(")", "");
        
        // Handle duplicate names by adding suffix (_SI, _pct)
        if (nameCount.contains(cleanVar)) {
            nameCount[cleanVar]++;
            cleanVar += "_pct";  // Second occurrence is percentage
        } else {
            nameCount[cleanVar] = 1;
            // Check if this name will appear again (d(Htot), power)
            if (cleanVar == "dHtot" || cleanVar == "power") {
                cleanVar += "_SI";  // First occurrence is SI units
            }
        }
        
        monData.variableNames.append(cleanVar);
        monData.data[cleanVar] = QVector<double>();
    }
    
    file->close();
    
    qDebug() << "Parsed Type 4 monitor file" << fileIndex << ":"
             << "Variables:" << monData.variableNames;
}

void SimulationDataManager::loadAllExistingData(int fileIndex) {
    if (fileIndex >= monitorFiles.size() || fileIndex >= monitorVariableTable.monitors.size()) {
        return;
    }
    
    QFile* file = monitorFiles[fileIndex];
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for loading existing data:" << monitorFilePaths[fileIndex];
        return;
    }
    
    QTextStream in(file);
    MonitorFileData& monData = monitorVariableTable.monitors[fileIndex];
    
    // Skip header lines based on monitor type
    int headerLines = monData.headerLines;
    for (int i = 0; i < headerLines; ++i) {
        in.readLine();
    }
    
    int lineCount = 0;
    bool isType4 = (monData.monitorType == 4);
    
    // Read all existing data lines
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty() || line.trimmed().isEmpty()) {
            continue;
        }
        
        QStringList values = line.split(" ", Qt::SkipEmptyParts);
        if (values.isEmpty()) continue;
        
        // Read variable values (skip first column which is Iter)
        for (int v = 0; v < monData.variableNames.size(); ++v) {
            if (v + 1 < values.size()) {
                QString varName = monData.variableNames[v];
                double val;
                if (isType4) {
                    // Use special parsing for Type 4 to handle *********** and Infinity
                    val = parseType4Value(values[v + 1]);
                } else {
                    val = values[v + 1].toDouble();
                }
                monData.data[varName].append(val);
            }
        }
        lineCount++;
    }
    
    // Record current position for future incremental reads
    monfilePositionTable[fileIndex] = in.pos();
    
    file->close();
    
    qDebug() << "Loaded" << lineCount << "existing data lines from" << monitorFilePaths[fileIndex]
             << "(Type" << monData.monitorType << ")";
}

QStringList SimulationDataManager::getAllVariableDisplayNames() const {
    QStringList names;
    for (const MonitorFileData& mon : monitorVariableTable.monitors) {
        names << mon.variableNames;
    }
    return names;
}

void SimulationDataManager::openFiles() {
    // Open dynamic monitor files
    for (int i = 0; i < monitorFiles.size(); ++i) {
        if (!monitorFiles[i]->isOpen()) {
            if (!(monitorFiles[i]->open(QIODevice::ReadOnly | QIODevice::Text))) {
                qDebug() << "Failed to open monitor file:" << monitorFilePaths[i];
            }
        }
    }
    
    // Open fixed perf file
    if (!perfFile.isOpen()) {
        if (!(perfFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "fail to read perform Files";
        }
    }

    // Open residual file
    if (!residualDataFile.isOpen()) {
        if (!(residualDataFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "fail to read hist File";
        }
    }
}

void SimulationDataManager::closeFiles() {
    // Close dynamic monitor files
    for (QFile* file : monitorFiles) {
        if (file->isOpen())
            file->close();
    }
    
    // Close fixed files
    if (perfFile.isOpen())
        perfFile.close();
    if (residualDataFile.isOpen())
        residualDataFile.close();
}

void SimulationDataManager::updateResidual() {
    if(!residualDataFile.isOpen() ){
        if(!(residualDataFile.open(QIODevice::ReadOnly | QIODevice::Text) )){
            qDebug() << "fail to read hist File";
            return;
        }
    }

    QTextStream in_Res(&residualDataFile);
    in_Res.seek(lastResFilePos);

    if (in_Res.atEnd()) {
        qDebug() << "Residual file is at end";
        return;
    }

    QString line_Res = in_Res.readLine();
    QStringList data = line_Res.split(" ", Qt::SkipEmptyParts);

    if (data.size() > 4) {
        int iter = data[1].toInt();
        double convergence1 = data[2].toDouble();
        double convergence2 = data[3].toDouble();
        emit residualDataUpdated(iter, convergence1, convergence2);
    }

    lastResFilePos = in_Res.pos();
}

void SimulationDataManager::updateMonitorData() {
    if (monitorFiles.isEmpty()) {
        qDebug() << "No monitor files configured";
        return;
    }
    
    // Open monitor files if needed
    for (int i = 0; i < monitorFiles.size(); ++i) {
        if (!monitorFiles[i]->isOpen()) {
            if (!(monitorFiles[i]->open(QIODevice::ReadOnly | QIODevice::Text))) {
                qDebug() << "Failed to open monitor file:" << monitorFilePaths[i];
                return;
            }
        }
    }
    
    // Open perf file
    if (!perfFile.isOpen()) {
        if (!(perfFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "Failed to read perform file";
            return;
        }
    }

    int currentIteration = -1;
    
    // Read data from each dynamic monitor file
    for (int i = 0; i < monitorFiles.size(); ++i) {
        if (i >= monitorVariableTable.monitors.size()) continue;
        
        MonitorFileData& monData = monitorVariableTable.monitors[i];
        bool isType4 = (monData.monitorType == 4);
        
        QTextStream in(monitorFiles[i]);
        in.seek(monfilePositionTable[i]);
        
        // Skip header lines on first read
        if (monfilePositionTable[i] == 0) {
            int headerLines = monData.headerLines;
            for (int h = 0; h < headerLines; ++h) {
                in.readLine();
            }
        }
        
        QString line = in.readLine();
        if (line.isEmpty()) {
            continue;
        }
        
        QStringList values = line.split(" ", Qt::SkipEmptyParts);
        if (values.isEmpty()) continue;
        
        // Read iteration from file data (first column is always Iter)
        currentIteration = values[0].toInt();
        
        // Read variable values dynamically
        for (int v = 0; v < monData.variableNames.size(); ++v) {
            if (v + 1 < values.size()) {
                QString varName = monData.variableNames[v];
                double val;
                if (isType4) {
                    // Use special parsing for Type 4 to handle *********** and Infinity
                    val = parseType4Value(values[v + 1]);
                } else {
                    val = values[v + 1].toDouble();
                }
                monData.data[varName].append(val);
            }
        }
        
        // Update file position
        monfilePositionTable[i] = in.pos();
    }
    
    // Read perf file (fixed structure)
    QTextStream inPerf(&perfFile);
    inPerf.seek(perfFilePos);
    
    if (perfFilePos == 0) {
        inPerf.readLine();
        inPerf.readLine();
    }
    
    QString linePerf = inPerf.readLine();
    if (!linePerf.isEmpty()) {
        QStringList valuesPerf = linePerf.split(" ", Qt::SkipEmptyParts);
        if (valuesPerf.size() > 6) {
            monitorVariableTable.perform.pRatio.append(valuesPerf[1].toDouble());
            monitorVariableTable.perform.tRatio.append(valuesPerf[2].toDouble());
            monitorVariableTable.perform.efficiency.append(valuesPerf[3].toDouble());
            monitorVariableTable.perform.turning.append(valuesPerf[4].toDouble());
            monitorVariableTable.perform.qInlet.append(valuesPerf[5].toDouble());
            monitorVariableTable.perform.qOutlet.append(valuesPerf[6].toDouble());
        }
    }
    perfFilePos = inPerf.pos();

    if (currentIteration >= 0) {
        emit monitorDataUpdated(currentIteration, monitorVariableTable);
    }
}

void SimulationDataManager::clearData() {
    iteration.clear();
    monitorVariableTable.clearMonTable();
    initializePositions();
}

bool SimulationDataManager::generatePressurePoints(double start_Pressure, double end_Pressure, int num_Points) {
    pressureList_AutoRun.clear();

    if(start_Pressure > end_Pressure) {
        return false;
    }
    double step = (end_Pressure - start_Pressure) / (num_Points - 1);
    for(int i = 0 ; i < num_Points ; i++){
        pressureList_AutoRun.append(start_Pressure+i*step);
    }

    return true;
}

void SimulationDataManager::saveCurrentOutputFile(double currentPressure) {
    QString pressureStr = QString::number(currentPressure);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");

    QString subFolderPath = "./pressure_" + pressureStr+ "_"+timestamp;

    QDir().mkpath(subFolderPath);

    QString command = QString("cp mon_* *grid.hdf *flow.hdf hist.dat GUI.yaml %1").arg(subFolderPath);
    qDebug() << "now is saving outputFiles";
    QProcess* copyProcess = new QProcess(this);
    connect(copyProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), copyProcess, &QProcess::deleteLater);
    copyProcess->start("/bin/bash", QStringList() << "-c" << command);
}

