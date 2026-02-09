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