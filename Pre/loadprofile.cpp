#include "loadprofile.h"
#include "ui_loadprofile.h"

LoadProfile::LoadProfile(PreProcessSettings *cfg_in, int zone_id_in, int bc_id_in, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoadProfile)
{
  ui->setupUi(this);

  cfg=cfg_in;
  zone_id = zone_id_in;
  bc_id = bc_id_in;
  QFileSystemModel *model = new QFileSystemModel(this);
  QString currentDir = QDir::currentPath();
  model->setRootPath(currentDir);
  ui->profile_file->setModel(model);
  ui->profile_file->setRootIndex(model->index(currentDir));

  connect(ui->profile_file, &QTreeView::doubleClicked, this, &LoadProfile::onDirectoryDoubleClicked);
  connect(ui->profile_file, &QTreeView::clicked, this, &LoadProfile::onDirectoryClicked);
}

void LoadProfile::onDirectoryDoubleClicked(const QModelIndex &index)
{
  QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->profile_file->model());
  if (model->isDir(index)) {
    ui->profile_file->setRootIndex(index);
  }
}

void LoadProfile::onDirectoryClicked(const QModelIndex &index)
{
    QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->profile_file->model());
    if (!model->isDir(index)) {
        currentFile = model->filePath(index);
    }
}

void LoadProfile::on_profile_close_button_clicked()
{
  this->close();
}

void LoadProfile::on_profile_back_button_clicked()
{
  QModelIndex currentIndex = ui->profile_file->rootIndex();
  if (currentIndex.parent().isValid()) {
    ui->profile_file->setRootIndex(currentIndex.parent());
  }
}


void LoadProfile::on_profile_load_button_clicked()
{
  if (currentFile.isEmpty()) {
    QMessageBox::information(nullptr, "Info Dialog", "No file selected");
    return;
  }

  std::ifstream file(currentFile.toStdString());

  if (!file.is_open()) {
    QMessageBox::information(nullptr, "Info Dialog", "Error opening file: " + currentFile);
    return ;
  }

  int numRow, direction;
  if (!(file >> numRow >> direction)) {
    QMessageBox::information(nullptr, "Info Dialog", "Error opening file: " + currentFile);
    return ;
  }
  file.close();

  std::pair<int, int> row_and_column= getFileDimensions(currentFile.toStdString());
  if (numRow != row_and_column.first) {
    QMessageBox::information(nullptr, "Info Dialog", "number of row is not consistent with actual rows");
    return;
  }

  int bnd_type = cfg->bnd[zone_id].Types[bc_id];
  int num_var;
  if (bnd_type==4 || bnd_type==6)
    num_var=cfg->bnd[zone_id].Inlets[bc_id].len_profile;
  else
    num_var=cfg->bnd[zone_id].Outlets[bc_id].len_profile;
  if (row_and_column.second != num_var) {
    QMessageBox::information(nullptr, "Info Dialog", QString::fromStdString("RANS model is "+
      cfg->GUI_rans_model+". There should be " + std::to_string(num_var) + " variables, however is now " +
      std::to_string(row_and_column.second) + " in profile file."));
    return;
  }

  file.open(currentFile.toStdString());
  std::string line;
  // 忽略到行尾，准备读取下一行
  std::getline(file, line);

  if (bnd_type==4 || bnd_type == 6) {
    cfg->bnd[zone_id].Inlets[bc_id].len_profile = num_var;
    cfg->bnd[zone_id].Inlets[bc_id].num_profile_in=numRow;
    cfg->bnd[zone_id].Inlets[bc_id].profile_distribution_direction_in=direction;
    cfg->bnd[zone_id].Inlets[bc_id].points_data_in.clear();
  }
  else
  {
    cfg->bnd[zone_id].Outlets[bc_id].num_profile_out=numRow;
    cfg->bnd[zone_id].Outlets[bc_id].profile_distribution_direction_out=direction;
    cfg->bnd[zone_id].Outlets[bc_id].points_data_out.clear();
  }

  // 读取接下来的 numRows 行
  std::vector<std::vector<std::string>> data;
  for (int i=0; i<numRow; i++){

    std::getline(file, line);
    std::istringstream iss(line);
    std::string entry;

    std::vector<double> line_profile;
    // 逐个读取
    while(iss>>entry)
    {
      double dat=std::stod(entry);
      line_profile.emplace_back(dat);
    }
    if (bnd_type==4 || bnd_type == 6)
      cfg->bnd[zone_id].Inlets[bc_id].points_data_in.emplace_back(line_profile);
    else {
      cfg->bnd[zone_id].Outlets[bc_id].points_data_out.emplace_back(line_profile);
      std::cout<<"yes"<<std::endl;
    }

  }
//
//  for (int i=0; i<numRow; i++) {
//    for (int j = 0; j < num_var; j++) {
//      if (bnd_type == 4 || bnd_type == 6)
//        std::cout<<cfg->bnd[zone_id].Inlets[bc_id].points_data_in[i][j]<<" ";
//      else
//        std::cout<<cfg->bnd[zone_id].Outlets[bc_id].points_data_out[i][j]<<" ";
//    }
//  }

  file.close();
  this->close();

}
std::pair<int, int> LoadProfile::getFileDimensions(const std::string& filepath) {
    std::ifstream inFile(filepath);
    std::string line;
    int rowCount = 0;
    int columnCount = 0;

    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open the file: " + filepath);
    }

    // Skip the header line
    std::getline(inFile, line);

    // Process the first data line to determine the number of columns
    if (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string cell;
        columnCount = 0;  // Initialize column count

        while (iss >> cell) {
            columnCount++;
        }
        rowCount++;  // Count the first row of data
    }

    // Process remaining data lines to count rows
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            rowCount++;  // Count each additional row
        }
    }

    inFile.close();
    return {rowCount, columnCount};
}

LoadProfile::~LoadProfile()
{
    delete ui;
}

