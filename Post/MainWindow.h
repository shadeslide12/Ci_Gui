#pragma once

#include <QMainWindow>

#include <string>

#include "vtkDisplayWindow.h"
#include "SelectBoundaryDialog.h"
#include "ColorBarDialog.h"
#include "IsoSurfaceDialog.h"
#include "CutplaneDialog.h"
#include "ScaleFactorDialog.h"
#include "ControlPanel.h"
#include "ConstHeightPlaneDialog.h"
#include "MeridionalPlaneDialog.h"
#include "ConstSettingDialog.h"
#include <vtkInteractorStyle.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCellPicker.h>
#include <vtkPointPicker.h>
#include <vtkPropPicker.h>
#include <vtkRendererCollection.h>
#include <vtkDataSetMapper.h>
#include <vtkPointLocator.h>
#include <vtkIdList.h>
#include <vtkPointData.h>
#include <vtkTextActor.h>
#include <vtkProperty2D.h>
#include <vtkTextProperty.h>
#include <vtkProperty.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkArrayCalculator.h>
#include <vtkGlyph2D.h>
#include <vtkGlyphSource2D.h>
#include <QVTKOpenGLNativeWidget.h>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct WindowState
    {

    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoadMesh_triggered();
    void on_actionUpdateFlow_triggered();
    void on_actionNewWindow_triggered();
    void on_actionOpenFile_triggered();
    void on_actionAddScalarBarActor_triggered();
    void on_actionAddAxisActor_triggered();
    void on_actionAddOutlineActor_triggered();
    void on_actionAddPointInformation_triggered();
    void on_ConstHeightCheckBox_toggled(bool trigger);

    void xoyViewTriggered();
    void xozViewTriggered();
    void yozViewTriggered();
    void xyzViewTriggered();

    void meshCheckBoxTriggered();
    void contourCheckBoxTriggered();
    void shadeCheckBoxTriggered();
    void edgeCheckBoxTriggered();
    void vectorCheckBoxTriggered();

    void transparancyCheckBoxTriggered();
    void lightingCheckBoxTriggered();

    void contourSettingButtonTriggered();
    void setColorBar(double,double,int,int);

    void vectorSettingButtonTriggered();
    void setVectorScaleFactor(double);
    void createNewVector(int *);

    void selectBoundaryButtonTriggeded();
    void showBoundaryActor(int,int,bool);
    void deleteSlice(int cutplaneIndex);

    void isoSurfaceCheckBoxTriggered();
    void isoSurfaceSettingButtonTriggered();
    void isoSurfaceChangeFlowNumber(int);
    void isoSurfaceValueChanged(double);
    void changeFloodNumber(int);
    
    void slicesCheckBoxTriggered();
    void slicesSettingButtonTriggered();
    void changeCutplane(double*,double*,int);
    void makeNewCutplane(double* origin, double* normal);
    void updateCutplaneColorMapping(double minValue, double maxValue, int numberOfColors, bool isBanded);
    void showCutplane(int, bool);

    void MeridionalButtonTriggered();
    void MeridionalCheckBoxTriggered();
    void ConstHeightButtonTriggered();
    void AddConstHeightPlane(double height);
    void ChangeMeridionalPlaneFlow(int flow);
    void ChangeConstHeightFlow(int flow);

    //* View Control 
    void on_Check_3Dview_toggled(bool checked);
    void on_Check_DoubleView_toggled(bool checked);
    void on_Check_Meri_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    vtkDisplayWindow *qtvtkWindow;
    SelectBoundaryDialog *selectBoundaryDialog = nullptr;
    ColorBarDialog *colorBarDialog = nullptr;
    IsoSurfaceDialog *isoSurfaceDialog = nullptr;
    CutplaneDialog *cutPlaneDialog = nullptr;
    ScaleFactorDialog *scaleFactorDialog = nullptr;

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> MeridionalrenderWindow= vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> Meridionalrenderer= vtkSmartPointer<vtkRenderer>::New();
    QVTKOpenGLNativeWidget *vtkWidget= new QVTKOpenGLNativeWidget(this);

    void InitializeMainWindow();
    void SetIcons();
    void SetvtkBox();
    void ResetScrollArea();
    void DisableScrollArea();


    //* test
    void CreateCutPreview();
    ControlPanel* controlPanel = nullptr;
};