#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <vtkProperty.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkArrayCalculator.h>
#include <vtkGlyph2D.h>
#include <vtkGlyphSource2D.h>
#include <QVTKOpenGLNativeWidget.h>
#include <QButtonGroup>
#include <QSplitter>
#include <QLabel>
#include <vtkInteractorStyleImage.h>
#include <QFileDialog>
#include <QFile>
#include <QHBoxLayout>
#include <QToolBar>
#include <QMessageBox>

#include <vtkRendererCollection.h>
#include <vtkCamera.h>

using std::string; using std::vector;

class MainWindow;

namespace
{
    class MouseInteractorStyle: public vtkInteractorStyleTrackballCamera
    {
    public:
        static MouseInteractorStyle* New();
        vtkTypeMacro(MouseInteractorStyle, vtkInteractorStyleTrackballCamera);
        MouseInteractorStyle() 
        {
            initialize();
        }
        
        void SetMainWindow(MainWindow* window) { mainWindow = window; }

        virtual void OnLeftButtonDown() override
        {
            vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
            
            if (!isAddTextActor) return;
            
            int *pos = this->Interactor->GetEventPosition();

            cellPicker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
            propPicker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

            if (propPicker->GetActor() != nullptr && propPicker->GetActor() != pointActor)
            {
                auto boundaryData = propPicker->GetActor()->GetMapper()->GetInput();
                auto pos = boundaryData->GetPoint(cellPicker->GetPointId());
                
                //* Variable Name in Probe Widget Tab
                std::string coordStr = "x: " + std::to_string(pos[0]) + 
                                      "\ny: " + std::to_string(pos[1]) + 
                                      "\nz: " + std::to_string(pos[2]);
                
                std::vector<std::pair<std::string, double>> probeData;
                for (int i = 0; i < parameterNames.size(); i++)
                {
                    std::string varName = boundaryData->GetPointData()->GetArray(parameterNames[i].c_str())->GetName();
                    double value = boundaryData->GetPointData()->
                        GetArray(parameterNames[i].c_str())->GetComponent(cellPicker->GetPointId(), 0);
                    probeData.push_back({varName, value});
                }
                
                //* Updating 
                if (mainWindow != nullptr)
                {
                    mainWindow->UpdateProbePanel(coordStr, probeData);
                }
                vtkSmartPointer<vtkPointLocator> locate = vtkSmartPointer<vtkPointLocator>::New();
                locate->SetDataSet(boundaryData);
                vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
                locate->FindClosestNPoints(2, pos, idlist);
                
                vtkSmartPointer<vtkMath> math = vtkSmartPointer<vtkMath>::New();
                double point1[3];
                boundaryData->GetPoint(idlist[0].GetId(0), point1);
                double point2[3];
                boundaryData->GetPoint(idlist[0].GetId(1), point2);
                double dis = sqrt(math->Distance2BetweenPoints(point1, point2)) / 3;
            
                auto displayPoint =  vtkSmartPointer<vtkSphereSource>::New();
                displayPoint->SetCenter(pos);
                displayPoint->SetRadius(dis);

                auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

                mapper->SetInputConnection(displayPoint->GetOutputPort());
                this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(pointActor);
                pointActor->SetMapper(mapper);
                this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(pointActor);
            }

            vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        }
        
        void initialize()
        {
            textActor = vtkSmartPointer<vtkTextActor>::New();
            textActor->SetInput("please select a point");
            textActor->GetProperty()->SetColor(0.0,0,0);
            textActor->GetTextProperty()->BoldOn();
            textActor->GetTextProperty()->SetFontSize(18);

            pointActor = vtkSmartPointer<vtkActor>::New();
            pointActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
            pointActor->VisibilityOff();

        }

        vtkSmartPointer<vtkTextActor> textActor = nullptr;
        vtkSmartPointer<vtkActor> pointActor = nullptr;
        std::vector<std::string> parameterNames = {"rho", "u", "v", "w", "P", "tb1"};
        bool isAddTextActor = false;
        
        vtkSmartPointer<vtkCellPicker> cellPicker = vtkSmartPointer<vtkCellPicker>::New();
        vtkSmartPointer<vtkPropPicker> propPicker = vtkSmartPointer<vtkPropPicker>::New();
        
        MainWindow* mainWindow = nullptr;  

        vtkSmartPointer<vtkActor> streamLineActor = vtkSmartPointer<vtkActor>::New();
        vtkSmartPointer<vtkActor> glyphActor = vtkSmartPointer<vtkActor>::New();
        vtkDataSet *meshDataSet = nullptr;
        bool hasPoint1Set = false;
        bool hasPoint2Set = false;
        double streamLinePoint1[3];
        double streamLinePoint2[3];
        bool readyToCreateStreamLine = false;
    };
    vtkStandardNewMacro(MouseInteractorStyle);
}

static ::MouseInteractorStyle* style = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    //* Load Qss file
    QFile styleFile("post.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
        qDebug() << "qss file loaded;";
    } else {
        qDebug() << "qss file not found";
    }
    if (menuBar()) {
        menuBar()->setStyleSheet(
            "QMenuBar {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                                stop:0 #5a9fd4, stop:1 #4a8fc4);"
            "    border-bottom: 2px solid #3d87c2;"
            "    padding: 3px;"
            "    color: white;"
            "}"
            "QMenuBar::item {"
            "    padding: 5px 10px;"
            "    background-color: transparent;"
            "    color: white;"
            "    font-weight: bold;"
            "}"
            "QMenuBar::item:selected {"
            "    background-color: rgba(255, 255, 255, 0.2);"
            "    border-radius: 3px;"
            "}"
            "QMenuBar::item:pressed {"
            "    background-color: rgba(255, 255, 255, 0.3);"
            "}"
        );
    }

    InitializeMainWindow();

}

MainWindow::~MainWindow()
{

    delete qtvtkWindow;
    delete ui;
}

void MainWindow::on_actionLoadMesh_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open File","./",tr("*.grid.hdf"));
    if (filename.length() == 0) 
    {
        cout << "Error choose aes file, please check and try it agian!" << endl;
        return;
    }
    else
    {
        cout << "reading aes grid file " << filename.toStdString() << endl << "please waiting for few seconds!" << endl;
        
        //* Rest All before loading new model
        ResetViewsAndRenderers();
        
        on_actionNewWindow_triggered();

        qtvtkWindow->ReadAesFile(filename.toStdString());
        ui->vtkBox->renderWindow()->Render();
    }
    ResetScrollArea();
    cout << "End Load Mesh" << endl;
    double* bounds = qtvtkWindow->GetModelBounds();
    if (bounds != nullptr) {
        qDebug() << "Outline range in X axis ：" << "Min  = " << bounds[0] << ", Max = " << bounds[1];
    }
}

void MainWindow::on_actionUpdateFlow_triggered()
{
    if (!qtvtkWindow->HasGrid())
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    QString filename = QFileDialog::getOpenFileName(this,"Open File","./",tr("*.hdf"));
    if (filename.length() == 0 || filename.toStdString().find("flow") == std::string::npos) 
    {
        cout << "Error choose flow file, please check and try it agian!" << endl;
        return;
    }
    qtvtkWindow->UpdateFlow(filename.toStdString());
    disconnect(ui->vectorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(vectorCheckBoxTriggered()));
    ui->vectorCheckBox->setCheckState(Qt::Unchecked);
    connect(ui->vectorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(vectorCheckBoxTriggered()));
    ui->vtkBox->renderWindow()->Render();
    cout << "End Update Flow" << endl;
}

void MainWindow::on_actionNewWindow_triggered()
{
    if (!qtvtkWindow->HasGrid()) 
    {
        cout << "the VTK Box is initialized." << endl;
        return;
    }
    cout << "Initialize the VTK Box" << endl;
    vtkDisplayWindow *newWindow = new vtkDisplayWindow();
    ui->vtkBox->setRenderWindow(newWindow->GetRenderWindow());
    delete qtvtkWindow;
    qtvtkWindow = newWindow;
    ui->vtkBox->renderWindow()->Render();
    if (selectBoundaryDialog != nullptr)
    {
        delete selectBoundaryDialog;
        selectBoundaryDialog = nullptr;
    }
    DisableScrollArea();
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open File","./",tr("*.hdf"));
    if (filename.length() == 0 || (filename.toStdString().find("flow") == std::string::npos &&
     filename.toStdString().find("grid") == std::string::npos))
    {
        cout << "Error choose flow file, please check and try it agian!" << endl;
        return;
    }
    if (filename.toStdString().find("flow") != std::string::npos)
    {
        if (!qtvtkWindow->HasGrid())
        {
            cout << "there is no grid file, please add a grid file first." << endl;
            return;
        }
        qtvtkWindow->UpdateFlow(filename.toStdString());
        disconnect(ui->vectorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(vectorCheckBoxTriggered()));
        ui->vectorCheckBox->setCheckState(Qt::Unchecked);
        connect(ui->vectorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(vectorCheckBoxTriggered()));

        ui->vtkBox->renderWindow()->Render();
        cout << "End Update Flow" << endl;
    }
    else if (filename.toStdString().find("grid") != std::string::npos)
    {
        cout << "reading aes grid file " << filename.toStdString() << endl << "please waiting for few seconds!" << endl;
        
        //* Rest All before loading new model
        ResetViewsAndRenderers();
        
        on_actionNewWindow_triggered();
        qtvtkWindow->ReadAesFile(filename.toStdString());
        ui->vtkBox->renderWindow()->Render();
        ResetScrollArea();
        cout << "End Load Mesh" << endl;
    }
}

void MainWindow::on_actionAddScalarBarActor_triggered()
{
    if (!qtvtkWindow->HasGrid())
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    if (qtvtkWindow->IsScalarBarWidgetActive())
    {
        qtvtkWindow->InActivateScalarBarWidget();
    }
    else if (!qtvtkWindow->IsScalarBarWidgetActive())
    {
        qtvtkWindow->ActivateScalarBarWidget();
    }
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::on_actionAddAxisActor_triggered()
{
    if (!qtvtkWindow->HasGrid())
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    if (qtvtkWindow->IsAxiesWidgetActive())
    {
        qtvtkWindow->InActivateAxiesWidget();
    }
    else qtvtkWindow->ActivateAxiesWidget();
    ui->vtkBox->renderWindow()->Render();    
}

void MainWindow::on_actionAddOutlineActor_triggered()
{
    if (!qtvtkWindow->HasGrid())
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    if (qtvtkWindow->IsOutlineActorVisiable())
    {
        qtvtkWindow->InVisiableOutlineActor();
    }
    else qtvtkWindow->VisiableOutlineActor();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::on_actionAddPointInformation_triggered()
{
    if (!qtvtkWindow->HasGrid())
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    if (::style == nullptr)
    {
        ::style = new MouseInteractorStyle();
        ::style->SetMainWindow(this);  
        cout << "initialize mouse interactor style" << endl;
        ui->vtkBox->interactor()->SetInteractorStyle(::style);
    }
    if (!::style->isAddTextActor)
    {

        ::style->isAddTextActor = true;
        ::style->pointActor->VisibilityOn();
        
        //* Probe Widget Shows
        if (probePanel) {
            probePanel->show();
            probePanel->ClearData();
        }
        
        ui->vtkBox->renderWindow()->Render();
        return;
    }
    if (::style->isAddTextActor && probePanel && probePanel->isVisible())
    {
        //* No longer use point information
        ::style->pointActor->VisibilityOff();
        
        probePanel->hide();
    }
    else
    {
        ::style->pointActor->VisibilityOff();
        
        if (probePanel) {
            probePanel->show();
            probePanel->ClearData();
        }
    }
    ui->vtkBox->renderWindow()->Render();

}

void MainWindow::on_actionExport_Picture_triggered()
{
    ExportPicDialog dialog(this);
    
    dialog.setRenderWindows(
        ui->vtkBox->renderWindow(),         
        MeridionalrenderWindow,               
        BladeToBladerenderWindow            
    );
    
    dialog.exec();
}

void MainWindow::xoyViewTriggered()
{
    qtvtkWindow->xoyViewRender();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::xozViewTriggered()
{
    qtvtkWindow->xozViewRender();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::yozViewTriggered()
{
    qtvtkWindow->yozViewRender();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::xyzViewTriggered()
{
    qtvtkWindow->xyzViewRender();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::meshCheckBoxTriggered()
{
    if (!qtvtkWindow->HasGrid()) 
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    if (ui->meshCheckBox->isChecked())
    {
        qtvtkWindow->AddMeshActor();
    }
    else qtvtkWindow->RemoveMeshActor();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::contourCheckBoxTriggered()
{
    if (!qtvtkWindow->HasGrid()) 
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    if (ui->contourCheckBox->isChecked())
    {
        qtvtkWindow->AddContourActor();
        if (ui->shadeCheckBox->isChecked())
        {
            qtvtkWindow->RemoveShadeActor();
        }
    }
    else 
    {
        qtvtkWindow->RemoveContourActor();
        if (ui->shadeCheckBox->isChecked())
        {
            qtvtkWindow->AddShadeActor();
        }
    }
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::shadeCheckBoxTriggered()
{
    if (!qtvtkWindow->HasGrid()) 
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    if (ui->shadeCheckBox->isChecked())
    {
        if (!ui->contourCheckBox->isChecked())
        {
            qtvtkWindow->AddShadeActor();
        }
    }
    else qtvtkWindow->RemoveShadeActor();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::edgeCheckBoxTriggered()
{
    if (!qtvtkWindow->HasGrid()) 
    {
        cout << "there is no grid file, please add a grid file first." << endl;
        return;
    }
    if (ui->edgeCheckBox->isChecked())
    {
        qtvtkWindow->AddEdgeActor();
        if (qtvtkWindow->IsOutlineActorVisiable())
        {
            qtvtkWindow->InVisiableOutlineActor();
        }
    }
    else 
    {
        qtvtkWindow->RemoveEdgeActor();
        if (!qtvtkWindow->IsOutlineActorVisiable())
        {
            qtvtkWindow->VisiableOutlineActor();
        }
    }
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::vectorCheckBoxTriggered()
{
    if (!qtvtkWindow->HasVector())
    {
        cout << "create vector, please wait." << endl;
        qtvtkWindow->CreateVelocityActor();
        qtvtkWindow->AddVelocityActor();
    }
    else
    {
        if (ui->vectorCheckBox->checkState() == Qt::Checked)
        {
            qtvtkWindow->AddVelocityActor();
        }
        else qtvtkWindow->RemoveVelocityActor();
    }
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::contourSettingButtonTriggered()
{
    colorBarDialog = new ColorBarDialog(this);
    colorBarDialog->setColorBarDialog(qtvtkWindow->GetFlows(), qtvtkWindow->GetCurFlowNumber());
    connect(colorBarDialog,SIGNAL(finishSetParameters(double,double,int,int,double,double)),this, SLOT(setColorBar(double,double,int,int,double,double)));
    colorBarDialog->setAttribute(Qt::WA_DeleteOnClose);
    colorBarDialog->setWindowModality(Qt::ApplicationModal);
    colorBarDialog->show();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::setColorBar(double m, double M, int number, int flowNumber, double width, double height)
{
    qtvtkWindow->SetScalarBar(m,M,number,flowNumber);
    qtvtkWindow->SetScalarBarSize(width, height);
    ui->vtkBox->renderWindow()->Render();

    auto plane = qtvtkWindow->ChangeMeridionalFlow(m, M, flowNumber);
    Meridionalrenderer->RemoveAllViewProps();
    for(int i = 0; i < plane.size(); i++)
    {
        Meridionalrenderer->AddActor(plane[i]);
    }
    MeridionalrenderWindow->Render();
}

void MainWindow::vectorSettingButtonTriggered()
{
    if (!qtvtkWindow->HasVector())
    {
        cout << "please add vector first" << endl;
        return;
    }
    scaleFactorDialog = new ScaleFactorDialog(this);
    scaleFactorDialog->setAttribute(Qt::WA_DeleteOnClose);
    scaleFactorDialog->setWindowModality(Qt::ApplicationModal);
    scaleFactorDialog->SetScaleTextEdit(qtvtkWindow->GetScaleFactor());
    scaleFactorDialog->SetVectorComponentsComboBox(qtvtkWindow->GetFlows(),qtvtkWindow->GetVectorComponentsNumber());
    connect(scaleFactorDialog, SIGNAL(SetScaleFactor(double)), this, SLOT(setVectorScaleFactor(double)));
    connect(scaleFactorDialog, SIGNAL(ChangeVectorComponentsNumber(int *)), this, SLOT(createNewVector(int *)));
    scaleFactorDialog->show();
}

void MainWindow::setVectorScaleFactor(double s)
{
    qtvtkWindow->SetVectorScaleFactor(s);
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::createNewVector(int *v)
{
    qtvtkWindow->CreateVelocityActor(v[0], v[1], v[2]);
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::selectBoundaryButtonTriggeded()
{
    //* Test Control Panel
    std::cout << "Control Test "<< std::endl;
    if (controlPanel == nullptr)
    {
        controlPanel = new ControlPanel(this);
        controlPanel->setWindowModality(Qt::NonModal);
        
        //* Get Boundary data to Control Panel
        auto boundaryData = qtvtkWindow->GetBoundaryDatasets();
        controlPanel->setupTable(boundaryData);
        
        connect(controlPanel, &ControlPanel::setBoundarys, this, &MainWindow::showBoundaryActor);
        connect(controlPanel, &ControlPanel::setCutplaneVisiable, this, &MainWindow::showCutplane);
        connect(controlPanel, &ControlPanel::boundaryTransparencyChanged, qtvtkWindow, &vtkDisplayWindow::SetBoundaryTransparency);
        connect(controlPanel, &ControlPanel::sliceTransparencyChanged, qtvtkWindow, &vtkDisplayWindow::SetSliceTransparency);
        connect(controlPanel, &ControlPanel::sliceDeleteRequested, this, &MainWindow::deleteSlice);
        connect(controlPanel, &ControlPanel::sliceContourModeChanged, qtvtkWindow, &vtkDisplayWindow::SetSliceContourMode);
        
        connect(controlPanel, &ControlPanel::sliceContourModeChanged, [this](const QString& mode) {
            if (cutPlaneDialog) {
                bool enableMapping = (mode == "isolated");
                cutPlaneDialog->setMappingControlEnabled(enableMapping);
            }
        });
        
        connect(controlPanel, &ControlPanel::sliceContourModeChanged, [this]() {
            ui->vtkBox->renderWindow()->Render();
        });
        
        controlPanel->setTransparencyControlsEnabled(ui->transparancyCheckBox->isChecked());
    }
    
    controlPanel->show();
    
}

void MainWindow::showBoundaryActor(int meshNumber, int boundaryNumber, bool flag)
{
    if (flag) qtvtkWindow->VisiableBoundaryActor(meshNumber, boundaryNumber);
    else
    {
        qtvtkWindow->InVisiableBoundaryActor(meshNumber, boundaryNumber);
    }
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::isoSurfaceCheckBoxTriggered()
{
    if (!qtvtkWindow->HasIsoSurface())
    {
        qtvtkWindow->CreateIsoSurfaceActor();
        qtvtkWindow->AddIsoSurfaceActor();
        ui->vtkBox->renderWindow()->Render();
        return;
    }

    if (ui->isoSurfaceCheckBox->isChecked())
    {
        qtvtkWindow->AddIsoSurfaceActor();
    }
    else qtvtkWindow->RemoveIsoSurfaceActor();
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::isoSurfaceSettingButtonTriggered()
{
    if (!qtvtkWindow->HasIsoSurface()) 
    {
        cout << "please add isosurface actor first" << endl;
        return;
    }
    if (!ui->isoSurfaceCheckBox->isChecked())
    {
        cout << "please show isosurface first" << endl;
        return;
    }
    IsoSurfaceDialog* isoSurfaceDialog = new IsoSurfaceDialog(this);
    isoSurfaceDialog->setAttribute(Qt::WA_DeleteOnClose);
    isoSurfaceDialog->setWindowModality(Qt::ApplicationModal);
    isoSurfaceDialog->setIsoSurfaceDialog(qtvtkWindow->GetFlows(), qtvtkWindow->GetCurFlowNumber() , qtvtkWindow->GetIsoSurfaceFloodNumber(), 
    qtvtkWindow->GetDeriveds().contourFilter->GetValue(0));
    connect(isoSurfaceDialog, SIGNAL(changeFloodParameter(int)), this, SLOT(changeFloodNumber(int)));
    connect(isoSurfaceDialog, SIGNAL(changeFlowParameter(int)), this, SLOT(isoSurfaceChangeFlowNumber(int)));
    connect(isoSurfaceDialog, SIGNAL(changeIsoSurfaceValue(double)), this, SLOT(isoSurfaceValueChanged(double)));
    isoSurfaceDialog->show();

}

void MainWindow::changeFloodNumber(int number)
{
    qtvtkWindow->ChangeFloodNumber(number);
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::isoSurfaceChangeFlowNumber(int number)
{
    qtvtkWindow->IsoSurfaceChangeFlowNumber(number);
    changeFloodNumber(number);
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::isoSurfaceValueChanged(double value)
{
    qtvtkWindow->SetIsoSurfaceValue(value);
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::slicesCheckBoxTriggered()
{
    if (!qtvtkWindow->HasCutplane())
    {
        cout << "test" << endl;
        qtvtkWindow->AddNewCutplane();

        if (controlPanel != nullptr) {
            int cutplaneIndex = qtvtkWindow->GetPlanes().size() - 1; 
            double origin[3] = {0.0, 0.0, 0.0};
            double normal[3] = {1.0, 0.0, 0.0};
            controlPanel->addCutplaneToTable(cutplaneIndex, origin, normal);
        }
        if (ui->slicesCheckBox->isChecked()) {
            qtvtkWindow->ShowCutplaneScalarBar();
        }

        cout << "add a simple cutplane" << endl;
        ui->vtkBox->renderWindow()->Render();
        return;
    }
    if (ui->slicesCheckBox->isChecked())
    {
        qtvtkWindow->AddCutplaneActors();
        qtvtkWindow->ShowCutplaneScalarBar();
    }
    else 
    {
        qtvtkWindow->RemoveCutplaneActors();
        qtvtkWindow->HideCutplaneScalarBar();
    }
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::slicesSettingButtonTriggered()
{
    if (ui->slicesCheckBox->checkState() == Qt::Unchecked)
    {
        cout << "please add slices actor first" << endl;
        return;
    }
    CutplaneDialog *cutplaneDialog = new CutplaneDialog(this);
    cutplaneDialog->setCutplaneDialog(qtvtkWindow->GetPlanes());

    double* bounds = qtvtkWindow->GetModelBounds();
    if (bounds != nullptr) {
        cutplaneDialog->setModelBounds(bounds);
    }
    
    cutplaneDialog->setFlowVariables(qtvtkWindow->GetFlows(), qtvtkWindow->GetCurFlowNumber());
    
    cutplaneDialog->setAttribute(Qt::WA_DeleteOnClose);
    cutplaneDialog->setWindowModality(Qt::ApplicationModal);
    connect(cutplaneDialog, SIGNAL(finishSetParameters(double*,double*,int)),this, SLOT(changeCutplane(double*,double*,int)));
    connect(cutplaneDialog, &CutplaneDialog::createNewCutplane, this, &MainWindow::makeNewCutplane);
    connect(cutplaneDialog, &CutplaneDialog::colorMappingChanged, this, &MainWindow::updateCutplaneColorMapping);
    connect(cutplaneDialog, &CutplaneDialog::colorSchemeChanged, [this](int index){
        qtvtkWindow->SetCutplaneColorScheme(index);
        ui->vtkBox->renderWindow()->Render();
    });
    
    connect(cutplaneDialog, &CutplaneDialog::variableSelectionChanged, [this](int flowNumber){
        qtvtkWindow->SetCutplaneVariable(flowNumber);
        ui->vtkBox->renderWindow()->Render();
    });
    //* test
    connect(cutplaneDialog, &CutplaneDialog::sliceLocation,
            [this](double value,int axis) {
                if (qtvtkWindow) {
                    qtvtkWindow->CreatePlanePreview(value,axis);
                    ui->vtkBox->renderWindow()->Render();
                }
            });

    connect(cutplaneDialog, &QDialog::finished,
        [this]() {
            if (qtvtkWindow) {
                qtvtkWindow->HidePlanePreview();
            }
        });

    cutplaneDialog->show();
}

void MainWindow::changeCutplane(double* origin, double *normal, int cutplaneNumber)
{
    // cout << origin[0] << " " << origin[1] << " " << origin[2] << endl;
    // cout << normal[0] << " " << normal[1] << " " << normal[2] << endl;
    qtvtkWindow->SetCutplane(cutplaneNumber, origin,normal);
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::makeNewCutplane(double* origin, double* normal)
{
    qtvtkWindow->AddNewCutplane(origin, normal);

    if (controlPanel != nullptr) {
        int cutplaneIndex = qtvtkWindow->GetPlanes().size() - 1;
        controlPanel->addCutplaneToTable(cutplaneIndex, origin, normal);
    }
    
    cout << "add new cut plane with origin(" << origin[0] << ", " << origin[1] << ", " << origin[2] 
         << ") normal(" << normal[0] << ", " << normal[1] << ", " << normal[2] << ")" << endl;
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::transparancyCheckBoxTriggered()
{
    static bool firstTimeEnabled = true;
    bool isChecked = ui->transparancyCheckBox->isChecked();
    
    if (isChecked) {
        //* only set tansparency 0.5 while first pressed
        if (firstTimeEnabled) {
            qtvtkWindow->SetActorTransparancy(0.5);
            firstTimeEnabled = false;
            //* now you need to tell control panel transparency is 0.5
        }
        vtkObject::GlobalWarningDisplayOff();
    }
    else {
        qtvtkWindow->SetActorTransparancy(1.0);
        vtkObject::GlobalWarningDisplayOn();
    }
    
    if (controlPanel) {
        controlPanel->setTransparencyControlsEnabled(isChecked);
    }
    
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::lightingCheckBoxTriggered()
{
    qtvtkWindow->SetActorLighting(ui->lightingCheckBox->isChecked());
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::showCutplane(int number, bool flag)
{
    if (flag) qtvtkWindow->AddCutplane(number);
    else
    {
        qtvtkWindow->RemoveCutplane(number);
    }
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::InitializeMainWindow()
{
    SetIcons();
    SetvtkBox();

    if (ui->CBtn_BackGround) {
        ui->CBtn_BackGround->setCurrentIndex(1);
    }

    connect(ui->xoyView, SIGNAL(clicked()), this, SLOT(xoyViewTriggered()));
    connect(ui->xozView, SIGNAL(clicked()), this, SLOT(xozViewTriggered()));
    connect(ui->yozView, SIGNAL(clicked()), this, SLOT(yozViewTriggered()));
    connect(ui->xyzView, SIGNAL(clicked()), this, SLOT(xyzViewTriggered()));

    connect(ui->contourSettingButton, SIGNAL(clicked()), this, SLOT(contourSettingButtonTriggered()));
    connect(ui->vectorSettingButton, SIGNAL(clicked()), this, SLOT(vectorSettingButtonTriggered()));
    connect(ui->selectBoundaryButton, SIGNAL(clicked()), this, SLOT(selectBoundaryButtonTriggeded()));
    connect(ui->IsoSurfaceSettingButton, SIGNAL(clicked()), this, SLOT(isoSurfaceSettingButtonTriggered()));
    connect(ui->addSliceButton, SIGNAL(clicked()), this, SLOT(slicesSettingButtonTriggered()));

    connect(ui->ConstHeightpushButton, SIGNAL(clicked()),this,SLOT(ConstHeightButtonTriggered()));
//    connect(ui->ConstHeightCheckBox, SIGNAL(stateChanged(int)), this, SLOT(ConstHeightCheckBoxTriggered()));
    connect(ui->MeridionalButton, SIGNAL(clicked()),this, SLOT(MeridionalButtonTriggered()));
    connect(ui->MeridionalcheckBox, SIGNAL(stateChanged(int)),this, SLOT(MeridionalCheckBoxTriggered()));
    
    connect(ui->BladeToBladePlaneButton, SIGNAL(clicked()), this, SLOT(BladeToBladePlaneButtonTriggered()));

    //* Set View Control    
    mainSplitter = new QSplitter(Qt::Horizontal, this);

    //* used for Main model view
    mainViewContainer = new QWidget(mainSplitter);
    QVBoxLayout *mainViewLayout = new QVBoxLayout(mainViewContainer);
    mainViewLayout->setContentsMargins(0, 0, 0, 0);
    mainViewLayout->addWidget(ui->vtkBox);
    mainSplitter->addWidget(mainViewContainer);

    //* used for Meridional and Blade-to-Blade
    rightPanel = new QWidget(mainSplitter);
    rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    meridionalViewContainer = new QWidget(rightPanel);
    QVBoxLayout *meridionalLayout = new QVBoxLayout(meridionalViewContainer);
    meridionalLayout->setContentsMargins(0, 0, 0, 0);
    meridionalLayout->addWidget(vtkWidget);
    
    //* forbidding rotation for Meridional View
    MeridionalrenderWindow->AddRenderer(Meridionalrenderer);
    vtkWidget->setRenderWindow(MeridionalrenderWindow);
    vtkSmartPointer<vtkInteractorStyleImage> meridionalStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
    if (MeridionalrenderWindow->GetInteractor())
    {
        MeridionalrenderWindow->GetInteractor()->SetInteractorStyle(meridionalStyle);
    }
    
    rightLayout->addWidget(meridionalViewContainer);

    //* Blade-to-Blade View Container
    bladeToBladeViewContainer = new QWidget(rightPanel);
    QVBoxLayout *bladeLayout = new QVBoxLayout(bladeToBladeViewContainer);
    bladeLayout->setContentsMargins(0, 0, 0, 0);
    bladeLayout->addWidget(bladeToBladevtkWidget);
    rightLayout->addWidget(bladeToBladeViewContainer);

    mainSplitter->addWidget(rightPanel);
    mainSplitter->setSizes(QList<int>() << 800 << 400);

    probePanel = new ProbePanel(this);
    probePanel->setMinimumWidth(300);
    probePanel->setMaximumWidth(500);
    probePanel->hide(); 
    
    connect(probePanel, &ProbePanel::panelClosed, this, &MainWindow::onProbePanelClosed);
    
    // Outer Splitrer to contain mainSplitter probePanel
    QSplitter *outerSplitter = new QSplitter(Qt::Horizontal, this);
    outerSplitter->addWidget(mainSplitter);
    outerSplitter->addWidget(probePanel);
    outerSplitter->setStretchFactor(0, 1);  
    outerSplitter->setStretchFactor(1, 0);  
    
    ui->VTKLayout->addWidget(outerSplitter);

    ui->Check_3Dview->setChecked(true);
    on_Check_3Dview_toggled(true);

    QButtonGroup *group_ViewControl = new QButtonGroup(this);
    group_ViewControl->setExclusive(true);
    group_ViewControl->addButton(ui->Check_3Dview);
    group_ViewControl->addButton(ui->Check_ThreeView);
    group_ViewControl->addButton(ui->Check_Meri);
    group_ViewControl->addButton(ui->Check_BladeToBlade);

}

void MainWindow::SetIcons()
{
    const string iconPath = ":/PostIcons/";

    //Orientation view buttons's icon
    ui->xoyView->setIcon(QIcon((iconPath+"xoy.png").c_str()));
    ui->xozView->setIcon(QIcon((iconPath+"xoz.png").c_str()));
    ui->yozView->setIcon(QIcon((iconPath+"yoz.png").c_str()));
    ui->xyzView->setIcon(QIcon((iconPath+"xyz.png").c_str()));

    ui->xoyView->setIconSize(ui->xoyView->sizeHint());
    ui->xozView->setIconSize(ui->xozView->sizeHint());
    ui->yozView->setIconSize(ui->yozView->sizeHint());
    ui->xyzView->setIconSize(ui->xyzView->sizeHint());

    ui->contourSettingButton->setIcon(QIcon((iconPath+"contour.png").c_str()));
    ui->vectorSettingButton->setIcon(QIcon((iconPath+"vector.png").c_str()));
    ui->IsoSurfaceSettingButton->setIcon(QIcon((iconPath+"isoSurface.png").c_str()));
    ui->addSliceButton->setIcon(QIcon((iconPath+"cutplane.png").c_str()));
    ui->addStreamLineButton->setIcon(QIcon((iconPath+"streamline.png").c_str()));

    ui->contourSettingButton->setIconSize(ui->contourSettingButton->sizeHint());
    ui->vectorSettingButton->setIconSize(ui->vectorSettingButton->sizeHint());
    ui->IsoSurfaceSettingButton->setIconSize(ui->IsoSurfaceSettingButton->sizeHint());
    ui->addSliceButton->setIconSize(ui->addSliceButton->sizeHint());
    ui->addStreamLineButton->setIconSize(ui->addStreamLineButton->sizeHint());

    //toolBar's icons
    ui->toolBar->setIconSize(QSize(40,40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->actionOpenFile->setIcon(QIcon((iconPath+"open.png").c_str()));
    ui->actionAddAxisActor->setIcon(QIcon((iconPath+"orient_axes.png").c_str()));
    ui->actionAddScalarBarActor->setIcon(QIcon((iconPath+"colorbar.png").c_str()));
    ui->actionAddOutlineActor->setIcon(QIcon((iconPath+"boundbox.png").c_str()));
    ui->actionAddPointInformation->setIcon(QIcon((iconPath+"text.png").c_str()));
    ui->actionCalculatorFunction->setIcon(QIcon((iconPath+"calculator.png").c_str()));
    ui->actionNewWindow->setIcon(QIcon((iconPath+"newwindow.png").c_str()));
    QIcon checkedIcon((iconPath+"open.png").c_str());
}

void MainWindow::SetvtkBox()
{
    qtvtkWindow = new vtkDisplayWindow();
    ui->vtkBox->setRenderWindow(qtvtkWindow->GetRenderWindow());
    ui->vtkBox->renderWindow()->Render();
}

void MainWindow::ResetScrollArea()
{
    ui->edgeCheckBox->setCheckState(Qt::Unchecked);
    ui->meshCheckBox->setCheckState(Qt::Unchecked);
    ui->shadeCheckBox->setCheckState(Qt::Checked);
    ui->contourCheckBox->setCheckState(Qt::Checked);
    ui->vectorCheckBox->setCheckState(Qt::Unchecked);
    ui->slicesCheckBox->setCheckState(Qt::Unchecked);
    ui->transparancyCheckBox->setCheckState(Qt::Unchecked);
    ui->lightingCheckBox->setCheckState(Qt::Checked);

    connect(ui->meshCheckBox, SIGNAL(stateChanged(int)), this, SLOT(meshCheckBoxTriggered()));
    connect(ui->contourCheckBox, SIGNAL(stateChanged(int)), this, SLOT(contourCheckBoxTriggered()));
    connect(ui->shadeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(shadeCheckBoxTriggered()));
    connect(ui->edgeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(edgeCheckBoxTriggered()));
    connect(ui->vectorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(vectorCheckBoxTriggered()));

    ui->isoSurfaceCheckBox->setCheckState(Qt::Unchecked);

    connect(ui->isoSurfaceCheckBox, SIGNAL(stateChanged(int)), this, SLOT(isoSurfaceCheckBoxTriggered()));
    connect(ui->slicesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slicesCheckBoxTriggered()));

    connect(ui->transparancyCheckBox, SIGNAL(stateChanged(int)), this, SLOT(transparancyCheckBoxTriggered()));
    connect(ui->lightingCheckBox, SIGNAL(stateChanged(int)), this, SLOT(lightingCheckBoxTriggered()));

    ui->scrollArea->setEnabled(true);
}

void MainWindow::DisableScrollArea()
{
    disconnect(ui->meshCheckBox, SIGNAL(stateChanged(int)), this, SLOT(meshCheckBoxTriggered()));
    disconnect(ui->contourCheckBox, SIGNAL(stateChanged(int)), this, SLOT(contourCheckBoxTriggered()));
    disconnect(ui->shadeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(shadeCheckBoxTriggered()));
    disconnect(ui->edgeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(edgeCheckBoxTriggered()));
    disconnect(ui->vectorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(vectorCheckBoxTriggered()));
    
    disconnect(ui->isoSurfaceCheckBox, SIGNAL(stateChanged(int)), this, SLOT(isoSurfaceCheckBoxTriggered()));
    disconnect(ui->slicesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slicesCheckBoxTriggered()));

    disconnect(ui->transparancyCheckBox, SIGNAL(stateChanged(int)), this, SLOT(transparancyCheckBoxTriggered()));
    disconnect(ui->lightingCheckBox, SIGNAL(stateChanged(int)), this, SLOT(lightingCheckBoxTriggered()));

    ui->scrollArea->setEnabled(false);
}


void MainWindow::MeridionalButtonTriggered()
{
    MeridionalPlaneDialog * meridionalPlaneDialog = new MeridionalPlaneDialog(this);
    meridionalPlaneDialog->show();
    meridionalPlaneDialog->setDialog(qtvtkWindow->GetFlows(), qtvtkWindow->GetCurFlowNumber());
    connect(meridionalPlaneDialog, SIGNAL(finishSetMeiridonalFlow(int)),this, SLOT(ChangeMeridionalPlaneFlow(int)));
}

void MainWindow::MeridionalCheckBoxTriggered()
{
    if(ui->MeridionalcheckBox->isChecked())
    {
        if(qtvtkWindow->MeridionalPlaneActor.empty())
        {
            MeridionalrenderWindow->Render();
        }
        else{
            vtkWidget->show();
        }
    }
    else{
        vtkWidget->hide();
    }
}

void MainWindow::on_ConstHeightCheckBox_toggled(bool trigger)
{
    if (trigger) {
        ConstHeightPlaneDialog *constheightdialog = new ConstHeightPlaneDialog(this);
        constheightdialog->show();
        connect(constheightdialog, SIGNAL(finishSetParameters(double)), this, SLOT(AddConstHeightPlane(double)));
    }
    else
    {
        qtvtkWindow->RemoveConstHeight();
        ui->vtkBox->renderWindow()->Render();
    }
}

void MainWindow::ConstHeightButtonTriggered()
{
    ConstSettingDialog * settingDialog = new ConstSettingDialog(this);
    settingDialog->setConstSettingDialog(qtvtkWindow->GetFlows(), qtvtkWindow->GetCurFlowNumber());
    settingDialog->show();
    connect(settingDialog,SIGNAL(finishSetHeight(double)),this, SLOT(AddConstHeightPlane(double)));
    connect(settingDialog,SIGNAL(finishSetFlow(int)),this, SLOT(ChangeConstHeightFlow(int)));
}
void MainWindow::AddConstHeightPlane(double height)
{
    qtvtkWindow->CreateConstHeight(height);
}

void MainWindow::ChangeConstHeightFlow(int flow)
{
    qtvtkWindow->ChangeConstHeightFlow(flow);
}

void MainWindow::BladeToBladePlaneButtonTriggered()
{
    BladeToBladePlaneDialog *bladeDialog = new BladeToBladePlaneDialog(this);
    bladeDialog->show();
    connect(bladeDialog, SIGNAL(finishSetParameters(double)), this, SLOT(AddBladeToBladePlane(double)));
}

void MainWindow::AddBladeToBladePlane(double span)
{
    qDebug() << "[B2B] Creating blade-to-blade plane at span =" << span;
    
    auto actors = qtvtkWindow->CreateBladeToBladePlane(span);
    
    qDebug() << "[B2B] Number of actors created:" << actors.size();
    
    if (actors.empty()) {
        qDebug() << "[B2B] ERROR: No actors created! Check console for details.";
        return;
    }
    
    for (int i = 0; i < actors.size(); i++)
    {
        BladeToBladerenderer->AddActor(actors[i]);
        qDebug() << "[B2B] Added actor" << i << "to BladeToBladerenderer";
    }
    
    vtkCamera* camera = BladeToBladerenderer->GetActiveCamera();
    camera->SetPosition(0, 0, 10);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetViewUp(0, 1, 0);
    camera->ParallelProjectionOn();
    
    // Reset camera to fit the 2D unwrapped surface
    BladeToBladerenderer->ResetCamera();
    
    qDebug() << "[B2B] Rendering BladeToBladerenderWindow...";
    BladeToBladerenderWindow->Render();
    qDebug() << "[B2B] Done!";
}

void MainWindow::ChangeBladeToBladePlaneFlow(int flow)
{
    // Remove old actors
    BladeToBladerenderer->RemoveAllViewProps();
    
    // Create new actors with updated flow variable
    auto actors = qtvtkWindow->ChangeBladeToBladePlaneFlow(flow);
    for (int i = 0; i < actors.size(); i++)
    {
        BladeToBladerenderer->AddActor(actors[i]);
    }
    BladeToBladerenderWindow->Render();
}

void MainWindow::ChangeMeridionalPlaneFlow(int flow)
{
    auto plane = qtvtkWindow->ChangeMeridionalFlow(0, 1, flow);
    Meridionalrenderer->RemoveAllViewProps();
    for(int i = 0; i < plane.size(); i++)
    {
        Meridionalrenderer->AddActor(plane[i]);
    }
    MeridionalrenderWindow->Render();
}

void MainWindow::updateCutplaneColorMapping(double minValue, double maxValue, int numberOfColors,bool isBaned)
{
    qtvtkWindow->SetCutplaneColorMapping(minValue, maxValue, numberOfColors,isBaned);
    ui->vtkBox->renderWindow()->Render();
}

//* View Control Functions
void MainWindow::on_Check_3Dview_toggled(bool checked)
{
    if (checked)
    {
        mainViewContainer->show();
        rightPanel->hide();

        mainSplitter->setSizes(QList<int>() << this->width() << 0);

        UpdateViewLabels();
        qDebug() << "Switched to 3D View mode";
    }
}

void MainWindow::on_Check_ThreeView_toggled(bool checked)
{
    if (checked)
    {
        // Setup views before showing them
        SetupMeridionalView();
        SetupBladeToBladeView();

        mainViewContainer->show();
        rightPanel->show();

        // Ensure sub-views are visible
        meridionalViewContainer->show();
        bladeToBladeViewContainer->show();

        // Adjust splitter sizes
        mainSplitter->setSizes(QList<int>() << (this->width() * 0.6) << (this->width() * 0.4));

        // Render all windows
        ui->vtkBox->renderWindow()->Render();
        MeridionalrenderWindow->Render();
        BladeToBladerenderWindow->Render();

        UpdateViewLabels();
        qDebug() << "Switched to Three View mode";
    }
}

void MainWindow::on_Check_Meri_toggled(bool checked)
{
    if (checked)
    {
        SetupMeridionalView();

        mainViewContainer->hide();
        rightPanel->show();

        // Only show the Meridional view
        meridionalViewContainer->show();
        bladeToBladeViewContainer->hide();

        // Adjust splitter sizes
        mainSplitter->setSizes(QList<int>() << 0 << this->width());

        MeridionalrenderWindow->Render();
        UpdateViewLabels();
        qDebug() << "Switched to Meridional View mode";
    }
}

void MainWindow::on_Check_BladeToBlade_toggled(bool checked)
{
    if (checked)
    {
        SetupBladeToBladeView();

        mainViewContainer->hide();
        rightPanel->show();

        // Only show the Blade-to-Blade view
        meridionalViewContainer->hide();
        bladeToBladeViewContainer->show();

        // Adjust splitter sizes
        mainSplitter->setSizes(QList<int>() << 0 << this->width());

        BladeToBladerenderWindow->Render();
        UpdateViewLabels();
        qDebug() << "Switched to Blade-to-Blade View mode";
    }
}

void MainWindow::deleteSlice(int cutplaneIndex)
{
    // 调用vtkDisplayWindow删除cutplane
    qtvtkWindow->DeleteCutplane(cutplaneIndex);
    
    ui->vtkBox->renderWindow()->Render();
}

//* Set BackGround for all views
void MainWindow::on_CBtn_BackGround_currentTextChanged(const QString &text)
{
    if (!qtvtkWindow->HasGrid())
    {
        return;
    }
    
    qtvtkWindow->SetBackgroundStyle(text);
    
    SetViewBackground(Meridionalrenderer, text);
    MeridionalrenderWindow->Render();
    
    SetViewBackground(BladeToBladerenderer, text);
    BladeToBladerenderWindow->Render();
}


void MainWindow::SetupMeridionalView()
{
    if (qtvtkWindow->MeridionalPlaneActor.empty())
    {
        SetViewBackground(Meridionalrenderer, ui->CBtn_BackGround->currentText());
        MeridionalrenderWindow->AddRenderer(Meridionalrenderer);
        vtkWidget->setRenderWindow(MeridionalrenderWindow);
        
        vtkSmartPointer<vtkInteractorStyleImage> imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
        if (MeridionalrenderWindow->GetInteractor())
        {
            MeridionalrenderWindow->GetInteractor()->SetInteractorStyle(imageStyle);
        }
        
        auto plane = qtvtkWindow->CreateMeridionalPlane(0, 10);
        for (int i = 0; i < plane.size(); i++)
        {
            Meridionalrenderer->AddActor(plane[i]);
        }
        MeridionalrenderWindow->Render();
    }
}

void MainWindow::SetupBladeToBladeView()
{
    SetViewBackground(BladeToBladerenderer, ui->CBtn_BackGround->currentText());
    BladeToBladerenderWindow->AddRenderer(BladeToBladerenderer);
    bladeToBladevtkWidget->setRenderWindow(BladeToBladerenderWindow);
    
    qDebug() << "[B2B Setup] Setting up Blade-to-Blade view";
    
    // Setup 2D camera (top view, looking down Z-axis)
    vtkCamera* camera = BladeToBladerenderer->GetActiveCamera();
    camera->SetPosition(0, 0, 10);       // Position camera above
    camera->SetFocalPoint(0, 0, 0);      // Look at Z=0 plane
    camera->SetViewUp(0, 1, 0);          // Y-axis points up
    camera->ParallelProjectionOn();      // Parallel projection for 2D
    
    // Restore any existing B2B planes if they exist
    if (!qtvtkWindow->BladeToBladePlaneActor.empty()) {
        qDebug() << "[B2B Setup] Restoring" << qtvtkWindow->BladeToBladePlaneActor.size() << "existing B2B planes";
        for (int i = 0; i < qtvtkWindow->BladeToBladePlaneActor.size(); i++) {
            BladeToBladerenderer->AddActor(qtvtkWindow->BladeToBladePlaneActor[i]);
        }
        BladeToBladerenderer->ResetCamera();
    }
    
    BladeToBladerenderWindow->Render();
}

void MainWindow::SetViewBackground(vtkSmartPointer<vtkRenderer> renderer, const QString &style)
{
    if (style == "Sky Blue") {
        renderer->SetBackground(1.0, 1.0, 1.0);
        renderer->SetBackground2(0.529, 0.8078, 0.92157);
        renderer->SetGradientBackground(true);
    } else if (style == "White") {
        renderer->SetBackground(1.0, 1.0, 1.0);
        renderer->SetGradientBackground(false);
    }
}

void MainWindow::HideAllViews()
{
    ui->vtkBox->hide();
    vtkWidget->hide();
    bladeToBladevtkWidget->hide();
}

void MainWindow::ShowMainView()
{
    ui->vtkBox->show();
}

void MainWindow::ShowMeridionalView()
{
    SetupMeridionalView();
    vtkWidget->show();
}

void MainWindow::ShowBladeToBladeView()
{
    SetupBladeToBladeView();
    bladeToBladevtkWidget->show();
}

void MainWindow::CreateViewLabels()
{
    if (!mainViewLabel) {
        mainViewLabel = new QLabel("3D View", this);
        mainViewLabel->setAlignment(Qt::AlignCenter);
        mainViewLabel->setStyleSheet("QLabel { background-color: rgba(70, 130, 180, 0.8); color: white; font-weight: bold; padding: 4px; border-radius: 4px; }");
        mainViewLabel->hide();
    }
    
    if (!meridionalViewLabel) {
        meridionalViewLabel = new QLabel("Meridional View", this);
        meridionalViewLabel->setAlignment(Qt::AlignCenter);
        meridionalViewLabel->setStyleSheet("QLabel { background-color: rgba(70, 130, 180, 0.8); color: white; font-weight: bold; padding: 4px; border-radius: 4px; }");
        meridionalViewLabel->hide();
    }
    
    if (!bladeToBladeViewLabel) {
        bladeToBladeViewLabel = new QLabel("Blade-to-Blade View", this);
        bladeToBladeViewLabel->setAlignment(Qt::AlignCenter);
        bladeToBladeViewLabel->setStyleSheet("QLabel { background-color: rgba(70, 130, 180, 0.8); color: white; font-weight: bold; padding: 4px; border-radius: 4px; }");
        bladeToBladeViewLabel->hide();
    }
}

void MainWindow::UpdateViewLabels()
{
    CreateViewLabels();

    mainViewLabel->setParent(mainViewContainer);
    mainViewLabel->setGeometry(10, 10, 100, 25);
    mainViewLabel->setVisible(mainViewContainer->isVisible());
    if(mainViewContainer->isVisible()) mainViewLabel->raise();

    meridionalViewLabel->setParent(meridionalViewContainer);
    meridionalViewLabel->setGeometry(10, 10, 120, 25);
    meridionalViewLabel->setVisible(meridionalViewContainer->isVisible());
    if(meridionalViewContainer->isVisible()) meridionalViewLabel->raise();

    bladeToBladeViewLabel->setParent(bladeToBladeViewContainer);
    bladeToBladeViewLabel->setGeometry(10, 10, 140, 25);
    bladeToBladeViewLabel->setVisible(bladeToBladeViewContainer->isVisible());
    if(bladeToBladeViewContainer->isVisible()) bladeToBladeViewLabel->raise();
}

//* Probe Panel Functions
void MainWindow::UpdateProbePanel(const std::string& coordinates, 
                                   const std::vector<std::pair<std::string, double>>& data)
{
    if (probePanel) {
        probePanel->UpdateProbeData(coordinates, data);
    }
}

void MainWindow::onProbePanelClosed()
{
    if (::style && ::style->isAddTextActor) {
        ::style->pointActor->VisibilityOff();
        ui->vtkBox->renderWindow()->Render();
        qDebug() << "Probe panel closed, probe mode disabled";
    }
}

void MainWindow::ResetViewsAndRenderers()
{
    cout << "Resetting all views and renderers to clear previous model..." << endl;
    
    if (Meridionalrenderer) {
        Meridionalrenderer->RemoveAllViewProps();
        if (MeridionalrenderWindow) {
            MeridionalrenderWindow->Render();
        }
    }
    
    if (BladeToBladerenderer) {
        BladeToBladerenderer->RemoveAllViewProps();
        if (BladeToBladerenderWindow) {
            BladeToBladerenderWindow->Render();
        }
    }
    
    if (ui->MeridionalcheckBox) {
        disconnect(ui->MeridionalcheckBox, SIGNAL(stateChanged(int)), this, SLOT(MeridionalCheckBoxTriggered()));
        ui->MeridionalcheckBox->setCheckState(Qt::Unchecked);
        connect(ui->MeridionalcheckBox, SIGNAL(stateChanged(int)), this, SLOT(MeridionalCheckBoxTriggered()));
    }
    
    cout << "Views and renderers reset completed." << endl;
}

//* Turbo Initialize Button
void MainWindow::on_Btn_TurboInitial_clicked()
{
    qDebug() << "[Turbo Init] Checking node_radius availability...";
    

    if (!qtvtkWindow->HasNodeRadius())
    {
        QMessageBox::warning(this, "Failed",
                           "Please Set Model as Rotation in PreProcessing !");
        qDebug() << "[Turbo Init] node_radius field not found!";
        ui->Wi_TurboSet->setEnabled(false);
        return;
    }
    
    // node_radius存在，启用Wi_TurboSet
    ui->Wi_TurboSet->setEnabled(true);

    qDebug() << "[Turbo Init] Successfully enabled Wi_TurboSet!";
}
