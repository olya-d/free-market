//
//  OneGoodConsumer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include "OneGoodConsumer.h"
#include "Constants.h"
#include "OneGoodMarket.h"


OneGoodConsumer::OneGoodConsumer(OneGoodMarket* market) {
    _market = market;
    demand = 0;
}

void OneGoodConsumer::buy(std::vector<OneGoodProducer *> producers) {
    int totalSupply =0;
    std::for_each(producers.begin(), producers.end(), [&](OneGoodProducer * p) {
        totalSupply += p->getSupply();
    });
    
    
    while (demand > 0 && totalSupply > 0) {
        OneGoodProducer * cheapestProducer = *std::min_element(producers.begin(), producers.end(), [](OneGoodProducer* p1, OneGoodProducer* p2) -> bool {
            if (p1->getSupply() == 0) {
                return false;
            }
            if (p2-> getSupply() == 0) {
                return true;
            }
            return p1->getPrice() < p2->getPrice();
        });
        if (cheapestProducer) {
            if (cheapestProducer->getPrice() > _market->getMaxAcceptablePrice()) {
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

int OneGoodConsumer::getDemand() {
    return demand;
}

void OneGoodConsumer::setDemand(int d) {
    demand = d;
}