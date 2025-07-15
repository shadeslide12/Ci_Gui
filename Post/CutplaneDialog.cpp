#include "CutplaneDialog.h"
#include "ui_CutplaneDialog.h"
#include <string>
using std::stod;
using std::string;
#include <iostream>
using std::cout;
using std::endl;

using std::vector;
CutplaneDialog::CutplaneDialog(QWidget *parent): QDialog(parent),ui(new Ui::CutplaneDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setParameters()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCutplaneNumber(int)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(createSignal()));

    // 连接新添加的控件信号
    connect(ui->Combo_SLiceLocation, SIGNAL(currentIndexChanged(int)), this, SLOT(onSliceLocationChanged(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));
    connect(ui->Btn_ExtractSlice, SIGNAL(clicked()), this, SLOT(onExtractSliceClicked()));
    
    // 初始化
    currentAxis = 0; // 默认为X轴
    // 初始化模型边界值为0
    for (int i = 0; i < 6; i++) {
        modelBounds[i] = 0.0;
    }
    
    // 设置滑块初始范围
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setValue(50);

    ui->label_Origin_x->hide();
    ui->label_Origin_y->hide();
    ui->label_Origin_z->hide();

    ui->label_Noraml_x->hide();
    ui->label_Noraml_y->hide();
    ui->label_Noraml_z->hide();

    ui->lineEdit_Origin_x->hide();
    ui->lineEdit_Origin_y->hide();
    ui->lineEdit_Origin_z->hide();

    ui->lineEdit_Noraml_x->hide();
    ui->lineEdit_Noraml_y->hide();
    ui->lineEdit_Noraml_z->hide();


    updateValueLabel(0.0);
}

CutplaneDialog::~CutplaneDialog()
{
    delete ui;
}

void CutplaneDialog::createSignal()
{
    createFlag = true;
    // emit(createNewCutplane());
}

void CutplaneDialog::setCutplaneDialog(vector<vtkSmartPointer<vtkPlane>> planes)
{
    int n = planes.size();
    for (int i = 1; i <= n; i++)
    {
        string name = "cutplane";
        name += std::to_string(i);
        ui->comboBox->addItem(name.c_str());

        origin.push_back(planes[i-1]->GetOrigin());
        normal.push_back(planes[i-1]->GetNormal());
    }
    ui->lineEdit_Origin_x->setText(std::to_string(origin[0][0]).c_str());
    ui->lineEdit_Origin_y->setText(std::to_string(origin[0][1]).c_str());
    ui->lineEdit_Origin_z->setText(std::to_string(origin[0][2]).c_str());
    ui->lineEdit_Noraml_x->setText(std::to_string(normal[0][0]).c_str());
    ui->lineEdit_Noraml_y->setText(std::to_string(normal[0][1]).c_str());
    ui->lineEdit_Noraml_z->setText(std::to_string(normal[0][2]).c_str());

    updateSliderRange();

}

void CutplaneDialog::changeCutplaneNumber(int number)
{
    if (origin.size() == 0) return;
    ui->lineEdit_Origin_x->setText(std::to_string(origin[number][0]).c_str());
    ui->lineEdit_Origin_y->setText(std::to_string(origin[number][1]).c_str());
    ui->lineEdit_Origin_z->setText(std::to_string(origin[number][2]).c_str());
    ui->lineEdit_Noraml_x->setText(std::to_string(normal[number][0]).c_str());
    ui->lineEdit_Noraml_y->setText(std::to_string(normal[number][1]).c_str());
    ui->lineEdit_Noraml_z->setText(std::to_string(normal[number][2]).c_str());
}

void CutplaneDialog::setParameters()
{
    curOrigin[0] = stod(ui->lineEdit_Origin_x->text().toStdString());
    curOrigin[1] = stod(ui->lineEdit_Origin_y->text().toStdString());
    curOrigin[2] = stod(ui->lineEdit_Origin_z->text().toStdString());
    curNormal[0] = stod(ui->lineEdit_Noraml_x->text().toStdString());
    curNormal[1] = stod(ui->lineEdit_Noraml_y->text().toStdString());
    curNormal[2] = stod(ui->lineEdit_Noraml_z->text().toStdString());
    emit(finishSetParameters(curOrigin, curNormal, ui->comboBox->currentIndex()));
    if (createFlag) emit(createNewCutplane());
}

// 新增：设置模型边界值
void CutplaneDialog::setModelBounds(double* bounds)
{
    if (bounds != nullptr) {
        for (int i = 0; i < 6; i++) {
            modelBounds[i] = bounds[i];
        }
        updateSliderRange();
    }
}

// 处理平面类型变化
void CutplaneDialog::onSliceLocationChanged(int index)
{
    currentAxis = index;
    updateSliderRange();
}

// 处理滑块值变化
void CutplaneDialog::onSliderValueChanged(int value)
{
    // 将滑块值（0-100）映射到当前轴的范围内
    double min = 0.0, max = 1.0;
    switch (currentAxis) {
        case 0: // X轴
            min = modelBounds[0];
            max = modelBounds[1];
            break;
        case 1: // Y轴
            min = modelBounds[2];
            max = modelBounds[3];
            break;
        case 2: // Z轴
            min = modelBounds[4];
            max = modelBounds[5];
            break;
    }
    
    double range = max - min;
    double actualValue = min + (range * value / 100.0);
    
    updateValueLabel(actualValue);
    setPlanePosition(actualValue);
    std::cout << "【Debug】emit signal slicelocation";
    emit sliceLocation(actualValue,currentAxis);
}

// 处理提取切片按钮点击
void CutplaneDialog::onExtractSliceClicked()
{
    // 根据当前设置创建新切面
    createFlag = true;
    emit(createNewCutplane());
}

// 更新滑块范围
void CutplaneDialog::updateSliderRange()
{
    // 滑块范围固定为0-100，实际值通过映射计算
    ui->horizontalSlider->setValue(50); // 默认在中间位置
    
    // 更新当前值显示
    onSliderValueChanged(50);
}

// 更新值标签显示
void CutplaneDialog::updateValueLabel(double value)
{
    QString axisName;
    switch (currentAxis) {
        case 0: axisName = "X"; break;
        case 1: axisName = "Y"; break;
        case 2: axisName = "Z"; break;
    }
    
    ui->label_ValueLocation->setText(QString("%1 : %2").arg(axisName).arg(value, 0, 'f', 4));
}

// 根据滑块值设置切面位置
void CutplaneDialog::setPlanePosition(double value)
{
    // 根据当前轴和值设置切面的原点和法向量
    switch (currentAxis) {
        case 0: // X轴 - YZ平面
            curOrigin[0] = value;
            curOrigin[1] = 0.0;
            curOrigin[2] = 0.0;
            curNormal[0] = 1.0;
            curNormal[1] = 0.0;
            curNormal[2] = 0.0;
            break;
        case 1: // Y轴 - XZ平面
            curOrigin[0] = 0.0;
            curOrigin[1] = value;
            curOrigin[2] = 0.0;
            curNormal[0] = 0.0;
            curNormal[1] = 1.0;
            curNormal[2] = 0.0;
            break;
        case 2: // Z轴 - XY平面
            curOrigin[0] = 0.0;
            curOrigin[1] = 0.0;
            curOrigin[2] = value;
            curNormal[0] = 0.0;
            curNormal[1] = 0.0;
            curNormal[2] = 1.0;
            break;
    }
    
    // 更新UI显示
    ui->lineEdit_Origin_x->setText(QString::number(curOrigin[0]));
    ui->lineEdit_Origin_y->setText(QString::number(curOrigin[1]));
    ui->lineEdit_Origin_z->setText(QString::number(curOrigin[2]));
    ui->lineEdit_Noraml_x->setText(QString::number(curNormal[0]));
    ui->lineEdit_Noraml_y->setText(QString::number(curNormal[1]));
    ui->lineEdit_Noraml_z->setText(QString::number(curNormal[2]));
}