//
// Created by Zhouteng Ye on 2024/6/13.
//

#include "PerformanceCurve.h"

//PerformanceCurve::PerformanceCurve();

void PerformanceCurve::UpdateBackPressure(double new_p)
{
  initial_p = target_p;
  target_p = new_p;
}

void PerformanceCurve::AppendNewPoint() {
  n_points +=1;
//  pressure_list.emplace_back()
//  case_list.emplace_back()
//  UpdateBackPressure()
}

void PerformanceCurve::DrawPerformanceCurve() {

}

void SaveFlowData::openFolderAndCopyFiles(const QString &filename) {
  QString folderPath = QFileDialog::getExistingDirectory(nullptr, tr("Select Folder"), "", QFileDialog::ShowDirsOnly);
  if (!folderPath.isEmpty()) {
    // Execute cp command to copy hist.dat to the selected folder
    QString command = QString("cp mon_* hist.dat " + filename +" %1").arg(folderPath);

    process = new QProcess(this);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &SaveFlowData::handleProcessFinished);
    process->start("/bin/bash", QStringList() << "-c" << command);
  }
}

void SaveFlowData::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
  if (exitStatus == QProcess::NormalExit && exitCode == 0) {
    QMessageBox::information(nullptr, tr("Success"), tr("Files copied successfully!"));
  } else {
    QMessageBox::critical(nullptr, tr("Error"), tr("Running error! The files could not be copied!"));
  }
  process->deleteLater(); // Delete process object after it finishes
  process = nullptr;
}



void LoadFlowData::addFileParameter(QVBoxLayout *mainLayout, int labelWidth, const QString &labelText, const QString &defaultValue) {
    QHBoxLayout *layout = new QHBoxLayout();
    QLabel *label = new QLabel(labelText, this);
    label->setMinimumWidth(labelWidth);
    QLineEdit *edit = new QLineEdit(defaultValue, this);
    edit->setReadOnly(true);
    edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(label);
    layout->addWidget(edit);

    parameterEdits.append(edit);
    mainLayout->addLayout(layout);
}
