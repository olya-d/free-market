//
//  Producer.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__Producer__
#define __FreeMarket__Producer__

#include <iostream>
#include <vector>
#include <map>


class SubstitutesMarket;

class SubstitutesProducer {
private:
    // TODO: add lastSold
    // The number of items available for sell for each good.
    std::map<std::string, int> supplies_;
    // Current prices.
    std::map<std::string, float> prices_;
    // Used to access configuration and the current state of the market (e.g. current average prices).
    SubstitutesMarket*market_;

public:
    SubstitutesProducer(SubstitutesMarket* market);

    int getSupply(const std::string& good) const {
        return supplies_.at(good);
    }
    // Returns the sum of getSupply() for each good.
    int getTotalSupply();
    float getPrice(const std::string& good) const {
        return prices_.at(good);
    }

    void setSupply(const std::string& good, int s) {
        supplies_[good] = s;
    }
    void setPrice(const std::string& good, float p) {
        prices_[good] = p;
    }
    // Producer changes pricing according to the following rules:
    // 1. If the leftover supply is non-zero, and the price of good set by producer
    // is greater than the cost of the good, decrement the price by multiplying by market.price_decrement.
    // Otherwise, increment the price by multiplying by market.price_increment.
    void changePricing();
    // Producer generates goods according to the following rules:
    // 1. Find the good with maximum profit (= average price - cost) and increase its supply
    // by market.supply_increment.
    // THIS METHOD SHOULD BE CALLED AFTER changePricing().
    // TODO: implement one method that will perform both change of prices and generation of goods by (probably), calculating and storing needed parameters in the market before each call to this method.
    // REMARK: this method will create more and more items of each good.
    void generateGoods();
};


#endif /* defined(__FreeMarket__Producer__) */