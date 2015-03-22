//
// Created by Olga on 3/17/15.
//

#include "SimulationConfigReader.h"
#include <json/json.h>
#include <fstream>


SimulationConfigReader::SimulationConfigReader() {
    Json::Value root;
    std::ifstream config_doc(path_to_config, std::ifstream::binary);
    config_doc >> root;

    std::string type = root.get("type", "one good").asString();
}


BaseSimulationConfig::SimulationType SimulationConfigReader::getSimulationType() {
    return BaseSimulationConfig::SimulationType::SUBSTITUTES;
}
