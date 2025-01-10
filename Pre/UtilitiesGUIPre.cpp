#include "UtilitiesGUIPre.h"

extern std::map<std::string, int>GUI_BC_Normal_Map={
  {"Invisid Wall", 1},
  {"Viscous Wall", 2},
  {"Freestream", 3},
  {"Subsonic Inflow", 4},
  {"Subsonic Outflow", 5},
  {"Supersonic Inflow", 6},
  {"Supersonic Outflow", 7},
  {"Lower Periodic", 9},
  {"Upper Periodic", 10},
};

extern std::map<int, std::string>GUI_Reverse_BC_Normal_Map={
        {1,"Invisid Wall"},
        {2,"Viscous Wall"},
        {3,"Freestream"},
        {4,"Subsonic Inflow"},
        {5,"Subsonic Outflow"},
        {6,"Supersonic Inflow"},
        {7,"Supersonic Outflow"},
        {9,"Lower Periodic"},
        {10,"Upper Periodic"}};

extern std::map<std::string, int>GUI_BC_Turbomachinery_Map={
    {"Invisid Wall", 1},
    {"Viscous Wall", 2},
    {"Counter-rotating wall", 2},
    {"Freestream", 3},
    {"Subsonic Inflow", 4},
    {"Subsonic Outflow", 5},
    {"Supersonic Inflow", 6},
    {"Supersonic Outflow", 7},
    {"Lower Periodic", 9},
    {"Upper Periodic", 10},
    {"Mixing plane AT inlet", 11},
    {"Mixing plane AT outlet", 12},
    {"Sliding plane AT inlet", 13},
    {"Sliding plane AT outlet", 14},
    {"Subsonic Outflow Radial Equal",15},
    {"Film cooling Inflow",28}};

extern std::map<int, std::string>GUI_Reverse_BC_Turbomachinery_Map={
        {1,"Invisid Wall"},
        {2,"Viscous Wall"},
        {3,"Freestream"},
        {4,"Subsonic Inflow"},
        {5,"Subsonic Outflow"},
        {6,"Supersonic Inflow"},
        {7,"Supersonic Outflow"},
        {9,"Lower Periodic"},
        {10,"Upper Periodic"},
        {11,"Mixing plane AT inlet"},
        {12,"Mixing plane AT outlet"},
        {13,"Sliding plane AT inlet"},
        {14,"Sliding plane AT outlet"},
        {15,"SUB_OUTFLOW_RAD_EQUAL"},
        {28,"Film cooling Inflow"}};

extern std::map<std::string, std::vector<std::string>> flow_vars=
{
{"Spalart-Allmaras(SA)",{"rho","u","v","w","p","sa\n(m2/s)"}},
{"k-epsilon(k-ε)",{"rho","u","v","w","p","k\n(m2/s2)","ε\n(m2/s3)"}},
{"k-omega(k-ω)",{"rho","u","v","w","p","k\n(m2/s2)","ω\n(1/s)"}},
{"k-omega(k-ω) gamma",{"rho","u","v","w","p","k\n(m2/s2)","ω\n(1/s)","γ"}},
{"laminar",{"rho","u","v","w","p"}}
};

extern std::map<std::string, std::string> GUI_rans_model_dic = {
        {"sa", "Spalart-Allmaras(SA)"},
        {"ke", "k-epsilon(k-ε)"},
        {"ko", "k-omega(k-ω)"},
        {"laminar","laminar"}
};

extern std::map<std::string, std::string> GUI_rans_model_dic_R = {
    {"Spalart-Allmaras(SA)","sa"},
    {"k-epsilon(k-ε)","ke"},
    {"k-omega(k-ω)","ko"},
    {"laminar","laminar"}
};

extern std::map<std::string, std::string> GUI_turbulence_model_dic = {
        {"rans", "RANS"},
        {"des", "DES"},
        {"les", "LES"}
};

extern std::map<std::string, std::string> GUI_turbulence_model_dic_R = {
    {"RANS", "rans"},
    {"DES", "des"},
    {"LES", "les"}
};

extern std::map<std::string, int> GUI_monitor_dict={
    {"Average flow property",1},
    {"Mixing plane boundary condition",2},
    {"Average-flow performance",3},
    {"Turbine efficiency",4},
    {"Wall force",5}
};

extern std::map<int, std::string> GUI_monitor_dict_R= {
   {1, "Average flow property"},
   {2, "Mixing plane boundary condition"},
   {3, "Average-flow performance"},
   {4, "Turbine efficiency"},
   {5, "Wall force"}
};

extern std::map<std::string, int> GUI_monitor_average={
        {"Area average",1},
        {"Mass average",2},
        {"Energy average",3},
};

extern std::map<int, std::string> GUI_monitor_average_R= {
        {1, "Area average"},
        {2, "Mass average"},
        {3, "Energy average"}
};

extern std::vector<QString> FilmCoolngVars=
        {
                "coordinate_x",
                "coordinate_y",
                "coordinate_z",
                "normal_vector_x",
                "normal_vector_y",
                "normal_vector_z",
                "hole_diameter",
                "hole_quantity",
                "hole_spacing"
        };

void SetupDoubleLineEdit(QObject *receiver, QLineEdit *edt, double value)
{
  QString str = QString::number(value, 'f', 8);
  str.remove(QRegExp("0+$")).remove(QRegExp("\\.$"));
  if (str.startsWith("0.") && str.length() > 3) {
    str = QString::number(value, 'e', 5);
    str.remove(QRegExp("0+$")).remove(QRegExp("\\.$"));
    str.remove(QRegExp("e[\\+\\-]0+$"));
  }

  edt->setText(str);
  emit edt->editingFinished();
  QDoubleValidator *validator=new QDoubleValidator(edt);
  edt->setValidator(validator);
  QObject::connect(edt, &QLineEdit::editingFinished, receiver, [edt](){
      bool valid = edt->hasAcceptableInput();
      edt->setStyleSheet(valid ? "border: 1px solid green;" : "border: 1px solid red;");
      bool ok;
      double value = edt->text().toDouble(&ok);
      if (ok && value != 0 && value < 0.01) {
        QString scientificNotation = QString::number(value, 'e');
        edt->setText(scientificNotation);
      }
  });
}

void SetupIntLineEdit(QObject *receiver, QLineEdit *edt, int value)
{
  QString str = QString::number(value);

  edt->setText(str);
  emit edt->editingFinished();
  QIntValidator *validator=new QIntValidator(edt);
  edt->setValidator(validator);
  QObject::connect(edt, &QLineEdit::editingFinished, receiver, [edt](){
      bool valid = edt->hasAcceptableInput();
      edt->setStyleSheet(valid ? "border: 1px solid green;" : "border: 1px solid red;");
  });
}
