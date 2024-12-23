#include "PreMainWindow.h"
#include "ui_PreMainWindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QProgressBar>
#include <QDebug>

PreMainWindow::PreMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PreMainWindow)
    , process(new QProcess(this))
    ,timer (new QTimer(this))
    ,residualplot(new Residual_Plot)
    ,performPlot(new Perform_Plot(this))
    ,monitorplot(new MonitorPlot(this))
    ,simulationDataManager(new SimulationDataManager(this))
    ,plotManager(new PlotManager(this))
{

  ui->setupUi(this);
  Setup_UI();
  setup_UiElements();
  setup_Connection();
  ui->scrollArea->setEnabled(false);
  connect(process, &QProcess::readyReadStandardOutput, this, &PreMainWindow::runOutputWindowReady);
  connect(process, &QProcess::errorOccurred, this, &PreMainWindow::handleError);
  connect(process, &QProcess::readyReadStandardError, this, &PreMainWindow::runOutputWindowError);
  connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, &PreMainWindow::showFinishDialog);

  //* [New]Residual Plot Start Here
  plotManager->initializePlots(residualplot,monitorplot,performPlot);

  ui->load_steady_flow->setVisible(false);
  ui->run_pre_process->setVisible(false);
  ui->saveYAMLButton->setVisible(false);
}

void PreMainWindow::runOutputWindowReady()
{
  QByteArray output = process->readAllStandardOutput();
  ui->runOutputWindow->append(output);
}

void PreMainWindow::runOutputWindowError()
{
  ui->runOutputWindow->append(process->readAllStandardError());
  ui->runOutputWindow->append(process->errorString());
  QString message= "Run error!\n"  + process->readAllStandardError() + "\n" + process->errorString();
  QMessageBox::information(nullptr, "Error Dialog", message);
  ui->continue_simulation_button->setEnabled(true);
  ui->run_pre_process->setEnabled(true);
  on_stop_simulation_button_clicked();
}


PreMainWindow::~PreMainWindow(){
    delete ui;
}

void PreMainWindow::on_actionGeneral_triggered(){
  on_stackedWidget_currentChanged(0);
}

void PreMainWindow::on_actionBC_triggered(){
  on_stackedWidget_currentChanged(3);
  Assign_BC();
}

void PreMainWindow::on_actionTurbo_triggered(){
  on_stackedWidget_currentChanged(1);
  Assign_Turbomachinery();
}

void PreMainWindow::on_actionSolver_triggered(){
  on_stackedWidget_currentChanged(2);
}

void PreMainWindow::on_actionactionSaveTab_triggered(){
  on_stackedWidget_currentChanged(5);
  Assign_Run();
}


void PreMainWindow::on_actionactionFilmCooling_triggered()
{
  on_stackedWidget_currentChanged(4);
  if (!cfg.is_film_generate)
    Assign_Film();
}


void PreMainWindow::Setup_UI()
{
  Setup_Validators();
  Assign_Value();
  setIcons();

}

void PreMainWindow::setIcons()
{
    const std::string iconPath = ":/PreIcons/";

    //toolBar's icons
  ui->toolBar->setIconSize(QSize(35,35));
  ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->actionGeneral->setIcon(QIcon((iconPath+"general.png").c_str()));
  ui->actionGeneral->setText("General");
  ui->actionTurbo->setIcon(QIcon((iconPath+"turbomachinery.png").c_str()));
  ui->actionTurbo->setText("Turbo");
  ui->actionSolver->setIcon(QIcon((iconPath+"flow.png").c_str()));
  ui->actionSolver->setText("Initial\n Flow");
  ui->actionBC->setIcon(QIcon((iconPath+"bc.png").c_str()));
  ui->actionBC->setText("Boundary\n Condition");
  ui->actionactionSaveTab->setIcon(QIcon((iconPath+"save.png").c_str()));
  ui->actionactionSaveTab->setText("Run\n Simulation");
  ui->actionactionFilmCooling->setIcon(QIcon((iconPath+"film.png").c_str()));
  ui->actionactionFilmCooling->setText("Film \nCooling");
}

void PreMainWindow::Setup_Validators()
{
  QDoubleValidator *doubleValidator = new QDoubleValidator(this);
  QIntValidator *intValidator = new QIntValidator(this);
  ui->lineEdit_des_dx->setValidator(doubleValidator);
  ui->lineEdit_les_dt->setValidator(doubleValidator);
  ui->lineEdit_les_dx->setValidator(doubleValidator);
  return;
}

void PreMainWindow::Assign_Value()
{
  Assign_General();
  Assign_Turbomachinery();
  Assign_BC();
  if (cfg.isFilmCoolModel && !cfg.is_film_generate)
    Assign_Film();
  Assign_Run();
  Assign_Solver();
  Assign_VTK();
}

void PreMainWindow::Assign_VTK()
{
#ifndef NO_VTK_WINDOW
  if(cfg.num_meshes > 0) {
    vector<vector<vtkSmartPointer<vtkUnstructuredGrid>>> datasets;
    vector<vector<vtkSmartPointer<vtkActor>>> actors(cfg.num_meshes);
    for (int i = 0; i < cfg.num_meshes; i++) {
      std::string filename = cfg.mesh_files[i] + ".cgns";
      CGNSReader reader(filename);
      vector<vtkSmartPointer<vtkUnstructuredGrid>> ds = reader.getDataSet();
      datasets.push_back(ds);
    }
    for (int i = 0; i < datasets.size(); i++) {
      for (int j = 1; j < datasets[i].size(); j++) {
        vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
        mapper->SetInputData(datasets[i][j]);
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actors[i].push_back(actor);
      }
    }
//    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow= vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
//    vtkSmartPointer<vtkRenderer> renderer= vtkSmartPointer<vtkRenderer>::New();
//    QVTKOpenGLNativeWidget *vtkWidget= new QVTKOpenGLNativeWidget(this);
    for (int i = 0; i < actors.size(); i++) {
      for (int j = 0; j < actors[i].size(); j++) {
        renderer->AddActor(actors[i][j]);
      }
    }

    renderer->ResetCamera();
    vtkWidget->renderWindow()->Render();
  }
  if (!isVTKWindow) {
    renderer->SetBackground(1.0, 1.0, 1.0);
    renderer->SetBackground2(0.529, 0.8078, 0.92157);
    renderer->SetGradientBackground(true);
    isVTKWindow = true;
    renderWindow->AddRenderer(renderer);
    vtkWidget->setRenderWindow(renderWindow);
    ui->RunGraphLayout->insertWidget(0, vtkWidget, 1);
    vtkWidget->renderWindow()->Render();
  }
#endif
}


void PreMainWindow::Assign_Run()
{
  ui->spinCPU->setValue(cfg.CPU_core);

  SetupIntLineEdit(this, ui->output_steady_lineEdit, int(cfg.file_write_step));
  SetupDoubleLineEdit(this, ui->CFL_lineEdit, cfg.solver_cfl);
  SetupIntLineEdit(this, ui->iteration_step_lineEdit, cfg.solver_iteration);

  SetupDoubleLineEdit(this, ui->period_lineEdit, cfg.unsteady_period_time);
  SetupIntLineEdit(this, ui->n_cycle_lineEdit, cfg.unsteady_n_period);
//  std::cout<<cfg.unsteady_output_step<<std::endl;
  SetupIntLineEdit(this, ui->step_per_cycle_lineEdit, cfg.unsteady_n_step);
  SetupIntLineEdit(this, ui->output_unsteady_lineEdit, cfg.unsteady_output_step);

  ui->current_p_value->setText(QString::number(cfg.p_curve.initial_p,'f',2));

  getBackPressure();

  if (cfg.isRunPerformanceCurve){
    ui->checkBox_performance->setChecked(true);
    ui->checkBox_performance->toggled(true);
    ui->current_p_value->setText(QString::number(cfg.p_curve.initial_p,'f',2));
    SetupDoubleLineEdit(this, ui->target_p_value, cfg.p_curve.target_p);
  }
  else
  {
    ui->checkBox_performance->setChecked(false);
    ui->checkBox_performance->toggled(false);
  }

  GetMonitorTree();

}

void PreMainWindow::GetMonitorTree()
{
  ui->monitor_tree->clear();
 for (int i=0;i<cfg.num_monitor; i++)
  {
    QTreeWidgetItem* treeItem= new QTreeWidgetItem();
    ui->monitor_tree->addTopLevelItem(treeItem);

    QComboBox *OneComboType = new QComboBox(this);
    QComboBox *OneComboFace = new QComboBox(this);
    QComboBox *OneComboMFace = new QComboBox(this);
    QComboBox *OneComboAverage = new QComboBox(this);
    QPushButton *OneButton = new QPushButton(this);

    for (auto iter:GUI_monitor_dict)
      OneComboType->addItem(QString::fromStdString(iter.first));

    for (auto iter:GUI_monitor_average)
      OneComboAverage->addItem(QString::fromStdString(iter.first));

    for (int j=0; j<cfg.monitor->global_bc_names.size(); j++) {
      OneComboFace->addItem(QString::fromStdString(cfg.monitor->global_bc_names[j]));
      OneComboMFace->addItem(QString::fromStdString(cfg.monitor->global_bc_names[j]));
    }

    int monitor_type = cfg.monitor->monitors[i].type;
    int average_type = cfg.monitor->monitors[i].average_type;
    int face_id = cfg.monitor->monitors[i].face_id;
    OneComboFace->setCurrentText(QString::fromStdString(cfg.monitor->global_bc_names[face_id-1]));
    int Mface_id = cfg.monitor->monitors[i].match_face_id;
    if (Mface_id != 0) {
      OneComboMFace->setCurrentText(QString::fromStdString(cfg.monitor->global_bc_names[Mface_id-1]));
      monitor_type=3;
    }
    else{
      OneComboMFace->setCurrentText(QString::fromStdString(cfg.monitor->global_bc_names[0]));
      OneComboMFace->setEnabled(false);
    }
    OneComboType->setCurrentText(QString::fromStdString(GUI_monitor_dict_R.at(monitor_type)));
    OneComboAverage->setCurrentText(QString::fromStdString(GUI_monitor_average_R.at(average_type)));
    OneButton->setMaximumWidth(50);
    OneButton->setText("X");

    ui->monitor_tree->setItemWidget(treeItem, 0, OneComboType);
    ui->monitor_tree->setItemWidget(treeItem, 1, OneComboFace);
    ui->monitor_tree->setItemWidget(treeItem, 2, OneComboMFace);
    ui->monitor_tree->setItemWidget(treeItem, 3, OneComboAverage);
    ui->monitor_tree->setItemWidget(treeItem, 4, OneButton);

    connect(OneComboType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this,OneComboType,OneComboMFace, i]{
                this->onMonitorTypeChange(OneComboType, OneComboMFace, i);
            });
    connect(OneComboFace, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this,OneComboFace, i]{
                this->onMonitorFaceChange(OneComboFace, i);
            });
    connect(OneComboMFace, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this,OneComboMFace, i]{
                this->onMonitorMFaceChange(OneComboMFace, i);
            });
    connect(OneComboAverage, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this,OneComboAverage, i]{
                this->onMonitorAverageChange(OneComboAverage, i);
            });
    connect(OneButton, QOverload<bool>::of(&QPushButton::clicked),
            [this,i]{
                this->onMonitorDeleteMonitor(i);
            });
  }
}

void PreMainWindow::Assign_General()
{
  ui->unsteady_checkbox->toggled(cfg.isUnsteady);
  ui->annular_checkbox->toggled(cfg.isAnnular);

  ui->unsteady_checkbox->setChecked(cfg.isUnsteady);
  ui->annular_checkbox->setChecked(cfg.isAnnular);

  ui->tb_type_combo->setCurrentText(QString::fromStdString(GUI_turbulence_model_dic.at(cfg.turbulence_model)));
  emit ui->tb_type_combo->currentTextChanged(ui->tb_type_combo->currentText());

  ui->conbo_rans->setCurrentText(QString::fromStdString(cfg.GUI_rans_model));
  emit ui->conbo_rans->currentTextChanged(ui->conbo_rans->currentText());

  ui->check_wf->toggled(cfg.rans_wall_function);
  ui->check_wf->setChecked(cfg.rans_wall_function);
  ui->comboBox_qcr->setCurrentText(QString::fromStdString(cfg.rans_qcr));
  ui->checkBox_transition->toggled(cfg.rans_transit);
  ui->checkBox_transition->setChecked(cfg.rans_transit);
  ui->checkBox_helicity->toggled(cfg.rans_helicity);
  ui->checkBox_helicity->setChecked(cfg.rans_helicity);
  ui->checkBox_cmott->toggled(cfg.rans_cmott);
  ui->checkBox_cmott->setChecked(cfg.rans_cmott);
  ui->checkBox_kl->toggled(cfg.rans_kl);
  ui->checkBox_kl->setChecked(cfg.rans_kl);

  ui->lineEdit_les_dx->setText(QString::fromStdString(std::to_string(cfg.les_dx)));
  ui->lineEdit_les_dt->setText(QString::fromStdString(std::to_string(cfg.les_dt)));
  ui->lineEdit_des_dx->setText(QString::fromStdString(std::to_string(cfg.des_dx)));

  ui->gas_type_combo->setCurrentText("Ideal gas");
  emit ui->gas_type_combo->currentTextChanged(ui->gas_type_combo->currentText());

//  ui->c
  ui->film_checkbox->setChecked(false);
  ui->film_checkbox->toggled(false);

  SetupDoubleLineEdit(this,ui->lineEdit_axis_x, cfg.rot_axis(0));
  SetupDoubleLineEdit(this,ui->lineEdit_axis_y, cfg.rot_axis(1));
  SetupDoubleLineEdit(this,ui->lineEdit_axis_z, cfg.rot_axis(2));
  SetupDoubleLineEdit(this,ui->lineEdit_factor_x, cfg.scaling_x);
  SetupDoubleLineEdit(this,ui->lineEdit_factor_y, cfg.scaling_y);
  SetupDoubleLineEdit(this,ui->lineEdit_factor_z, cfg.scaling_z);
}

void PreMainWindow::Assign_Turbomachinery()
{
  ui->turbo_zone_tree->clear();
  ui->turbo_interface_tree->clear();

  for (int i=0; i<cfg.num_meshes; i++)
  {
    QTreeWidgetItem* treeItem= new QTreeWidgetItem();
    ui->turbo_zone_tree->addTopLevelItem(treeItem);

    QLabel*OneZone_label = new QLabel(QString::fromStdString(cfg.mesh_files[i]),this);
    QComboBox *OneZone_combo = new QComboBox(this);
    QLineEdit *OneZone_extra = new QLineEdit(this);

    ui->turbo_zone_tree->setItemWidget(treeItem,0,OneZone_label);
    ui->turbo_zone_tree->setItemWidget(treeItem,1,OneZone_combo);
    ui->turbo_zone_tree->setItemWidget(treeItem,2,OneZone_extra);

    SetupDoubleLineEdit(this,OneZone_extra, cfg.bnd[i].zone_angular_velocity);
    OneZone_combo->addItem("Rotor ");
    OneZone_combo->addItem("Stator");
    std::string rs_value = cfg.turbo_rotor_stator[i]==1 ? "Rotor ":"Stator";
    OneZone_combo->setCurrentText(QString::fromStdString(rs_value));
    if (cfg.turbo_rotor_stator[i]==2) OneZone_extra->setEnabled(false);

    connect(OneZone_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this,OneZone_combo,OneZone_extra, i]{
                this->onTurboRSComboChanged(OneZone_combo, OneZone_extra, i);
                });


    connect(OneZone_extra, &QLineEdit::editingFinished,
            [this,OneZone_extra, i]{
                this->onTurboRSValueChanged(OneZone_extra, i);
            });
  }

// Zone List
//  ui->turbo
  if ( cfg.num_meshes>=1) {
    for (int i = 0; i < cfg.num_meshes - 1; i++) {
      QTreeWidgetItem *treeItem = new QTreeWidgetItem();
      QTreeWidgetItem *treeItem_name = new QTreeWidgetItem();
      ui->turbo_interface_tree->addTopLevelItem(treeItem_name);
      ui->turbo_interface_tree->addTopLevelItem(treeItem);

      QComboBox *InterfaceOutflow_combo = new QComboBox(this);
      for (int j = 0; j < cfg.bnd[i].num_BC; j++)
        InterfaceOutflow_combo->addItem(QString::fromStdString(cfg.mesh_files[i] + ":" + cfg.bnd[i].Names[j]));
      InterfaceOutflow_combo->addItem(QString::fromStdString("NONE"));
      std::string atOut_label;
      if (cfg.InterfacePairs[i][0]!=999)
        atOut_label = cfg.mesh_files[i] + ":" + cfg.global_name[cfg.InterfacePairs[i][0]-1];
      else
        atOut_label = "NONE";
      InterfaceOutflow_combo->setCurrentText(QString::fromStdString(atOut_label));

      QComboBox *InterfaceInflow_combo = new QComboBox(this);
      for (int j = 0; j < cfg.bnd[i + 1].num_BC; j++)
        InterfaceInflow_combo->addItem(QString::fromStdString(cfg.mesh_files[i + 1] + ":" + cfg.bnd[i + 1].Names[j]));
      InterfaceInflow_combo->addItem(QString::fromStdString("NONE"));
      std::string down_label;
      if (cfg.InterfacePairs[i][1]!=999)
        down_label = cfg.mesh_files[i + 1] + ":" + cfg.global_name[cfg.InterfacePairs[i][1]-1];
      else
        down_label = "NONE";
      InterfaceInflow_combo->setCurrentText(QString::fromStdString(down_label));

      QLabel *interface_label = new QLabel(QString::fromStdString(cfg.mesh_files[i] + "&" + cfg.mesh_files[i + 1]));

      ui->turbo_interface_tree->setItemWidget(treeItem_name, 0, interface_label);
      ui->turbo_interface_tree->setItemWidget(treeItem, 0, InterfaceOutflow_combo);
      ui->turbo_interface_tree->setItemWidget(treeItem, 1, InterfaceInflow_combo);

      connect(InterfaceOutflow_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
              [this, InterfaceOutflow_combo, InterfaceInflow_combo, i] {
                  this->onUpstreamChanged(InterfaceOutflow_combo, InterfaceInflow_combo, i);
              });

      connect(InterfaceInflow_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
              [this, InterfaceInflow_combo, InterfaceOutflow_combo, i] {
                  this->onDownstreamChanged(InterfaceInflow_combo, InterfaceOutflow_combo, i);
              });
    }
  }

  // repeat
  if (cfg.isUnsteady)
  {
    for (uint32_t i=0; i<cfg.num_meshes; i++){
      if (cfg.num_passages[i]>1){
        ui->checkBox_passage_repeat->setChecked(true);
        ui->checkBox_passage_repeat->toggled(true);
        break;
      }
    }

    ShowPassageRepeatTree();
  }
}

void PreMainWindow::Assign_Film()
{
  ui->Zone_list_2->clear();
  for (int i=0; i< cfg.mesh_files.size(); i++)
  {
    ui->Zone_list_2->addItem(QString::fromStdString(cfg.mesh_files[i]));
  }
  connect(ui->Zone_list_2,  &QListWidget::itemClicked, this, &PreMainWindow::Show_FilmCooling_List);
  if (ui->Zone_list_2->count()>0)
  {
    ui->Zone_list_2->setCurrentRow(0);
    Show_FilmCooling_List(ui->Zone_list_2->item((0)));
  }
  return;
}

void PreMainWindow::Assign_Solver()
{
//  ui->rho_lineEdit->setText(QString::number(cfg.rho_ic,'f',5));
  SetupDoubleLineEdit(this,ui->rho_lineEdit, cfg.rho_ic);
  SetupDoubleLineEdit(this,ui->u_lineEdit, cfg.u_ic);
  SetupDoubleLineEdit(this,ui->v_lineEdit, cfg.v_ic);
  SetupDoubleLineEdit(this,ui->w_lineEdit, cfg.w_ic);
  SetupDoubleLineEdit(this,ui->p_lineEdit, cfg.p_ic);
  SetupDoubleLineEdit(this,ui->sa_lineEdit, cfg.sa_ic);
  SetupDoubleLineEdit(this,ui->k_lineEdit, cfg.k_ic);
  SetupDoubleLineEdit(this,ui->epsilon_lineEdit, cfg.e_ic);
  SetupDoubleLineEdit(this,ui->omega_lineEdit, cfg.o_ic);
  SetupDoubleLineEdit(this,ui->gamma_lineEdit, cfg.g_ic);
  SetupDoubleLineEdit(this,ui->period_match_lineEdit, cfg.match_tol);
  SetupIntLineEdit(this, ui->residual_lineEdit, int(cfg.solver_residual));
  SetupDoubleLineEdit(this, ui->CFL_ramp_lineEdit, int(cfg.CFL_ramp_up));
  ui->mg_level_spinBox->setValue(cfg.mg_levels);
  ui->skip_pre_checkBox->toggled(!cfg.isPreProcessRun);
  ui->skip_pre_checkBox->setChecked(!cfg.isPreProcessRun);
}

void PreMainWindow::Assign_BC()
{
//  for (uint32_t i=0;i<cfg.InterfacePairs.size();i++){
//    std::cout<<cfg.InterfacePairs[i][0]<<" ";
//    std::cout<<cfg.InterfacePairs[i][1]<<std::endl;
//  }
//  std::cout<<cfg.InterfacePairs[1][0]<<std::endl;
//  std::cout<<cfg.InterfacePairs[1][1]<<std::endl;
  ui->Zone_list->clear();
  for (int i=0; i< cfg.mesh_files.size(); i++)
  {
    ui->Zone_list->addItem(QString::fromStdString(cfg.mesh_files[i]));
  }
  connect(ui->Zone_list,  &QListWidget::itemClicked, this, &PreMainWindow::Show_BC_List);
  if (ui->Zone_list->count()>0)
  {
    ui->Zone_list->setCurrentRow(0);
    Show_BC_List(ui->Zone_list->item((0)));
  }
  return;
}

void PreMainWindow::on_stackedWidget_currentChanged(int i)
{
  ui->stackedWidget->setCurrentIndex(i);
}

void PreMainWindow::on_annular_checkbox_toggled(bool checked) {
  if (checked) {
    cfg.isAnnular=true;
    ui->actionTurbo->setEnabled(true);
    global_annular=1;
  }
  else {
    cfg.isAnnular=false;
    ui->actionTurbo->setEnabled(false);
    global_annular=-1;
  }
}

void PreMainWindow::on_actionNew_triggered()
{
  cfg = PreProcessSettings();

  SelectFile *selectfile = new SelectFile(&cfg);
  selectfile->setModal(true);
  selectfile->show();
  connect(selectfile, &QDialog::finished, this, &PreMainWindow::Assign_Value);
  ui->scrollArea->setEnabled(true);
}

void PreMainWindow::on_tb_type_combo_currentTextChanged(const QString &arg1)
{
  cfg.turbulence_model = GUI_turbulence_model_dic_R.at(arg1.toStdString());

  if (arg1.toStdString() == "RANS" ||arg1.toStdString() == "DES")
  {
    for (int i=0;i<ui->steady_simulation_layout->count(); i++)
      ui->steady_simulation_layout->itemAt(i)->widget()->setVisible(true);
    if (cfg.isUnsteady) {
      ui->steady_iteration_label->setVisible(false);
      ui->unsteady_inner_label->setVisible(true);
      ui->output_steady_label->setVisible(false);
      ui->output_steady_lineEdit->setVisible(false);
    }
    else {
      ui->steady_iteration_label->setVisible(true);
      ui->unsteady_inner_label->setVisible(false);
      ui->output_steady_label->setVisible(true);
      ui->output_steady_lineEdit->setVisible(true);
    }
    for (int i=0;i<ui->rans_layout->count(); i++)
      ui->rans_layout->itemAt(i)->widget()->setVisible(true);
    if (arg1.toStdString() == "DES"){
      for (int i=0;i<ui->DES_area->count(); i++)
        ui->DES_area->itemAt(i)->widget()->setVisible(true);
    }
    else{
      for (int i=0;i<ui->DES_area->count(); i++)
        ui->DES_area->itemAt(i)->widget()->setVisible(false);
    }
    ui->lineEdit_les_dt->setVisible(false);
    ui->label_les_dt->setVisible(false);
    for (int i=0;i<ui->LES_area->count(); i++)
      ui->LES_area->itemAt(i)->widget()->setVisible(false);
  }

  if (arg1.toStdString() == "LES")
  {
    ui->conbo_rans->setCurrentText("laminar");
    ui->lineEdit_les_dt->setVisible(true);
    ui->label_les_dt->setVisible(true);
    for (int i=0;i<ui->LES_area->count(); i++)
      ui->LES_area->itemAt(i)->widget()->setVisible(true);
    cfg.GUI_rans_model="laminar";
    ui->steady_iteration_label->setVisible(false);
    for (int i=0;i<ui->steady_simulation_layout->count(); i++)
      ui->steady_simulation_layout->itemAt(i)->widget()->setVisible(false);
    for (int i=0;i<ui->rans_layout->count(); i++)
      ui->rans_layout->itemAt(i)->widget()->setVisible(false);
    ui->unsteady_inner_label->setVisible(false);
    ui->lineEdit_des_dx->setVisible(false);
    ui->label_des_dx->setVisible(false);
  }
}

void PreMainWindow::Show_FilmCooling_List(QListWidgetItem *item) {
  int zone_id = ui->Zone_list_2->currentRow();
  current_zone = zone_id;
  ui->FilmCooling_List->clear();
  int num_BC = cfg.bnd[zone_id].num_BC;

//  std::cout <<"zon" <<std::endl;
  // 创建自定义头部小部件
  QWidget *headerWidget = new QWidget(this);
  QHBoxLayout *headerLayout = new QHBoxLayout;

  // 创建并添加列标签
  QLabel *headerLabel1 = new QLabel("BcName", this);
  QLabel *headerLabel2 = new QLabel("FilmOption", this);
  QLabel *headerLabel3 = new QLabel("RowsData", this);

  headerLayout->addWidget(headerLabel1);
  headerLayout->addWidget(headerLabel2);
  headerLayout->addWidget(headerLabel3);
  headerWidget->setLayout(headerLayout);

  // 创建一个新的 QListWidgetItem 作为头部项
  QListWidgetItem *headerItem = new QListWidgetItem();
  ui->FilmCooling_List->addItem(headerItem);
  headerItem->setSizeHint(headerWidget->sizeHint());
  ui->FilmCooling_List->setItemWidget(headerItem, headerWidget);

  for (int i = 0; i < num_BC; i++) {
    // 创建列表项
    QListWidgetItem *listItem = new QListWidgetItem();
    ui->FilmCooling_List->addItem(listItem);

    // 创建自定义小部件
    QWidget *OneFilmBC_widget = new QWidget(this);

    // 创建并设置标签
    QLabel *OneFilmBC_label = new QLabel(QString::fromStdString(cfg.boundary_film_option[zone_id][i].first), this);

    // 创建并设置组合框，用于选择 true 或 false
    QString combobox_option1 = "false";
    QString combobox_option2 = "true";
    if (cfg.boundary_film_option[zone_id][i].second) {
      combobox_option1 = "true";
      combobox_option2 = "false";
    }
    QComboBox *OneFilmBC_combo = new QComboBox(this);
    OneFilmBC_combo->addItem(combobox_option1);
    OneFilmBC_combo->addItem(combobox_option2);

    // 创建按钮
    QPushButton *OneFilmBC_button = new QPushButton("Add", this);
    OneFilmBC_button->setEnabled(false); // 初始状态下按钮禁用
    if (combobox_option1 == "true") OneFilmBC_button->setEnabled(true);

    // 创建布局并添加小部件
    QHBoxLayout *OneFilmBC_layout = new QHBoxLayout;
    OneFilmBC_layout->addWidget(OneFilmBC_label);
    OneFilmBC_layout->addWidget(OneFilmBC_combo);
    OneFilmBC_layout->addWidget(OneFilmBC_button);

    // 将布局设置到自定义小部件
    OneFilmBC_widget->setLayout(OneFilmBC_layout);

    // 调整列表项大小并将自定义小部件设置为列表项的显示部件
    listItem->setSizeHint(OneFilmBC_widget->sizeHint());
    ui->FilmCooling_List->setItemWidget(listItem, OneFilmBC_widget);

    // 连接组合框的信号到独立的槽函数
    connect(OneFilmBC_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this,OneFilmBC_combo, OneFilmBC_button, zone_id,i]{
                this->onFilmComboChanged(OneFilmBC_combo, OneFilmBC_button, zone_id,i);
            });

    // 连接组合框的信号到槽，以便当选择改变时更新按钮状态
    connect(OneFilmBC_combo, &QComboBox::currentTextChanged, OneFilmBC_button, [OneFilmBC_button](const QString &text) {
        OneFilmBC_button->setEnabled(text == "true");
    });

    // 连接按钮的信号到独立的槽函数
    connect(OneFilmBC_button, &QPushButton::clicked,
            [this,OneFilmBC_combo,zone_id,i]{
                this->onFilmBCbuttonClicked(OneFilmBC_combo, zone_id, i);
            });
  }
}

void PreMainWindow::onFilmComboChanged(QComboBox* cmb, QPushButton* btn, int zone_id, int bc_id)
{
  std::string bc_text=cmb->currentText().toStdString();
  if (bc_text == "true")
    cfg.boundary_film_option[zone_id][bc_id].second = true;
  else
    cfg.boundary_film_option[zone_id][bc_id].second = false;

}

void PreMainWindow::onFilmBCbuttonClicked(QComboBox *bmd, int zone_id, int bc_id)
{
  // 从 cfg.all_film_config_data 中读取初始数据
  QVector<QVector<double>> tableData;
  for (size_t i = 0; i < cfg.all_film_config_data[zone_id][bc_id].second.size(); ++i) {
    QVector<double> tableData1;
    for (size_t j = 0; j < cfg.all_film_config_data[zone_id][bc_id].second[i].size(); ++j) {
      tableData1.push_back(cfg.all_film_config_data[zone_id][bc_id].second[i][j]);
    }
    tableData.push_back(tableData1);
  }

  QVector<QVector<double>> tableData_input;
  for (size_t i = 0; i < cfg.all_film_input_data[zone_id][bc_id].second.size(); ++i) {
    QVector<double> tableData1;
    for (size_t j = 0; j < cfg.all_film_input_data[zone_id][bc_id].second[i].size(); ++j) {
      tableData1.push_back(cfg.all_film_input_data[zone_id][bc_id].second[i][j]);
//      std::cout <<i << cfg.all_film_input_data[zone_id][bc_id].second[i][j] << std::endl;
    }
    tableData_input.push_back(tableData1);
  }

  // 创建一个新的对话框供用户输入参数
  QDialog dialog(this);
  QVBoxLayout layout(&dialog);

  QLabel label("Film cooling row config data:", &dialog);

  // 根据初始数据行数创建表格
  QTableWidget tableWidget(static_cast<int>(tableData.size()), 9, &dialog);

  // 设置第一行的标签
  QStringList headers = {"CoordX", "CoordY", "CoordZ", "NormalX", "NormalY", "NormalZ", "Diameter", "Quantity", "Distance"};
  tableWidget.setHorizontalHeaderLabels(headers);

  // 初始化表格的值为读取的数据
  for (int row = 0; row < tableWidget.rowCount(); ++row) {
    for (int col = 0; col < tableWidget.columnCount(); ++col) {
      QTableWidgetItem *item = new QTableWidgetItem(QString::number(tableData[row][col]));
      tableWidget.setItem(row, col, item);
    }
  }

  // 创建一个新的对话框供用户输入参数
  QDialog dialog1(this);
  QVBoxLayout layout1(&dialog1);

  QLabel label1("Film cooling row input data:", &dialog1);

  // 根据初始数据行数创建表格
  QTableWidget tableWidget1(static_cast<int>(tableData_input.size()), 7, &dialog1);

  // 设置第一行的标签
  QStringList headers1 = {"VelocityX", "VelocityY", "VelocityZ", "Density", "Fraction","MassFlow", "Temperature"};
  tableWidget1.setHorizontalHeaderLabels(headers1);

  // 初始化表格的值为读取的数据
  for (int row = 0; row < tableWidget1.rowCount(); ++row) {
    for (int col = 0; col < tableWidget1.columnCount(); ++col) {
      QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(tableData_input[row][col]));
      tableWidget1.setItem(row, col, item1);
    }
  }

  QPushButton addButton("Add", &dialog);
  QPushButton removeButton("Decrease", &dialog);
  QPushButton okButton("OK", &dialog);
  QPushButton cancelButton("Cancel", &dialog);

  QHBoxLayout buttonLayout;
  buttonLayout.addWidget(&addButton);
  buttonLayout.addWidget(&removeButton);

  QHBoxLayout okCancelLayout;
  okCancelLayout.addWidget(&okButton);
  okCancelLayout.addWidget(&cancelButton);

  layout.addWidget(&label);
  layout.addWidget(&tableWidget);
  layout.addWidget(&label1);
  layout.addWidget(&tableWidget1);
  layout.addLayout(&buttonLayout);
  layout.addLayout(&okCancelLayout);

  dialog.resize(1000, 600);

  // 连接增加行按钮的点击信号到槽
  connect(&addButton, &QPushButton::clicked, [&]() {
      int rows = tableWidget.rowCount();
      tableWidget.insertRow(rows);
      for (int col = 0; col < tableWidget.columnCount(); ++col) {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(0));
        tableWidget.setItem(rows, col, item);
      }
      int rows1 = tableWidget1.rowCount();
      tableWidget1.insertRow(rows1);
      for (int col = 0; col < tableWidget1.columnCount(); ++col) {
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(0));
        tableWidget1.setItem(rows, col, item1);
      }
  });

  // 连接减少行按钮的点击信号到槽
  connect(&removeButton, &QPushButton::clicked, [&]() {
      int rows = tableWidget.rowCount();
      if (rows > 1) {  // 保证至少保留标签行和一行数据行
        tableWidget.removeRow(rows - 1);
      }

      int rows1 = tableWidget1.rowCount();
      if (rows1 > 1) {  // 保证至少保留标签行和一行数据行
        tableWidget1.removeRow(rows1 - 1);
      }
  });

  // 连接OK按钮的点击信号到槽
  connect(&okButton, &QPushButton::clicked, [&dialog,&dialog1, &tableWidget,&tableWidget1, &tableData,&tableData_input]() {
      int rows = tableWidget.rowCount();
      int cols = tableWidget.columnCount();
      tableData.resize(rows);
      for (int row = 0; row < rows; ++row) {
        tableData[row].resize(cols);
        for (int col = 0; col < cols; ++col) {
          QTableWidgetItem *item = tableWidget.item(row, col);
          if (item) {
            tableData[row][col] = item->text().toDouble();
          }
        }
      }
      dialog.accept();

      int rows1 = tableWidget1.rowCount();
      int cols1 = tableWidget1.columnCount();
      tableData_input.resize(rows1);
      for (int row = 0; row < rows1; ++row) {
        tableData_input[row].resize(cols1);
        for (int col = 0; col < cols1; ++col) {
          QTableWidgetItem *item1 = tableWidget1.item(row, col);
          if (item1) {
            tableData_input[row][col] = item1->text().toDouble();
          }
        }
      }
      dialog1.accept();
  });

  // 连接取消按钮的点击信号到槽
  connect(&cancelButton, &QPushButton::clicked, [&dialog,&dialog1]() {
      dialog.reject();
      dialog1.reject();
  });

  dialog.exec();

//  // 更新 cfg.all_film_config_data
//  cfg.all_film_config_data[zone_id][bc_id].second.clear();
//  for (int i = 0; i < tableData.size(); ++i) {
//    std::vector<double> temp_data1;
//    for (int j = 0; j < tableData[i].size(); ++j) {
//      temp_data1.emplace_back(tableData[i][j]);
////      std::cout<< tableData[i][j] <<std::endl;
//    }
//    cfg.all_film_config_data[zone_id][bc_id].second.emplace_back(temp_data1);
//  }

//  cfg.all_film_input_data[zone_id][bc_id].second.clear();
//  for (int i = 0; i < tableData_input.size(); ++i) {
//    std::vector<double> temp_data1;
//    for (int j = 0; j < tableData_input[i].size(); ++j) {
//      temp_data1.emplace_back(tableData_input[i][j]);
////      std::cout<< tableData[i][j] <<std::endl;
//    }
//    cfg.all_film_input_data[zone_id][bc_id].second.emplace_back(temp_data1);
//  }

}



void PreMainWindow::Show_BC_List(QListWidgetItem* item)
{
  ui->BC_list->clear();
  int zone_id = ui->Zone_list->currentRow();
  current_zone = zone_id;
  int num_BC = cfg.bnd[zone_id].num_BC;
  for (int i=0; i<num_BC; i++)
  {
    QListWidgetItem* listItem= new QListWidgetItem();
    ui->BC_list->addItem(listItem);

    QWidget* OneBC_widget = new QWidget(this);
    QLabel*OneBC_label = new QLabel(QString::fromStdString(cfg.bnd[zone_id].Names[i]),this);
    QComboBox *OneBC_combo = new QComboBox(this);
    QPushButton *OneBC_extra = new QPushButton(this);
    QLayout*OneBC_layout = new QHBoxLayout;
    OneBC_layout->addWidget(OneBC_label);
    OneBC_layout->addWidget(OneBC_combo);
    OneBC_layout->addWidget(OneBC_extra);
    OneBC_widget->setLayout(OneBC_layout);

    listItem->setSizeHint(OneBC_layout->sizeHint());
    ui->BC_list->setItemWidget(listItem,OneBC_widget);

    OneBC_extra->setText("...");
    for (const auto &pair: GUI_BC_Normal_Map) {
      OneBC_combo->addItem(QString::fromStdString(pair.first));
    }
    if (cfg.bnd[zone_id].Types[i]==11 ||
      cfg.bnd[zone_id].Types[i]==12 ||
        cfg.bnd[zone_id].Types[i]==13 ||
            cfg.bnd[zone_id].Types[i]==14 ){
      OneBC_combo->addItem(QString::fromStdString(GUI_Reverse_BC_Turbomachinery_Map.at(cfg.bnd[zone_id].Types[i])));
      OneBC_combo->setEnabled(false);
    }
    std::string current_bc = GUI_Reverse_BC_Turbomachinery_Map.at(cfg.bnd[zone_id].Types[i]);
    OneBC_combo->setCurrentText(QString::fromStdString(current_bc));
    if (cfg.turbo_rotor_stator[zone_id]==1) {
      OneBC_combo->addItem(QString::fromStdString("Counter-rotating wall"));
      if (cfg.bnd[zone_id].Types[i]==2 &&
          std::abs(cfg.bnd[zone_id].Walls[i].wall_angular_velocity) > 1e-5 &&
          std::abs(cfg.bnd[zone_id].Walls[i].wall_angular_velocity + cfg.turbo_zone_velocity[zone_id]<1e-5)){
        OneBC_combo->setCurrentText("Counter-rotating wall");
      }
    }

    if (cfg.bnd[zone_id].Types[i]==28 ){
      OneBC_combo->addItem(QString::fromStdString("Film cooling Inflow"));
      OneBC_combo->setCurrentText("Film cooling Inflow");
      OneBC_combo->setEnabled(false);
      OneBC_extra->setEnabled(false);
    }

    connect(OneBC_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
           [this,OneBC_combo, OneBC_extra, zone_id,i]{
               this->onBCComboChanged(OneBC_combo, OneBC_extra, zone_id,i);
           });

    connect(OneBC_extra, &QPushButton::clicked,
            [this,OneBC_combo,zone_id,i]{
                this->onBCExtraClicked(OneBC_combo, zone_id, i);
            });

  }
}

void PreMainWindow::onBCComboChanged(QComboBox* cmb, QPushButton* btn, int zone_id, int bc_id)
{
  std::string bc_text=cmb->currentText().toStdString();
  cfg.bnd[zone_id].Types[bc_id] = GUI_BC_Turbomachinery_Map.at(bc_text);
  if (bc_text=="Viscous wall") {
    btn->setVisible(true);
  }
  else if (bc_text=="Counter-rotating wall") {
    btn->setVisible(true);
    cfg.bnd[zone_id].Walls[bc_id].wall_angular_velocity=-cfg.turbo_zone_velocity[zone_id];
  }
  else if (bc_text=="Subsonic Inflow" || bc_text=="Supersonic Inflow") {
    btn->setVisible(true);
    cfg.bnd[zone_id].Inlets[bc_id].angular_velocity_in=-cfg.turbo_zone_velocity[zone_id];
    cfg.bnd[zone_id].Inlets[bc_id].profile_distribution_direction_in=4;
    cfg.bnd[zone_id].Inlets[bc_id].num_profile_in=2;
    cfg.bnd[zone_id].Inlets[bc_id].len_profile=flow_vars.at(cfg.GUI_rans_model).size();
    if (bc_text=="Supersonic Inflow") cfg.bnd[zone_id].Inlets[bc_id].len_profile+=1;
    cfg.bnd[zone_id].Inlets[bc_id].points_data_in.clear();
    for (int i=0; i<cfg.bnd[zone_id].Inlets[bc_id].num_profile_in; i++){
      std::vector<double> one_vector;
      for (int i=0; i<cfg.bnd[zone_id].Inlets[bc_id].len_profile; i++){
        one_vector.emplace_back(0.0);
      }
      cfg.bnd[zone_id].Inlets[bc_id].points_data_in.emplace_back(one_vector);
      cfg.bnd[zone_id].Inlets[bc_id].inlet_file="BC_files/"+cfg.mesh_files[zone_id]
          + "-inlet-" + cfg.bnd[zone_id].Names[bc_id]+".dat";
    }
  }
  else if (bc_text=="Subsonic Outflow" || bc_text=="Supersonic Outflow" ||
           bc_text=="Subsonic Outflow Radial Equal") {
    btn->setVisible(true);
    cfg.bnd[zone_id].Outlets[bc_id].angular_velocity_out = -cfg.turbo_zone_velocity[zone_id];
    cfg.bnd[zone_id].Outlets[bc_id].profile_distribution_direction_out = 4;
    cfg.bnd[zone_id].Outlets[bc_id].num_profile_out = 2;
    cfg.bnd[zone_id].Outlets[bc_id].len_profile = 3;
    for (int i = 0; i < cfg.bnd[zone_id].Outlets[bc_id].num_profile_out; i++) {
      std::vector<double> one_vector;
      for (int i = 0; i < cfg.bnd[zone_id].Outlets[bc_id].len_profile; i++) {
        one_vector.emplace_back(0.0);
      }
      cfg.bnd[zone_id].Outlets[bc_id].points_data_out.emplace_back(one_vector);
      cfg.bnd[zone_id].Outlets[bc_id].outlet_file = "BC_files/" + cfg.mesh_files[zone_id]
                                                    + "-outlet-" + cfg.bnd[zone_id].Names[bc_id] + ".dat";
    }
  }
}

void PreMainWindow::onTurboRSComboChanged(QComboBox *cmb, QLineEdit *edt, int zone_id) {
//  cfg.bnd[zone_id].Types[bc_id] = bctype_map.at(cmb->currentText().toStdString());
  std::string rs = cmb->currentText().toStdString();
  if (rs=="Stator")
  {
    cfg.turbo_rotor_stator[zone_id] = 2;
    cfg.turbo_zone_velocity[zone_id] = 0.0;
    edt->setEnabled(false);
  }
  else
  {
    cfg.turbo_rotor_stator[zone_id] = 1;
    edt->setEnabled(true);
    edt->setText(QString::fromStdString(std::to_string(cfg.turbo_zone_velocity[zone_id])));
  }
}

void PreMainWindow::onTurboRSValueChanged(QLineEdit *edt, int zone_id) {
  cfg.turbo_zone_velocity[zone_id] = edt->text().toDouble();
  cfg.bnd[zone_id].zone_angular_velocity = edt->text().toDouble();
  for (int i=0; i<cfg.num_meshes;i++){
      for (int j=0; j<cfg.bnd[i].num_BC;j++){
        if (cfg.bnd[i].Types[j]==4 || cfg.bnd[i].Types[j]==6) {
          cfg.bnd[zone_id].Inlets[j].angular_velocity_in=-cfg.turbo_zone_velocity[zone_id];
        }
        else if (cfg.bnd[i].Types[j]==5 || cfg.bnd[i].Types[j]==7 || cfg.bnd[i].Types[j]==15) {
          cfg.bnd[zone_id].Outlets[j].angular_velocity_out = -cfg.turbo_zone_velocity[zone_id];
        }
    }
  }
}

void PreMainWindow::onUpstreamChanged(QComboBox* edt, QComboBox *edt2, int zone_id)
{
  if (cfg.isUnsteady)
  {
    // If exist any mixing plane at upsteam(towards downsteam), set invisid wall
    for (uint32_t i = 0; i < cfg.bnd[zone_id].num_BC; i++)
      if (cfg.bnd[zone_id].Types[i] == 14)
        cfg.bnd[zone_id].Types[i] = 1;
    // If NONE, the pairing downdtream combo should be none
    // Update the corresponding boundary condition
    if (edt->currentText().toStdString() == "NONE") {
      edt2->setCurrentText("NONE");
      cfg.InterfacePairs[zone_id][0] = 999;
      cfg.InterfacePairs[zone_id][1] = 999;
      for (uint32_t i = 0; i < cfg.bnd[zone_id + 1].num_BC; i++)
        if (cfg.bnd[zone_id + 1].Types[i] == 13)
          cfg.bnd[zone_id + 1].Types[i] = 1;
    }
    else {
      cfg.bnd[zone_id].Types[edt->currentIndex()] = 14;
      cfg.InterfacePairs[zone_id][0] = cfg.global_id[zone_id][edt->currentIndex()];
    }
  }
  else
  {
    for (uint32_t i = 0; i < cfg.bnd[zone_id].num_BC; i++)
      if (cfg.bnd[zone_id].Types[i] == 12)
        cfg.bnd[zone_id].Types[i] = 1;
    // If NONE, the pairing downdtream combo should be none
    // Update the corresponding boundary condition
    if (edt->currentText().toStdString() == "NONE") {
      edt2->setCurrentText("NONE");
      cfg.InterfacePairs[zone_id][0] = 999;
      cfg.InterfacePairs[zone_id][1] = 999;
      for (uint32_t i = 0; i < cfg.bnd[zone_id + 1].num_BC; i++)
        if (cfg.bnd[zone_id + 1].Types[i] == 11)
          cfg.bnd[zone_id + 1].Types[i] = 1;
    }
    else {
      cfg.bnd[zone_id].Types[edt->currentIndex()] = 12;
      cfg.InterfacePairs[zone_id][0] = cfg.global_id[zone_id][edt->currentIndex()];
    }
  }
}

void PreMainWindow::onDownstreamChanged(QComboBox* edt, QComboBox *edt2, int zone_id)
{
  if (cfg.isUnsteady) {
    // If exist any mixing plane at downsteam(towards upsteam), set invisid wall
    for (uint32_t i = 0; i < cfg.bnd[zone_id+1].num_BC; i++)
      if (cfg.bnd[zone_id+1].Types[i] == 13)
        cfg.bnd[zone_id+1].Types[i] = 1;
    // If NONE, the pairing downdtream combo should be none
    // Update the corresponding boundary condition
    if (edt->currentText().toStdString() == "NONE") {
      edt2->setCurrentText("NONE");
      cfg.InterfacePairs[zone_id][0] = 999;
      cfg.InterfacePairs[zone_id][1] = 999;
      for (uint32_t i = 0; i < cfg.bnd[zone_id].num_BC; i++)
        if (cfg.bnd[zone_id].Types[i] == 14)
          cfg.bnd[zone_id].Types[i] = 1;
    }
    else {
      cfg.bnd[zone_id+1].Types[edt->currentIndex()] = 13;
      cfg.InterfacePairs[zone_id][1] = cfg.global_id[zone_id+1][edt->currentIndex()];
    }
  }
  else{
    // If exist any mixing plane at downsteam(towards upsteam), set invisid wall
    for (uint32_t i = 0; i < cfg.bnd[zone_id].num_BC; i++)
      if (cfg.bnd[zone_id+1].Types[i] == 11)
        cfg.bnd[zone_id+1].Types[i] = 1;
    // If NONE, the pairing downdtream combo should be none
    // Update the corresponding boundary condition
    if (edt->currentText().toStdString() == "NONE") {
      edt2->setCurrentText("NONE");
      cfg.InterfacePairs[zone_id][0] = 999;
      cfg.InterfacePairs[zone_id][1] = 999;
      for (uint32_t i = 0; i < cfg.bnd[zone_id - 1].num_BC; i++)
        if (cfg.bnd[zone_id].Types[i] == 12)
          cfg.bnd[zone_id].Types[i] = 1;
    } else {
      cfg.bnd[zone_id+1].Types[edt->currentIndex()] = 11;
      cfg.InterfacePairs[zone_id][1] = cfg.global_id[zone_id+1][edt->currentIndex()];
    }
  }
}

void PreMainWindow::onBCExtraClicked(QComboBox *cmb, int zone_id, int bc_id)
{
  BCExtra *extra_bc_window = new BCExtra(&cfg, zone_id, bc_id, cmb->currentText().toStdString(), this);
  extra_bc_window->setModal(true);
  extra_bc_window->show();
}

void PreMainWindow::on_actionLoadMain_triggered()
{
  cfg=PreProcessSettings();
  cfg.LoadYAML(global_pre_setup_yaml);
  ui->scrollArea->setEnabled(true);
  Assign_Value();
}

void PreMainWindow::on_conbo_rans_currentTextChanged(const QString &arg1)
{
  cfg.GUI_rans_model=arg1.toStdString();
  if (arg1.toStdString() == "Spalart-Allmaras(SA)")
  {
    // Initial conditions
    ui->sa_label->setVisible(true);
    ui->sa_lineEdit->setVisible(true);
    ui->sa_unit_label->setVisible(true);
    ui->k_label->setVisible(false);
    ui->k_unit_label->setVisible(false);
    ui->k_lineEdit->setVisible(false);
    ui->omega_label->setVisible(false);
    ui->omega_unit_label->setVisible(false);
    ui->omega_lineEdit->setVisible(false);
    ui->epsilon_label->setVisible(false);
    ui->epsilon_unit_label->setVisible(false);
    ui->epsilon_lineEdit->setVisible(false);
    ui->gamma_label->setVisible(false);
    ui->gamma_lineEdit->setVisible(false);
    // Enable RANS extra
    ui->check_wf->setEnabled(true);
    ui->check_wf->setVisible(true);
    ui->label_wf1->setVisible(true);
    ui->label_qcr->setVisible(true);
    ui->comboBox_qcr->setVisible(true);
    ui->label_helicity->setVisible(true);
    ui->checkBox_helicity->setVisible(true);
    // Disable RANS extra
    ui->checkBox_transition->setVisible(false);
    ui->checkBox_transition->setChecked(false);
    ui->checkBox_transition->toggled(false);
    ui->checkBox_cmott->setVisible(false);
    ui->checkBox_cmott->setChecked(false);
    ui->checkBox_cmott->toggled(false);
    ui->checkBox_kl->setVisible(false);
    ui->checkBox_kl->setChecked(false);
    ui->checkBox_kl->toggled(false);
    ui->label_transition->setVisible(false);
    ui->label_cmott->setVisible(false);
    ui->label_kl->setVisible(false);
  }
  else if (arg1.toStdString() == "k-epsilon(k-ε)")
  {
    // initial conditions
    ui->sa_label->setVisible(false);
    ui->sa_lineEdit->setVisible(false);
    ui->sa_unit_label->setVisible(false);
    ui->k_label->setVisible(true);
    ui->k_unit_label->setVisible(true);

    ui->k_lineEdit->setVisible(true);
    ui->omega_label->setVisible(false);
    ui->omega_unit_label->setVisible(false);
    ui->omega_lineEdit->setVisible(false);
    ui->epsilon_label->setVisible(true);
    ui->epsilon_unit_label->setVisible(true);
    ui->epsilon_lineEdit->setVisible(true);
    ui->gamma_label->setVisible(false);
    ui->gamma_lineEdit->setVisible(false);
     // Enable RANS extra
    ui->check_wf->setVisible(true);
    ui->checkBox_cmott->setVisible(true);
    ui->checkBox_kl->setVisible(true);
    ui->label_wf1->setVisible(true);
    ui->label_cmott->setVisible(true);
    ui->label_kl->setVisible(true);
    // Disable RANS extra
    ui->checkBox_transition->setVisible(false);
    ui->checkBox_transition->setChecked(false);
    ui->checkBox_transition->toggled(false);
    ui->comboBox_qcr->setVisible(false);
    ui->comboBox_qcr->setCurrentText("none");
    ui->checkBox_helicity->setVisible(false);
    ui->checkBox_helicity->toggled(false);
    ui->checkBox_helicity->setChecked(false);
    ui->label_transition->setVisible(false);
    ui->label_qcr->setVisible(false);
    ui->label_helicity->setVisible(false);
  }
  else if (arg1.toStdString() == "k-omega(k-ω)")
  {
    ui->sa_label->setVisible(false);
    ui->sa_lineEdit->setVisible(false);
    ui->k_label->setVisible(true);
    ui->k_unit_label->setVisible(true);
    ui->k_lineEdit->setVisible(true);
    ui->omega_label->setVisible(true);
    ui->omega_unit_label->setVisible(true);
    ui->omega_lineEdit->setVisible(true);
    ui->epsilon_unit_label->setVisible(false);
    ui->epsilon_lineEdit->setVisible(false);
    ui->epsilon_label->setVisible(false);
    ui->check_wf->setEnabled(false);
    ui->check_wf->toggled(false);
    // Enable RANS extra
    ui->checkBox_transition->setVisible(true);
    ui->label_transition->setVisible(true);
    ui->check_wf->setEnabled(true);
    ui->check_wf->setVisible(true);
    ui->label_wf1->setVisible(true);
    ui->label_qcr->setVisible(true);
    ui->comboBox_qcr->setVisible(true);
    ui->label_helicity->setVisible(true);
    ui->checkBox_helicity->setVisible(true);
    // Disable RANS extra
    ui->checkBox_cmott->setVisible(false);
    ui->checkBox_cmott->setChecked(false);
    ui->checkBox_cmott->toggled(false);
    ui->checkBox_kl->setVisible(false);
    ui->checkBox_kl->setChecked(false);
    ui->checkBox_kl->toggled(false);
    ui->label_cmott->setVisible(false);
    ui->label_kl->setVisible(false);
    // Trainsition model
    if (cfg.rans_transit) {
      ui->gamma_label->setVisible(true);
      ui->gamma_lineEdit->setVisible(true);
    }
    else{
      ui->gamma_label->setVisible(false);
      ui->gamma_lineEdit->setVisible(false);
    }
  }
  else if (arg1.toStdString() == "laminar")
  {
    // initial condition
    ui->sa_label->setVisible(false);
    ui->sa_lineEdit->setVisible(false);
    ui->k_unit_label->setVisible(false);
    ui->k_label->setVisible(false);
    ui->k_lineEdit->setVisible(false);
    ui->omega_label->setVisible(false);
    ui->omega_unit_label->setVisible(false);
    ui->omega_lineEdit->setVisible(false);
    ui->epsilon_unit_label->setVisible(false);
    ui->epsilon_lineEdit->setVisible(false);
    ui->epsilon_label->setVisible(false);
    ui->gamma_label->setVisible(false);
    ui->gamma_lineEdit->setVisible(false);
    // labels
    ui->check_wf->setEnabled(false);
    ui->check_wf->toggled(false);
    ui->check_wf->setChecked(false);
    ui->checkBox_transition->setVisible(false);
    ui->checkBox_transition->toggled(false);
    ui->label_transition->setVisible(false);
    ui->label_qcr->setVisible(false);
    ui->comboBox_qcr->setVisible(false);
    ui->label_helicity->setVisible(false);
    ui->checkBox_helicity->setVisible(false);
    ui->checkBox_cmott->setVisible(false);
    ui->checkBox_cmott->setChecked(false);
    ui->checkBox_cmott->toggled(false);
    ui->checkBox_kl->setVisible(false);
    ui->checkBox_kl->setChecked(false);
    ui->checkBox_kl->toggled(false);
    ui->label_cmott->setVisible(false);
    ui->label_kl->setVisible(false);
  }
  return;
}

void PreMainWindow::on_check_wf_toggled(bool checked){
  cfg.rans_wall_function = checked? true:false;
}

void PreMainWindow::on_lineEdit_des_dx_textEdited(const QString &arg1){
  cfg.des_dx=arg1.toDouble();
}

void PreMainWindow::on_lineEdit_les_dx_textEdited(const QString &arg1){
  cfg.les_dx=arg1.toDouble();
}

void PreMainWindow::on_lineEdit_les_dt_textEdited(const QString &arg1){
  cfg.les_dt=arg1.toDouble();
}

void PreMainWindow::on_rho_lineEdit_textEdited(const QString &arg1){cfg.rho_ic=arg1.toDouble();}
void PreMainWindow::on_u_lineEdit_textEdited(const QString &arg1){cfg.u_ic=arg1.toDouble();}
void PreMainWindow::on_v_lineEdit_textEdited(const QString &arg1){cfg.v_ic=arg1.toDouble();}
void PreMainWindow::on_w_lineEdit_textEdited(const QString &arg1){cfg.w_ic=arg1.toDouble();}
void PreMainWindow::on_p_lineEdit_textEdited(const QString &arg1){cfg.p_ic=arg1.toDouble();}
void PreMainWindow::on_sa_lineEdit_textEdited(const QString &arg1){cfg.sa_ic=arg1.toDouble();}
void PreMainWindow::on_k_lineEdit_textEdited(const QString &arg1){cfg.k_ic=arg1.toDouble();}
void PreMainWindow::on_omega_lineEdit_textEdited(const QString &arg1){cfg.o_ic=arg1.toDouble();}
void PreMainWindow::on_epsilon_lineEdit_textEdited(const QString &arg1){cfg.e_ic=arg1.toDouble();}
void PreMainWindow::on_gamma_lineEdit_textEdited(const QString &arg1){cfg.g_ic=arg1.toDouble();}

void PreMainWindow::on_lineEdit_axis_x_textEdited(const QString &arg1){cfg.rot_axis(0)=arg1.toDouble();}
void PreMainWindow::on_lineEdit_axis_y_textEdited(const QString &arg1){cfg.rot_axis(1)=arg1.toDouble();}
void PreMainWindow::on_lineEdit_axis_z_textEdited(const QString &arg1){cfg.rot_axis(2)=arg1.toDouble();}
void PreMainWindow::on_lineEdit_factor_x_textEdited(const QString &arg1){cfg.scaling_x=arg1.toDouble();}
void PreMainWindow::on_lineEdit_factor_y_textEdited(const QString &arg1){cfg.scaling_y=arg1.toDouble();}
void PreMainWindow::on_lineEdit_factor_z_textEdited(const QString &arg1){cfg.scaling_z=arg1.toDouble();}

void PreMainWindow::on_iteration_step_lineEdit_textEdited(const QString &arg1){cfg.solver_iteration=arg1.toInt();}

void PreMainWindow::on_CFL_lineEdit_textEdited(const QString &arg1){cfg.solver_cfl=arg1.toDouble();}
void PreMainWindow::on_CFL_ramp_lineEdit_textEdited(const QString &arg1){cfg.CFL_ramp_up=arg1.toInt();}
void PreMainWindow::on_residual_lineEdit_textEdited(const QString &arg1){cfg.solver_residual=arg1.toDouble();}
void PreMainWindow::on_period_lineEdit_textEdited(const QString &arg1){cfg.unsteady_period_time=arg1.toDouble();}
void PreMainWindow::on_n_cycle_lineEdit_textEdited(const QString &arg1){cfg.unsteady_n_period=arg1.toDouble();}
void PreMainWindow::on_step_per_cycle_lineEdit_textEdited(const QString &arg1){cfg.unsteady_n_step=arg1.toInt();}
void PreMainWindow::on_mg_level_spinBox_valueChanged(int arg1){cfg.mg_levels=arg1;}

void PreMainWindow::on_unsteady_checkbox_toggled(bool checked)
{
    if (checked)
    {
      cfg.isUnsteady=true;
      ui->load_steady_flow->setVisible(true);
      ui->tb_name_label->setVisible(true);
      ui->tb_type_combo->setVisible(true);
      ui->unsteady_simulation_label->setVisible(true);
      ui->n_cycle_label->setVisible(true);
      ui->n_cycle_lineEdit->setVisible(true);
      ui->period_label->setVisible(true);
      ui->period_unit_label->setVisible(true);
      ui->period_lineEdit->setVisible(true);
      ui->step_per_cycle_label->setVisible(true);
      ui->step_per_cycle_lineEdit->setVisible(true);
      ui->output_steady_label->setVisible(false);
      ui->output_steady_lineEdit->setVisible(false);
      ui->output_unsteady_label->setVisible(true);
      ui->output_unsteady_lineEdit->setVisible(true);
      ui->unsteady_inner_label->setVisible(true);
      ui->steady_iteration_label->setVisible(false);
      ui->interface_type_label->setText("Type: sliding plane");
      ui->passage_label->setVisible(true);
      ui->passage_repeat_tree->setVisible(true);
      ui->checkBox_passage_repeat->setVisible(true);
      ui->load_steady_flow->setVisible(true);
      for (uint32_t i=0;i<cfg.num_meshes; i++){
        for (uint32_t j=0;j<cfg.bnd[i].num_BC; j++){
          bool test=cfg.bnd[i].Types[j]==11;
          if (cfg.bnd[i].Types[j]==11) cfg.bnd[i].Types[j]=13;
          if (cfg.bnd[i].Types[j]==12) cfg.bnd[i].Types[j]=14;
        }
      }
//      ui->iteration_step_lineEdit->setText("20");
//      ui->output_unsteady_lineEdit->setText("100");
//      ui->period_lineEdit->setText("0.01");
//      ui->n_cycle_lineEdit->setText("1");
//      ui->step_per_cycle_lineEdit->setText("1800");
//      cfg.solver_iteration=20;
//      cfg.unsteady_output_step=100;
//      cfg.unsteady_period_time=0.01;
//      cfg.unsteady_n_period=1.0;
//      cfg.unsteady_n_step=1800;
      if(cfg.num_meshes>1){
        cfg.isMixingPlane = false;
        cfg.isSlidingPlane = true;
      }
    }
    else
    {
      if(cfg.num_meshes>1){
        cfg.isMixingPlane = true;
        cfg.isSlidingPlane = false;
      }
      ui->load_steady_flow->setVisible(true);
      cfg.isUnsteady=false;
      ui->tb_type_combo->setCurrentText("RANS");
      ui->tb_name_label->setVisible(false);
      ui->tb_type_combo->setVisible(false);
      ui->unsteady_simulation_label->setVisible(false);
      ui->n_cycle_label->setVisible(false);
      ui->n_cycle_lineEdit->setVisible(false);
      ui->period_label->setVisible(false);
      ui->period_unit_label->setVisible(false);
      ui->period_lineEdit->setVisible(false);
      ui->step_per_cycle_label->setVisible(false);
      ui->step_per_cycle_lineEdit->setVisible(false);
      ui->output_steady_label->setVisible(true);
      ui->output_steady_lineEdit->setVisible(true);
      ui->output_unsteady_label->setVisible(false);
      ui->output_unsteady_lineEdit->setVisible(false);
      ui->unsteady_inner_label->setVisible(false);
      ui->steady_iteration_label->setVisible(true);
      ui->iteration_step_lineEdit->setText("10000");
      cfg.solver_iteration=10000;
      ui->interface_type_label->setText("Type: mixing plane");
      ui->passage_label->setVisible(false);
      ui->passage_repeat_tree->setVisible(false);
      ui->checkBox_passage_repeat->setVisible(false);
      ui->load_steady_flow->setVisible(false);
      for (uint32_t i=0;i<cfg.num_meshes; i++){
        for (uint32_t j=0;j<cfg.bnd[i].num_BC; j++){
          if (cfg.bnd[i].Types[j]==13) cfg.bnd[i].Types[j]=11;
          if (cfg.bnd[i].Types[j]==14) cfg.bnd[i].Types[j]=12;
        }
      }
    }
}

void PreMainWindow::on_output_unsteady_lineEdit_textChanged(const QString &arg1)
{
  cfg.unsteady_output_step=arg1.toInt();
}


void PreMainWindow::on_output_steady_lineEdit_textChanged(const QString &arg1)
{
  cfg.file_write_step=arg1.toInt();
}

void PreMainWindow::on_start_simulation_button_clicked() {
    //* [New] Others Start Here
    timer->setInterval(1000);
    timer->start();

    simulationDataManager->closeFiles();
    simulationDataManager->clearData();

    residualplot->clearSeries();
    monitorplot->clearSeries();

    cfg.SaveYAML(cfg.GUI_yaml);
    QString program = "";
    program += "rm -rf mon_*.dat && ";
    program += "rm -rf hist.dat && ";
    if (cfg.isPreProcessRun) {
        cfg.SyncStep2();
        program += std::string(global_solver_name+"-pre step2 && ").c_str();
        program += "cp " + QString::fromStdString(cfg.GUI_yaml) + " " + QString::fromStdString(global_pre_setup_yaml) + "&& ";
        program += std::string(global_solver_name+"-pre step3 && ").c_str();
    }
    qDebug() << program;
    program += "cp " + QString::fromStdString(cfg.GUI_yaml) + " " + QString::fromStdString(global_pre_setup_yaml) + "&& ";
    program += QString::fromStdString(global_solver_name)+"-tools 3 1 && ";
//    program += "rm -rf mon_*.dat && ";
//    program += "rm -rf hist.dat && ";
    program += "cp " + QString::fromStdString(cfg.GUI_yaml) + " " + QString::fromStdString(global_pre_setup_yaml) + "&& ";
    //* [New]* some change for easy test
    program += "cp zjui.cfg input.dat && " ;
    program += "mpirun.mpich -np " + ui->spinCPU->text() + " " "./cipher-1.0.5";
    qDebug() << program;
    QStringList arguments;

    cfg.isPreProcessRun=false;
    ui->skip_pre_checkBox->setChecked(!cfg.isPreProcessRun);

//   std::cout<<program.toStdString()<<std::endl;

    process->start("/bin/bash", QStringList() << "-c" << program);

//* [New] updateProgressBarStatus
    progressBar->setValue(0);

    if(!simulationDataManager->isAutoRunning)
        this->updateRunningStatusMessage(QString("SingleRunning"));
//  ui->start_simulation_button->setEnabled(false);
    ui->continue_simulation_button->setEnabled(false);
    ui->run_pre_process->setEnabled(false);
    EnablePerformanceCurve(false);

}

void PreMainWindow::on_stop_simulation_button_clicked() {
  qDebug()<< "progress stopped";
//* [New]timer
  timer->stop();
  process->terminate();

  ui->start_simulation_button->setEnabled(true);
  ui->continue_simulation_button->setEnabled(true);
  ui->run_pre_process->setEnabled(true);
  EnablePerformanceCurve(true);
}

void PreMainWindow::on_gas_type_combo_currentTextChanged(const QString &arg1)
{
  if (arg1=="Ideal gas")
  {
    ui->gas_friction_lineEdit->setVisible(false);
    ui->gas_friction_label->setVisible(false);
  }
  else
  {
    ui->gas_friction_lineEdit->setVisible(true);
    ui->gas_friction_label->setVisible(true);
  }
}

void PreMainWindow::on_film_checkbox_toggled(bool checked)
{
    if (checked) {
      ui->actionactionFilmCooling->setEnabled(true);
      cfg.isFilmCoolModel=true;
      //init a empty array to store config data, 2 colum
      std::vector<std::vector<double>> film_config;
      for (uint32_t i = 0; i < 1; i++) {
        std::vector<double> film_config1;
        for (uint32_t j = 0; j < 9; j++) {
          film_config1.emplace_back(0);
        }
        film_config.emplace_back(film_config1);
      }
      //init a empty array to store input data, 2 colum
      std::vector<std::vector<double>> film_input;
      for (uint32_t i = 0; i < 1; i++) {
        std::vector<double> film_config1;
        for (uint32_t j = 0; j < 7; j++) {
          film_config1.emplace_back(0);
        }
        film_input.emplace_back(film_config1);
      }

      //init data structure for display
      for (uint32_t i = 0; i < cfg.num_meshes; i++)
      {
        std::vector<std::pair<std::string,bool>> zone_film_option;
        std::vector<std::pair<std::string,std::vector<std::vector<double>>>> zone_film_config;
        std::vector<std::pair<std::string,std::vector<std::vector<double>>>> zone_film_input;
        for (uint32_t j = 0; j < cfg.bnd[i].num_BC; j++)
        {
          std::pair<std::string,std::vector<std::vector<double>>> boundary_config;
          std::pair<std::string,std::vector<std::vector<double>>> boundary_input;
          std::pair<std::string,bool> bc_film_option;
          bc_film_option.first = cfg.bnd[i].Names[j];
          boundary_config.first = cfg.bnd[i].Names[j];
          boundary_input.first =  cfg.bnd[i].Names[j];
          bc_film_option.second = false;
          boundary_config.second = film_config;
          boundary_input.second = film_input;
          zone_film_option.emplace_back(bc_film_option);
          zone_film_config.emplace_back(boundary_config);
          zone_film_input.emplace_back(boundary_input);
        }
        cfg.boundary_film_option.emplace_back(zone_film_option);
        cfg.all_film_config_data.emplace_back(zone_film_config);
        cfg.all_film_input_data.emplace_back(zone_film_input);
      }
      // read film cooling config file
      std::ifstream file(cfg.FCconfigfile);
      std::ifstream file1(cfg.FCInputfile);
      if(cfg.isFilmCoolModel && file.good() && file1.good())
      {
        SourceParser film;
        film.ReadFilmConfigFile(cfg.FCconfigfile,cfg.mesh_files,cfg.film_groups);
        film.ReadFilmConfigFile(cfg.FCInputfile,cfg.mesh_files,cfg.film_groups_data);
        for (uint32_t i = 0; i < cfg.film_groups.size(); i++)
        {
          if (cfg.film_groups[i].flag_film_cool)
          {
            for (uint32_t j = 0; j < cfg.film_groups[i].surface_name.size(); j++)
            {
              for (uint32_t k = 0; k < cfg.boundary_film_option[i].size(); k++)
              {
                if (cfg.boundary_film_option[i][k].first == cfg.film_groups[i].surface_name[j]) {
                  cfg.boundary_film_option[i][k].second = true;
                  cfg.all_film_config_data[i][k].second.clear();
                  cfg.all_film_config_data[i][k].second = cfg.film_groups[i].config_data[j];
                }
              }
            }
          }
        }

        for (uint32_t i = 0; i < cfg.film_groups_data.size(); i++)
        {
          if (cfg.film_groups_data[i].flag_film_cool)
          {
            for (uint32_t j = 0; j < cfg.film_groups_data[i].surface_name.size(); j++)
            {
              for (uint32_t k = 0; k < cfg.boundary_film_option[i].size(); k++)
              {
                if (cfg.boundary_film_option[i][k].first == cfg.film_groups_data[i].surface_name[j]) {
                  cfg.boundary_film_option[i][k].second = true;
                  cfg.all_film_input_data[i][k].second.clear();
                  cfg.all_film_input_data[i][k].second = cfg.film_groups_data[i].config_data[j];
                }
              }
            }
          }
        }
      }
    }
    else {
      ui->actionactionFilmCooling->setEnabled(false);
      cfg.isFilmCoolModel=false;
    }
}

void PreMainWindow::on_pushButton_clicked()
{
  ConfigParser::monitor_struct new_tree;
  new_tree.type=1;
  new_tree.average_type=2;
  new_tree.face_id=1;
  new_tree.match_face_id=0;
  new_tree.output_step=1;
  new_tree.filename="monitor_"+std::to_string(cfg.num_monitor)+".dat";
  cfg.num_monitor+=1;
  cfg.monitor->num_monitors+=1;
  cfg.monitor->monitors.emplace_back(new_tree);
  GetMonitorTree();
}

void PreMainWindow::onMonitorTypeChange(QComboBox *cmb1, QComboBox *cmb2, int id)
{
  int type_id = GUI_monitor_dict.at(cmb1->currentText().toStdString());
  if (type_id==3) {
    cmb2->setEnabled(true);
    cmb2->setCurrentText(QString::fromStdString(cfg.monitor->global_bc_names[0]));
    cfg.monitor->monitors[id].type=1;
  }
  else
  {
    cmb2->setEnabled(false);
    cmb2->setCurrentText("");
    cfg.monitor->monitors[id].type=type_id;
    cfg.monitor->monitors[id].match_face_id=0;
  }
}

void PreMainWindow::onMonitorFaceChange(QComboBox *cmb1, int id)
{
  std::string st=cmb1->currentText().toStdString();
  auto it = std::find(cfg.monitor->global_bc_names.begin(), cfg.monitor->global_bc_names.end(), st);
  int ind;
  if (it != cfg.monitor->global_bc_names.end())
    ind = std::distance(cfg.monitor->global_bc_names.begin(),it);
  cfg.monitor->monitors[id].face_id=ind+1;
}

void PreMainWindow::onMonitorMFaceChange(QComboBox *cmb1, int id)
{
  std::string st=cmb1->currentText().toStdString();
  auto it = std::find(cfg.monitor->global_bc_names.begin(), cfg.monitor->global_bc_names.end(), st);
  int ind;
  if (it != cfg.monitor->global_bc_names.end())
    ind = std::distance(cfg.monitor->global_bc_names.begin(),it);
  cfg.monitor->monitors[id].match_face_id=ind+1;
}

void PreMainWindow::onMonitorAverageChange(QComboBox *cmb1, int id) {
  std::string st=cmb1->currentText().toStdString();
  cfg.monitor->monitors[id].average_type=GUI_monitor_average.at(st);
}

void PreMainWindow::onMonitorDeleteMonitor(int id) {
  cfg.monitor->monitors.erase(cfg.monitor->monitors.begin()+id);
  cfg.num_monitor-=1;
  cfg.monitor->num_monitors-=1;
  GetMonitorTree();
}

void PreMainWindow::showFinishDialog(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Enter showFinishDialog";
    qDebug() << "exitCode:" << exitCode;
    qDebug() << "exitStatus:" << exitStatus;
    timer->stop();

    this->setResultTableData();
    performPlot->updateChart(simulationDataManager->getMonitorData());
    statusLabel->setText("Status: waiting");

//* [New] some change here for auto Running
  if (exitCode==0 && exitStatus==QProcess::NormalExit) {
      qDebug() << "Inside if condition";
      qDebug() << "progress arrived at 100";
      progressBar->setValue(100);
      if(!simulationDataManager->isAutoRunning)
        QMessageBox::information(nullptr, "Finish Dialog", "Finished");
      on_stop_simulation_button_clicked();
  }

  if(simulationDataManager->isAutoRunning){
    simulationDataManager->currentIndex_AutoRunPressure++;
    this->updateHistoryCombox();
    simulationDataManager->saveCurrentOutputFile(cfg.p_curve.target_p);
    QTimer::singleShot(3000,[=]{this->autoSingleRun();});
  }

}

void PreMainWindow::handleError(QProcess::ProcessError error) {
    QString errorMsg;
    switch (error) {
        case QProcess::FailedToStart:
            errorMsg = "The process failed to start. This means the path is incorrect, "
                       "the file is not executable, or you do not have the required permissions.";
            break;
        case QProcess::Crashed:
            errorMsg = "The process has crashed after starting successfully.";
            break;
        case QProcess::Timedout:
            errorMsg = "The process timed out.";
            break;
        case QProcess::WriteError:
            errorMsg = "An I/O error occurred when writing to the process.";
            break;
        case QProcess::ReadError:
            errorMsg = "An I/O error occurred when reading from the process.";
            break;
        case QProcess::UnknownError:
            errorMsg = "An unknown error occurred.";
            break;
    }
    QMessageBox::critical(nullptr, "Process Error", errorMsg);
  on_stop_simulation_button_clicked();
}

void PreMainWindow::on_continue_simulation_button_clicked()
{

  simulationDataManager->closeFiles();
  simulationDataManager->clearData();
  residualplot->clearSeries();
  monitorplot->clearSeries();

  cfg.isAppend=true;
  cfg.SaveYAML(cfg.GUI_yaml);
  QString program = "";
  program += "cp " + QString::fromStdString(cfg.GUI_yaml) + " " + QString::fromStdString(global_pre_setup_yaml) + "&& ";
  program += QString::fromStdString(global_solver_name)+"-tools 3 1 && ";
  //* [New]*some change for easy test
  program += "rm -rf mon_*.dat && ";
  program += "rm -rf hist.dat && ";
  program += "cp zjui.cfg input.dat && " ;
  program += "mpirun -np " + ui->spinCPU->text() + " " +"./cipher-1.0.5";
  QStringList arguments;
  qDebug() << program;
  process->start("/bin/bash", QStringList() << "-c" << program);

  ui->start_simulation_button->setEnabled(false);
  ui->continue_simulation_button->setEnabled(false);
  ui->run_pre_process->setEnabled(false);
  EnablePerformanceCurve(false);

  progressBar->setValue(0);
  if(!simulationDataManager->isAutoRunning)
      this->updateRunningStatusMessage(QString("SingleRunning"));
  //* [New] timer
  timer->start();
}


void PreMainWindow::on_run_pre_process_clicked()
{
  cfg.isAppend=true;
  cfg.SaveYAML(cfg.GUI_yaml);
  cfg.SyncStep2();
  QString program = "";
  program += QString::fromStdString(global_solver_name)+"-pre step2 && ";
  program += "cp " + QString::fromStdString(cfg.GUI_yaml) + " " + QString::fromStdString(global_pre_setup_yaml) + "&& ";
  program += QString::fromStdString(global_solver_name)+"-pre step3 && ";
  program += QString::fromStdString(global_solver_name)+"-tools 3 1";
  QStringList arguments;

//  std::cout<<program.toStdString()<<std::endl;

  process->start("/bin/bash", QStringList() << "-c" << program);

  ui->start_simulation_button->setEnabled(false);
  ui->continue_simulation_button->setEnabled(false);
  ui->run_pre_process->setEnabled(false);
  EnablePerformanceCurve(false);
}


void PreMainWindow::on_saveYAMLButton_clicked()
{
  cfg.SaveYAML(cfg.GUI_yaml);
}

void PreMainWindow::on_checkBox_passage_repeat_clicked(bool checked)
{
  ui->passage_repeat_tree->setEnabled(checked);
  if (!checked){
    for (uint32_t i=0; i<cfg.num_meshes; i++) {
      cfg.num_passages[i] = 1;
    }
  }
  ShowPassageRepeatTree();
}

void PreMainWindow::onPassageRepeatChanged(QLineEdit *edt, int zone_id) {
  cfg.num_passages[zone_id]=edt->text().toInt();
}

void PreMainWindow::on_checkBox_helicity_toggled(bool checked)
{
  cfg.rans_helicity=checked;
}

void PreMainWindow::on_checkBox_cmott_toggled(bool checked)
{
  if (checked) {
    ui->checkBox_kl->toggled(false);
    ui->checkBox_kl->setEnabled(false);
  }
  else
  {
    ui->checkBox_kl->setEnabled(true);
  }
  cfg.rans_cmott=checked;
}


void PreMainWindow::on_checkBox_kl_toggled(bool checked)
{
  if (checked) {
    ui->checkBox_cmott->toggled(false);
    ui->checkBox_cmott->setEnabled(false);
  }
  else
  {
    ui->checkBox_cmott->setEnabled(true);
  }
  cfg.rans_kl=checked;
}


void PreMainWindow::on_checkBox_transition_toggled(bool checked)
{
  if (checked){
    ui->check_wf->toggled(false);
    ui->check_wf->setChecked(false);
    ui->check_wf->setEnabled(false);
    ui->checkBox_helicity->toggled(false);
    ui->checkBox_helicity->setChecked(false);
    ui->checkBox_helicity->setEnabled(false);
    ui->comboBox_qcr->setEnabled(false);
    ui->comboBox_qcr->setCurrentText("none");
  }
  else
  {
    ui->check_wf->setEnabled(true);
    ui->comboBox_qcr->setEnabled(true);
    ui->checkBox_helicity->setEnabled(true);
  }
  cfg.rans_transit=checked;
}

void PreMainWindow::on_comboBox_qcr_currentTextChanged(const QString &arg1)
{
  cfg.rans_qcr=arg1.toStdString();
}

void PreMainWindow::on_checkBox_performance_toggled(bool checked)
{
  if (checked) {
    ShowPerformanceCurve(true);
    cfg.isRunPerformanceCurve=true;
  }
  else{
    ShowPerformanceCurve(false);
    cfg.isRunPerformanceCurve=false;
  }
}

void PreMainWindow::on_save_p_button_clicked()
{
//  QString flowname = "AEAC.flow.hdf" ;
  QString flowname = QString::fromStdString(cfg.all_solu_fname) ;
  SaveFlowData *saveflow_data = new SaveFlowData(this);
  saveflow_data->openFolderAndCopyFiles(flowname);
  connect(saveflow_data, &SaveFlowData::destroyed, [saveflow_data]() {
      delete saveflow_data;
  });
  cfg.p_curve.initial_p=ui->target_p_value->text().toDouble();
  ui->current_p_value->setText(ui->target_p_value->text());
  ui->target_p_value->setText("");
  ui->start_simulation_button->setEnabled(true);
//  cfg.p_curve.n_points+=1;
  cfg.p_curve.n_points+=1;
  cfg.p_curve.pressure_list.emplace_back(cfg.p_curve.target_p);
  cfg.p_curve.case_list.emplace_back(flowname.toStdString());

}

void PreMainWindow::on_load_p_button_clicked()
{
  QString current_flow_file = QString::fromStdString(cfg.all_solu_init_fname);

  LoadFlowData dialog(this, current_flow_file);
  if (dialog.exec() == QDialog::Accepted) {
    QString flowFileName = dialog.getFlowFileName();
//    QString relativeFlowFileName = dialog.getRelativeFlowFileName();2
//
//    QString input_flow = relativeFlowFileName + flowFileName;

    QString program = "";
    program += "cp " + flowFileName + " ./" + QString::fromStdString(cfg.all_solu_fname);

    process->start("/bin/bash", QStringList() << "-c" << program);
  }
  ui->start_simulation_button->setEnabled(true);

}

void PreMainWindow::getBackPressure()
{
  double current_p=0.0;
  for (uint32_t i = 0; i < cfg.num_meshes; i++) {
    for (uint32_t j = 0; j < cfg.bnd[i].num_BC; j++) {
      if (cfg.bnd[i].Types[j] == 5) {
        current_p = cfg.bnd[i].Outlets[j].points_data_out[0][1];
      }
    }
  }
  ui->target_p_value->setText(QString::number(current_p));
  ui->target_p_value->editingFinished();
}

void PreMainWindow::on_target_p_value_editingFinished()
{
  QString current_p = ui->target_p_value->text();
  cfg.p_curve.target_p=current_p.toDouble();
//  ui->current_p_value->setText(current_p);

  for (uint32_t i = 0; i < cfg.num_meshes; i++){
    for (uint32_t j = 0; j < cfg.bnd[i].num_BC; j++){
      if(cfg.bnd[i].Types[j] == 5){
        for (uint32_t k = 0; k<cfg.bnd[i].Outlets[j].points_data_out.size(); k++)
          cfg.bnd[i].Outlets[j].points_data_out[k][1] = current_p.toDouble();
      }
    }
  }
//  cfg.SaveYAML(cfg.GUI_yaml);
//
//  QString program = "";
//  program += "cp " + QString::fromStdString(cfg.GUI_yaml) + " " + QString::fromStdString(global_pre_setup_yaml);
//  program += "&& aesim-uns-tools 3 1";
//  QStringList arguments;
//
//  process->start("/bin/bash", QStringList() << "-c" << program);
}


void PreMainWindow::on_spinCPU_valueChanged(int arg1)
{
  cfg.CPU_core=arg1;
}

void PreMainWindow::on_skip_pre_checkBox_toggled(bool checked)
{
  if (checked)
    cfg.isPreProcessRun=false;
  else
    cfg.isPreProcessRun=true;
}

void PreMainWindow::ShowPerformanceCurve(bool isShow) {
  for (int i = 0; i < ui->curve_grid_layout->count(); i++) {
    ui->curve_grid_layout->itemAt(i)->widget()->setVisible(isShow);
  }
}

void PreMainWindow::EnablePerformanceCurve(bool isEnable) {
  for (int i = 0; i < ui->curve_grid_layout->count(); i++) {
    ui->curve_grid_layout->itemAt(i)->widget()->setEnabled(isEnable);
  }
}

void PreMainWindow::ShowPassageRepeatTree() {
  ui->passage_repeat_tree->clear();
  if (!ui->checkBox_passage_repeat) return;
  for (int i=0; i<cfg.num_passages.size(); i++)
  {
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    ui->passage_repeat_tree->addTopLevelItem(treeItem);
    QLabel *zone_name = new QLabel(this);
    QLabel *angle = new QLabel(this);
    QLineEdit *p_num = new QLineEdit(this);
    zone_name->setText(QString::fromStdString(cfg.mesh_files[i]));
    angle->setText("TODO");
    p_num->setText(QString::number(cfg.num_passages[i]));

    ui->passage_repeat_tree->setItemWidget(treeItem, 0, zone_name);
    ui->passage_repeat_tree->setItemWidget(treeItem, 1, angle);
    ui->passage_repeat_tree->setItemWidget(treeItem, 2, p_num);

    connect(p_num, &QLineEdit::editingFinished,
            [this, p_num, i] {
                this->onPassageRepeatChanged(p_num, i);
            });
  }
}

void PreMainWindow::on_generate_film_boundary_clicked()
{
  cfg.is_film_generate = true;
  for (uint32_t i = 0; i < cfg.num_meshes; i++)
  {
    uint32_t boundary_count =0;
    uint32_t num_bc = cfg.bnd[i].num_BC;
    for (uint32_t j = 0; j < num_bc; j++)
    {
      if (cfg.boundary_film_option[i][j].second) //decide which boundary have film boundary
      {
//        std::cout << " " << cfg.boundary_film_option[i][j].first<< std::endl;
        boundary_count +=1;
        for (uint32_t k = 0; k < cfg.all_film_config_data[i][j].second.size(); k++)
        {
          std::string film_bc_name ="surf"+ std::to_string(boundary_count)+"-row"+std::to_string(k+1);
          BoundaryParser::bc_wall new_wall;
          BoundaryParser::bc_subsonic_inlet new_in;
          BoundaryParser::bc_subsonic_outlet new_out;
          BoundaryParser::bc_film_cool_inlet new_film;
          new_film.num_profile_in =2;
          new_film.film_file = "BC_files/" + cfg.mesh_files[i] + "-" + film_bc_name+".dat" ;
          uint32_t len = 6;
          if (cfg.rans_model != "sa") len = 7;
          std::vector<std::vector<double>> profile;
          for (uint32_t l = 0; l < 2; l++)
          {
            std::vector<double> profile1;
            if (l == 0) profile1.emplace_back(-1000);
            else profile1.emplace_back(1000);
            for (uint32_t m = 0; m < len; m++)
            {
              if (m < 5) profile1.emplace_back(cfg.all_film_input_data[i][j].second[k][m]);
              else if (cfg.rans_model == "sa") profile1.emplace_back(1.7616e-04);
              else profile1.emplace_back(1);
            }
            profile.emplace_back(profile1);
          }
          new_film.points_data_in=profile;
          new_film.profile_distribution_direction_in = 1;
          new_film.mass_flow_in = cfg.all_film_input_data[i][j].second[k][5];
          new_film.temperature_in = cfg.all_film_input_data[i][j].second[k][6];

          cfg.bnd[i].Walls.emplace_back(new_wall);
          cfg.bnd[i].Inlets.emplace_back(new_in);
          cfg.bnd[i].Outlets.emplace_back(new_out);
          cfg.bnd[i].FilmCoolInlets.emplace_back(new_film);
          cfg.bnd[i].num_BC+=1;
          cfg.bnd[i].Types.emplace_back(28);
          cfg.bnd[i].Names.emplace_back(film_bc_name);
        }
      }
    }
  }
}



//Monitor Start Here
void PreMainWindow::onSelectFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Select Monitor File", "", "Monitor Files (mon*.dat);;All Files (*)");

    if (filePath.isEmpty()){
        qDebug() << "select a valid file path";
        return;
    }

    ui->List_Variable->clear();
    if(filePath.contains("inlet")){
        ui->List_Variable->addItem("pTotal(inlet)");
        ui->List_Variable->addItem("tTotal(inlet)");
        ui->List_Variable->addItem("vAxial(inlet)");
        ui->List_Variable->addItem("vTheta(inlet)");
        ui->List_Variable->addItem("pStatic(inlet)");
        ui->List_Variable->addItem("mDot(inlet)");
    }
    if(filePath.contains("outlet")){
        ui->List_Variable->addItem("pTotal(outlet)");
        ui->List_Variable->addItem("tTotal(outlet)");
        ui->List_Variable->addItem("vAxial(outlet)");
        ui->List_Variable->addItem("vTheta(outlet)");
        ui->List_Variable->addItem("pStatic(outlet)");
        ui->List_Variable->addItem("mDot(outlet)");
    }
    if(filePath.contains("perf")){
        ui->List_Variable->addItem("pRatio");
        ui->List_Variable->addItem("tRatio");
        ui->List_Variable->addItem("efficiency");
        ui->List_Variable->addItem("turning");
        ui->List_Variable->addItem("qInlet");
        ui->List_Variable->addItem("qOutlet");
    }
}



void PreMainWindow::onVariableSelectionChanged()
{
    if(ui->List_Variable->selectedItems().isEmpty()){
        monitorplot->hideSeries();
        qDebug() << "List is empty ";
        return;
    }

    monitorplot->displayVariableList.clear();
    for(auto const item : ui->List_Variable->selectedItems()){
        qDebug()<<item->data(Qt::DisplayRole).toString();
        monitorplot->displayVariableList.append(item->data(Qt::DisplayRole).toString());
    }

    monitorplot->updateSeriesVisibility(monitorplot->displayVariableList);
    monitorplot->updateRangeOnVariableChange();
    //updateMonitorData();

}



//* [New]Others StartHere
void PreMainWindow::updateInterfaceUI() {
    qDebug()<<ui->CBox_Theme->currentIndex();
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
            ui->CBox_Theme->itemData(ui->CBox_Theme->currentIndex()).toInt());
    monitorplot->monitorchart->setTheme(theme);
    residualplot->residualchart->setTheme(theme);

    if(syncMainWindowTheme == 1) {
        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
            //![8]
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }
    monitorplot->setChartStyle();
    residualplot->setChartStyle();
}

void PreMainWindow::updateHistoryCombox() {
    QString historyName = QString("Pressure: %1").arg(cfg.p_curve.target_p);
    residualplot->updateDataHistory(historyName);
    ui->CBtn_History->clear();
    ui->CBtn_History->addItem(" ");
    ui->CBtn_History->addItems(residualplot->getHistoryName());
}

void PreMainWindow::on_CBtnHisotyIndexChanged(int index) {
    QString currentItemText = ui->CBtn_History->itemText(index);
    if(currentItemText == " ")
        return;
    else
        residualplot->loadHisotyData(currentItemText);
}

void PreMainWindow::on_Btn_ClearHistory_clicked() {
    residualplot->clearHistory();
    ui->CBtn_History->clear();
    this->on_Btn_ClearPerformData_clicked();
}

void PreMainWindow::updateProgressBar() {
    auto& iteration = simulationDataManager->getIterations();
    if(iteration.isEmpty())
        return;
    int currentProgress = (iteration.last()*100 / cfg.solver_iteration );

    progressBar->setValue(currentProgress);

}

void PreMainWindow::updateRunningStatusMessage(QString runningStatus) {
    QString statusMsg = " ";
    if(runningStatus == "AutoRunning") {
        double currentPressure = simulationDataManager->pressureList_AutoRun[simulationDataManager->currentIndex_AutoRunPressure];
        statusMsg = QString("Status: Running(Calculating Pressure Point:%1 Pa  %2/%3)")
                .arg(currentPressure)
                .arg(simulationDataManager->currentIndex_AutoRunPressure + 1)
                .arg(simulationDataManager->pressureList_AutoRun.size());
    }
    if(runningStatus == "SingleRunning"){
        double currentPressure = cfg.p_curve.target_p;
        statusMsg = QString("Status: Running(Calculating Pressure:%1 Pa)")
                .arg(currentPressure);
    }

    statusLabel->setText(statusMsg);
}

void PreMainWindow::setResultTableData() {
    if(simulationDataManager->getMonitorData().perform.pRatio.isEmpty())
        return;
    ui->Result_Table->setItem(indexResultTable,0,new QTableWidgetItem(QString::number(indexResultTable+1)) );
    ui->Result_Table->setItem(indexResultTable,1,new QTableWidgetItem(QString::number(cfg.p_curve.target_p) ) );
    ui->Result_Table->setItem(indexResultTable,2,new QTableWidgetItem(QString::number(simulationDataManager->getMonitorData().outlet.mDot.last())) );
    ui->Result_Table->setItem(indexResultTable,3,new QTableWidgetItem(QString::number(simulationDataManager->getMonitorData().perform.pRatio.last())) );
    ui->Result_Table->setItem(indexResultTable,4,new QTableWidgetItem(QString::number(simulationDataManager->getMonitorData().perform.tRatio.last())) );
    ui->Result_Table->setItem(indexResultTable,5,new QTableWidgetItem(QString::number(simulationDataManager->getMonitorData().perform.efficiency.last())) );

    indexResultTable++;
}

void PreMainWindow::on_Btn_ClearPerformData_clicked() {
    //* saving table Header
    QStringList headers;
    for(int i = 0; i < ui->Result_Table->columnCount(); i++) {
        headers << ui->Result_Table->horizontalHeaderItem(i)->text();
    }

    ui->Result_Table->clear();
    ui->Result_Table->setHorizontalHeaderLabels(headers);

    performPlot->clearChartData();
    indexResultTable = 0 ;
}

void PreMainWindow::on_Btn_Start_AutoRun_clicked() {
    qDebug() << "you pressed the Start Button" ;
    simulationDataManager->currentIndex_AutoRunPressure = 0 ;
    if(ui->LEdit_StartPressure_AutoRun->text().isEmpty() ||ui->LEdit_EndPressure_AutoRun->text().isEmpty()
       ||ui->LEdit_NumPoints_AutoRun->text().isEmpty())
    {
        QMessageBox::warning(this,"warning","enter the valid values");
        return;
    }

    double start_Pressure = ui->LEdit_StartPressure_AutoRun->text().toDouble();
    double end_Pressure = ui->LEdit_EndPressure_AutoRun->text().toDouble();
    int num_Points = ui->LEdit_NumPoints_AutoRun->text().toInt();

    if(!simulationDataManager->generatePressurePoints(start_Pressure,end_Pressure,num_Points) ){
        QMessageBox::warning(this,"warning","Invalid Input");
        return;
    }

    simulationDataManager->isAutoRunning = 1;
    this->on_Btn_ClearHistory_clicked();
    this->autoSingleRun();
    ui->start_simulation_button->setEnabled(false);
    ui->continue_simulation_button->setEnabled(false);
    ui->stop_simulation_button->setEnabled(false);
    ui->Btn_Start_AutoRun->setEnabled(false);
    ui->Btn_Skip_AutoRun->setEnabled(true);
    ui->Btn_End_AutoRun->setEnabled(true);
}

void PreMainWindow::on_Btn_Skip_AutoRun_clicked() {
    qDebug() << "you pressed the Skip Button" ;
    this->on_stop_simulation_button_clicked();
}

void PreMainWindow::on_Btn_End_AutoRun_clicked() {
    qDebug() << "you pressed the End Button" ;
    simulationDataManager->isAutoRunning = 0 ;
    this->on_stop_simulation_button_clicked();
    ui->start_simulation_button->setEnabled(true);
    ui->continue_simulation_button->setEnabled(true);
    ui->stop_simulation_button->setEnabled(true);
    ui->Btn_Start_AutoRun->setEnabled(true);
    ui->Btn_End_AutoRun->setEnabled(true);
}

void PreMainWindow::autoSingleRun() {
    qDebug() << "cipher is auto running" ;
    int currentIndex_AutoRunPressure = simulationDataManager->currentIndex_AutoRunPressure;
    QList<double>& pressureList_AutoRun = simulationDataManager->pressureList_AutoRun;

    if(currentIndex_AutoRunPressure >= pressureList_AutoRun.size()){
        QMessageBox::information(this,"information","All calculation is finished");
        simulationDataManager->isAutoRunning = 0;
        ui->start_simulation_button->setEnabled(true);
        ui->continue_simulation_button->setEnabled(true);
        ui->stop_simulation_button->setEnabled(true);
        ui->Btn_Start_AutoRun->setEnabled(true);
        ui->Btn_Skip_AutoRun->setEnabled(false);
        ui->Btn_End_AutoRun->setEnabled(false);
        return;
    }
    this->updateRunningStatusMessage(QString("AutoRunning"));
    int currentPressure = static_cast<int> (pressureList_AutoRun[currentIndex_AutoRunPressure]);
    cfg.p_curve.target_p = currentPressure;

    if(currentIndex_AutoRunPressure == 0)
        this->on_start_simulation_button_clicked();
    else{
        this->on_continue_simulation_button_clicked();
    }

}

void PreMainWindow::showTimeMessge(QLabel* label, const QString message, int mesc) {
    label->setText(message);
    QTimer::singleShot(mesc,label,[label]{label->clear();});
}

void PreMainWindow::on_Btn_ExportPerformPic_clicked()
{
    qDebug()<< "you pressed export Button";

    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Chart Image"),
                                                    "PerformView.png",tr("Images (*.png *.jpg *.bmp)"));

    QPixmap pixPerform = performPlot->grab(QRect(QPoint(0, 0), performPlot->chart()->size().toSize()));

    if (!pixPerform.save(fileName)) {
        QMessageBox::warning(this, tr("Save Error"),
                             tr("Failed to save the image."));
        return;
    }
}

void PreMainWindow::setup_UiElements() {

    ui->LayoutforPerform->addWidget(performPlot);
    ui->LayoutforConverPlot->addWidget(residualplot);
    ui->Lay_MonitorPlot->addWidget(monitorplot);

    ui->Show_MainWindow->setCurrentIndex(0);

//* [New]ResultTable Style Start Here
    ui->Result_Table->verticalHeader()->setVisible(false);
    ui->Result_Table->horizontalHeader()->setStretchLastSection(true);
    ui->Result_Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Result_Table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Result_Table->setSelectionMode(QAbstractItemView::SingleSelection);
//  ui->Result_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->Result_Table->verticalHeader()->setDefaultSectionSize(40);
//* [New]StatusBar Start
    statusLabel = new QLabel("Status: waiting",this);
    QWidget* tempwidget = new QWidget(this);
    progressBar = new QProgressBar(this);
    progressBar->setFixedWidth(800);
    progressBar->setValue(0);
    ui->statusbar->addWidget(statusLabel);
    ui->statusbar->insertPermanentWidget(1,tempwidget,1);
    ui->statusbar->insertPermanentWidget(2, progressBar, 1);
//* [New]Qss Loading
    QFile file(":/qss/linux.qss");
    if(file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Failed to open stylesheet:" << file.errorString();
    }

    //* [New]Residual Start Here

    ui->control_panel_Range_Res->setEnabled(0);

    //* [New]Monitor Start Here

    ui->control_panel_Range_Mon->setEnabled(false);

    //* [New]Perf Start Here
    QStringList perfVariable = {"Pressure Ratio","Temperature Ratio","Efficiency"};
    ui->CBtn_SelectPerfVariable->addItems(perfVariable);
    this->performPlot->updateVisibility(0);

    //* [New]Button Status Initialize
    ui->Btn_Skip_AutoRun->setEnabled(false);
    ui->Btn_End_AutoRun->setEnabled(false);

    ui->CBox_Theme->addItem("Light", QChart::ChartThemeLight);
    ui->CBox_Theme->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    ui->CBox_Theme->addItem("Dark", QChart::ChartThemeDark);
    ui->CBox_Theme->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    ui->CBox_Theme->addItem("High Contrast", QChart::ChartThemeHighContrast);
    ui->CBox_Theme->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    ui->CBox_Theme->addItem("Qt", QChart::ChartThemeQt);
    ui->Btn_SyncWindowTheme->setVisible(false);

//    QMainWindow* container_TabModel = new QMainWindow(this);
//    ui->LayoutforContainTab1->addWidget(container_TabModel);
//    QWidget* centralWidget = new QWidget(container_TabModel);
//    QVBoxLayout* RunGraphLayout = new QVBoxLayout(centralWidget);
//    RunGraphLayout->setSpacing(0);
//    RunGraphLayout->setContentsMargins(0, 0, 0, 0);
}

void PreMainWindow::setup_Connection() {
    connect(timer, &QTimer::timeout, simulationDataManager, &SimulationDataManager::updateResidual);
    connect(timer, &QTimer::timeout, simulationDataManager, &SimulationDataManager::updateMonitorData);
    connect(timer,&QTimer::timeout,this, &PreMainWindow::updateProgressBar);

    connect(simulationDataManager, &SimulationDataManager::residualDataUpdated,
            residualplot, &Residual_Plot::updateResidualPlot);
    connect(simulationDataManager, &SimulationDataManager::monitorDataUpdated,
            monitorplot, &MonitorPlot::updateMonitorChart);


    //* [New]Residual Button Binding Here

    connect(ui->Btn_ManualScale_Res,&QPushButton::clicked,this,[this](){residualplot->setManualScaleMode();ui->control_panel_Range_Res->setEnabled(1);});
    connect(ui->Btn_AutoScale_Res, &QPushButton::clicked,this,[this](){residualplot->setAutoScaleMode();ui->control_panel_Range_Res->setEnabled(0);});

    connect(ui->Line_RangeX_Res_Min,&QLineEdit::textChanged,this,[this](const QString& text){
        residualplot->setRangeX_Min(text);});
    connect(ui->Line_RangeX_Res_Max,&QLineEdit::textChanged,this,[this](const QString& text){
        residualplot->setRangeX_Max(text);});
    connect(ui->Line_RangeY1_Res_Min,&QLineEdit::textChanged,this,[this](const QString& text){
        residualplot->setRangeY1_Min(text);});
    connect(ui->Line_RangeY1_Res_Max,&QLineEdit::textChanged,this,[this](const QString& text){
        residualplot->setRangeY1_Max(text);});
    connect(ui->Line_RangeY2_Res_Min,&QLineEdit::textChanged,this,[this](const QString& text){
        residualplot->setRangeY2_Min(text);});
    connect(ui->Line_RangeY2_Res_Max,&QLineEdit::textChanged,this,[this](const QString& text){
        residualplot->setRangeY2_Max(text);});


    //* [New]Monitor Button Binding Here

    connect(ui->Btn_SelectMonitor, &QPushButton::clicked, this, &PreMainWindow::onSelectFile);
    connect(ui->List_Variable, &QListWidget::itemSelectionChanged,
            this, &PreMainWindow::onVariableSelectionChanged);
    connect(ui->Line_RangeX_Mon_Min,&QLineEdit::textChanged,this,[this](const QString& text){
        monitorplot->setRangeX_Min(text);});
    connect(ui->Line_RangeX_Mon_Max,&QLineEdit::textChanged,this,[this](const QString& text){
        monitorplot->setRangeX_Max(text);});
    connect(ui->Line_RangeY_Mon_Min,&QLineEdit::textChanged,this,[this](const QString& text){
        monitorplot->setRangeY_Min(text);});
    connect(ui->Line_RangeY_Mon_Max,&QLineEdit::textChanged,this,[this](const QString& text){
        monitorplot->setRangeY_Max(text);});

    connect(ui->Btn_ManualScale_Mon,&QPushButton::clicked,this,[this](){monitorplot->setManualScaleMode();ui->control_panel_Range_Mon->setEnabled(1);});
    connect(ui->Btn_AutoScale_Mon, &QPushButton::clicked,this,[this](){monitorplot->setAutoScaleMode();ui->control_panel_Range_Mon->setEnabled(0);});


    //* [New]Perf Button Binding Here

    connect(ui->Line_RangeX_Perf_Min,&QLineEdit::textChanged,this,[this](const QString& text){
        performPlot->setRangeX_Min(text);});
    connect(ui->Line_RangeX_Perf_Max,&QLineEdit::textChanged,this,[this](const QString& text){
        performPlot->setRangeX_Max(text);});
    connect(ui->Line_RangeY_Perf_Min,&QLineEdit::textChanged,this,[this](const QString& text){
        performPlot->setRangeY_Min(text);});
    connect(ui->Line_RangeY_Perf_Max,&QLineEdit::textChanged,this,[this](const QString& text){
        performPlot->setRangeY_Max(text);});
    connect(ui->CBtn_SelectPerfVariable,QOverload<int>::of(&QComboBox::currentIndexChanged),performPlot,&Perform_Plot::updateVisibility);
    connect(ui->CBtn_History,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&PreMainWindow::on_CBtnHisotyIndexChanged);//* [New]Others Start Here
    //* [New]Others Start Here

    connect(ui->CBox_Theme,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&PreMainWindow::updateInterfaceUI);
    connect(ui->Btn_SyncWindowTheme,&QPushButton::clicked,this,[this](){
        if(!syncMainWindowTheme){ui->Btn_SyncWindowTheme->setText("UnSync");syncMainWindowTheme=1;}
        else{ui->Btn_SyncWindowTheme->setText("Sync");syncMainWindowTheme=0;};
    });
}