#pragma once

#include <QObject>
#include <vtkBox.h>
#include <vtkClipPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkScalarBarWidget.h>
#include <vtkOutlineFilter.h>
#include <vtkContourFilter.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
//<<<<<<< Updated upstream
#include <vtkStreamTracer.h>
#include <vtkMaskPoints.h>
#include <vtkLineSource.h>
#include <vtkGlyph3D.h>
#include <vtkPointInterpolator.h>
//=======
//#include <vtkPointInterpolator.h>
//#include <yaml-cpp/yaml.h>
//>>>>>>> Stashed changes

#include "vtkAesReader.h"
#include <vtkPlaneSource.h>
#include <vtkLookupTable.h>
#include <vtkScalarBarActor.h>

class vtkDisplayWindow : public QObject
{
Q_OBJECT

public:
    struct BasicObject
    {
    public:
        vtkSmartPointer<vtkActor> meshActor;
        vtkSmartPointer<vtkActor> shadeActor;
        vtkSmartPointer<vtkActor> contourActor;
        vtkSmartPointer<vtkActor> edgeActor;
        vtkSmartPointer<vtkActor> velocityActor;
        vtkSmartPointer<vtkGlyph3D> glyph3D = nullptr;
    };

    struct AuxiliaryObject
    {
    public:
        vtkSmartPointer<vtkOrientationMarkerWidget> axisWidget;
        vtkSmartPointer<vtkScalarBarWidget> scalarBarWidget;
        std::vector<vtkSmartPointer<vtkActor>> outlineActors;
    };

    struct DerivedObject
    {
    public:
        vtkSmartPointer<vtkActor> isoSurfaceActor;
        vtkSmartPointer<vtkContourFilter> contourFilter;

        std::vector<vtkSmartPointer<vtkActor>> cutplaneActors;
        std::vector<vtkSmartPointer<vtkPlane>> cutplanes;
        std::vector<vtkSmartPointer<vtkCutter>> cutters;
        
        //* 所有cutplane共用的独立云图映射
        vtkSmartPointer<vtkLookupTable> cutplaneLookupTable;
        vtkSmartPointer<vtkScalarBarActor> cutplaneScalarBar;
        
        //* cutplane云图参数
        struct CutplaneColorMapping {
            double minValue;
            double maxValue;
            int numberOfColors;
            bool useCustomRange;
            
            CutplaneColorMapping() : minValue(0.0), maxValue(1.0), numberOfColors(256), useCustomRange(false) {}
        } cutplaneColorMapping;
    };

public:

    vtkDisplayWindow(QObject *parent = nullptr);
    ~vtkDisplayWindow();

    void ReadAesFile(std::string aesFileName);
    void UpdateFlow(std::string flowFileName);
    
    void VisiableBoundaryActor(int zoneNumber, int bNumber);
    void InVisiableBoundaryActor(int zoneNumber, int bNumber);
    void AddMeshActor();
    void RemoveMeshActor();
    void AddContourActor();
    void RemoveContourActor();
    void AddShadeActor();
    void RemoveShadeActor();
    void AddEdgeActor();
    void RemoveEdgeActor();
    void CreateVelocityActor(int vx = 1, int vy = 2, int vz = 3);
    void AddVelocityActor();
    void RemoveVelocityActor();

    void RemoveMeridianActor();
    void RemoveConstHeight();

    void ActivateAxiesWidget();
    void InActivateAxiesWidget();
    void ActivateScalarBarWidget();
    void InActivateScalarBarWidget();
    void SetScalarBar(double,double,int,int);
    void VisiableOutlineActor();
    void InVisiableOutlineActor();
    void SetVectorScaleFactor(double);

    void xoyViewRender();
    void xozViewRender();
    void yozViewRender();
    void xyzViewRender();

    void CreateIsoSurfaceActor();
    void AddIsoSurfaceActor();
    void RemoveIsoSurfaceActor();
    void ChangeFloodNumber(int);
    void IsoSurfaceChangeFlowNumber(int);
    void SetIsoSurfaceValue(double);

    void AddNewCutplane();
    void AddNewCutplane(double* origin, double* normal);
    void SetCutplane(int cutplaneNumber, double *origin, double *normal);
    void SetCutplaneColorMapping(double minValue, double maxValue, int numberOfColors,bool isBanded);
    void UpdateCutplaneColorMapping();
    DerivedObject::CutplaneColorMapping GetCutplaneColorMapping();
    void SetCutplaneColorScheme(int schemeIndex);  // 设置切片颜色方案
    void AddCutplaneActors();
    void RemoveCutplaneActors();
    void AddCutplane(int number);
    void RemoveCutplane(int number);    

    void SetActorTransparancy(bool);
    void SetActorLighting(bool);

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> GetRenderWindow(){return renderWindow;}
    std::vector<vtkAesReader::FlowData> GetFlows(){return aesReader.GetFlows();}
    std::vector<std::vector<vtkAesReader::Boundary>> GetBoundaryDatasets(){return aesReader.GetBoundarys();}
    DerivedObject GetDeriveds() {return deriveds;}
    std::vector<vtkSmartPointer<vtkPlane>> GetPlanes() {return deriveds.cutplanes;}
    int GetCurFlowNumber(){return curFlow;}
    double GetScaleFactor(){return boundarys[0][0].glyph3D->GetScaleFactor();}
    int *GetVectorComponentsNumber(){return aesReader.GetVectorCompontesNumber();}
    int GetIsoSurfaceFloodNumber(){return isoSurfaceFloodNumber;}
    int GetIsoSurfaceFlowNumber(){return isoSurfaceFlowNumber;}
    bool HasGrid(){return hasGrid;};
    bool HasVector(){return hasVector;}
    bool HasIsoSurface(){return hasIsoSurface;}
    bool HasCutplane(){return deriveds.cutplanes.size() != 0;}
    bool IsAxiesWidgetActive(){return auxiliarys.axisWidget->GetEnabled();}
    bool IsOutlineActorVisiable(){return auxiliarys.outlineActors[0]->GetVisibility();}
    bool IsScalarBarWidgetActive(){return auxiliarys.scalarBarWidget->GetEnabled();}

    double* GetModelBounds();

    std::vector<vtkSmartPointer<vtkActor>> CreateMeridionalPlane(double minRange, double maxRange);
    void CreateConstHeight(double height);
    std::vector<vtkSmartPointer<vtkActor>> ChangeMeridionalFlow(double minRange, double maxRange, int flowNumber);
    void ChangeConstHeightFlow(int flowNumber);
    std::vector<vtkSmartPointer<vtkActor>> MeridionalPlaneActor;
    std::vector<vtkSmartPointer<vtkActor>> ConstHeightPlaneActor;
    std::vector<vtkSmartPointer<vtkPolyData>> MeridionalPlane;
    std::vector<vtkSmartPointer<vtkContourFilter>> ConstHeightPlane;
private:
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;

    vtkAesReader aesReader;
    bool hasGrid = false;
    bool hasVector = false;
    bool hasIsoSurface = false;
    int curFlow = 0;
    int isoSurfaceFloodNumber = 0;
    int isoSurfaceFlowNumber = 0;
    std::vector<std::vector<BasicObject>> boundarys;
    AuxiliaryObject auxiliarys;
    DerivedObject deriveds;

    void VisualizeMeridonalPlane();
    void SetBackground();
    void CreateBasicObjects();
    void CreateAuxiliaryObject();
    void CreateAxisWidget();
    void CreateScalarBarWidget();
    void CreateOutlineActor();
    void setBackground();
    
public:
    void CreatePlanePreview(double value,int currenAxis);
    void HidePlanePreview();
    vtkSmartPointer<vtkPlaneSource> xPlaneSource;
    vtkSmartPointer<vtkActor> xPlaneActor;
    vtkSmartPointer<vtkPolyDataMapper> xPlaneMapper;

    //* add Control Cut Bar
    void ShowCutplaneScalarBar();
    void HideCutplaneScalarBar();
    void InitializeCutplaneScalarBar();
};
