//
//  Consumer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include "Consumer.h"
#include "Producer.h"

#include "Constants.h"


Consumer::Consumer() {
    demand = 0;
}

void Consumer::buy(std::vector<Producer*> producers) {
    int totalSupply =0;
    std::for_each(producers.begin(), producers.end(), [&](Producer* p) {
        totalSupply += p->getSupply();
    });
    
    
    while (demand > 0 && totalSupply > 0) {
        Producer* cheapestProducer = *std::min_element(producers.begin(), producers.end(), [](Producer* p1, Producer* p2) -> bool {
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

int Consumer::getDemand() {
    return demand;
}

void Consumer::setDemand(int d) {
    demand = d;
}