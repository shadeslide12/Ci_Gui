#include "BCExtra.h"
#include "ui_BCExtra.h"

BCExtra::BCExtra(PreProcessSettings *cfg_in, int zone_id_in, int bc_id_in, std::string bc_text_in, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BCExtra)
{
  ui->setupUi(this);
  cfg = cfg_in;
  zone_id = zone_id_in;
  bc_id = bc_id_in;
  bc_text = bc_text_in;
  bc_type = cfg->bnd[zone_id].Types[bc_id];
  SetupUI();
}

BCExtra::~BCExtra()
{
    delete ui;
}

void BCExtra::SetupProfileTable() {
  ui->profile_table->clear();
  std::string tb_local = cfg->GUI_rans_model;
  if ( cfg->GUI_rans_model == "k-omega(k-ω)" && cfg->rans_transit)
    tb_local = "k-omega(k-ω) gamma";
  int num_var=flow_vars.at(tb_local).size();
  ui->profile_table->setVisible(false);
  ui->profile_label->setVisible(false);
  ui->load_profile_button->setVisible(false);
  std::vector<std::vector<double>> data;
  int num_profile;
  if (bc_text == "Subsonic Inflow" || bc_text == "Supersonic Inflow") {
    int sup_shift=0;
    QStringList head_string;
    if (bc_text == "Subsonic Inflow"){
      head_string.append({"coord\n(m)","total\ntemperature\n(k)","total\npressure\n(Pa)","yaw angle\n(°)", "pitch angle\n(°)"});
    }
    else{
      head_string.append({"coord\n(m)","total\ntemperature\n(k)","total\npressure\n(Pa)","mach number","yaw angle\n(°)", "pitch angle\n(°)"});
      sup_shift=1;
    }
    ui->profile_table->setColumnCount(num_var+sup_shift);
    num_profile=cfg->bnd[zone_id].Inlets[bc_id].num_profile_in;
    ui->profile_table->setRowCount(num_profile);
    cfg->bnd[zone_id].Inlets[bc_id].len_profile=num_var;
    for (uint32_t i=5;i<num_var;i++)
    {
      head_string.append(QString::fromStdString(flow_vars.at(tb_local)[i]));
    }
    ui->profile_table->setHorizontalHeaderLabels(head_string);
    ui->profile_table->setVisible(true);
    ui->profile_label->setVisible(true);
    ui->load_profile_button->setVisible(true);
    data=cfg->bnd[zone_id].Inlets[bc_id].points_data_in;
    if (num_profile>data.size()){
      int insert_line=num_profile-data.size();
      for (int i=0;i<insert_line;i++) {
        data.emplace_back(data.back());
      }
      cfg->bnd[zone_id].Inlets[bc_id].points_data_in = data;
    }
    for (int i = 0; i < data.size(); ++i) {
      for (int j = 0; j < data[i].size(); ++j) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(data[i][j]));
        ui->profile_table->setItem(i, j, item);
      }
    }
  }
  else if (bc_text == "Subsonic Outflow" || bc_text == "Supersonic Outflow") {
    QStringList head_string={"coord\n(m)","pressure\n(Pa)","total\ntemperature\n(k)"};
    ui->profile_table->setColumnCount(3);
    num_profile=cfg->bnd[zone_id].Outlets[bc_id].num_profile_out;
    ui->profile_table->setRowCount(num_profile);

    ui->profile_table->setHorizontalHeaderLabels(head_string);
    ui->profile_table->setVisible(true);
    ui->profile_label->setVisible(true);
    ui->load_profile_button->setVisible(true);
    data=cfg->bnd[zone_id].Outlets[bc_id].points_data_out;
    if (num_profile>data.size())
    {
      int insert_line=num_profile-data.size();
      for (int i=0;i<insert_line;i++) {
        data.emplace_back(data.back());
      }
      cfg->bnd[zone_id].Outlets[bc_id].points_data_out = data;
    }
    for (int i = 0; i < data.size(); ++i) {
      for (int j = 0; j < data[i].size(); ++j) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(data[i][j]));
        ui->profile_table->setItem(i, j, item);
      }
    }
  }

  //  ui->show();
  connect(ui->profile_table, &QTableWidget::itemChanged, this, &BCExtra::onItemChanged);
}

void BCExtra::SetupUI() {
  ui->zone_name_edit->setText(QString::fromStdString(cfg->mesh_files[zone_id]));
  ui->BC_name_edit->setText(QString::fromStdString(cfg->bnd[zone_id].Names[bc_id]));
  ui->BC_type_edit->setText(QString::fromStdString(bc_text));
  if(cfg->isAnnular)
  {
    ui->angular_velocity_edit->setVisible(true);
    ui->angular_velocity_label->setVisible(true);
    ui->angular_velocity_edit->setText(QString::fromStdString(std::to_string(cfg->turbo_zone_velocity[zone_id] )+ " rad/s"));
    SetupDoubleLineEdit(this, ui->wall_angular_velocity_lineEdit, cfg->bnd[zone_id].Walls[bc_id].wall_angular_velocity);
  }
  else
  {
    ui->angular_velocity_label->setVisible(false);
    ui->angular_velocity_edit->setVisible(false);
    ui->angular_velocity_edit->setText("0.0");
    SetupDoubleLineEdit(this, ui->wall_velocity_u_lineEdit, cfg->bnd[zone_id].Walls[bc_id].wall_x_velocity);
    SetupDoubleLineEdit(this, ui->wall_velocity_v_lineEdit, cfg->bnd[zone_id].Walls[bc_id].wall_y_velocity);
    SetupDoubleLineEdit(this, ui->wall_velocity_w_lineEdit, cfg->bnd[zone_id].Walls[bc_id].wall_z_velocity);
  }
  SetupDoubleLineEdit(this, ui->wall_temperature_lineEdit, cfg->bnd[zone_id].Walls[bc_id].wall_temperature);
  if (bc_text == "Subsonic Inflow" || bc_text == "Supersonic Inflow")
  {
    ui->no_extra_label->hide();
    ui->velocity_profile_num_in_edit->setText(QString::fromStdString(std::to_string(cfg->bnd[zone_id].Inlets[bc_id].num_profile_in)));
    ui->profile_distribution_in_combo->setCurrentIndex(cfg->bnd[zone_id].Inlets[bc_id].profile_distribution_direction_in-1);
    ShowHideLayout(ui->in_out_layout, true);
    ShowHideLayout(ui->visc_wall_layout, false);
    ui->velocity_u_lineEdit->setVisible(false);
    ui->velocity_v_lineEdit->setVisible(false);
    ui->velocity_w_lineEdit->setVisible(false);
    ui->velocity_u_label->setVisible(false);
    ui->velocity_v_label->setVisible(false);
    ui->velocity_w_label->setVisible(false);
    ui->velocity_u_unit_label->setVisible(false);
    ui->velocity_v_unit_label->setVisible(false);
    ui->velocity_w_unit_label->setVisible(false);

  }
  else if (bc_text == "Subsonic Outflow" || bc_text == "Supersonic Outflow")
  {
    ui->no_extra_label->hide();
    ShowHideLayout(ui->in_out_layout, true);
    ShowHideLayout(ui->visc_wall_layout, false);
    ui->velocity_profile_num_in_edit->setText(QString::fromStdString(std::to_string(cfg->bnd[zone_id].Outlets[bc_id].num_profile_out)));
    ui->profile_distribution_in_combo->setCurrentIndex(cfg->bnd[zone_id].Outlets[bc_id].profile_distribution_direction_out-1);
    ui->velocity_u_lineEdit->setVisible(false);
    ui->velocity_v_lineEdit->setVisible(false);
    ui->velocity_w_lineEdit->setVisible(false);
    ui->velocity_u_label->setVisible(false);
    ui->velocity_v_label->setVisible(false);
    ui->velocity_w_label->setVisible(false);
    ui->velocity_u_unit_label->setVisible(false);
    ui->velocity_v_unit_label->setVisible(false);
    ui->velocity_w_unit_label->setVisible(false);
  }
  else if (bc_text == "Viscous Wall" || bc_text=="Counter-rotating wall")
  {
    ui->no_extra_label->hide();
    ShowHideLayout(ui->in_out_layout, false);
    ShowHideLayout(ui->visc_wall_layout, true);
    if (cfg->isAnnular)
    {
      ui->wall_angular_velocity_lineEdit->setVisible(true);
      if (bc_text=="Counter-rotating wall")
        ui->wall_angular_velocity_lineEdit->setText(QString::fromStdString(std::to_string(-cfg->turbo_zone_velocity[zone_id])));
      ui->wall_velocity_u_lineEdit->setVisible(false);
      ui->wall_velocity_v_lineEdit->setVisible(false);
      ui->wall_velocity_w_lineEdit->setVisible(false);
      ui->wall_angular_velocity_label->setVisible(true);
      ui->wall_velocity_u_label->setVisible(false);
      ui->wall_velocity_v_label->setVisible(false);
      ui->wall_velocity_w_label->setVisible(false);
      ui->wall_angular_velocity_unit_label->setVisible(true);
      ui->wall_velocity_u_unit_label->setVisible(false);
      ui->wall_velocity_v_unit_label->setVisible(false);
      ui->wall_velocity_w_unit_label->setVisible(false);
    }
    else
    {
      ui->wall_angular_velocity_lineEdit->setVisible(false);
      ui->wall_velocity_u_lineEdit->setVisible(true);
      ui->wall_velocity_v_lineEdit->setVisible(true);
      ui->wall_velocity_w_lineEdit->setVisible(true);
      ui->wall_angular_velocity_label->setVisible(false);
      ui->wall_velocity_u_label->setVisible(true);
      ui->wall_velocity_v_label->setVisible(true);
      ui->wall_velocity_w_label->setVisible(true);
      ui->wall_angular_velocity_unit_label->setVisible(false);
      ui->wall_velocity_u_unit_label->setVisible(true);
      ui->wall_velocity_v_unit_label->setVisible(true);
      ui->wall_velocity_w_unit_label->setVisible(true);
    }
  }
  else
  {
    ui->no_extra_label->show();
    ShowHideLayout(ui->in_out_layout, false);
    ShowHideLayout(ui->visc_wall_layout, false);
  }
  SetupProfileTable();
}

void BCExtra::ShowHideLayout(QLayout* lay, bool flag)
{
  if (flag) {
    for (int i = 0; i < lay->count(); i++)
      lay->itemAt(i)->widget()->setVisible(true);
  }
  else
  {
    for (int i = 0; i < lay->count(); i++)
      lay->itemAt(i)->widget()->setVisible(false);
  }
}

void BCExtra::on_clostbutton_clicked()
{
    this->close();
}

void BCExtra::on_velocity_profile_num_in_edit_textChanged(const QString &arg1)
{
  if (bc_text=="Subsonic Inflow" || bc_text=="Supersonic Inflow") {
    cfg->bnd[zone_id].Inlets[bc_id].num_profile_in = arg1.toInt();
  }
  if (bc_text=="Subsonic Outflow" || bc_text=="Supersonic Outflow" || bc_text=="Subsonic Outflow Radial Equal")
    cfg->bnd[zone_id].Outlets[bc_id].num_profile_out=arg1.toInt();
  SetupProfileTable();
}

void BCExtra::on_wall_angular_velocity_lineEdit_textChanged(const QString &arg1)
{
  cfg->bnd[zone_id].Walls[bc_id].wall_angular_velocity=arg1.toDouble();
}


void BCExtra::on_wall_velocity_u_lineEdit_textChanged(const QString &arg1)
{
  cfg->bnd[zone_id].Walls[bc_id].wall_x_velocity=arg1.toDouble();
}

void BCExtra::on_wall_velocity_v_lineEdit_textChanged(const QString &arg1)
{
  cfg->bnd[zone_id].Walls[bc_id].wall_y_velocity=arg1.toDouble();
}

void BCExtra::on_wall_velocity_w_lineEdit_textChanged(const QString &arg1)
{
  cfg->bnd[zone_id].Walls[bc_id].wall_z_velocity=arg1.toDouble();
}

void BCExtra::on_wall_temperature_lineEdit_textChanged(const QString &arg1)
{
  cfg->bnd[zone_id].Walls[bc_id].wall_temperature=arg1.toDouble();
}


void BCExtra::on_load_profile_button_clicked()
{
//  std::cout<<cfg->num_flow_var<<std::endl;
  LoadProfile *load_profile_window = new LoadProfile(cfg, zone_id, bc_id, this);
  load_profile_window->setModal(true);
  load_profile_window->exec();
  SetupUI();
}

void BCExtra::onItemChanged(QTableWidgetItem *item)
{
  int row = item->row();
  int column = item->column();
  double value = item->text().toDouble();
//  std::cout<<row<<" "<<column<<std::endl;
  if (bc_text == "Subsonic Inflow" || bc_text == "Supersonic Inflow") {
    cfg->bnd[zone_id].Inlets[bc_id].points_data_in[row][column] = value;
  }
  else{
    cfg->bnd[zone_id].Outlets[bc_id].points_data_out[row][column] = value;
  }
}