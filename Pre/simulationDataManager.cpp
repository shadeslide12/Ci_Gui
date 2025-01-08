//
// Created by Niko on 2024/12/31.
//

#include "simulationDataManager.h"

SimulationDataManager::SimulationDataManager(QObject *parent)
    : QObject(parent)
{
    initializePositions();
    setFilePaths("./mon_inlet.dat","./mon_outlet.dat",
                 "./mon_perf.dat","./hist.dat");
}

SimulationDataManager::~SimulationDataManager() {
    closeFiles();
}

void SimulationDataManager::initializePositions() {
    monfilePositionTable.resize(3); // For inlet, outlet, and perf files
    monfilePositionTable[0] = 0;
    monfilePositionTable[1] = 0;
    monfilePositionTable[2] = 0;
    lastResFilePos = 0;
}

void SimulationDataManager::setFilePaths(const QString& inletPath, const QString& outletPath,
                                       const QString& perfPath, const QString& residualPath) {

    inletFile.setFileName(inletPath);
    outletFile.setFileName(outletPath);
    perfFile.setFileName(perfPath);
    residualDataFile.setFileName(residualPath);

//    return openFiles();
}

void SimulationDataManager::openFiles() {

    if(!inletFile.isOpen()) {
        if (!(inletFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "fail to read inlet Files";
            return;
        }
    }
    if(!outletFile.isOpen()) {
        if (!(outletFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "fail to read outlet Files";
            return;
        }
    }
    if(!perfFile.isOpen()) {
        if (!(perfFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "fail to read perform Files";
            return;
        }
    }

    if(!residualDataFile.isOpen() ){
        if(!(residualDataFile.open(QIODevice::ReadOnly | QIODevice::Text) )){
            qDebug() << "fail to read hist File";
            return;
        }
    }

}

void SimulationDataManager::closeFiles() {
    if (inletFile.isOpen())
        inletFile.close();
    if (outletFile.isOpen())
        outletFile.close();
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
    qDebug() << "Hey";
    if(!inletFile.isOpen()) {
        if (!(inletFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "fail to read inlet Files";
            return;
        }
    }
    if(!outletFile.isOpen()) {
        if (!(outletFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "fail to read outlet Files";
            return;
        }
    }
    if(!perfFile.isOpen()) {
        if (!(perfFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "fail to read perform Files";
            return;
        }
    }

    QTextStream inInlet(&inletFile);
    QTextStream inOutlet(&outletFile);
    QTextStream inPerf(&perfFile);

    inInlet.seek(monfilePositionTable[0]);
    inOutlet.seek(monfilePositionTable[1]);
    inPerf.seek(monfilePositionTable[2]);

    if (monfilePositionTable[0] == 0) {
        inInlet.readLine();
        inInlet.readLine();
        inOutlet.readLine();
        inOutlet.readLine();
        inPerf.readLine();
        inPerf.readLine();
    }

    QString lineInlet = inInlet.readLine();
    QString lineOutlet = inOutlet.readLine();
    QString linePerf = inPerf.readLine();

    if (lineInlet.isEmpty() || lineOutlet.isEmpty() || linePerf.isEmpty()) {
        qDebug() << "One or more data lines are empty";
        return;
    }

    QStringList valuesInlet = lineInlet.split(" ", Qt::SkipEmptyParts);
    if (!valuesInlet.isEmpty()) {
        iteration.append(valuesInlet[0].toInt());
        monitorVariableTable.inlet.pTotal.append(valuesInlet[1].toDouble());
        monitorVariableTable.inlet.tTotal.append(valuesInlet[2].toDouble());
        monitorVariableTable.inlet.vAxial.append(valuesInlet[3].toDouble());
        monitorVariableTable.inlet.vTheta.append(valuesInlet[4].toDouble());
        monitorVariableTable.inlet.pStatic.append(valuesInlet[5].toDouble());
        monitorVariableTable.inlet.mDot.append(valuesInlet[6].toDouble());
    }

    // Process outlet data
    QStringList valuesOutlet = lineOutlet.split(" ", Qt::SkipEmptyParts);
    if (!valuesOutlet.isEmpty()) {
        monitorVariableTable.outlet.pTotal.append(valuesOutlet[1].toDouble());
        monitorVariableTable.outlet.tTotal.append(valuesOutlet[2].toDouble());
        monitorVariableTable.outlet.vAxial.append(valuesOutlet[3].toDouble());
        monitorVariableTable.outlet.vTheta.append(valuesOutlet[4].toDouble());
        monitorVariableTable.outlet.pStatic.append(valuesOutlet[5].toDouble());
        monitorVariableTable.outlet.mDot.append(valuesOutlet[6].toDouble());
    }

    // Process performance data
    QStringList valuesPerf = linePerf.split(" ", Qt::SkipEmptyParts);
    if (!valuesPerf.isEmpty()) {
        monitorVariableTable.perform.pRatio.append(valuesPerf[1].toDouble());
        monitorVariableTable.perform.tRatio.append(valuesPerf[2].toDouble());
        monitorVariableTable.perform.efficiency.append(valuesPerf[3].toDouble());
        monitorVariableTable.perform.turning.append(valuesPerf[4].toDouble());
        monitorVariableTable.perform.qInlet.append(valuesPerf[5].toDouble());
        monitorVariableTable.perform.qOutlet.append(valuesPerf[6].toDouble());
    }

    // Update file positions
    monfilePositionTable[0] = inInlet.pos();
    monfilePositionTable[1] = inOutlet.pos();
    monfilePositionTable[2] = inPerf.pos();

    emit monitorDataUpdated(iteration.last(), monitorVariableTable);
}

void SimulationDataManager::clearData() {
    iteration.clear();
    monitorVariableTable.clearMonTable();
    initializePositions();
}
