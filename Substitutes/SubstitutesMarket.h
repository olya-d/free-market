//
//  Market.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__Market__
#define __FreeMarket__Market__

#include <stdio.h>
#include <vector>
#include <fstream>
#include "SubstitutesSimulationConfig.h"


class SubstitutesProducer;
class SubstitutesConsumer;


class SubstitutesMarket {
    SubstitutesSimulationConfig* _config;

    std::vector<SubstitutesProducer*> producers;
    std::vector<SubstitutesConsumer*> consumers;

    std::ofstream demandData;
    std::ofstream priceData;
    std::ofstream supplyData;
    
    void writeData();
    
    
public:
    SubstitutesMarket(SubstitutesSimulationConfig* config);
    int supply(const std::string& good);
    int totalDemand();
    int totalSupply();
    float averagePrice(const std::string& good);

    SubstitutesProducer* cheapestProducer(const std::string& good, bool ignoreZeroSupply);
    std::pair<std::string, float> maxAveragePrice();

    void simulate(int times);
    std::string cheapestGood();

    std::vector<std::string> const &getGoods() const {
        return _config->getGoods();
    }

    std::map<std::string, int> const &getMaxAcceptablePrices() const {
        return _config->getMaxAcceptablePrices();
    }

    std::map<std::string, int> const &getCosts() const {
        return _config->getCosts();
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

#endif /* defined(__FreeMarket__Market__) */
