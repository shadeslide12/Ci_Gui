#include "vtkDisplayWindow.h"

using std::string; using std::vector;
#include "time.h"
using std::string; using std::vector; using std::set;

#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkFeatureEdges.h>
#include <vtkCamera.h>
#include <vtkMaskPoints.h>
#include <vtkGlyph3D.h>
#include <vtkGlyph2D.h>
#include <vtkGlyphSource2D.h>
#include <vtkArrowSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkLookupTable.h>
#include <vtkAxesActor.h>
#include <vtkCaptionActor2D.h>
#include <vtkTextProperty.h>
#include <vtkNamedColors.h>
#include <vtkArrayCalculator.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindowInteractor.h>
#include "vtkAesReader.h"
#include <vtkAppendFilter.h>

#include <vtkOpenGLState.h>
#include <vtkObject.h>

//=======
#include <vtkPointInterpolator.h>
#include <vtkGaussianKernel.h>
#include <vtkLinearKernel.h>
#include <vtkVoronoiKernel.h>
#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkRotationalExtrusionFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkIntersectionPolyDataFilter.h>
#include <vtkImplicitSelectionLoop.h>
#include <vtkClipPolyData.h>
#include <vtkLine.h>
#include <vtkProbeFilter.h>
#include <vtkImplicitPolyDataDistance.h>
#include <vtkClipDataSet.h>
#include <vtkUnstructuredGridGeometryFilter.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkPolyLine.h>
#include <vtkCleanPolyData.h>

vtkDisplayWindow::vtkDisplayWindow(QObject *parent):QObject(parent)
{
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    SetBackground();
}

vtkDisplayWindow::~vtkDisplayWindow(){}

void vtkDisplayWindow::ReadAesFile(string aesFileName)
{
    aesReader.ReadGrid(aesFileName);
    aesReader.UpdateFlow(aesFileName.erase(aesFileName.length()-8)+"flow.hdf");
    auto boundaryDatasets = aesReader.GetBoundarys();
    CreateBasicObjects();
    CreateAuxiliaryObject();
    renderer->ResetCamera();
    hasGrid = true;
}

void vtkDisplayWindow::UpdateFlow(string flowFileName)
{
    aesReader.UpdateFlow(flowFileName);
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            y.contourActor->GetMapper()->SetScalarRange(aesReader.GetFlows()[0].range);
            y.contourActor->GetMapper()->SetLookupTable(aesReader.GetFlows()[0].scalarBar->GetLookupTable());
        }
    }
    auxiliarys.scalarBarWidget->SetScalarBarActor(aesReader.GetFlows()[0].scalarBar);
    if (hasVector)
    {
        hasVector = false;
        RemoveVelocityActor();
    }
    curFlow = 0;
}

void vtkDisplayWindow::CreateBasicObjects()
{
    auto boundaryDatasets = aesReader.GetBoundarys();
    for (auto &x : boundaryDatasets)
    {
        vector<BasicObject> zoneBoundarys;
        for (auto &y : x)
        {
            vtkSmartPointer<vtkDataSetMapper> meshMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            vtkSmartPointer<vtkDataSetMapper> shadeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            vtkSmartPointer<vtkDataSetMapper> contourMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            vtkSmartPointer<vtkDataSetMapper> edgeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            meshMapper->SetInputData(y.dataset);
            meshMapper->ScalarVisibilityOff();
            shadeMapper->SetInputData(y.dataset);
            shadeMapper->ScalarVisibilityOff();
            contourMapper->SetInputData(y.dataset);
            contourMapper->ScalarVisibilityOn();
            contourMapper->SetInterpolateScalarsBeforeMapping(true);
            auto flow = aesReader.GetFlows().front();
            contourMapper->SetScalarRange(flow.range);
            contourMapper->GetInput()->GetPointData()->SetActiveScalars(flow.name.c_str());
            contourMapper->SetLookupTable(flow.scalarBar->GetLookupTable());
            vtkSmartPointer<vtkDataSetSurfaceFilter> dsSurfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
            dsSurfaceFilter->SetInputData(y.dataset);
            vtkSmartPointer<vtkFeatureEdges> edgeFilter = vtkSmartPointer<vtkFeatureEdges>::New();
            edgeFilter->SetInputConnection(dsSurfaceFilter->GetOutputPort());
            edgeFilter->BoundaryEdgesOn();
            edgeFilter->NonManifoldEdgesOff();
            edgeFilter->ManifoldEdgesOff();
            edgeFilter->SetFeatureAngle(100);
            edgeMapper->SetInputConnection(edgeFilter->GetOutputPort());
            edgeMapper->ScalarVisibilityOff();
            BasicObject boundary;
            boundary.meshActor = vtkSmartPointer<vtkActor>::New();
            boundary.shadeActor = vtkSmartPointer<vtkActor>::New();
            boundary.contourActor = vtkSmartPointer<vtkActor>::New();
            boundary.edgeActor = vtkSmartPointer<vtkActor>::New();
            boundary.velocityActor = vtkSmartPointer<vtkActor>::New();
            boundary.meshActor->SetMapper(meshMapper);
            boundary.meshActor->GetProperty()->SetRepresentationToWireframe();
            boundary.meshActor->GetProperty()->SetColor(0,0,0);
            boundary.meshActor->SetVisibility(true);
            boundary.shadeActor->SetMapper(shadeMapper);
            boundary.shadeActor->SetVisibility(true);
            boundary.shadeActor->GetProperty()->SetColor(0.83,0.83,0.83);
            boundary.contourActor->SetMapper(contourMapper);
            boundary.contourActor->SetVisibility(true);
            boundary.edgeActor->SetMapper(edgeMapper);
            boundary.edgeActor->SetVisibility(true);
            boundary.edgeActor->GetProperty()->SetColor(0,0,0); 
            boundary.edgeActor->GetProperty()->SetLineWidth(5.0);
            zoneBoundarys.emplace_back(boundary);
            renderer->AddActor(boundary.contourActor);
        }
        boundarys.emplace_back(zoneBoundarys);
    }
}

void vtkDisplayWindow::CreateAuxiliaryObject()
{
    CreateAxisWidget();
    CreateScalarBarWidget();
    CreateOutlineActor();
}

void vtkDisplayWindow::CreateAxisWidget()
{
    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
    axes->SetPosition(0,0,0);
    axes->SetTotalLength(3,3,3);
    axes->SetShaftType(0);
    axes->SetCylinderRadius(0.05);

    axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->ItalicOff();
    axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->BoldOff();
    axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(0, 0, 0);
    axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->ShadowOff();
    axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetFontSize(16);

    axes->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ItalicOff();
    axes->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->BoldOff();
    axes->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(0, 0, 0);
    axes->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShadowOff();
    axes->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->SetFontSize(16);

    axes->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ItalicOff();
    axes->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->BoldOff();
    axes->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(0, 0, 0);
    axes->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShadowOff();
    axes->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->SetFontSize(16);

    auxiliarys.axisWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    vtkSmartPointer<vtkNamedColors> color = vtkSmartPointer<vtkNamedColors>::New();
    double rgb[3];
    color->GetColorRGB("Carrot", rgb);
    auxiliarys.axisWidget->SetOutlineColor(rgb[0],rgb[1],rgb[2]);
    auxiliarys.axisWidget->SetOrientationMarker(axes);
    auxiliarys.axisWidget->SetViewport(0.0, 0.0, 0.2, 0.2);
    auxiliarys.axisWidget->SetInteractor(renderWindow->GetInteractor());
    auxiliarys.axisWidget->SetEnabled(1);
    auxiliarys.axisWidget->InteractiveOff();
}

void vtkDisplayWindow::CreateScalarBarWidget()
{
    auxiliarys.scalarBarWidget = vtkSmartPointer<vtkScalarBarWidget>::New();
    auxiliarys.scalarBarWidget->SetScalarBarActor(aesReader.GetFlows()[0].scalarBar);
    auxiliarys.scalarBarWidget->SetInteractor(renderWindow->GetInteractor());
    auxiliarys.scalarBarWidget->SetEnabled(1);
}

void vtkDisplayWindow::CreateOutlineActor()
{
    auto zoneGrids = aesReader.GetZoneGrids();
    for (auto &x : zoneGrids)
    {
        vtkSmartPointer<vtkOutlineFilter> filter = vtkSmartPointer<vtkOutlineFilter>::New();
        filter->SetInputData(x.dataset);
        filter->Update();
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(filter->GetOutput());
        vtkSmartPointer<vtkActor> outline = vtkSmartPointer<vtkActor>::New();
        outline->SetMapper(mapper);
        outline->GetProperty()->SetColor(0,0,0);
        auxiliarys.outlineActors.emplace_back(outline);
        outline->SetVisibility(true);
        renderer->AddActor(outline);
    }
}

void vtkDisplayWindow::VisiableBoundaryActor(int zNumber, int bNumber)
{
    boundarys[zNumber][bNumber].meshActor->SetVisibility(true);
    boundarys[zNumber][bNumber].shadeActor->SetVisibility(true);
    boundarys[zNumber][bNumber].contourActor->SetVisibility(true);
    boundarys[zNumber][bNumber].edgeActor->SetVisibility(true);
    boundarys[zNumber][bNumber].velocityActor->SetVisibility(true);
}

void vtkDisplayWindow::InVisiableBoundaryActor(int zNumber, int bNumber)
{
    boundarys[zNumber][bNumber].meshActor->SetVisibility(false);
    boundarys[zNumber][bNumber].shadeActor->SetVisibility(false);
    boundarys[zNumber][bNumber].contourActor->SetVisibility(false);
    boundarys[zNumber][bNumber].edgeActor->SetVisibility(false);
    boundarys[zNumber][bNumber].velocityActor->SetVisibility(false);
}

void vtkDisplayWindow::AddMeshActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->AddActor(y.meshActor);
        }
    }
}

void vtkDisplayWindow::RemoveMeshActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->RemoveActor(y.meshActor);
        }
    }
}

void vtkDisplayWindow::AddContourActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->AddActor(y.contourActor);
        }
    }
    ActivateScalarBarWidget();
}

void vtkDisplayWindow::RemoveContourActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->RemoveActor(y.contourActor);
        }
    }
    InActivateScalarBarWidget();
}

void vtkDisplayWindow::AddShadeActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->AddActor(y.shadeActor);
        }
    }
}

void vtkDisplayWindow::RemoveMeridianActor()
{
    for(int i = 0;i < MeridionalPlaneActor.size();i++)
    {
        renderer->RemoveActor(MeridionalPlaneActor[i]);
    }
}

void vtkDisplayWindow::RemoveConstHeight()
{
    for(int i = 0;i < ConstHeightPlaneActor.size();i++)
    {
        renderer->RemoveActor(ConstHeightPlaneActor[i]);
    }
}

void vtkDisplayWindow::RemoveShadeActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->RemoveActor(y.shadeActor);
        }
    }
}

void vtkDisplayWindow::AddEdgeActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->AddActor(y.edgeActor);
        }
    }
}

void vtkDisplayWindow::RemoveEdgeActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->RemoveActor(y.edgeActor);
        }
    }
}

void vtkDisplayWindow::CreateVelocityActor(int vx, int vy, int vz)
{
    aesReader.CreateVector(vx,vy,vz);
    cout << "begin to create velocity actor." << endl;
    for (int i = 0; i < boundarys.size(); i++)
    {
        for (int j = 0; j < boundarys[i].size(); j++)
        {
            vtkNew<vtkMaskPoints> mask;
            mask->SetOnRatio(1);
            mask->SetRandomMode(true);
            mask->SetInputData(aesReader.GetBoundarys()[i][j].dataset);
            mask->Update();

            vtkSmartPointer<vtkDataSetMapper> velocityMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            auto &glyph3D = boundarys[i][j].glyph3D;
            if (glyph3D == nullptr) 
            {
                glyph3D = vtkSmartPointer<vtkGlyph3D>::New();
                vtkSmartPointer<vtkArrowSource> arrow = vtkSmartPointer<vtkArrowSource>::New();
                arrow->Update();
                glyph3D->SetSourceData(arrow->GetOutput());
                
                glyph3D->SetScaleModeToScaleByVector();
                glyph3D->SetVectorModeToUseVector();
                glyph3D->SetColorMode(1);
            }
                glyph3D->SetInputData(mask->GetOutput());
                glyph3D->SetScaleFactor(aesReader.GetScaleFactor());

            glyph3D->Update();
            velocityMapper->SetInputData(glyph3D->GetOutput());
            velocityMapper->ScalarVisibilityOff();
            velocityMapper->Update();
            boundarys[i][j].velocityActor->SetMapper(velocityMapper);
            boundarys[i][j].velocityActor->GetProperty()->SetColor(0,0,0);
        }
    }
    cout << "end create velocity actor." << endl;
    hasVector = true;
}

void vtkDisplayWindow::AddVelocityActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->AddActor(y.velocityActor);
        }
    }
}

void vtkDisplayWindow::RemoveVelocityActor()
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            renderer->RemoveActor(y.velocityActor);
        }
    }
}

void vtkDisplayWindow::ActivateAxiesWidget()
{
    auxiliarys.axisWidget->SetEnabled(1);
}

void vtkDisplayWindow::InActivateAxiesWidget()
{
    auxiliarys.axisWidget->SetEnabled(0);
}

void vtkDisplayWindow::ActivateScalarBarWidget()
{
    auxiliarys.scalarBarWidget->SetEnabled(1);
}

void vtkDisplayWindow::InActivateScalarBarWidget()
{
    auxiliarys.scalarBarWidget->SetEnabled(0);
}

void vtkDisplayWindow::SetScalarBar(double m, double M, int number, int flowNumber)
{
    aesReader.ChangeScalarBar(m,M,number,flowNumber);
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            y.contourActor->GetMapper()->GetInput()->GetPointData()->SetActiveScalars(aesReader.GetFlows()[flowNumber].name.c_str());
            y.contourActor->GetMapper()->SetScalarRange(m,M);
            y.contourActor->GetMapper()->SetLookupTable(aesReader.GetFlows()[flowNumber].scalarBar->GetLookupTable());
            y.contourActor->GetMapper()->Update();
        }
    }
    
    auxiliarys.scalarBarWidget->SetScalarBarActor(aesReader.GetFlows()[flowNumber].scalarBar);
    curFlow = flowNumber;
}

void vtkDisplayWindow::VisiableOutlineActor()
{
    for (auto &x : auxiliarys.outlineActors)
    {
        x->SetVisibility(true);
    }
}

void vtkDisplayWindow::InVisiableOutlineActor()
{
    for (auto &x : auxiliarys.outlineActors)
    {
        x->SetVisibility(false);
    }
}

void vtkDisplayWindow::SetVectorScaleFactor(double scale)
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            y.glyph3D->SetScaleFactor(scale);
            y.glyph3D->Update();
        }
    }
}

void vtkDisplayWindow::xoyViewRender()
{
    auto camera = renderer->GetActiveCamera();
    camera->SetFocalPoint(0,0,0);
    camera->SetPosition(0,0,1);
    camera->SetViewUp(0,1,0);
    renderer->ResetCamera();
}

void vtkDisplayWindow::xozViewRender()
{
    auto camera = renderer->GetActiveCamera();
    camera->SetFocalPoint(0,0,0);
    camera->SetPosition(0,-1,0);
    camera->SetViewUp(0,0,1);
    renderer->ResetCamera();
}

void vtkDisplayWindow::yozViewRender()
{
    auto camera = renderer->GetActiveCamera();
    camera->SetFocalPoint(0,0,0);
    camera->SetPosition(1,0,0);
    camera->SetViewUp(0,0,1);
    renderer->ResetCamera();    
}

void vtkDisplayWindow::xyzViewRender()
{
    auto camera = renderer->GetActiveCamera();
    camera->SetFocalPoint(0,0,0);
    camera->SetPosition(1,1,1);
    camera->SetViewUp(0,0,1);
    renderer->ResetCamera();
}

void vtkDisplayWindow::CreateIsoSurfaceActor()
{
    deriveds.contourFilter = vtkSmartPointer<vtkContourFilter>::New();
    deriveds.contourFilter->SetInputData(aesReader.GetTotalGrid());
    auto range = aesReader.GetFlows()[0].range;
    deriveds.contourFilter->SetValue(0, range[0] + (range[1] - range[0]) * 0.5);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(deriveds.contourFilter->GetOutputPort());
    mapper->SetLookupTable(aesReader.GetFlows()[0].scalarBar->GetLookupTable());
    mapper->SetScalarRange(aesReader.GetFlows()[0].scalarBar->GetLookupTable()->GetRange());
    deriveds.isoSurfaceActor = vtkSmartPointer<vtkActor>::New();
    deriveds.isoSurfaceActor->SetMapper(mapper);
    renderer->AddActor(deriveds.isoSurfaceActor);
    deriveds.isoSurfaceActor->VisibilityOff();

    hasIsoSurface = true;
}

void vtkDisplayWindow::AddIsoSurfaceActor()
{
    deriveds.isoSurfaceActor->VisibilityOn();
}

void vtkDisplayWindow::RemoveIsoSurfaceActor()
{
    deriveds.isoSurfaceActor->VisibilityOff();
}

void vtkDisplayWindow::ChangeFloodNumber(int floodNumber)
{
    deriveds.isoSurfaceActor->GetMapper()->SetLookupTable(aesReader.GetFlows()[floodNumber].scalarBar->GetLookupTable());
    deriveds.isoSurfaceActor->GetMapper()->SetScalarRange(aesReader.GetFlows()[floodNumber].scalarBar->GetLookupTable()->GetRange());
    deriveds.isoSurfaceActor->GetMapper()->GetInput()->GetPointData()->SetActiveScalars(aesReader.GetFlows()[floodNumber].name.c_str());
    isoSurfaceFloodNumber = floodNumber;
}

void vtkDisplayWindow::IsoSurfaceChangeFlowNumber(int flowNumber)
{
    aesReader.GetTotalGrid()->GetPointData()->SetActiveScalars(aesReader.GetFlows()[flowNumber].name.c_str());
    auto range = aesReader.GetFlows()[flowNumber].range;
    deriveds.contourFilter->SetValue(0, range[0] + (range[1]-range[0]) * 0.5);
    deriveds.contourFilter->Update();
    isoSurfaceFlowNumber = flowNumber;
}

void vtkDisplayWindow::SetIsoSurfaceValue(double value)
{
    deriveds.contourFilter->SetValue(0, value);
    deriveds.contourFilter->Update();
}

void vtkDisplayWindow::AddNewCutplane() {
    AddNewCutplane(nullptr,nullptr);
}

void vtkDisplayWindow::AddNewCutplane(double* origin, double* normal)
{
    auto totalMesh = aesReader.GetTotalGrid();
    vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
    
    // 如果提供了参数，使用提供的参数；否则使用默认值
    if (origin && normal) {
        plane->SetOrigin(origin);
        plane->SetNormal(normal);
        std::cout << "[Debug] Creating cutplane with custom parameters: origin(" 
                  << origin[0] << ", " << origin[1] << ", " << origin[2] 
                  << ") normal(" << normal[0] << ", " << normal[1] << ", " << normal[2] << ")" << std::endl;
    } else {
        plane->SetOrigin(0,0,0);
        plane->SetNormal(1,0,0);
        std::cout << "[Debug] Creating cutplane with default parameters" << std::endl;
    }
    
    cutter->SetInputData(totalMesh);
    cutter->SetCutFunction(plane);
    
    // 如果是第一个cutplane，创建共享的LookupTable
    if (deriveds.cutplanes.empty()) {
        // 添加边界检查，防止程序卡住
        auto flows = aesReader.GetFlows();
        if (flows.empty() || curFlow < 0 || curFlow >= flows.size()) {
            std::cerr << "[Error] Invalid flow data or curFlow index: " << curFlow 
                      << ", flows size: " << flows.size() << std::endl;
            return;
        }
        
        deriveds.cutplaneLookupTable = vtkSmartPointer<vtkLookupTable>::New();
        deriveds.cutplaneLookupTable->SetNumberOfTableValues(10);
        deriveds.cutplaneLookupTable->SetRange(flows[curFlow].range);
        deriveds.cutplaneLookupTable->SetHueRange(0.6667, 0.0);  // 蓝到红渐变，与主模型一致
        deriveds.cutplaneLookupTable->Build();
        
        // 初始化颜色映射参数
        deriveds.cutplaneColorMapping.minValue = flows[curFlow].range[0];
        deriveds.cutplaneColorMapping.maxValue = flows[curFlow].range[1];
        deriveds.cutplaneColorMapping.numberOfColors = 256;
        deriveds.cutplaneColorMapping.useCustomRange = false;
        
        std::cout << "[Debug] Created shared cutplane LookupTable with range: [" 
                  << deriveds.cutplaneColorMapping.minValue << ", " 
                  << deriveds.cutplaneColorMapping.maxValue << "]" << std::endl;
    }
    
    // 创建mapper并使用共享的LookupTable
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(cutter->GetOutputPort());
    mapper->SetLookupTable(deriveds.cutplaneLookupTable);
    mapper->SetScalarRange(deriveds.cutplaneLookupTable->GetRange());
    
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    
    // 添加到容器
    deriveds.cutplanes.emplace_back(plane);
    deriveds.cutters.emplace_back(cutter);
    deriveds.cutplaneActors.emplace_back(actor);
    
    renderer->AddActor(deriveds.cutplaneActors.back());
    
    std::cout << "[Debug] Added cutplane " << (deriveds.cutplanes.size() - 1) 
              << ", total cutplanes: " << deriveds.cutplanes.size() << std::endl;
}

void vtkDisplayWindow::SetCutplane(int cutplaneNumber, double *origin, double *normal)
{
    deriveds.cutplanes[cutplaneNumber]->SetOrigin(origin);
    deriveds.cutplanes[cutplaneNumber]->SetNormal(normal);
    deriveds.cutters[cutplaneNumber]->Update();
}

void vtkDisplayWindow::AddCutplaneActors()
{
    for (auto &x : deriveds.cutplaneActors)
    {
        renderer->AddActor(x);
    }
}

void vtkDisplayWindow::RemoveCutplaneActors()
{
    for (auto &x : deriveds.cutplaneActors)
    {
        renderer->RemoveActor(x);
    }
}

void vtkDisplayWindow::AddCutplane(int number)
{
    deriveds.cutplaneActors[number]->VisibilityOn();
}

void vtkDisplayWindow::RemoveCutplane(int number)
{
    deriveds.cutplaneActors[number]->VisibilityOff();
}

void vtkDisplayWindow::SetActorTransparancy(double opacity)
{
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            y.contourActor->GetProperty()->SetOpacity(opacity);
            y.shadeActor->GetProperty()->SetOpacity(opacity);
        }
    }
    std::cout<< "[Debug] SetActorTransparancy "<<std::endl;
}

void vtkDisplayWindow::SetActorLighting(bool flag)
{
    if (flag)
    {
        for (auto &x : boundarys) {
            for (auto &y: x) {
                y.contourActor->GetProperty()->SetAmbient(0);
                y.shadeActor->GetProperty()->SetAmbient(0);
            }
        }
    }
    else
    {
        for (auto &x : boundarys)
        {
            for (auto &y : x)
            {
                y.contourActor->GetProperty()->SetAmbient(1);  
                y.shadeActor->GetProperty()->SetAmbient(1);
            }
        }
    }
}


void vtkDisplayWindow::SetBackground()
{
    renderer->SetUseDepthPeeling(1);
    renderer->SetOcclusionRatio(0.1);
    renderer->SetMaximumNumberOfPeels(100);

    // renderWindow->SetMultiSamples(1);
    // renderWindow->SetAlphaBitPlanes(1);

    renderer->SetBackground(1.0,1.0,1.0);
    renderer->SetBackground2(0.529, 0.8078, 0.92157);
    renderer->SetGradientBackground(true);

}

std::vector<vtkSmartPointer<vtkActor>> vtkDisplayWindow::CreateMeridionalPlane(double minRange, double maxRange)
{

  if(MeridionalPlaneActor.empty())
  {
    auto BndGrid = aesReader.GetBoundarys();
    auto Flow = aesReader.GetFlows();
    vtkSmartPointer<vtkUnstructuredGrid> md = vtkSmartPointer<vtkUnstructuredGrid>::New();

    for(int zone = 0; zone < BndGrid.size(); zone++) {
      for (int i = 0; i < BndGrid[zone].size(); i++) {
        if (BndGrid[zone][i].type == 9) {
          vtkSmartPointer<vtkAppendFilter> appendFilter = vtkSmartPointer<vtkAppendFilter>::New();
          appendFilter->AddInputData(md);
          appendFilter->AddInputData(BndGrid[zone][i].dataset);
          appendFilter->Update();

          md->DeepCopy(appendFilter->GetOutput());
          break;
        }
      }
    }
    vtkSmartPointer<vtkPoints> planepts = vtkSmartPointer<vtkPoints>::New();
    for (int m = 0; m < md->GetNumberOfPoints(); m++) {
      double y = md->GetPoint(m)[1];
      double z = md->GetPoint(m)[2];
      double r = sqrt(y * y + z * z);
      planepts->InsertNextPoint(md->GetPoint(m)[0], r * cos(0), r * sin(0));
    }

  vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

  // 设置点
  polyData->SetPoints(planepts);

  polyData->SetPolys(md->GetCells());

      MeridionalPlane.emplace_back(polyData);

      ChangeMeridionalFlow(Flow[0].range[0], Flow[0].range[1], curFlow);
      return MeridionalPlaneActor;
    }
}
std::vector<vtkSmartPointer<vtkActor>> vtkDisplayWindow::ChangeMeridionalFlow(double minRange, double maxRange, int flowNumber)
{
    RemoveMeridianActor();
    MeridionalPlaneActor.clear();
    auto Mesh = aesReader.GetZoneGrids();
    auto Flow = aesReader.GetFlows();
    auto TotalMesh = aesReader.GetTotalGrid();
    vtkSmartPointer<vtkDoubleArray> scalar = vtkSmartPointer<vtkDoubleArray>::New();
    int start = 0;
//    for(int i = 0; i < zone; i++)
//    {
//        start += TotalMesh->GetNumberOfPoints();
//    }
    vtkSmartPointer<vtkPolyData> ply = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    for(int i = 0; i < TotalMesh->GetNumberOfPoints();i++){
        double ny = TotalMesh->GetPoint(i)[1];
        double nz = TotalMesh->GetPoint(i)[2];
        double nr = sqrt(ny * ny + nz * nz);
        pts->InsertNextPoint(TotalMesh->GetPoint(i)[0], nr * cos(0), nr * sin(0));
    }
    ply->SetPoints(pts);
    for(int i = 0; i < TotalMesh->GetNumberOfPoints();i++)
    {
        scalar->InsertNextValue(Flow[flowNumber].datas[i]);
    }

    ply->GetPointData()->SetScalars(scalar);
    vtkSmartPointer<vtkPointInterpolator> inter = vtkSmartPointer<vtkPointInterpolator>::New();

    if (MeridionalPlane.empty()) {
        std::cout << "[DEBug] MeridionalPlane is empty "<< std::endl;
        return {};
    }

    inter->SetInputData(MeridionalPlane[0]);
    inter->SetSourceData(ply);
//    vtkSmartPointer<vtkGaussianKernel> kernel = vtkSmartPointer<vtkGaussianKernel>::New();
    vtkSmartPointer<vtkVoronoiKernel> kernel = vtkSmartPointer<vtkVoronoiKernel>::New();
//    kernel->SetRadius(0.001);

    inter->SetKernel(kernel);
    vtkSmartPointer<vtkPolyDataMapper> mapper =vtkSmartPointer<vtkPolyDataMapper>::New();

    mapper->SetInputConnection(inter->GetOutputPort());
    mapper->SetLookupTable(Flow[flowNumber].scalarBar->GetLookupTable());
    mapper->SetScalarRange(minRange,maxRange);
    mapper->Update();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    std::cout << "[Debug] Mer 6 "<< std::endl;

    MeridionalPlaneActor.emplace_back(actor);
//    renderer->AddActor(actor);
//    renderer->ResetCamera();

    return MeridionalPlaneActor;

}
void vtkDisplayWindow::VisualizeMeridonalPlane()
{
    if(MeridionalPlaneActor[0]->GetVisibility() == true)
    {
        for(int i = 0; i < MeridionalPlaneActor.size(); i++)
        {
            MeridionalPlaneActor[i]->VisibilityOff();
        }
    }
    else{
        for(int i = 0; i < MeridionalPlaneActor.size(); i++)
        {
            MeridionalPlaneActor[i]->VisibilityOn();
        }
    }

}

void vtkDisplayWindow::CreateConstHeight(double height)
{
//    if(aesReader.node_radius.empty())
//    {
//        std::cout << "can not use this function" << std::endl;
//        return;
//    }
    auto Mesh = aesReader.GetZoneGrids();
    auto Flow = aesReader.GetFlows();
    auto BndGrid = aesReader.GetBoundarys();
    auto TotalMeshes = aesReader.GetTotalGrid();
    vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
    contour->SetInputData(TotalMeshes);
    TotalMeshes->GetPointData()->SetActiveScalars("radius");
    contour->SetValue(0,height);
    contour->Update();
//    contour->GetOutput()->GetPointData()->GetArray(curFlow);
    contour->GetOutput()->GetPointData()->SetActiveScalars(Flow[curFlow].name.c_str());
    ConstHeightPlane.emplace_back(contour);
    vtkSmartPointer<vtkPolyData> polydata;
//    contour->SetArrayComponent(curFlow);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(contour->GetOutputPort());
    mapper->SetScalarRange(Flow[curFlow].range);
    mapper->SetLookupTable(Flow[curFlow].scalarBar->GetLookupTable());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    ConstHeightPlaneActor.emplace_back(actor);
    renderer->AddActor(actor);
}

void vtkDisplayWindow::ChangeConstHeightFlow(int flowNumber)
{
    auto Flow = aesReader.GetFlows();
    for(int i = 0;i < ConstHeightPlaneActor.size();i++)
    {
        renderer->RemoveActor(ConstHeightPlaneActor[i]);
    }
    ConstHeightPlaneActor.clear();
    for(int i = 0; i < ConstHeightPlane.size(); i++)
    {
        ConstHeightPlane[i]->GetOutput()->GetPointData()->SetActiveScalars(Flow[flowNumber].name.c_str());
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(ConstHeightPlane[i]->GetOutputPort());
        mapper->SetScalarRange(Flow[flowNumber].range);
        mapper->SetLookupTable(Flow[flowNumber].scalarBar->GetLookupTable());
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        ConstHeightPlaneActor.emplace_back(actor);
        renderer->AddActor(actor);
    }
}

vtkSmartPointer<vtkPolyData> ConvertUnstructuredGridToPolyData(vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid)
{
  vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

  // 设置点
  polyData->SetPoints(unstructuredGrid->GetPoints());

  // 用于存储单元
  vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();

  for (vtkIdType i = 0; i < unstructuredGrid->GetNumberOfCells(); ++i)
  {
    vtkSmartPointer<vtkCell> cell = unstructuredGrid->GetCell(i);

    if (cell->GetCellType() == VTK_TRIANGLE || cell->GetCellType() == VTK_QUAD)
    {
      polys->InsertNextCell(cell);
    }
  }

  polyData->SetPolys(polys);

  return polyData;
}

double* vtkDisplayWindow::GetModelBounds()
{
    if (!hasGrid)
    {
        std::cout << "没有加载网格数据，无法获取边界值" << std::endl;
        return nullptr;
    }
    
    // 获取总网格数据的边界值
    return aesReader.GetTotalGrid()->GetBounds();
    
    // 返回的数组包含6个值：[xmin, xmax, ymin, ymax, zmin, zmax]
}

void vtkDisplayWindow::CreatePlanePreview(double value,int currenAxis)
{
    // 获取模型的边界框
    std::cout << "[Debug] Preview Location actual value: " << value << std::endl;

    double bounds[6];
    if (aesReader.GetTotalGrid())
    {
        aesReader.GetTotalGrid()->GetBounds(bounds);
        std::cout << "边界框: [" << bounds[0] << ", " << bounds[1] << ", " 
                  << bounds[2] << ", " << bounds[3] << ", " 
                  << bounds[4] << ", " << bounds[5] << "]" << std::endl;
    }
    else
    {
        std::cout << "未找到模型网格！" << std::endl;
        return;  // 没有模型就不创建平面
    }
    
    // 创建一个平面 - 直接使用边界框中间的x位置
    double position = value;
    double xRange = bounds[1] - bounds[0];
    double yRange = bounds[3] - bounds[2];
    double zRange = bounds[5] - bounds[4];

    if (!xPlaneSource) {
        xPlaneSource = vtkSmartPointer<vtkPlaneSource>::New();
    }

    switch ( currenAxis) {
        case 0: // X轴 - YZ平面
            xPlaneSource->SetCenter(position, 0.0, 0.0);
            xPlaneSource->SetNormal(1.0, 0.0, 0.0);
            xPlaneSource->SetOrigin(position, bounds[2] - 0.1*yRange, bounds[4] - 0.1*zRange);
            xPlaneSource->SetPoint1(position, bounds[3] + 0.1*yRange, bounds[4] - 0.1*zRange);
            xPlaneSource->SetPoint2(position, bounds[2] - 0.1*yRange, bounds[5] + 0.1*zRange);
            break;

        case 1: // Y轴 - XZ平面
            xPlaneSource->SetCenter(0.0, position, 0.0);
            xPlaneSource->SetNormal(0.0, 1.0, 0.0);
            xPlaneSource->SetOrigin(bounds[0] - 0.1*xRange, position, bounds[4] - 0.1*zRange);
            xPlaneSource->SetPoint1(bounds[1] + 0.1*xRange, position, bounds[4] - 0.1*zRange);
            xPlaneSource->SetPoint2(bounds[0] - 0.1*xRange, position, bounds[5] + 0.1*zRange);
            break;

        case 2: // Z轴 - XY平面
            xPlaneSource->SetCenter(0.0, 0.0, position);
            xPlaneSource->SetNormal(0.0, 0.0, 1.0);
            xPlaneSource->SetOrigin(bounds[0] - 0.1*xRange, bounds[2] - 0.1*yRange, position);
            xPlaneSource->SetPoint1(bounds[1] + 0.1*xRange, bounds[2] - 0.1*yRange, position);
            xPlaneSource->SetPoint2(bounds[0] - 0.1*xRange, bounds[3] + 0.1*yRange, position);
            break;
    }
    
    // 创建映射器和Actor - 直接使用平面而不是裁剪的结果
    if (!xPlaneMapper) {
        xPlaneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    }
    xPlaneMapper->SetInputConnection(xPlaneSource->GetOutputPort());
    xPlaneMapper->SetInputConnection(xPlaneSource->GetOutputPort());
    
    if (!xPlaneActor) {
        xPlaneActor = vtkSmartPointer<vtkActor>::New();
    }
    xPlaneActor->SetMapper(xPlaneMapper);

    xPlaneActor->GetProperty()->SetColor(0.0, 0.5, 1.0);
    // xPlaneActor->GetProperty()->SetOpacity(0.3);

    renderer->AddActor(xPlaneActor);
    renderWindow->Render();
}

void vtkDisplayWindow::HidePlanePreview()
{
    // 如果存在预览平面Actor，则从渲染器中移除
    if (xPlaneActor)
    {
        std::cout << "隐藏预览平面" << std::endl;
        renderer->RemoveActor(xPlaneActor);
        renderWindow->Render();
    }
}

void vtkDisplayWindow::SetCutplaneColorMapping(double minValue, double maxValue, int numberOfColors,bool isBanded)
{
    if (!deriveds.cutplaneLookupTable) {
        std::cerr << "No cutplane LookupTable exists" << std::endl;
        return;
    }
    
    // 更新颜色映射参数
    deriveds.cutplaneColorMapping.minValue = minValue;
    deriveds.cutplaneColorMapping.maxValue = maxValue;
    deriveds.cutplaneColorMapping.useCustomRange = true;
    if (isBanded)
        deriveds.cutplaneColorMapping.numberOfColors = numberOfColors;
    else
        deriveds.cutplaneColorMapping.numberOfColors = 256;
    // 更新LookupTable
    UpdateCutplaneColorMapping();
}

void vtkDisplayWindow::UpdateCutplaneColorMapping()
{
    if (!deriveds.cutplaneLookupTable) {
        std::cerr << "No cutplane LookupTable exists" << std::endl;
        return;
    }
    
    auto& colorMapping = deriveds.cutplaneColorMapping;
    
    // 设置LookupTable参数
    deriveds.cutplaneLookupTable->SetNumberOfTableValues(colorMapping.numberOfColors);
    deriveds.cutplaneLookupTable->SetRange(colorMapping.minValue, colorMapping.maxValue);
    deriveds.cutplaneLookupTable->Build();

    // 更新所有cutplane actors的mapper范围
    for (auto& actor : deriveds.cutplaneActors) {
        auto mapper = actor->GetMapper();
        mapper->SetScalarRange(colorMapping.minValue, colorMapping.maxValue);
    }
    
    // 更新ScalarBar
    if (deriveds.cutplaneScalarBar) {
        deriveds.cutplaneScalarBar->SetLookupTable(deriveds.cutplaneLookupTable);
    }
    
    std::cout << "[Debug] Updated shared cutplane color mapping: range[" 
              << colorMapping.minValue << ", " << colorMapping.maxValue 
              << "], colors=" << colorMapping.numberOfColors << std::endl;
}

vtkDisplayWindow::DerivedObject::CutplaneColorMapping vtkDisplayWindow::GetCutplaneColorMapping()
{
    return deriveds.cutplaneColorMapping;
}


void vtkDisplayWindow::InitializeCutplaneScalarBar()
{
    // 确保cutplaneLookupTable存在
    if (!deriveds.cutplaneLookupTable) {
        std::cerr << "[Error] Cannot initialize cutplane ScalarBar: cutplaneLookupTable not found" << std::endl;
        return;
    }
    
    // 如果ScalarBar还没创建，创建它
    if (!deriveds.cutplaneScalarBar) {
        deriveds.cutplaneScalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
        deriveds.cutplaneScalarBar->SetLookupTable(deriveds.cutplaneLookupTable);
        deriveds.cutplaneScalarBar->SetTitle("Slice");
        deriveds.cutplaneScalarBar->SetNumberOfLabels(10);
        
        // 设置位置 - 水平显示在窗口中下方（避免被截断）
        deriveds.cutplaneScalarBar->SetOrientationToHorizontal();
        deriveds.cutplaneScalarBar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
        deriveds.cutplaneScalarBar->GetPositionCoordinate()->SetValue(0.2, 0.1);   // 中下方位置
        deriveds.cutplaneScalarBar->SetWidth(0.6);   // 宽度占窗口60%
        deriveds.cutplaneScalarBar->SetHeight(0.06); // 高度占窗口6%
        
        // 设置字体 - 更小的字体
        deriveds.cutplaneScalarBar->GetTitleTextProperty()->SetFontSize(10);
        deriveds.cutplaneScalarBar->GetLabelTextProperty()->SetFontSize(8);
        
        // 确保可见性
        deriveds.cutplaneScalarBar->SetVisibility(1);
        
        std::cout << "[Debug] Initialized cutplane ScalarBar at position (0.2, 0.1) with size (0.6, 0.06)" << std::endl;
    }
}


void vtkDisplayWindow::ShowCutplaneScalarBar()
{
    std::cout << "[Debug] ShowCutplaneScalarBar called" << std::endl;
    
    // 初始化ScalarBar（如果需要）
    InitializeCutplaneScalarBar();
    
    if (deriveds.cutplaneScalarBar) {
        std::cout << "[Debug] cutplaneScalarBar exists" << std::endl;
        
        // 添加到渲染器（如果还没添加）
        if (!renderer->HasViewProp(deriveds.cutplaneScalarBar)) {
            renderer->AddActor2D(deriveds.cutplaneScalarBar);
            std::cout << "[Debug] Added cutplaneScalarBar to renderer" << std::endl;
        } else {
            std::cout << "[Debug] cutplaneScalarBar already in renderer" << std::endl;
        }
        
        // 设置可见
        deriveds.cutplaneScalarBar->SetVisibility(1);
        std::cout << "[Debug] Set cutplaneScalarBar visibility to 1" << std::endl;
        std::cout << "[Debug] Showing cutplane ScalarBar" << std::endl;
    } else {
        std::cout << "[Debug] cutplaneScalarBar is null!" << std::endl;
    }
}

void vtkDisplayWindow::HideCutplaneScalarBar()
{
    if (deriveds.cutplaneScalarBar) {
        // 从渲染器中移除
        if (renderer->HasViewProp(deriveds.cutplaneScalarBar)) {
            renderer->RemoveActor2D(deriveds.cutplaneScalarBar);
        }
        
        // 设置不可见
        deriveds.cutplaneScalarBar->SetVisibility(0);
        std::cout << "[Debug] Hiding cutplane ScalarBar" << std::endl;
    }
}

void vtkDisplayWindow::SetCutplaneColorScheme(int schemeIndex)
{
    if (!deriveds.cutplaneLookupTable) {
        std::cerr << "[Error] Cannot set color scheme: cutplaneLookupTable not found" << std::endl;
        return;
    }
    
    std::cout << "[Debug] Setting cutplane color scheme to index: " << schemeIndex << std::endl;
    
    switch (schemeIndex) {
        case 0: // Rainbow (彩虹色) - 默认
            deriveds.cutplaneLookupTable->SetNumberOfTableValues(256);
            deriveds.cutplaneLookupTable->SetHueRange(0.6667, 0.0);  // 蓝到红
            deriveds.cutplaneLookupTable->SetSaturationRange(1.0, 1.0);
            deriveds.cutplaneLookupTable->SetValueRange(1.0, 1.0);
            break;
        case 1: // Viridis
            // Viridis配色方案：深紫色到黄色
            deriveds.cutplaneLookupTable->SetNumberOfTableValues(256);
            deriveds.cutplaneLookupTable->SetHueRange(0.75, 0.167);  // 紫色到黄色
            deriveds.cutplaneLookupTable->SetSaturationRange(0.8, 0.9);
            deriveds.cutplaneLookupTable->SetValueRange(0.2, 0.95);
            break;
        case 2: // Gray (灰度)
            deriveds.cutplaneLookupTable->SetNumberOfTableValues(256);
            deriveds.cutplaneLookupTable->SetHueRange(0.0, 0.0);
            deriveds.cutplaneLookupTable->SetSaturationRange(0.0, 0.0);
            deriveds.cutplaneLookupTable->SetValueRange(0.0, 1.0);
            break;

        default:
            std::cerr << "[Warning] Unknown color scheme index: " << schemeIndex << ", using Rainbow" << std::endl;
            deriveds.cutplaneLookupTable->SetNumberOfTableValues(256);
            deriveds.cutplaneLookupTable->SetHueRange(0.6667, 0.0);
            deriveds.cutplaneLookupTable->SetSaturationRange(1.0, 1.0);
            deriveds.cutplaneLookupTable->SetValueRange(1.0, 1.0);
            break;
    }
    
    // 更新ScalarBar（如果存在）
    if (deriveds.cutplaneScalarBar) {
        deriveds.cutplaneScalarBar->SetLookupTable(deriveds.cutplaneLookupTable);
    }
    
    std::cout << "[Debug] Cutplane color scheme updated successfully" << std::endl;
}