#ifndef PREPROCESSSETTINGS_H
#define PREPROCESSSETTINGS_H

#include "input.h"
#include "BoundaryParser.h"
#include "ConfigParser.h"
#include "UtilitiesGUIPre.h"
#include "PerformanceCurve.h"
#include <QMessageBox>
#include <QString>
#include "SourceParser.h"

class PreProcessSettings : public Input
{
public:
    PreProcessSettings();
    PreProcessSettings(const std::string &filename);
    ~PreProcessSettings()=default;

    void LoadYAML(const std::string &filename);
    void SaveYAML(const std::string &filename);

    void SyncStep2();

    void GetGlobalbndID();

    std::vector<BoundaryParser> bnd;
    std::shared_ptr<ConfigParser> monitor;

    bool isTurbomachinery=true;
    bool isAnnular=true;
    bool isPeriodic;
    bool isRealGas=false;

    std::string GUI_rans_model;

    std::vector<int> turbo_rotor_stator;
    std::vector<double> turbo_zone_velocity;
    int num_interface;
    std::vector<int> vector;

    int num_flow_var;
    int num_monitor=0;

    std::vector<std::vector<std::pair<std::string,std::vector<std::vector<double>>>>> all_film_config_data;
    std::vector<std::vector<std::pair<std::string,std::vector<std::vector<double>>>>> all_film_input_data;
    std::vector<std::vector<std::pair<std::string,bool>>> boundary_film_option;
    std::vector<SourceParser::default_film_grp> film_groups;
    std::vector<SourceParser::default_film_grp> film_groups_data;
    std::string FCconfigfile = "FilmCoolingConfig.yaml";
    std::string FCInputfile =  "FilmCoolingInput.yaml";


    std::string GUI_yaml="GUI.yaml";

    std::vector<std::vector<int>> global_id;
    std::vector<std::string> global_name;

    bool interface_check=true;

    PerformanceCurve p_curve;
    bool isRunPerformanceCurve=false;

    bool isPreProcessRun=true;
    int CPU_core=1;
    //* add flags
    int Flag_Type_Files = 0; // 0 = cgns 1 = cas.h5
    bool isVtkReady = false;

};

#endif // PREPROCESSSETTINGS_H
