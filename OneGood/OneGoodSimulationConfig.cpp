//
// Created by Olga on 3/22/15.
//

#include "OneGoodSimulationConfig.h"
#include <fstream>


OneGoodSimulationConfig::OneGoodSimulationConfig(std::string path_to_config) {
    readConfig(path_to_config);
}

void OneGoodSimulationConfig::readConfig(std::string path) {
    Json::Value root;
    std::ifstream config_doc(path, std::ifstream::binary);
    config_doc >> root;

    readCommonConfig(root);

    max_starting_profit = root.get("max_starting_profit", 5.0).asInt();
    max_acceptable_price = root.get("max_acceptable_price", 50).asInt();
    cost = root.get("cost", 5).asInt();
}