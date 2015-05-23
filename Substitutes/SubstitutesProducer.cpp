//
//  Producer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include <iostream>

#include "SubstitutesProducer.h"
#include "SubstitutesMarket.h"


SubstitutesProducer::SubstitutesProducer(SubstitutesMarket* market) {
    this->market_ = market;
    for (auto good : market->getGoods()) {
        supplies_[good] = 0;
        prices_[good] = 0;
    }
}

void SubstitutesProducer::changePricing() {
    for (const std::string good : market_->getGoods()) {
        if (supplies_[good] > 0) {
            if (prices_[good] > market_->getCosts().at(good)) {
                prices_[good] *= market_->getPriceDecrement();
            }
        } else {
            prices_[good] *= market_->getPriceIncrement();
        }
    }
}

void SubstitutesProducer::generateGoods() {
    std::string goodWithMaxProfit = market_->getGoods()[0];
    float maxProfit = market_->getAveragePriceOf(goodWithMaxProfit) - market_->getCosts().at(goodWithMaxProfit);
    for (auto good : market_->getGoods()) {
        float profit = market_->getAveragePriceOf(good) - market_->getCosts().at(good);
        if (profit >= maxProfit) {
            maxProfit = profit;
            goodWithMaxProfit = good;
        }
    }
    if (maxProfit > 0) {
        supplies_[goodWithMaxProfit] += market_->getSupplyIncrement();
    }
}

int SubstitutesProducer::getTotalSupply() {
    int sum = 0;
    for (std::pair<std::string, int> supply : supplies_) {
        sum += supply.second;
    }
    return sum;
}

