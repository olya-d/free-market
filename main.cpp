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

void readConfiguration(Json::Value *root) {

//    MarketConstants::SimulationDuration = root->get("duration", MarketConstants::SimulationDuration).asInt();
//    MarketConstants::NumOfProducers = root->get("number_of_producers", MarketConstants::NumOfProducers).asInt();
//    MarketConstants::MaxStartingSupply = root->get("max_starting_supply", MarketConstants::MaxStartingSupply).asInt();
//    MarketConstants::SupplyIncrement = root->get("supply_increment", MarketConstants::SupplyIncrement).asInt();
////    MarketConstants::MaxStartingProfit = root->get("max_starting_profit", MarketConstants::MaxStartingProfit).asInt();
////    MarketConstants::Cost = root->get("cost", MarketConstants::Cost).asInt();
//    MarketConstants::PriceIncrement = root->get("price_increment", MarketConstants::PriceIncrement).asFloat();
//    MarketConstants::PriceDecrement = root->get("price_decrement", MarketConstants::PriceDecrement).asFloat();
////    MarketConstants::MaxAcceptablePrice = root->get("max_acceptable_price", MarketConstants::MaxAcceptablePrice).asInt();
//    MarketConstants::NumOfConsumers = root->get("number_of_consumers", MarketConstants::NumOfConsumers).asInt();
//    MarketConstants::DemandFile = root->get("demand_file", MarketConstants::DemandFile).asString();
//    MarketConstants::SupplyFile = root->get("supply_file", MarketConstants::SupplyFile).asString();
//    MarketConstants::PriceFile = root->get("price_file", MarketConstants::PriceFile).asString();

}

int main(int argc, const char * argv[]) {
//    Json::Value root;
//    Json::Reader reader;
//
//    std::ifstream configFile;
//    configFile.open("config.json");
//
//    bool parsingSuccessful = reader.parse(configFile, root);
//    if (!parsingSuccessful) {
//        std::cout << "Failed to parse configuration" << std::endl
//                << reader.getFormattedErrorMessages();
//        return -1;
//    }
//    readConfiguration(&root);

    Market* market = new Market();
    market->simulate(MarketConstants::SimulationDuration);
    return 0;
}
