//
//  OneGoodConsumer.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__Consumer__
#define __FreeMarket__Consumer__

#include <stdio.h>
#include <vector>

#include "OneGoodProducer.h"


class OneGoodMarket;

// Simulates the behaviour of consumer when there is only one good in the market.
class OneGoodConsumer {
private:
    OneGoodMarket* market_;
    int demand_;
    
public:
    OneGoodConsumer(OneGoodMarket* market);
    
    int getDemand();
    
    void setDemand(int d);

    // The consumer buys in the following way:
    // 1. If demand_ is not satisfied and there is some supply left in the market,
    // go to 2., otherwise finish.
    // 2. Find the cheapest producer.
    // 3. If his/her price is greater than the acceptable price, reduce the demand_ by half.
    // 4. Buy as much as possible, but not greater than the current demand_, units from
    // this producer. Go to 1.
    void buy(std::vector<OneGoodProducer *> producers);
};

#endif /* defined(__FreeMarket__Consumer__) */
