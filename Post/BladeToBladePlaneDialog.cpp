//
// Created for blade-to-blade view
//

#include "BladeToBladePlaneDialog.h"
#include "ui_BladeToBladePlaneDialog.h"


BladeToBladePlaneDialog::BladeToBladePlaneDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::BladeToBladePlaneDialog) {
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(setParameters()));
}

BladeToBladePlaneDialog::~BladeToBladePlaneDialog() {
    delete ui;
}

void BladeToBladePlaneDialog::setParameters()
{
    span = stod(ui->spanLineEdit->text().toStdString());
    emit(finishSetParameters(span));
    this->close();
}
