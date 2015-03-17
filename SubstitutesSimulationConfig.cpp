//
// Created by Olga on 3/17/15.
//

#include "SubstitutesSimulationConfig.h"
#include <fstream>


void SubstitutesSimulationConfig::readConfig(std::string path) {
    Json::Value root;
    std::ifstream config_doc("config.json", std::ifstream::binary);
    config_doc >> root;

    readCommonConfig(root);

    const Json::Value goods_from_config = root["goods"];
    std::vector<std::string> goods = std::vector<std::string>();
    std::map<std::string, int> max_starting_profits = std::map<std::string, int>();
    std::map<std::string, int> max_acceptable_prices = std::map<std::string, int>();
    std::map<std::string, int> costs = std::map<std::string, int>();

    for (int i = 0; i < goods_from_config.size(); ++i) {
        goods.push_back(goods_from_config[i].asString());
        max_starting_profits[goods[i]] = root["max_starting_profits"][goods[i]].asInt();
        max_acceptable_prices[goods[i]] = root["max_acceptable_prices"][goods[i]].asInt();
        costs[goods[i]] = root["costs"][goods[i]].asInt();
    }
    goods = std::vector<std::string> (goods);
    max_starting_profits = std::map<std::string, int>(max_starting_profits);
    max_acceptable_prices = std::map<std::string, int>(max_acceptable_prices);
    costs = std::map<std::string, int>(costs);
}