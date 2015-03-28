//
// Created by Olga on 3/24/15.
//

#include "ComplementsSimulationConfig.h"
#include <fstream>


ComplementsSimulationConfig::ComplementsSimulationConfig(std::string path_to_config) {
    readConfig(path_to_config);
}

void ComplementsSimulationConfig::readConfig(std::string path) {
    Json::Value root;
    std::ifstream config_doc(path, std::ifstream::binary);
    config_doc >> root;

    readMultipleGoodsConfig(root);

    const Json::Value ratios_config = root["ratios"];
    _ratios = std::map<std::string, int>();
    if (ratios_config == Json::Value::null) {
        argumentMissingExit("ratios");
    }
    for (int i = 0; i < getGoods().size(); ++i) {
        _ratios[goods[i]] = root["ratios"][goods[i]].asInt();
    }
}

std::map<std::string, int> const &ComplementsSimulationConfig::getRatios() const {
    return _ratios;
}