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

#include "Producer.h"
#include "Consumer.h"


class Market {
    std::vector<Producer*> producers;
    std::vector<Consumer*> consumers;
    
    std::ofstream demandData;
    std::ofstream priceData;
    std::ofstream supplyData;
    
    void writeData();
    
public:
    Market();
    
    float averagePrice();
    int supply();
    int demand();

    void simulate(int times);
};

#endif /* defined(__FreeMarket__Market__) */
