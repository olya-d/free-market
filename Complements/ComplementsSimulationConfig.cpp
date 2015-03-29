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

    readCommonConfig(root);

    const Json::Value goods_from_config = root["goods"];
    goods_ = std::vector<std::string>();
    max_starting_profits_ = std::map<std::string, int>();
    max_acceptable_prices_ = std::map<std::string, int>();
    costs_ = std::map<std::string, int>();
    ratios_ = std::map<std::string, int>();

    for (int i = 0; i < goods_from_config.size(); ++i) {
        goods_.push_back(goods_from_config[i].asString());
        max_starting_profits_[goods_[i]] = root["max_starting_profits"][goods_[i]].asInt();
        max_acceptable_prices_[goods_[i]] = root["max_acceptable_prices"][goods_[i]].asInt();
        costs_[goods_[i]] = root["costs"][goods_[i]].asInt();
        ratios_[goods_[i]] = root["ratios"][goods_[i]].asInt();
    }
}

