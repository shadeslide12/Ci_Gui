#pragma once

#include <QMainWindow>

#include <string>

#include "vtkDisplayWindow.h"
#include "SelectBoundaryDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PostMainWindow; }
QT_END_NAMESPACE

class PostMainWindow : public QMainWindow
{
    Q_OBJECT

    struct WindowState
    {
        bool hasMesh = false;
        bool hasVector = false;
        int flowNumber = 0;
        int isoSurfaceFlowNumber = 0;
        int floodNumber = 0;
        bool isAxisShow = true;
        bool isScalarBarShow = false;
        bool isOutlineShow = false;
        bool isTextActorShow = false;

        bool hasIsoSurface = false;
        bool hasSlices = false;
        bool hasStreamLine = false;
    };

public:
    PostMainWindow(QWidget *parent = nullptr);
    ~PostMainWindow();

private slots:
    void on_actionLoadMesh_triggered();
    void on_actionOpenFile_triggered();
    void on_actionAddAxisActor_triggered();
    void on_actionAddScalarBarActor_triggered();
    void on_actionAddOutlineActor_triggered();
    void on_actionAddPointInformation_triggered();
    void on_actionCalculatorFunction_triggered();

    void meshCheckBoxTriggered();
    void contourCheckBoxTriggered();
    void shadeCheckBoxTriggered();
    void edgeCheckBoxTriggered();
    void vectorCheckBoxTriggered();
    void contourSettingButtonTriggered();
    void selectBoundaryButtonTriggeded();

    void xoyViewTriggered();
    void xozViewTriggered();
    void yozViewTriggered();
    void xyzViewTriggered();

    void isoSurfaceCheckBoxTriggered();
    void isoSurfaceSettingButtonTriggered();
    void slicesCheckBoxTriggered();
    void slicesSettingButtonTriggered();
    void streamlineCheckBoxTriggered();

    void setColorBar(double,double,int,int);
    void changeFloodNumber(int);
    void isoSurfaceChangeFlowNumber(int);
    void isoSurfaceValueChanged(double);
    void showBoundaryActor(int,int,bool);
    void changeCutplane(double*,double*,int);
    void makeNewCutplane();
    void showCutplane(int, bool);

    void addNewParameter(QString, QString);

    void meridionalPlaneButtonTriggered();
    void addMeridionalPlane(int);
    void constHeightPlanneButtonTriggered();
    void addConstHeightPlane(int,double);
private:
    Ui::PostMainWindow *ui;
    vtkDisplayWindow qtvtkWindow;

    //initialize the PostMainWindow
    void initializeMainWindow();
    void setIcons();
    void setvtkBox();

    WindowState guiState;

    SelectBoundaryDialog *selectBoundaryDialog;
};