//
// Created by Olga on 3/17/15.
//

#include "SubstitutesSimulationConfig.h"
#include <fstream>


SubstitutesSimulationConfig::SubstitutesSimulationConfig(std::string path_to_config) {
    readConfig(path_to_config);
}

void SubstitutesSimulationConfig::readConfig(std::string path) {
    Json::Value root;
    std::ifstream config_doc(path, std::ifstream::binary);
    config_doc >> root;

    readCommonConfig(root);

    const Json::Value goods_config = root["goods"];
    const Json::Value max_starting_profits_config = root["max_starting_profits"];
    const Json::Value max_acceptable_prices_config = root["max_acceptable_prices"];
    const Json::Value costs_config = root["costs"];
    if (goods_config == Json::Value::null) {
        argumentMissingExit("goods");
    }
    if (max_starting_profits_config == Json::Value::null) {
        argumentMissingExit("max_starting_profits");
    }
    if (max_acceptable_prices_config == Json::Value::null) {
        argumentMissingExit("max_acceptable_prices");
    }
    if (costs_config == Json::Value::null) {
        argumentMissingExit("costs");
    }
    max_starting_profits = std::map<std::string, int>();
    max_acceptable_prices = std::map<std::string, int>();
    costs = std::map<std::string, int>();

    for (int i = 0; i < goods_config.size(); ++i) {
        goods.push_back(goods_config[i].asString());
        max_starting_profits[goods[i]] = max_starting_profits_config[goods[i]].asInt();
        max_acceptable_prices[goods[i]] = max_acceptable_prices_config[goods[i]].asInt();
        costs[goods[i]] = costs_config[goods[i]].asInt();
    }
}


void SubstitutesSimulationConfig::argumentMissingExit(std::string name) {
    std::cout << "Please specify key \"" << name << "\" in the configuration file (config.json by default)";
    exit(1);
}