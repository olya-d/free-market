//
//  Constants.cpp
//  FreeMarket
//
//  Created by Olga on 03.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#include "Constants.h"


int MarketConstants::SimulationDuration = 150;
int MarketConstants::NumOfProducers = 10;
int MarketConstants::NumOfConsumers = 10;

int MarketConstants::MaxStartingSupply = 30;
int MarketConstants::SupplyIncrement = 100;

std::vector<std::string> MarketConstants::Goods = {"potatoes", "carrot"};
std::map<std::string, int> MarketConstants::Costs = {{"potatoes", 10}, {"carrot", 10}};

std::map<std::string, int> MarketConstants::MaxAcceptablePrices = {{"potatoes", 50}, {"carrot", 50}};

std::map<std::string, int> MarketConstants::MaxStartingProfits = {{"potatoes", 15}, {"carrot", 15}};
float MarketConstants::PriceIncrement = 1.1f;
float MarketConstants::PriceDecrement = 0.9f;

std::string MarketConstants::DemandFile = "demand.txt";
std::string MarketConstants::SupplyFile = "supply.csv";
std::string MarketConstants::PriceFile = "price.csv";
