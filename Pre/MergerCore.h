#pragma once

#include "ToolsWriteCGNS.h"
#include "PreProcessSettings.h"
#include "PreMainModules.h"
#include "InputParser.h"

class MergerCore
{
public:
    MergerCore(PreProcessSettings *cfg_in);
    ~MergerCore();
  std::map <std::string, int> rule_types={
  {"period_lo",9},
  {"period_up",10},
  {"inflow",4},
  {"outflow",5},
  {"visc_wall",2},
  {"inv_wall",1},
  {"blade",2},
  {"hub",2},
  {"shroud",2},
  {"ungrouped",2}
  };

  std::map <std::string, std::vector<std::vector<std::string>>> rule_subgroups={
  //*small change for easy test
          {"period_lo",{{"per","lo"},{"per","down"},{"periodic1"}}},
          {"period_up",{{"per","up"},{"per","hi"},{"periodic2"}}},
          {"inflow",{{"inflow"},{"inlet"}}},
          {"outflow",{{"outflow"},{"outlet"}}},
          {"visc_wall",{{"wall"}}},
          {"inv_wall",{{"wall","inv"}}},
          {"blade",{{"blade"}}},
          {"hub",{{"hub"}}},
          {"shroud",{{"shroud"},{"casing"},{"case"}}},
          {"splitter",{{"splitter"}}},
  };

  std::vector<std::map<std::string,std::vector<std::string>>> zone_subgroups;
  std::vector<std::map<std::string,int>> zone_types;

  void GenStep1File(bool mergeFlag);

  void GenerateStep2();

  void LoadStep2();

  void save_rules_yaml(std::ofstream& file);

  void UpdateSubgroupsStep2();

private:
    PreProcessSettings *cfg;
};
