#include "PreProcessSettings.h"

PreProcessSettings::PreProcessSettings() {
  num_meshes=0;
  this->case_name = global_solver_name;
  this->isAnnular = true;
  this->isPeriodic = true;
  this->isMixingPlane = false;
  this->isSlidingPlane = false;
  this->isLowMach = false;

  // Turbulence Model
  this->turbulence_model = "rans"; // rans, les, des
  this->rans_model = "sa"; // sa, ke, ko
  this->rans_wall_function = false;
  this->rans_transit = false;

  // Solver Parameters
  this->solver_iteration = 1000;
  this->screen_print_step = 1;
  this->solver_cfl = 2.0;
  this->CFL_ramp_up = 10;
  this->file_write_step = 50;
  this->solver_residual = 15;
  this->match_tol = 1.0000000000000001e-05;
  this->scaling_x = 1.0;
  this->scaling_y = 1.0;
  this->scaling_z = 1.0;
  this->rot_axis(0) = 1.0;
  this->rot_axis(1) = 0.0;
  this->rot_axis(2) = 0.0;

  this->unsteady_n_step = 10;
  this->unsteady_n_period = 1800;
  this->unsteady_period_time = 1.0;
  this->unsteady_output_step = 100;

  // Initial Conditions
  this->u_ic = 0.0;
  this->v_ic = 0.0;
  this->w_ic = 0.0;
  this->rho_ic = 1.226;
  this->p_ic = 101300.0;
  this->sa_ic = 1.7616e-4;
  this->k_ic = 0.0;
  this->o_ic = 0.0;
  this->e_ic = 0.0;
  this->g_ic = 1.0;

  //Misc options, mostly for developers
  this->preprocessor_cfg_format = "legacy";
}

PreProcessSettings::PreProcessSettings(const std::string &filename)
{
  LoadYAML(filename);
}

void PreProcessSettings::LoadYAML(const std::string &filename) {
  FileIO::YAMLReader yr;
  yr.LoadFile(global_pre_setup_yaml);
  ReadMainInput(yr);
  Input temp_input;
  temp_input.ReadMainInput(yr);
  bnd.clear();
  for (uint32_t i = 0; i < num_meshes; i++) {
    BoundaryParser one_bc;
    one_bc.ReadBoundaryYAML(global_pre_setup_yaml, mesh_files[i]);
    bnd.emplace_back(one_bc);
    turbo_zone_velocity.emplace_back(bnd[i].zone_angular_velocity);
    if (abs(bnd[i].zone_angular_velocity) < 1e-10) {
      turbo_rotor_stator.emplace_back(2);
    } else {
      turbo_rotor_stator.emplace_back(1);
    }
  }

  yr.GetScalar("gui_scale_factor_x", scaling_x, 1.0);
  yr.GetScalar("gui_scale_factor_y", scaling_y, 1.0);
  yr.GetScalar("gui_scale_factor_z", scaling_z, 1.0);
  yr.GetScalar("gui_rotation_x", rot_axis(0), 1.0);
  yr.GetScalar("gui_rotation_y", rot_axis(1), 0.0);
  yr.GetScalar("gui_rotation_z", rot_axis(2), 0.0);

  yr.GetScalar("GUI_Params/flag_run_preprocess", isPreProcessRun, true);
  yr.GetScalar("GUI_Params/CPU_core", CPU_core, 1);
  yr.GetScalar("GUI_Params/current_p", p_curve.initial_p, 0.0);
//  yr.GetScalar("GUI_Params/curve_n_points", p_curve.n_points, 0);
//  if (p_curve.n_points>0)
//  {
//    yr.GetVector("GUI_Params/curve_pressure", p_curve.pressure_list);
//    yr.GetVector("GUI_Params/curve_case", p_curve.case_list);
//  }

  GetGlobalbndID();

  InterfacePairs.clear();
  for (int i = 0; i < num_meshes - 1; i++) {
    int num_up=0;
    int num_down=0;
    uint32_t temp_id_1, temp_id_2;
    for (int j = 0; j < bnd[i].num_BC; j++) {
      if (bnd[i].Types[j] == 12 || bnd[i].Types[j] == 14) {
        temp_id_1 = global_id[i][j];
        num_up+=1;
      }
      if (bnd[i+1].Types[j] == 11 || bnd[i+1].Types[j] == 13) {
        temp_id_2 = global_id[i+1][j];
        num_down+=1;
      }
    }
    if (num_up==1 && num_down==1)
    {
      std::vector<uint32_t> one_pair={temp_id_1,temp_id_2};
      InterfacePairs.emplace_back(one_pair);
    }
    else
    {
      std::vector<uint32_t> one_pair={999,999};
      InterfacePairs.emplace_back(one_pair);
      QMessageBox::information(nullptr, "Warning Dialog", "Warning: Rotor-stator interface mismatch, all rotor-stator interface cleared.");
    }

  }

  if (rans_model=="ko" && rans_transit)
    GUI_rans_model="SST(k-ω SST)";
  else
    GUI_rans_model=GUI_rans_model_dic.at(rans_model);

  // Read config
  monitor=std::make_shared<ConfigParser>(&temp_input);
  monitor->ReadMonitorFile(global_pre_setup_yaml);
  monitor->GetGlobalGroup();
  num_monitor=monitor->num_monitors;
  isAnnular = global_annular==1 ? true:false;

  // Film Cooling read
//  films.resize(num_meshes);
//  for (uint32_t i=0;i<num_meshes;i++) {
//    film_cooling_rows.emplace_back(0);
//  }
}


void PreProcessSettings::SaveYAML(const std::string &filename) {
  YAML::Node config;

  GetGlobalbndID();
  rans_model=GUI_rans_model_dic_R.at(GUI_rans_model);

  // File and Mesh Information
  config["case_name"] = case_name;
  config["mg_levels"] = mg_levels;
  config["num_mesh"] = mesh_files.size();
  config["mesh_files"] = mesh_files;

  // Solver Options
  config["set_annular"] = isAnnular;
  config["unsteady"] = isUnsteady;
  config["flag_mixing_plane"] = isMixingPlane;
  config["flag_sliding_plane"] = isSlidingPlane;
  config["flag_low_mach"] = isLowMach;

  // Turbulence Model
  config["turbulence_type"] = turbulence_model;
  config["rans_model"] = rans_model;
  config["rans_wall_function"] = rans_wall_function;
  config["rans_transit_model"] = rans_transit;
  config["rans_qcr"] = rans_qcr;
  config["rans_helicity"] = rans_helicity;
  config["rans_kl"] = rans_kl;
  config["rans_cmott"] = rans_cmott;
  config["des_dx"] = des_dx;
  config["les_dx"] = les_dx;
  config["les_dt"] = les_dt;

  // Solver Parameters
  config["iteration_number"] = solver_iteration;
  config["screen_print_step"] = screen_print_step;
  config["CFL"] = solver_cfl;
  config["CFL_ramp_up"] = CFL_ramp_up;
  config["file_write_step"] = file_write_step;
  config["residual_level"] = solver_residual;
  config["periodic_match_tol"] = match_tol;

  // Coordinate Transformation
  config["gui_scale_factor_x"] = scaling_x;
  config["gui_scale_factor_y"] = scaling_y;
  config["gui_scale_factor_z"] = scaling_z;
  config["gui_rotation_x"] = rot_axis(0);
  config["gui_rotation_y"] = rot_axis(1);
  config["gui_rotation_z"] = rot_axis(2);

  // run simulation
  config["flag_append_hist"] = isAppend;

  // Initial Conditions
  config["u_ic"] = u_ic;
  config["v_ic"] = v_ic;
  config["w_ic"] = w_ic;
  config["rho_ic"] = rho_ic;
  config["p_ic"] = p_ic;
  config["sa_ic"] = sa_ic;
  config["k_ic"] = k_ic;
  config["o_ic"] = o_ic;
  config["e_ic"] = e_ic;
  config["g_ic"] = g_ic;

  config["solver_cfg"] = preprocessor_cfg_format;

  config["solver_cfg"] = preprocessor_cfg_format;

  config["flag_calculate_turbo_post"]=true;

  if (isUnsteady)
  {
    config["unsteady_period_time"]=unsteady_period_time;
    config["unsteady_n_period"]=unsteady_n_period;
    config["unsteady_n_step"]=unsteady_n_step;
    config["unsteady_output_step"]=unsteady_output_step;
    config["num_passages"]= num_passages;
    config["init_flow_mixing"]= isInitFromMixing;
    config["init_flow_file"]= mixing_flow_file;
    config["init_flow_file"]= mixing_flow_file;
    config["interface_pairs"]= InterfacePairs;
  }

  std::string outFileName = filename;
  std::ofstream outFile(outFileName);
  if (!outFile.is_open()) {
    std::cerr << "Error: Unable to open config.yaml for writing." << std::endl;
    return;
  }

  YAML::Node gui_node;
  gui_node["flag_run_preprocess"] = isPreProcessRun;
  gui_node["CPU_core"] = CPU_core;
  gui_node["current_p"] = p_curve.initial_p;
  config["GUI_Params"] = gui_node;

  outFile << config;
  outFile.close();

  // Write boundary condition part
  for (uint32_t i = 0; i < num_meshes; i++) {
    bnd[i].zone_angular_velocity=turbo_zone_velocity[i];
    bnd[i].WriteBoundaryYAML(outFileName, mesh_files[i]);
  }


  // Write monitor part
  monitor->WriteMonitorFile(outFileName);
}

void PreProcessSettings::GetGlobalbndID() {
  global_id.clear();
  uint32_t g_id=0;
  for (int i=0; i<num_meshes; i++){
    std::vector<int> zone_id;
    for (int j=0; j<bnd[i].num_BC; j++){
      g_id+=1;
      zone_id.emplace_back(g_id);
      global_name.emplace_back(bnd[i].Names[j]);
    }
    global_id.emplace_back(zone_id);
  }
}

void PreProcessSettings::SyncStep2()
{
  YAML::Node step2_yaml=YAML::LoadFile(global_pre_convert_yaml);
  step2_yaml["case_name"] = case_name;
  step2_yaml["unsteady"] = isUnsteady;
  step2_yaml["set_annular"] = isAnnular;
  step2_yaml["turbulence_type"] = turbulence_model;
  step2_yaml["rans_transit_model"] = rans_transit;
  step2_yaml["rans_qcr"] = rans_qcr;
  step2_yaml["rans_helicity"] = rans_helicity;
  step2_yaml["rans_kl"] = rans_kl;
  step2_yaml["rans_cmott"] = rans_cmott;

  step2_yaml["scale_factor_x"] = scaling_x;
  step2_yaml["scale_factor_y"] = scaling_y;
  step2_yaml["scale_factor_z"] = scaling_z;

  step2_yaml["rotation_factor_x"] = rot_axis(0);
  step2_yaml["rotation_factor_y"] = rot_axis(1);
  step2_yaml["rotation_factor_z"] = rot_axis(2);

  step2_yaml["flag_film_cool"] = isFilmCoolModel;

  std::ofstream outFile(global_pre_convert_yaml);
  outFile<<step2_yaml;
  outFile.close();

}