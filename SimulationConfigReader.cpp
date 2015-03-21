//
// Created by Olga on 3/17/15.
//

#include "SimulationConfigReader.h"
#include "SubstitutesSimulationConfig.h"
#include <json/json.h>
#include <fstream>


BaseSimulationConfig* SimulationConfigReader::getConfig() {
    Json::Value root;
    std::ifstream config_doc(path_to_config, std::ifstream::binary);
    config_doc >> root;

    std::string type = root.get("type", "one good").asString();
    if (type == "substitutes") {
        config = new SubstitutesSimulationConfig();
    }
    std::cout << path_to_config;
    config->readConfig(path_to_config);
    return config;
}
