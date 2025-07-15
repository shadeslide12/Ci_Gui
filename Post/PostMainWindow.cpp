#include "PostMainWindow.h"
#include "ui_PostMainWindow.h"

#include "ColorBarDialog.h"
#include "IsoSurfaceDialog.h"
#include "CutplaneDialog.h"
#include "MeridionalPlaneDialog.h"
#include "ConstHeightPlaneDialog.h"
#include "CalculatorDialog.h"

using std::string; using std::vector;

#include <QFileDialog>

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
#include <vtkMaskPoints.h>
#include <vtkLineSource.h>
#include <vtkStreamTracer.h>

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

        virtual void OnLeftButtonDown() override
        {
            int *pos = this->Interactor->GetEventPosition();

            vtkSmartPointer<vtkCellPicker> cellPicker = vtkSmartPointer<vtkCellPicker>::New();
            vtkSmartPointer<vtkPropPicker> propPicker = vtkSmartPointer<vtkPropPicker>::New();
            cellPicker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
            propPicker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

            if (isAddTextActor && propPicker->GetActor() != nullptr && propPicker->GetActor() != pointActor)
            {
                auto boundaryData = propPicker->GetActor()->GetMapper()->GetInput();
                auto pos = boundaryData->GetPoint(cellPicker->GetPointId());
                string pointCoordinates = "Postion: " + std::to_string(pos[0]) + ", " + std::to_string(pos[1]) + ", " + 
                std::to_string(pos[2]) + "\n";

                for (int i = 0; i < parameterNames.size(); i++)
                {
                    if (i > 0 && i % 6 == 0) pointCoordinates.push_back('\n'); 
                    pointCoordinates += boundaryData->GetPointData()->GetArray(parameterNames[i].c_str())->GetName();
                    pointCoordinates.push_back(':');
                    pointCoordinates += to_string(boundaryData->GetPointData()->
                        GetArray(parameterNames[i].c_str())->GetComponent(cellPicker->GetPointId(),0));
                    pointCoordinates.push_back(' ');
                }
                
                
                textActor->SetInput(pointCoordinates.c_str());
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
        
        virtual void OnRightButtonDown() override
        {
            cout << "test" << endl;
            if (readyToCreateStreamLine) 
            {
                    int *pos = this->Interactor->GetEventPosition();
                    vtkSmartPointer<vtkCellPicker> cellPicker = vtkSmartPointer<vtkCellPicker>::New();
                    vtkSmartPointer<vtkPropPicker> propPicker = vtkSmartPointer<vtkPropPicker>::New();
                    cellPicker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
                    propPicker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

                    if (propPicker->GetActor() == nullptr)
                    {
                        cout << "please choose a point!" << endl;
                    }
                    else
                    {
                        vtkSmartPointer<vtkDataSet> curData = propPicker->GetActor()->GetMapper()->GetInput();
                        auto pickedActor = propPicker->GetActor();
                        if (!hasPoint1Set) 
                        {
                            curData->GetPoint(cellPicker->GetPointId(), streamLinePoint1);
                            cout << "the first point is being set to " << streamLinePoint1[0] << " " << streamLinePoint1[1] << " " << streamLinePoint1[2] << endl;
                            hasPoint1Set = true;
                        }
                        else if (hasPoint1Set && !hasPoint2Set)
                        {
                            curData->GetPoint(cellPicker->GetPointId(), streamLinePoint2);
                            cout << "the second point is being set to " << streamLinePoint2[0] << " " << streamLinePoint2[1] << " " << streamLinePoint2[2] << endl;
                            hasPoint2Set = true;
                        }

                        if (hasPoint1Set&&hasPoint2Set)
                        {
                            cout << "begin to create streamLine" << endl;

                            createStreamLineActor();

                            cout << "finish create streamline" << endl;

                            hasPoint1Set = false;
                            hasPoint2Set = false;   
                        }
                    }
            }
            vtkInteractorStyleTrackballCamera::OnRightButtonDown();
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

        void createStreamLineActor()
        {
            vtkSmartPointer<vtkLineSource> line = vtkSmartPointer<vtkLineSource>::New();
	        line->SetPoint1(streamLinePoint1);
	        line->SetPoint2(streamLinePoint2);
	        line->SetResolution(10);
	        line->Update();
	        
            if (meshDataSet == nullptr) 
            {
                cout << "mesh is empty" << endl;
                return;
            }
            vtkSmartPointer<vtkStreamTracer> streamline = vtkSmartPointer<vtkStreamTracer>::New();
	        streamline->SetSourceConnection(line->GetOutputPort());
	        streamline->SetInputData(meshDataSet);
            // streamline->SetIntegratorTypeToRungeKutta4();
	        streamline->SetIntegratorTypeToRungeKutta45();//设置流线的积分类型
	        // streamline->SetMaximumPropagation(5000);//设置流线长度
	        streamline->SetIntegrationStepUnit(0.01);//设置流线积分步长单位
            streamline->SetMaximumPropagation(1.0);
	        streamline->SetIntegrationDirectionToBoth();//设置流线积分方向
	        streamline->Update();

            auto streamlinedata = streamline->GetOutput();
            streamlinedata->GetPointData()->SetActiveVectors("velocity");

            vtkSmartPointer<vtkMaskPoints> maskPoints = vtkSmartPointer<vtkMaskPoints>::New();
            // maskPoints->SetInputConnection(calc->GetOutputPort());
            maskPoints->SetInputData(streamlinedata);
            // maskPoints->SetInputData(boundaryActors[0][6]->GetMapper()->GetInput());
            maskPoints->SetRandomMode(1);
            maskPoints->SetRandomModeType(2);
            maskPoints->SetMaximumNumberOfPoints(50);
            maskPoints->Update();
        

            vtkSmartPointer<vtkGlyphSource2D> Glyph2d =vtkSmartPointer<vtkGlyphSource2D>::New();
            // 新建二维箭头类型指针
            Glyph2d->SetScale(1);//设置二维箭头比例
            Glyph2d->SetGlyphTypeToArrow();//设置箭头类型为箭头
            Glyph2d->SetFilled(0);//关闭箭头填充
            Glyph2d->SetOutputPointsPrecision(vtkAlgorithm::SINGLE_PRECISION);//设置箭头输出精度
            Glyph2d->Update(); 
            vtkSmartPointer<vtkGlyph3D> Glyph =vtkSmartPointer<vtkGlyph3D>::New();//新建矢量指针
            Glyph->SetSourceConnection(Glyph2d->GetOutputPort());//设置之前设置好的矢量箭头为矢量符号。
            Glyph->SetInputConnection(maskPoints->GetOutputPort());//设置通过maskpoints过滤的点数据为输入数据。
            Glyph->SetScaleMode(1);//开启箭头比例缩放模式
            Glyph->SetScaleModeToScaleByVector();
            Glyph->SetVectorModeToUseVector();
            Glyph->SetScaleModeToDataScalingOff();//关闭箭头随速度或者标量大小而变化
            Glyph->SetScaleFactor(0.01);//控制箭头比例，大小
            Glyph->SetColorMode(1);
            Glyph->Update();
        
            vtkSmartPointer<vtkPolyDataMapper> streamlinemappper = vtkSmartPointer<vtkPolyDataMapper>::New();
            streamlinemappper->SetInputData(streamline->GetOutput());
            streamlinemappper->ScalarVisibilityOff();
        
            vtkSmartPointer<vtkPolyDataMapper> glyphmappper = vtkSmartPointer<vtkPolyDataMapper>::New();
            glyphmappper->SetInputConnection(Glyph->GetOutputPort());
            glyphmappper->ScalarVisibilityOff();
            
            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(streamLineActor);
            streamLineActor->SetMapper(streamlinemappper);
            streamLineActor->GetProperty()->SetColor(0,0,0);

            cout << streamLineActor->GetMapper()->GetInput()->GetPointData()->GetVectors()->GetName() << endl;

            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(streamLineActor);
            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(glyphActor);
            glyphActor->SetMapper(glyphmappper);
            glyphActor->GetProperty()->SetColor(0,0,0);
            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(glyphActor);

        }

        vtkSmartPointer<vtkTextActor> textActor = nullptr;
        vtkSmartPointer<vtkActor> pointActor = nullptr;
        vector<string> parameterNames = {"rho", "u", "v", "w", "P", "tb"};
        bool isAddTextActor = false;

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


// namespace
// {
//     class MouseInteractorStyle: public vtkInteractorStyleTrackballCamera
//     {
//     public:
//         static MouseInteractorStyle* New();
//         vtkTypeMacro(MouseInteractorStyle, vtkInteractorStyleTrackballCamera);
//         MouseInteractorStyle() 
//         {
//             initialize();
//         }

//         virtual void OnLeftButtonDown() override
//         {
//             int *pos = this->Interactor->GetEventPosition();

//             vtkSmartPointer<vtkCellPicker> cellPicker = vtkSmartPointer<vtkCellPicker>::New();
//             vtkSmartPointer<vtkPropPicker> propPicker = vtkSmartPointer<vtkPropPicker>::New();
//             cellPicker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
//             propPicker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

//             if (isAddTextActor && propPicker->GetActor() != nullptr && propPicker->GetActor() != pointActor)
//             {
//                 auto boundaryData = propPicker->GetActor()->GetMapper()->GetInput();
//                 auto pos = boundaryData->GetPoint(cellPicker->GetPointId());
//                 string pointCoordinates = "Postion: " + std::to_string(pos[0]) + ", " + std::to_string(pos[1]) + ", " + 
//                 std::to_string(pos[2]) + "\nAttributes: " + std::to_string(boundaryData->GetPointData()->GetScalars()->GetTuple(cellPicker->GetPointId())[0]);
//                 textActor->SetInput(pointCoordinates.c_str());
//                 vtkSmartPointer<vtkPointLocator> locate = vtkSmartPointer<vtkPointLocator>::New();
//                 locate->SetDataSet(boundaryData);
//                 vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
//                 locate->FindClosestNPoints(2, pos, idlist);
                
//                 vtkSmartPointer<vtkMath> math = vtkSmartPointer<vtkMath>::New();
//                 double point1[3];
//                 boundaryData->GetPoint(idlist[0].GetId(0), point1);
//                 double point2[3];
//                 boundaryData->GetPoint(idlist[0].GetId(1), point2);
//                 double dis = sqrt(math->Distance2BetweenPoints(point1, point2)) / 3;
            
//                 auto displayPoint =  vtkSmartPointer<vtkSphereSource>::New();
//                 displayPoint->SetCenter(pos);
//                 displayPoint->SetRadius(dis);

//                 auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

//                 mapper->SetInputConnection(displayPoint->GetOutputPort());
//                 this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(pointActor);
//                 pointActor->SetMapper(mapper);
//                 this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(pointActor);
//             }

//             vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
//         }
        
//         void initialize()
//         {
//             textActor = vtkSmartPointer<vtkTextActor>::New();
//             textActor->SetInput("please select a point");
//             textActor->GetProperty()->SetColor(0.0,0,0);
//             textActor->GetTextProperty()->BoldOn();
//             textActor->GetTextProperty()->SetFontSize(18);

//             pointActor = vtkSmartPointer<vtkActor>::New();
//             pointActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
//             pointActor->VisibilityOff();

//         }
//         vtkSmartPointer<vtkTextActor> textActor = nullptr;
//         vtkSmartPointer<vtkActor> pointActor = nullptr;
//         vector<string> parameterNames = {"rho", "u", "v", "w", "P", "tb"};
//         bool isAddTextActor = false;

//     };
//     vtkStandardNewMacro(MouseInteractorStyle);
    
// }


PostMainWindow::PostMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PostMainWindow)
{
    ui->setupUi(this);
    initializeMainWindow();
}

PostMainWindow::~PostMainWindow()
{
    delete ui;
}

void PostMainWindow::on_actionLoadMesh_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open File","./",tr("*.flow.hdf"));
    if (guiState.hasMesh)
    {
        cout << "there is a grid file already, please restart CFD Post Tool and try to read a new grid file." << endl;
        return;
    }
    if (filename.length() == 0) 
    {
        cout << "Error choose aes file, please check and try it agian!" << endl;
        return;
    }
    else
    {
        cout << "reading aes grid file " << filename.toStdString() << endl << "please waiting for few seconds!" << endl;;
        QString filepath = QFileInfo(filename).path();
        qtvtkWindow.setFileName(filepath.toStdString(), filename.toStdString());
        ui->vtkBox->renderWindow()->Render();
        guiState.hasMesh = true;
        selectBoundaryDialog->setSelectBoundaryDialog(qtvtkWindow.getBoundarys());
        connect(selectBoundaryDialog, SIGNAL(setBoundarys(int,int,bool)), this, SLOT(showBoundaryActor(int,int,bool)));
        connect(selectBoundaryDialog, SIGNAL(setCutplaneVisiable(int,bool)), this, SLOT(showCutplane(int, bool)));
        cout << "end read aes file." << endl;
    }
    ui->scrollArea->setEnabled(true);
    vtkSmartPointer<MouseInteractorStyle> style = vtkSmartPointer<MouseInteractorStyle>::New();
    ui->vtkBox->interactor()->SetInteractorStyle(style);
}

void PostMainWindow::on_actionOpenFile_triggered()
{
    on_actionLoadMesh_triggered();
}

void PostMainWindow::on_actionAddAxisActor_triggered()
{
    if (!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }
    if (guiState.isAxisShow)
    {
        guiState.isAxisShow = false;
        qtvtkWindow.removeAxisActor();
        ui->vtkBox->renderWindow()->Render();
    }
    else
    {
        guiState.isAxisShow = true;
        qtvtkWindow.addAxisActor();
        ui->vtkBox->renderWindow()->Render();
    }
}

void PostMainWindow::on_actionAddScalarBarActor_triggered()
{
    if (!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }
    if (guiState.isScalarBarShow) 
    {
        qtvtkWindow.removeScalarBarActor();
        guiState.isScalarBarShow = false;
    }
    else if (!guiState.isScalarBarShow && ui->contourCheckBox->isChecked())
    {
        qtvtkWindow.addScalarBarActor();
        guiState.isScalarBarShow = true;
    }
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::on_actionAddOutlineActor_triggered()
{
    if (!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }
    if (guiState.isOutlineShow) 
    {
        qtvtkWindow.removeOutlineActor();
        guiState.isOutlineShow = false;
    }
    else
    {
        qtvtkWindow.addOutlineActor();
        guiState.isOutlineShow = true;
    }
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::on_actionAddPointInformation_triggered()
{
    if (!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }
    auto style = dynamic_cast<MouseInteractorStyle*>(ui->vtkBox->interactor()->GetInteractorStyle());
    if (!style->isAddTextActor)
    {
        ui->vtkBox->renderWindow()->GetRenderers()->GetFirstRenderer()->AddActor2D(style->textActor);
        style->isAddTextActor = true;
        style->pointActor->VisibilityOn();
        guiState.isTextActorShow = true;
        ui->vtkBox->renderWindow()->Render();
        return;
    }
    if (guiState.isTextActorShow)
    {
        style->textActor->VisibilityOff();
        style->pointActor->VisibilityOff();
        ui->vtkBox->renderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(style->pointActor);
        guiState.isTextActorShow = false;
    }
    else
    {
        style->textActor->VisibilityOn();
        style->pointActor->VisibilityOn();
        ui->vtkBox->renderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(style->pointActor);
        style->textActor->SetInput("please select a point");
        guiState.isTextActorShow = true;
    }


    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::on_actionCalculatorFunction_triggered()
{
    if (!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }

    CalculatorDialog *calculatorDialog = new CalculatorDialog(this);
    connect(calculatorDialog, SIGNAL(setParameter(QString, QString)), this, SLOT(addNewParameter(QString, QString)));
    calculatorDialog->show();
    
}

void PostMainWindow::meshCheckBoxTriggered()
{
    if (ui->meshCheckBox->isChecked())
    {
        qtvtkWindow.addMeshActor();
    }
    else qtvtkWindow.removeMeshActor();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::contourCheckBoxTriggered()
{
    if (ui->contourCheckBox->isChecked())
    {
        qtvtkWindow.addContourActor();
        guiState.isScalarBarShow = true;
    }
    else 
    {
        qtvtkWindow.removeContourActor();
        guiState.isScalarBarShow = false;
    }
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::shadeCheckBoxTriggered()
{
    if (ui->shadeCheckBox->isChecked())
    {
        qtvtkWindow.addShadeActor();
        if (ui->contourCheckBox->isChecked())
        {
            qtvtkWindow.removeContourActor();
            qtvtkWindow.addContourActor();
        }
    }
    else qtvtkWindow.removeShadeActor();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::edgeCheckBoxTriggered()
{
    if (ui->edgeCheckBox->isChecked())
    {
        qtvtkWindow.addEdgeActor();
    }
    else qtvtkWindow.removeEdgeActor();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::contourSettingButtonTriggered()
{
    if (!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }
    ColorBarDialog* colorBarDialog = new ColorBarDialog(this);
    colorBarDialog->setColorBarDialog(qtvtkWindow.getFlows(), guiState.flowNumber);
    connect(colorBarDialog,SIGNAL(finishSetParameters(double,double,int,int)),this, SLOT(setColorBar(double,double,int,int)));
    colorBarDialog->show();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::selectBoundaryButtonTriggeded()
{
    if (!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }
    selectBoundaryDialog->show();

}

void PostMainWindow::setColorBar(double m, double M, int number, int flowNumber)
{
    qtvtkWindow.setColorBar(m,M,number,flowNumber);
    guiState.flowNumber = flowNumber;
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::showBoundaryActor(int meshNumber, int boundaryNumber, bool flag)
{
    if (flag) qtvtkWindow.addBoundaryActor(meshNumber, boundaryNumber);
    else
    {
        qtvtkWindow.removeBoundaryActor(meshNumber, boundaryNumber);
    }
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::vectorCheckBoxTriggered()
{
    if (!guiState.hasVector) 
    {
        qtvtkWindow.createVelocityActor(1,2,3);
        guiState.hasVector = true;
    }
    if (ui->vectorCheckBox->isChecked())
    {
        qtvtkWindow.addVelocityActor();
    }
    else qtvtkWindow.removeVelocityActor();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::xoyViewTriggered()
{
    qtvtkWindow.xoyViewRender();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::xozViewTriggered()
{
    qtvtkWindow.xozViewRender();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::yozViewTriggered()
{
    qtvtkWindow.yozViewRender();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::xyzViewTriggered()
{
    qtvtkWindow.xyzViewRender();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::isoSurfaceCheckBoxTriggered()
{
    if (!guiState.hasIsoSurface)
    {
        qtvtkWindow.createIsoSurfaceActor();
        qtvtkWindow.addIsoSurfaceActor();
        guiState.hasIsoSurface = true;
        ui->vtkBox->renderWindow()->Render();
        return;
    }

    if (ui->isoSurfaceCheckBox->isChecked())
    {
        qtvtkWindow.addIsoSurfaceActor();
    }
    else qtvtkWindow.removeIsoSurfaceActor();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::isoSurfaceSettingButtonTriggered()
{
    if (!guiState.hasIsoSurface) 
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
    isoSurfaceDialog->setIsoSurfaceDialog(qtvtkWindow.getFlows(), guiState.isoSurfaceFlowNumber , guiState.floodNumber, 
    qtvtkWindow.getDeriveds().contourFilter->GetValue(0));
    connect(isoSurfaceDialog, SIGNAL(changeFloodParameter(int)), this, SLOT(changeFloodNumber(int)));
    connect(isoSurfaceDialog, SIGNAL(changeFlowParameter(int)), this, SLOT(isoSurfaceChangeFlowNumber(int)));
    connect(isoSurfaceDialog, SIGNAL(changeIsoSurfaceValue(double)), this, SLOT(isoSurfaceValueChanged(double)));
    isoSurfaceDialog->show();

}

void PostMainWindow::slicesCheckBoxTriggered()
{
    if (!guiState.hasSlices)
    {
        qtvtkWindow.addNewCutplane();
        selectBoundaryDialog->setSelectCutplaneItems();
        cout << "add a simple cutplane" << endl;
        guiState.hasSlices = true;
        ui->vtkBox->renderWindow()->Render();
        return;
    }
    if (ui->slicesCheckBox->isChecked())
    {
        qtvtkWindow.addCutplaneActors();
    }
    else qtvtkWindow.removeCutplaneActors();
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::slicesSettingButtonTriggered()
{
    if (ui->slicesCheckBox->checkState() == Qt::Unchecked)
    {
        cout << "please add slices actor first" << endl;
        return;
    }
    CutplaneDialog *cutplaneDialog = new CutplaneDialog(this);
    cutplaneDialog->setCutplaneDialog(qtvtkWindow.getPlanes());
    connect(cutplaneDialog, SIGNAL(finishSetParameters(double*,double*,int)),this, SLOT(changeCutplane(double*,double*,int)));
    connect(cutplaneDialog, SIGNAL(createNewCutplane()), this, SLOT(makeNewCutplane()));
    cutplaneDialog->show();
}

void PostMainWindow::streamlineCheckBoxTriggered()
{
    if (!guiState.hasVector)
    {
        qtvtkWindow.createVelocityActor(1,2,3);
        guiState.hasVector = true;
    }

    auto style = dynamic_cast<MouseInteractorStyle*>(ui->vtkBox->interactor()->GetInteractorStyle());
    if (style->meshDataSet == nullptr) style->meshDataSet = qtvtkWindow.getTotalMesh()->GetMapper()->GetInput();

    if (!guiState.hasStreamLine)
    {
        guiState.hasStreamLine = true;
        style->readyToCreateStreamLine = true;
        style->hasPoint1Set = false;
        style->hasPoint2Set = false;
        ui->vtkBox->renderWindow()->Render();
        return;
    }
    else if (guiState.hasStreamLine)
    {
        style->readyToCreateStreamLine = false;
    }
}

void PostMainWindow::changeFloodNumber(int number)
{
    qtvtkWindow.changeFloodNumber(number);
    guiState.floodNumber = number;
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::isoSurfaceChangeFlowNumber(int number)
{
    qtvtkWindow.isoSurfaceChangeFlowNumber(number);
    guiState.isoSurfaceFlowNumber = number;
    changeFloodNumber(number);
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::isoSurfaceValueChanged(double value)
{
    qtvtkWindow.setIsoSurfaceValue(value);
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::changeCutplane(double* origin, double *normal, int cutplaneNumber)
{
    qtvtkWindow.setCutplane(cutplaneNumber, origin,normal);
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::makeNewCutplane()
{
    qtvtkWindow.addNewCutplane();
    selectBoundaryDialog->addCutplaneItem();
    cout << "add new cut plane" << endl;
}

void PostMainWindow::showCutplane(int number, bool flag)
{
    if (flag) qtvtkWindow.addCutplane(number);
    else
    {
        qtvtkWindow.removeCutplane(number);
    }
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::addNewParameter(QString expression, QString name)
{
    qtvtkWindow.addNewParameter(expression.toStdString(), name.toStdString());
    auto style = dynamic_cast<MouseInteractorStyle*>(ui->vtkBox->interactor()->GetInteractorStyle());
    style->parameterNames.emplace_back(name.toStdString());
}

void PostMainWindow::initializeMainWindow()
{
    setIcons();
    setvtkBox();

    //set basicObject checkBox connections
    connect(ui->meshCheckBox, SIGNAL(stateChanged(int)), this, SLOT(meshCheckBoxTriggered()));
    connect(ui->contourCheckBox, SIGNAL(stateChanged(int)), this, SLOT(contourCheckBoxTriggered()));
    connect(ui->shadeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(shadeCheckBoxTriggered()));
    connect(ui->edgeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(edgeCheckBoxTriggered()));
    connect(ui->vectorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(vectorCheckBoxTriggered()));    
    connect(ui->contourSettingButton, SIGNAL(clicked()), this, SLOT(contourSettingButtonTriggered()));
    connect(ui->selectBoundaryButton, SIGNAL(clicked()), this, SLOT(selectBoundaryButtonTriggeded()));

    connect(ui->isoSurfaceCheckBox, SIGNAL(stateChanged(int)), this, SLOT(isoSurfaceCheckBoxTriggered()));
    connect(ui->IsoSurfaceSettingButton, SIGNAL(clicked()), this, SLOT(isoSurfaceSettingButtonTriggered()));
    connect(ui->slicesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slicesCheckBoxTriggered()));
    connect(ui->addSliceButton, SIGNAL(clicked()), this, SLOT(slicesSettingButtonTriggered()));
    connect(ui->streamlineCheckBox, SIGNAL(stateChanged(int)), this, SLOT(streamlineCheckBoxTriggered()));

    connect(ui->addMeridionalPlaneButton, SIGNAL(clicked()), this, SLOT(meridionalPlaneButtonTriggered()));
    connect(ui->addConstHeightPlaneButton, SIGNAL(clicked()), this, SLOT(constHeightPlanneButtonTriggered()));
    //set quick orientation view
    connect(ui->xoyView, SIGNAL(clicked()), this, SLOT(xoyViewTriggered()));
    connect(ui->xozView, SIGNAL(clicked()), this, SLOT(xozViewTriggered()));
    connect(ui->yozView, SIGNAL(clicked()), this, SLOT(yozViewTriggered()));
    connect(ui->xyzView, SIGNAL(clicked()), this, SLOT(xyzViewTriggered()));

    selectBoundaryDialog = new SelectBoundaryDialog(this);
}

void PostMainWindow::setIcons()
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
    ui->actionOpenFile->setIcon(QIcon((iconPath+"open.png").c_str()));
    ui->actionAddAxisActor->setIcon(QIcon((iconPath+"orient_axes.png").c_str()));
    ui->actionAddScalarBarActor->setIcon(QIcon((iconPath+"colorbar.png").c_str()));
    ui->actionAddOutlineActor->setIcon(QIcon((iconPath+"boundbox.png").c_str()));
    ui->actionAddPointInformation->setIcon(QIcon((iconPath+"text.png").c_str()));
    ui->actionCalculatorFunction->setIcon(QIcon((iconPath+"calculator.png").c_str()));
}

void PostMainWindow::setvtkBox()
{
    ui->vtkBox->setRenderWindow(qtvtkWindow.getRenderWindow());
    ui->vtkBox->renderWindow()->Render();
}

void PostMainWindow::meridionalPlaneButtonTriggered()
{
    if(!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }
    else{
        MeridionalPlaneDialog * meridionalplanedialog = new MeridionalPlaneDialog(this);
        connect(meridionalplanedialog, SIGNAL(finishSetZone(int)),this, SLOT(addMeridionalPlane(int)));
        meridionalplanedialog->show();
    }
}

void PostMainWindow::addMeridionalPlane(int zoneNumber)
{
    qtvtkWindow.setMeridionalPlane(zoneNumber,guiState.flowNumber);
    ui->vtkBox->renderWindow()->Render();
}



void PostMainWindow::constHeightPlanneButtonTriggered()
{
    if(!guiState.hasMesh)
    {
        cout << "There are not a grid file yet, please open a grid file first!" << endl;
        return;
    }
    else {
        ConstHeightPlaneDialog * constheightplanedialog = new ConstHeightPlaneDialog(this);
        connect(constheightplanedialog, SIGNAL(finishSetParameters(int, double)), this, SLOT(addConstHeightPlane(int, double)));
        constheightplanedialog->show();
    }

}

void PostMainWindow::addConstHeightPlane(int zoneNumber, double height)
{
    qtvtkWindow.setConstHeightPlane(zoneNumber,guiState.flowNumber,height);
    ui->vtkBox->renderWindow()->Render();
}