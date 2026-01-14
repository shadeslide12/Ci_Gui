//
// Created by Niko on 2024/12/31.
//

#ifndef PREPROCESSOR_SIMULATIONDATAMANAGER_H
#define PREPROCESSOR_SIMULATIONDATAMANAGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <QProcess>
#include <QRegExp>
#include <QFileInfo>
#include <QMap>
#include "DataStructure.h"

class SimulationDataManager : public QObject {
    Q_OBJECT

public:
    explicit SimulationDataManager(QObject* parent = nullptr);
    ~SimulationDataManager();

    // File management
    void openFiles();
    void closeFiles();
    void setFilePaths(const QString& perfPath, const QString& residualPath);
    void updateMonitorFilePaths(const QStringList& newMonitorFilePaths);

    // Data Getter
    MonitorVariableTable& getMonitorData() { return monitorVariableTable; }
    QVector<int>& getIterations() { return iteration; }
    
    // Get all available variable display names (for UI)
    QStringList getAllVariableDisplayNames() const;

    // AutoRun Data
    QList<double> pressureList_AutoRun;
    int currentIndex_AutoRunPressure = 0;
    bool isAutoRunning = 0;

    bool generatePressurePoints(double start_Pressure, double end_Pressure, int num_Points);
    void saveCurrentOutputFile(double currentPressure);

signals:
    void residualDataUpdated(const int& iteration, const double& convergence1, const double& convergence2);
    void monitorDataUpdated(int iteration_last, MonitorVariableTable& monitorVariableTable);

public slots:
    void updateResidual();
    void updateMonitorData();
    void clearData();

private:
    // File handles
    QVector<QFile*> monitorFiles;   // Dynamic monitor files (Type 1/3/5)
    QFile perfFile;                  // Fixed perf file
    QFile residualDataFile;          // Fixed residual file

    // Data storage
    MonitorVariableTable monitorVariableTable;
    QVector<int> iteration;

    // File positions
    qint64 lastResFilePos;
    qint64 perfFilePos;
    QVector<qint64> monfilePositionTable;
    
    // File paths
    QStringList monitorFilePaths;
    
    // Cache for monitor data (file path -> data)
    QMap<QString, MonitorFileData> monitorDataCache;
    QMap<QString, qint64> monitorPositionCache;

    // Helper functions
    void initializePositions();
    void parseMonitorFileHeader(int fileIndex);
    int parseMonitorType(const QString& headerLine);
    void loadAllExistingData(int fileIndex);  // 首次加载全部数据
    
    // Type 4 specific functions
    bool isType4File(int fileIndex);
    void parseType4Header(int fileIndex);
    double parseType4Value(const QString& valueStr);  // Handle ***, Infinity
};

#endif //PREPROCESSOR_SIMULATIONDATAMANAGER_H
