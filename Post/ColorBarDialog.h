#pragma once

#include <QDialog>

#include <string>
#include <vector>

#include "vtkAesReader.h"

namespace Ui {
class ColorBarDialog;
}

class ColorBarDialog: public QDialog
{
    Q_OBJECT
    
public:
    ColorBarDialog(QWidget *parent = nullptr);
    ~ColorBarDialog();

    void setColorBarDialog(std::vector<vtkAesReader::FlowData> flows, int flowNumber);

private slots:
    void setParameters();
    void changeFlowNumber(int);

signals:
    void finishSetParameters(double, double, int, int);

private:
    Ui::ColorBarDialog *ui;
    std::vector<vtkAesReader::FlowData> flowInfo;
    double rangeM;
    double rangem;
    double m;
    double M;
    int colorNumber;
};