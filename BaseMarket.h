//
//  BaseMarket.h
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

#include "BaseProducer.h"
#include "BaseConsumer.h"


class BaseMarket {
    std::vector<BaseProducer *> producers;
    std::vector<BaseConsumer *> consumers;
    
    std::ofstream demandData;
    std::ofstream priceData;
    std::ofstream supplyData;
    
    void writeData();
    
public:
    BaseMarket();
    
    float averagePrice();
    int supply();
    int demand();

    void simulate(int times);
};

#endif /* defined(__FreeMarket__Market__) */
