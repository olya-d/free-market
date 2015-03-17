//
//  Producer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include <iostream>

#include "SubstitutesProducer.h"


SubstitutesProducer::SubstitutesProducer(IMarket* market) {
    this->market = market;
    for (auto good : MarketConstants::Goods) {
        supplies[good] = 0;
        prices[good] = 0;
    }
}

void SubstitutesProducer::changePricing() {
    for (const std::string good : MarketConstants::Goods) {
        if (supplies[good] > 0) {
            if (prices[good] > MarketConstants::Costs[good]) {
                prices[good] *= MarketConstants::PriceDecrement;
            }
        } else {
            prices[good] *= MarketConstants::PriceIncrement;
        }
    }
}


void SubstitutesProducer::generateGoods() {
    std::pair<std::string, float> max = market->maxAveragePrice();
    if (prices[max.first] > MarketConstants::Costs[max.first]) {
        supplies[max.first] += MarketConstants::SupplyIncrement;
    }
}


void SubstitutesProducer::produce() {
    changePricing();
    generateGoods();
}


float SubstitutesProducer::getPrice(const std::string& good) {
    return prices[good];
}

int SubstitutesProducer::getSupply(const std::string& good) {
    return supplies[good];
}

int SubstitutesProducer::getTotalSupply() {
    int sum = 0;
    for (std::pair<std::string, int> supply : supplies) {
        sum += supply.second;
    }
    return sum;
}

void SubstitutesProducer::setSupply(const std::string& good, int s) {
    supplies[good] = s;
}

void SubstitutesProducer::setPrice(const std::string& good, float p) {
    prices[good] = p;
}
