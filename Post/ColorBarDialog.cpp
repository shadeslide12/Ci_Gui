#include "ColorBarDialog.h"
#include "ui_ColorBarDialog.h"

#include <QString>
#include <stdlib.h>
using std::string;
using std::vector;
using std::to_string;
using std::stod; using std::stoi;
#include <iostream>
using std::cout; using std::endl;

#include <vtkLookupTable.h>
#include <exception>

ColorBarDialog::ColorBarDialog(QWidget *parent):QDialog(parent),ui(new Ui::ColorBarDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setParameters()));
    connect(ui->nameComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFlowNumber(int)));
    cout << "create colorbar dialog" << endl;
}

ColorBarDialog::~ColorBarDialog()
{
    cout << "destroy colorbar dialog" << endl;
    delete ui;
}

void ColorBarDialog::setColorBarDialog(vector<vtkAesReader::FlowData> flows, int flowNumber)
{
    auto flow = flows[flowNumber];
    flowInfo = flows;
    rangem = flow.range[0];
    rangeM = flow.range[1];
    m = flow.scalarBar->GetLookupTable()->GetRange()[0];
    M = flow.scalarBar->GetLookupTable()->GetRange()[1];
    for (auto &x : flows)
    {
        ui->nameComboBox->addItem(x.name.c_str());
    }
    ui->nameComboBox->setCurrentIndex(flowNumber);
    string rangeText = "(" + to_string(rangem) + ", " + to_string(rangeM) + ")";
    ui->textParameterRange->setText(rangeText.c_str());
    ui->textColorBarmin->setText(to_string(m).c_str());
    ui->textColorBarMax->setText(to_string(M).c_str());
    ui->textColorNumber->setText(to_string(flow.scalarBar->GetNumberOfLabels()).c_str());
}

void ColorBarDialog::changeFlowNumber(int number)
{
    auto flow = flowInfo[number];
    rangem = flow.range[0];
    rangeM = flow.range[1];
    m = flow.range[0];
    M = flow.range[1];

    string rangeText = "(" + to_string(rangem) + ", " + to_string(rangeM) + ")";
    ui->textParameterRange->setText(rangeText.c_str());
    ui->textColorBarmin->setText(to_string(m).c_str());
    ui->textColorBarMax->setText(to_string(M).c_str());
    ui->textColorNumber->setText(to_string(flow.scalarBar->GetNumberOfLabels()).c_str());
    emit(finishSetParameters(m, M, flow.scalarBar->GetNumberOfLabels(), ui->nameComboBox->currentIndex()));
}

void ColorBarDialog::setParameters()
{
    try
    {
        m = stod(ui->textColorBarmin->text().toStdString());
        M = stod(ui->textColorBarMax->text().toStdString());
        colorNumber = stoi(ui->textColorNumber->text().toStdString());
    }
    catch (const std::exception& e)
    {
        cout << "catch exception while setting parameters, please check." << endl << 
        "exception is: " << e.what() << endl;
        this->close();
        return;
    }

    if ((colorNumber < 2 || colorNumber > 256) || (m > M))
    {
        cout << "error set colorbar parameters, please check and set again!" << endl;
        this->close();
        return;
    }
    emit(finishSetParameters(m, M, colorNumber, ui->nameComboBox->currentIndex()));
}