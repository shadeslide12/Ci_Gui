//
// Created by Zhouteng Ye on 2024/6/10.
//

#include "MergerCore.h"

MergerCore::MergerCore(PreProcessSettings *cfg_in) {
  cfg=cfg_in;
}

void MergerCore::GenStep1File(bool mergeFlag)
{
  // Generating STEP-1-Config.yaml
  std::ofstream new_file(global_pre_mesh_yaml);
  new_file << "mesh_files:\n";
  for (int i=0; i<cfg->mesh_files.size(); i++)
  {
    new_file << "  - " << cfg->mesh_files[i] << "\n";
  }
  if (! mergeFlag) new_file << "disable_rule: true\n";
  save_rules_yaml(new_file);

  // Write mesh_files section
  new_file.close();
}


void MergerCore::GenerateStep2()
{
  InputParser ET;
  ET.GenInput(global_pre_mesh_yaml);
  FileIO::YAMLReader yr;
  ET.InitializeYAML();
}

void MergerCore::LoadStep2() {
  YAML::Node config = YAML::LoadFile(global_pre_convert_yaml);
  zone_subgroups.clear();
  zone_types.clear();
  for (int i=0; i<cfg->mesh_files.size(); i++)
  {
    std::map<std::string,std::vector<std::string>> one_zone;
    std::map<std::string,int> one_zone_type;
    YAML::Node zone_node = config[cfg->mesh_files[i]]["boundary_conditions"];
    if (config[cfg->mesh_files[i]]["bc_subgroup"].as<bool>()) {
      for (auto it = zone_node.begin(); it != zone_node.end(); ++it) {
        auto key = it->first.as<std::string>();
        auto value = it->second["subfaces"].as<std::vector<std::string>>();
        auto type = it->second["type"].as<int>();
        one_zone.insert(std::pair<std::string, std::vector<std::string>>(key, value));
        one_zone_type.insert(std::pair<std::string, int>(key, type));
      }
    }
    else
    {
      for (auto it = zone_node.begin(); it != zone_node.end(); ++it) {
        auto key = it->first.as<std::string>();
        std::vector<std::string> value = {key};
        auto type = it->second.as<int>();
        one_zone.insert(std::pair<std::string, std::vector<std::string>>(key, value));
        one_zone_type.insert(std::pair<std::string, int>(key, type));
      }
    }
    zone_subgroups.emplace_back(one_zone);
    zone_types.emplace_back(one_zone_type);
  }
}

void MergerCore::save_rules_yaml(std::ofstream &file)
{
    if (!file.is_open()) {
        std::cerr << "Failed to open bc_rules.yaml for writing." << std::endl;
    }

    file << "bc_rules:" << std::endl;
    for (const auto& pair : rule_types) {
      if (pair.first=="ungrouped") continue;
        file << "  " << pair.first << ":" << std::endl;
        file << "    type: " << pair.second << std::endl;
        file << "    keywords:" << std::endl;

        auto rules_it = rule_subgroups.find(pair.first);
        if (rules_it != rule_subgroups.end()) {
            for (const auto& ruleSet : rules_it->second) {
                file << "      - [";
                for (auto rule = ruleSet.begin(); rule != ruleSet.end(); ++rule) {
                    file << "\"" << *rule << "\"";
                    if (std::next(rule) != ruleSet.end()) file << ", ";
                }
                file << "]" << std::endl;
            }
        }
    }
    file.close();
}

void MergerCore::UpdateSubgroupsStep2()
{
    YAML::Node step2_yaml=YAML::LoadFile(global_pre_convert_yaml);

    for (int i=0;i<cfg->num_meshes;i++)
    {
        std::string f_type = step2_yaml[cfg->mesh_files[i]]["file_type"].as<std::string>();
        YAML::Node node;
        YAML::Node rootNode;
        rootNode["bc_subgroup"] = true;
        rootNode["file_type"] = f_type;
        for (auto item:zone_subgroups[i]) {
            YAML::Node node1;
            if (item.second.size() > 0) {
                node1["type"] = zone_types[i][item.first];
                node1["subfaces"] = item.second;
                node[item.first] = node1;
            }
        }

        rootNode["boundary_conditions"] = node;
        step2_yaml[cfg->mesh_files[i]]=rootNode;
    }

    std::ofstream outFile(global_pre_convert_yaml);
    outFile<<step2_yaml;
    outFile.close();
}