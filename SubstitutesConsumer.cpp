//
//  Consumer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include "SubstitutesConsumer.h"
#include "Constants.h"
#include "SubstitutesMarket.h"


SubstitutesConsumer::SubstitutesConsumer(SubstitutesMarket* market) {
    demand = 0;
    this->market = market;
}

void SubstitutesConsumer::buy(const std::string& good) {
    int totalSupply = market->totalSupply();
    
    while (demand > 0 && totalSupply > 0) {
        std::string good = market->cheapestGood();
        int goodSupply = market->supply(good);
        while (demand > 0 & goodSupply > 0) {
            SubstitutesProducer* cheapestProducer = market->cheapestProducer(good, true);
            
            if (cheapestProducer->getPrice(good) > MarketConstants::MaxAcceptablePrices[good]) {
                demand /= 2;
            }
            int cheapestSupply = cheapestProducer->getSupply(good);
            if (demand > cheapestSupply) {
                demand -= cheapestSupply;
                totalSupply -= cheapestSupply;
                goodSupply -= cheapestSupply;
                cheapestProducer->setSupply(good, 0);
            } else {
                totalSupply -= demand;
                goodSupply -= demand;
                cheapestProducer->setSupply(good, cheapestSupply - demand);
                demand = 0;
            }
        }
    }
}

int SubstitutesConsumer::getDemand() {
    return demand;
}

void SubstitutesConsumer::setDemand(int d) {
    demand = d;
}