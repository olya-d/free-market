//
//  Consumer.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__Consumer__
#define __FreeMarket__Consumer__

#include <stdio.h>
#include <vector>

#include "Producer.h"

class Consumer {
private:
    int demand;
    
public:
    Consumer();
    
    int getDemand();
    
    void setDemand(int d);
    
    void buy(std::vector<Producer *> producers);
};

#endif /* defined(__FreeMarket__Consumer__) */
