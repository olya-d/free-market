//
//  BaseConsumer.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__Consumer__
#define __FreeMarket__Consumer__

#include <stdio.h>
#include <vector>

#include "BaseProducer.h"

class BaseConsumer {
private:
    int demand;
    
public:
    BaseConsumer();
    
    int getDemand();
    
    void setDemand(int d);
    
    void buy(std::vector<BaseProducer *> producers);
};

#endif /* defined(__FreeMarket__Consumer__) */
