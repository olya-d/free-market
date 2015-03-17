//
//  main.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <json/json.h>

#include "Market.h"
#include "Constants.cpp"


void readConfiguration(Json::Value root) {

    MarketConstants::SimulationDuration = root.get("duration", MarketConstants::SimulationDuration).asInt();
    MarketConstants::NumOfProducers = root.get("number_of_producers", MarketConstants::NumOfProducers).asInt();
    MarketConstants::MaxStartingSupply = root.get("max_starting_supply", MarketConstants::MaxStartingSupply).asInt();
    MarketConstants::SupplyIncrement = root.get("supply_increment", MarketConstants::SupplyIncrement).asInt();

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
    MarketConstants::Goods = std::vector<std::string> (goods);
    MarketConstants::MaxStartingProfits = std::map<std::string, int>(max_starting_profits);
    MarketConstants::MaxAcceptablePrices = std::map<std::string, int>(max_acceptable_prices);
    MarketConstants::Costs = std::map<std::string, int>(costs);

    MarketConstants::PriceIncrement = root.get("price_increment", MarketConstants::PriceIncrement).asFloat();
    MarketConstants::PriceDecrement = root.get("price_decrement", MarketConstants::PriceDecrement).asFloat();
    MarketConstants::NumOfConsumers = root.get("number_of_consumers", MarketConstants::NumOfConsumers).asInt();
    MarketConstants::DemandFile = root.get("demand_file", MarketConstants::DemandFile).asString();
    MarketConstants::SupplyFile = root.get("supply_file", MarketConstants::SupplyFile).asString();
    MarketConstants::PriceFile = root.get("price_file", MarketConstants::PriceFile).asString();

}

int main(int argc, const char *argv[]) {
    Json::Value root;
    std::ifstream config_doc("config.json", std::ifstream::binary);
    config_doc >> root;
    readConfiguration(root);
    Market *market = new Market();
    market->simulate(MarketConstants::SimulationDuration);
    return 0;
}
