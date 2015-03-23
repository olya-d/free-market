//
//  OneGoodMarket.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#ifndef __FreeMarket__OneGoodMarket__
#define __FreeMarket__OneGoodMarket__

#include <stdio.h>
#include <vector>
#include <fstream>
#include "OneGoodSimulationConfig.h"


class OneGoodProducer;
class OneGoodConsumer;


class OneGoodMarket {
    OneGoodSimulationConfig* _config;

    std::vector<OneGoodProducer *> producers;
    std::vector<OneGoodConsumer *> consumers;
    
    std::ofstream demandData;
    std::ofstream priceData;
    std::ofstream supplyData;
    
    void writeData();
    
public:
    OneGoodMarket(OneGoodSimulationConfig* config);
    
    float averagePrice();
    int supply();
    int demand();

    void simulate(int times);

    int getMaxStartingProfit() const {
        return _config->getMaxStartingProfit();
    }

    int getCost() const {
        return _config->getCost();
    }

    int getMaxAcceptablePrice() const {
        return _config->getMaxAcceptablePrice();
    }

    int getSupplyIncrement() const {
        return _config->getSupplyIncrement();
    }

    float getPriceIncrement() const {
        return _config->getPriceIncrement();
    }

    float getPriceDecrement() const {
        return _config->getPriceDecrement();
    }
};

#endif /* defined(__FreeMarket__OneGoodMarket__) */
