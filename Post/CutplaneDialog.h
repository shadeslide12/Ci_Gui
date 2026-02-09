#pragma once

#include <QDialog>

#include <vector>
#include <vtkSmartPointer.h>
#include <vtkPlane.h>

namespace Ui {
class CutplaneDialog;
}

class CutplaneDialog: public QDialog
{
    Q_OBJECT
    
public:
    CutplaneDialog(QWidget *parent = nullptr);
    ~CutplaneDialog();

    void setCutplaneDialog(std::vector<vtkSmartPointer<vtkPlane>> planes);

private slots:
    void setParameters();
    void createSignal();
    void changeCutplaneNumber(int number);

signals:
    void finishSetParameters(double*, double*, int);
    void createNewCutplane();

private:
    Ui::CutplaneDialog *ui;

    std::vector<double*> origin;
    std::vector<double*> normal;
    double curOrigin[3];
    double curNormal[3];
    bool createFlag = false;
};