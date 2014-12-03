//
//  Producer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#include "Producer.h"
#include "Constants.h"

Producer::Producer() {
    supply = 0;
    price = 0;
}


void Producer::generateGoods() {
    if (price > MarketConstants::Cost) {
        supply += MarketConstants::SupplyIncrement;
    }
}


void Producer::produce() {
    if (supply > 0) {
        if (price*MarketConstants::PriceDecrement >= MarketConstants::Cost) {
            price *= MarketConstants::PriceDecrement;
        }
    } else { // Supply was bought!
        price *= MarketConstants::PriceIncrement; // Increase price.
        generateGoods(); // Make more product.
    }
}


float Producer::getPrice() {
    return price;
}

int Producer::getSupply() {
    return supply;
}

void Producer::setSupply(int s) {
    supply = s;
}

void Producer::setPrice(float p) {
    price = p;
}
