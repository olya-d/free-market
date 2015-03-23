//
//  BaseProducer.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#include "OneGoodProducer.h"
#include "OneGoodMarket.h"


OneGoodProducer::OneGoodProducer(OneGoodMarket* market) {
    _market = market;
    supply = 0;
    price = 0;
}

void OneGoodProducer::generateGoods() {
    if (price > _market->getCost()) {
        supply += _market->getSupplyIncrement();
    }
}

void OneGoodProducer::produce() {
    if (supply > 0) {
        if (price*_market->getPriceDecrement() >= _market->getCost()) {
            price *= _market->getPriceDecrement();
        }
    } else { // Supply was bought!
        price *= _market->getPriceIncrement(); // Increase price.
        generateGoods(); // Make more product.
    }
}

float OneGoodProducer::getPrice() {
    return price;
}

int OneGoodProducer::getSupply() {
    return supply;
}

void OneGoodProducer::setSupply(int s) {
    supply = s;
}

void OneGoodProducer::setPrice(float p) {
    price = p;
}
