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
#include "DataStructure.h"

class SimulationDataManager : public QObject {
    Q_OBJECT

public:
    explicit SimulationDataManager(QObject* parent = nullptr);
    ~SimulationDataManager();

    // File management
    void openFiles();
    void closeFiles();
    void setFilePaths(const QString& inletPath, const QString& outletPath,
                      const QString& perfPath, const QString& residualPath);

    // Data Getter
     MonitorVariableTable& getMonitorData()  { return monitorVariableTable; }
     QVector<int>& getIterations()  { return iteration; }

    //AutoRun Data
    QList<double> pressureList_AutoRun;
    int currentIndex_AutoRunPressure = 0;
    bool autoRunning = 0;

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
    QFile inletFile;
    QFile outletFile;
    QFile perfFile;
    QFile residualDataFile;

    // Data storage
    MonitorVariableTable monitorVariableTable;
    QVector<int> iteration;

    // File positions
    qint64 lastResFilePos;
    QVector<qint64> monfilePositionTable;

    void initializePositions();

};

#endif //PREPROCESSOR_SIMULATIONDATAMANAGER_H
