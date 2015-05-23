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
#include <map>
#include <iostream>

#include "SubstitutesProducer.h"


class SubstitutesMarket;

// Simulates behaviour of the consumer in the market of substitutes.
class SubstitutesConsumer {
private:
    SubstitutesMarket* market_;
    int demand_;

public:
    SubstitutesConsumer(SubstitutesMarket* market);
    
    int getDemand() const {
        return demand_;
    }
    // TODO: demand can't be negative.
    void setDemand(int d) {
        demand_ = d;
    }
    // Consumer buys in the following way:
    // 1. If demand is greater than zero and there is some supply in the market, go to 2,
    // otherwise finish.
    // 2. Find the cheapest good and try to satisfy the demand by sequentially buying
    // from the cheapest producer.
    // When demand is satisfied or the supply of the good is finished, go to 1.
    void buy();
};

#endif /* defined(__FreeMarket__Consumer__) */
