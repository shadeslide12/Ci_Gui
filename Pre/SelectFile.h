#pragma once
#ifndef SELECTFILE_H
#define SELECTFILE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QComboBox>
#include <QTreeWidgetItem>
#include "ToolsWriteCGNS.h"
#include "PreProcessSettings.h"
#include "InputParser.h"
#include "BoundaryMerger.h"

namespace Ui {
class SelectFile;
}

class SelectFile : public QDialog
{
    Q_OBJECT

public:
    explicit SelectFile(PreProcessSettings *cfg_in, QWidget *parent = nullptr);
    ~SelectFile();

    PreProcessSettings *cfg;

private slots:
    void onDirectoryDoubleClicked(const QModelIndex &index);

    void onDirectoryClicked(const QModelIndex &index);

    void Destroy();

    void on_back_clicked();

    void on_select_clicked();

    void on_unselect_clicked();

    void on_boundary_merger_button_clicked();

    void on_load_file_button_clicked();

    void on_show_boundary_button_clicked();

    void ShowBCTree();

    std::vector<QString> extractFileNames(QStandardItemModel* model);

private:
    Ui::SelectFile *ui;
    QString currentFile;
    QStandardItemModel *selectedFilesModel;

//    std::map<std::string, int> set_types;
//    std::map<std::string, std::vector<std::vector<std::string>>> set_rules;

  MergerCore *merger;

  bool mergeFlag=false;

};


#endif // SELECTFILE_H
