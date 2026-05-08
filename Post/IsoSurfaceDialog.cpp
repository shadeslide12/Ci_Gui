#include "IsoSurfaceDialog.h"
#include "ui_IsoSurfaceDialog.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

IsoSurfaceDialog::IsoSurfaceDialog(QWidget *parent): QDialog(parent),ui(new Ui::IsoSurfaceDialog)
{
    ui->setupUi(this);
    // connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setParameters()));
    connect(ui->nameComboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(parameterChanged()));
    connect(ui->nameComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(flowNumberChanged()));
    connect(ui->horizontalSlider, SIGNAL(sliderReleased()), this, SLOT(valueChanged()));
    cout << "create iso-surface dialog" << endl;
}

IsoSurfaceDialog::~IsoSurfaceDialog()
{
    delete ui;
    cout << "destroy iso-surface dialog" << endl;
}

void IsoSurfaceDialog::setIsoSurfaceDialog(std::vector<vtkAesReader::FlowData> flows, int flowNumber, int floodNumber, double value)
{
    flowdata = flows;
    ui->nameComboBox->blockSignals(true);
    ui->nameComboBox_2->blockSignals(true);
    ui->horizontalSlider->blockSignals(true);

    ui->nameComboBox->clear();
    ui->nameComboBox_2->clear();
    for (auto &x : flows)
    {
        ui->nameComboBox_2->addItem(x.name.c_str());
        ui->nameComboBox->addItem(x.name.c_str());
    }

    if (flowNumber >= 0 && flowNumber < static_cast<int>(flows.size())) {
        ui->nameComboBox->setCurrentIndex(flowNumber);

        double minValue = flows[flowNumber].range[0];
        double maxValue = flows[flowNumber].range[1];
        int sliderValue = 50;
        if (maxValue != minValue) {
            double percent = (value - minValue) / (maxValue - minValue);
            if (percent < 0.0) percent = 0.0;
            if (percent > 1.0) percent = 1.0;
            sliderValue = static_cast<int>(percent * 100.0 + 0.5);
        }
        ui->horizontalSlider->setValue(sliderValue);
    }
    if (floodNumber >= 0 && floodNumber < static_cast<int>(flows.size())) {
        ui->nameComboBox_2->setCurrentIndex(floodNumber);
    }

    ui->horizontalSlider->blockSignals(false);
    ui->nameComboBox_2->blockSignals(false);
    ui->nameComboBox->blockSignals(false);
}

void IsoSurfaceDialog::setParameters()
{
    // double value = stod(ui->textsurfaceValue->text().toStdString());
    // if (value < m || value > M)
    // {
    //     cout << "parameter value less than the min data or larger than the max data, please set the value again!" << endl;
    //     return;
    // }

    // emit(finishSetParameters(value));
}

void IsoSurfaceDialog::valueChanged()
{
    if (flowdata.empty() || ui->nameComboBox->currentIndex() < 0) {
        return;
    }
    auto range = this->flowdata[ui->nameComboBox->currentIndex()].range;
    double value = range[0] + (range[1]-range[0])*ui->horizontalSlider->value()/100.0;
    emit(changeIsoSurfaceValue(value));
}

void IsoSurfaceDialog::parameterChanged()
{
    // int number = ui->comboBox->currentIndex();
    emit(changeFloodParameter(ui->nameComboBox_2->currentIndex()));
}

void IsoSurfaceDialog::flowNumberChanged()
{
    if (flowdata.empty() || ui->nameComboBox->currentIndex() < 0) {
        return;
    }
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setValue(50);
    ui->horizontalSlider->blockSignals(false);
    ui->nameComboBox_2->setCurrentIndex(ui->nameComboBox->currentIndex());
    emit(changeFlowParameter(ui->nameComboBox->currentIndex()));
}
