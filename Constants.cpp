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

int MarketConstants::MaxStartingSupply = 20;
int MarketConstants::SupplyIncrement = 80;

int MarketConstants::Cost = 5;
int MarketConstants::MaxAcceptablePrice = Cost*10;
int MarketConstants::MaxStartingProfit = 5;
float MarketConstants::PriceIncrement = 1.1f;
float MarketConstants::PriceDecrement = 0.9f;

std::string MarketConstants::DemandFile = "demand.txt";
std::string MarketConstants::SupplyFile = "supply.txt";
std::string MarketConstants::PriceFile = "price.txt";
