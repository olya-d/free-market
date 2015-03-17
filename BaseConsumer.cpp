//
//  BaseConsumer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include "BaseConsumer.h"
#include "Constants.h"

BaseConsumer::BaseConsumer() {
    demand = 0;
}

void BaseConsumer::buy(std::vector<BaseProducer *> producers) {
    int totalSupply =0;
    std::for_each(producers.begin(), producers.end(), [&](BaseProducer * p) {
        totalSupply += p->getSupply();
    });
    
    
    while (demand > 0 && totalSupply > 0) {
        BaseProducer * cheapestProducer = *std::min_element(producers.begin(), producers.end(), [](BaseProducer * p1, BaseProducer * p2) -> bool {
            if (p1->getSupply() == 0) {
                return false;
            }
            if (p2-> getSupply() == 0) {
                return true;
            }
            return p1->getPrice() < p2->getPrice();
        });
        if (cheapestProducer) {
            if (cheapestProducer->getPrice() > MarketConstants::MaxAcceptablePrice) {
                demand /= 2;
            }
            float cheapestSupply = cheapestProducer->getSupply();
            if (demand > cheapestSupply) {
                demand -= cheapestSupply;
                totalSupply -= cheapestSupply;
                cheapestProducer->setSupply(0);
            } else {
                totalSupply -= demand;
                cheapestProducer->setSupply(cheapestSupply - demand);
                demand = 0;
            }
        }
    }
}

int BaseConsumer::getDemand() {
    return demand;
}

void BaseConsumer::setDemand(int d) {
    demand = d;
}