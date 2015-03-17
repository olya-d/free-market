//
//  BaseProducer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#include "BaseProducer.h"
#include "Constants.h"

BaseProducer::BaseProducer() {
    supply = 0;
    price = 0;
}


void BaseProducer::generateGoods() {
    if (price > MarketConstants::Cost) {
        supply += MarketConstants::SupplyIncrement;
    }
}


void BaseProducer::produce() {
    if (supply > 0) {
        if (price*MarketConstants::PriceDecrement >= MarketConstants::Cost) {
            price *= MarketConstants::PriceDecrement;
        }
    } else { // Supply was bought!
        price *= MarketConstants::PriceIncrement; // Increase price.
        generateGoods(); // Make more product.
    }
}


float BaseProducer::getPrice() {
    return price;
}

int BaseProducer::getSupply() {
    return supply;
}

void BaseProducer::setSupply(int s) {
    supply = s;
}

void BaseProducer::setPrice(float p) {
    price = p;
}
