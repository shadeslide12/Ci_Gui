#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QVector>

struct Mon_Variable_Inlet{
    QVector<double> pTotal;
    QVector<double> tTotal;
    QVector<double> vAxial;
    QVector<double> vTheta;
    QVector<double> pStatic;
    QVector<double> mDot;
};

struct Mon_Variable_Outlet{
    QVector<double> pTotal;
    QVector<double> tTotal;
    QVector<double> vAxial;
    QVector<double> vTheta;
    QVector<double> pStatic;
    QVector<double> mDot;
};

struct Mon_Variable_Peform{
    QVector<double> pRatio;
    QVector<double> tRatio;
    QVector<double> efficiency;
    QVector<double> turning;
    QVector<double> qInlet;
    QVector<double> qOutlet;
};

struct MonitorVariableTable{
    Mon_Variable_Inlet inlet;
    Mon_Variable_Outlet outlet;
    Mon_Variable_Peform perform;
};


#endif