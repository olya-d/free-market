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


class SubstitutesConsumer {
private:
    SubstitutesMarket* market;
    int demand;

public:
    SubstitutesConsumer(SubstitutesMarket* market);
    
    int getDemand();
    
    void setDemand(int d);
    
    void buy(const std::string& good);
};

#endif /* defined(__FreeMarket__Consumer__) */
