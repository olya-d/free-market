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


class SubstitutesProducer;
class SubstitutesConsumer;


class SubstitutesMarket {
    std::vector<SubstitutesProducer*> producers;
    std::vector<SubstitutesConsumer*> consumers;
    
    std::pair<std::string, float> mostExpensiveGood;
    
    std::ofstream demandData;
    std::ofstream priceData;
    std::ofstream supplyData;
    
    void writeData();
    
    
public:
    SubstitutesMarket();
    int supply(const std::string& good);
    int totalDemand();
    int totalSupply();
    float averagePrice(const std::string& good);

    SubstitutesProducer* cheapestProducer(const std::string& good, bool ignoreZeroSupply);
    std::pair<std::string, float> maxAveragePrice();

    void simulate(int times);
    std::string cheapestGood();
};

#endif /* defined(__FreeMarket__Market__) */
