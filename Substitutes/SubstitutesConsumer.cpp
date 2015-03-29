//
//  Consumer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include "SubstitutesConsumer.h"
#include "SubstitutesMarket.h"


SubstitutesConsumer::SubstitutesConsumer(SubstitutesMarket* market) {
    demand_ = 0;
    this->market_ = market;
}

void SubstitutesConsumer::buy() {
    int totalSupply = market_->getTotalSupply();

    while (demand_ > 0 && totalSupply > 0) {
        std::string good = market_->cheapestGood();
        int goodSupply = market_->getSupplyOf(good);
        while (demand_ > 0 & goodSupply > 0) {
            SubstitutesProducer* cheapestProducer = market_->getCheapestProducerOf(good, true);
            
            if (cheapestProducer->getPrice(good) > market_->getMaxAcceptablePrices().at(good)) {
                demand_ /= 2;
            }
            int cheapestSupply = cheapestProducer->getSupply(good);
            if (demand_ > cheapestSupply) {
                demand_ -= cheapestSupply;
                totalSupply -= cheapestSupply;
                goodSupply -= cheapestSupply;
                cheapestProducer->setSupply(good, 0);
            } else {
                totalSupply -= demand_;
                goodSupply -= demand_;
                cheapestProducer->setSupply(good, cheapestSupply - demand_);
                demand_ = 0;
            }
        }
    }
}

