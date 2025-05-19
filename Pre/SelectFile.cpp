#include "SelectFile.h"
#include "ui_SelectFile.h"
#include <fstream>
#include <iostream>
#include <QMenu>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <vector>
#include <QString>
#include <QDir>
#include <QTreeView>
#include <QDebug>

SelectFile::SelectFile(PreProcessSettings *cfg_in, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectFile)
{
    ui->setupUi(this);
    cfg=cfg_in;
    merger = new MergerCore(cfg);

    ui->load_file_button->setEnabled(false);

    QFileSystemModel *model = new QFileSystemModel(this);
    model->setNameFilters(QStringList()<<"*.cgns"<<"*.cas.h5");
    model->setNameFilterDisables(false);
    QString currentDir = QDir::currentPath();
    model->setRootPath(currentDir);
    ui->directory_file->setModel(model);
    ui->directory_file->setRootIndex(model->index(currentDir));

    connect(ui->directory_file, &QTreeView::doubleClicked, this, &SelectFile::onDirectoryDoubleClicked);
    connect(ui->directory_file, &QTreeView::clicked, this, &SelectFile::onDirectoryClicked);

    selectedFilesModel = new QStandardItemModel(this);
    ui->selected_file->setModel(selectedFilesModel);

    ui->boundary_merger_button->setEnabled(false);
}

SelectFile::~SelectFile()
{
    delete ui;
    //* Avoid Memory Leakage
    delete merger;
}

void SelectFile::onDirectoryDoubleClicked(const QModelIndex &index)
{
    QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->directory_file->model());
    if (model->isDir(index)) {
        ui->directory_file->setRootIndex(index);
    }
}

void SelectFile::onDirectoryClicked(const QModelIndex &index)
{
    QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->directory_file->model());
    if (!model->isDir(index)) {
        currentFile = model->filePath(index);
    }
}


void SelectFile::on_back_clicked()
{
    QModelIndex currentIndex = ui->directory_file->rootIndex();
    if (currentIndex.parent().isValid()) {
        ui->directory_file->setRootIndex(currentIndex.parent());
    }
}

void SelectFile::on_select_clicked()
{
    if (!currentFile.isEmpty()) {
        bool alreadyAdded = false;
        for (int i = 0; i < selectedFilesModel->rowCount(); ++i) {
            QStandardItem *item = selectedFilesModel->item(i);
            if (item && item->text() == currentFile) {
                alreadyAdded = true;
                break;
            }
        }
        if (!alreadyAdded) {
            QStandardItem *item = new QStandardItem(currentFile);
            selectedFilesModel->appendRow(item);
        }
    }
}

void SelectFile::on_unselect_clicked()
{
    QModelIndexList selectedIndexes = ui->selected_file->selectionModel()->selectedIndexes();

    for (const QModelIndex &index : selectedIndexes) {
        selectedFilesModel->removeRow(index.row());
    }
}

std::vector<QString> SelectFile::extractFileNames(QStandardItemModel* model) {
    std::vector<QString> fileNames;

    if (model != nullptr) {
        for (int i = 0; i < model->rowCount(); ++i) {
            QStandardItem *item = model->item(i);
            if (item) {
                QFileInfo fileInfo(item->text());
                QString baseName = fileInfo.baseName();
                fileNames.push_back(baseName);
            }
        }
    }
    return fileNames;
}

void SelectFile::Destroy()
{
  this->close();
}

void SelectFile::on_boundary_merger_button_clicked()
{

  std::vector<QString> fileNames = extractFileNames(selectedFilesModel);
  std::vector<std::string> stdfileNames;
  for (const auto& qstr : fileNames) {
    stdfileNames.push_back(qstr.toStdString());
  }

  cfg->mesh_files = stdfileNames;

  BoundaryMerger *boundary_merger = new BoundaryMerger(cfg, merger);
  boundary_merger->setModal(true);
  boundary_merger->show();
  mergeFlag=true;

}

void SelectFile::on_show_boundary_button_clicked()
{
//  BoundaryMerger
  //* Ensure user selected Mesh files
  if (selectedFilesModel->rowCount() <= 0) {
    QMessageBox::warning(this, "warning", "Please Select a Mesh File");
    return;
  }
  std::vector<QString> fileNames = extractFileNames(selectedFilesModel);
  std::vector<std::string> stdfileNames;
  for (const auto& qstr : fileNames) {
    stdfileNames.push_back(qstr.toStdString());
  }

  //* fix the bug in selecting Files
  QStandardItem *item = selectedFilesModel->item(0);
  if (item) {
    QFileInfo fileInfo(item->text());
    QString fileDir = fileInfo.absolutePath();
    QDir::setCurrent(fileDir);
    qDebug() << "Changed working directory to: " << fileDir;
  }


  cfg->mesh_files = stdfileNames;
  cfg->num_meshes = cfg->mesh_files.size();

  merger->GenStep1File(mergeFlag);
  merger->GenerateStep2();
  merger->LoadStep2();

  ShowBCTree();

  ui->boundary_merger_button->setEnabled(true);
  ui->load_file_button->setEnabled(true);

}

void SelectFile::on_load_file_button_clicked(){
  PreMainModule SolverPre;
  SolverPre.LoadYAMLConfigs(2);
  SolverPre.ConvertStep2_3_yaml();
  cfg->LoadYAML(global_pre_setup_yaml);
  this->close();
}

void SelectFile::ShowBCTree() {
  ui->step1_bc_tree->clear();
  ui->step1_bc_tree->setColumnCount(1);
  for (int i=0; i< cfg->num_meshes; i++) {
    QTreeWidgetItem* zoneItem= new QTreeWidgetItem();
    ui->step1_bc_tree->addTopLevelItem(zoneItem);
    QLabel *zoneLabel = new QLabel();
    zoneLabel->setText(QString::fromStdString(cfg->mesh_files[i]));
    ui->step1_bc_tree->setItemWidget(zoneItem, 0, zoneLabel);
    for (const auto &pair: merger->zone_subgroups[i]) {
      for (int i=0; i< pair.second.size(); i++)
      {
        QTreeWidgetItem* BCItem= new QTreeWidgetItem(zoneItem);
        QLabel *BCLabel = new QLabel();
        BCLabel->setText(QString::fromStdString(pair.second[i]));
        ui->step1_bc_tree->setItemWidget(BCItem,0,BCLabel);
      }
    }
  }
  ui->step1_bc_tree->expandAll();
}