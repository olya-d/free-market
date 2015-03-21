//
//  Producer.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__Producer__
#define __FreeMarket__Producer__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include "Constants.h"

class SubstitutesMarket;

class SubstitutesProducer {
private:
    std::map<std::string, int> supplies;
    std::map<std::string, float> prices;
    SubstitutesMarket* market;

    void generateGoods();
    void changePricing();
    
public:
    SubstitutesProducer(SubstitutesMarket* market);
    
    int getSupply(const std::string& good);
    int getTotalSupply();
    float getPrice(const std::string& good);
    
    void setSupply(const std::string& good, int s);
    void setPrice(const std::string& good, float p);
    
    void produce();
};


#endif /* defined(__FreeMarket__Producer__) */
