#ifndef LOADPROFILE_H
#define LOADPROFILE_H

#include <QDialog>
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
#include <QMessageBox>
#include "PreProcessSettings.h"

namespace Ui {
class LoadProfile;
}

class LoadProfile : public QDialog
{
    Q_OBJECT

public:
    explicit LoadProfile(PreProcessSettings *cfg_in, int zone_id_in, int bc_id_in, QWidget *parent = nullptr);
    ~LoadProfile();

    void onDirectoryDoubleClicked(const QModelIndex &index);
    void onDirectoryClicked(const QModelIndex &index);

private slots:
    void on_profile_close_button_clicked();

    void on_profile_back_button_clicked();

    void on_profile_load_button_clicked();

    std::pair<int, int> getFileDimensions(const std::string& filepath);

private:
    Ui::LoadProfile *ui;

    QString currentFile;
    PreProcessSettings *cfg;
    int zone_id;
    int bc_id;
};

#endif // LOADPROFILE_H
