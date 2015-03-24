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
    goods = std::vector<std::string>();
    max_starting_profits = std::map<std::string, int>();
    max_acceptable_prices = std::map<std::string, int>();
    costs = std::map<std::string, int>();
    ratios = std::map<std::string, int>();

    for (int i = 0; i < goods_from_config.size(); ++i) {
        goods.push_back(goods_from_config[i].asString());
        max_starting_profits[goods[i]] = root["max_starting_profits"][goods[i]].asInt();
        max_acceptable_prices[goods[i]] = root["max_acceptable_prices"][goods[i]].asInt();
        costs[goods[i]] = root["costs"][goods[i]].asInt();
        ratios[goods[i]] = root["ratios"][goods[i]].asInt();
    }
}

