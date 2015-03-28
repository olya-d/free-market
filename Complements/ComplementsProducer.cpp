//
// Created by Olga on 3/24/15.
//

#include "ComplementsProducer.h"
#include "ComplementsMarket.h"


ComplementsProducer::ComplementsProducer(ComplementsMarket *market) {
    this->market = market;
    for (auto good : market->getGoods()) {
        lastSold[good] = 0;
        supplies[good] = 0;
        prices[good] = 0;
    }
}

void ComplementsProducer::setSupply(const std::string &good, int s) {
    supplies[good] = s;
}

void ComplementsProducer::setPrice(const std::string &good, float p) {
   prices[good] = p;
}

int ComplementsProducer::getSupply(const std::string &good) const {
    return supplies.at(good);
}

float ComplementsProducer::getPrice(const std::string &good) const {
    return prices.at(good);
}

void ComplementsProducer::produce() {
    changePricing();
    generateGoods();
}

void ComplementsProducer::changePricing() {
    for (const std::string good : market->getGoods()) {
        if (supplies[good] > 0) {
            if (prices[good] > market->getCosts().at(good)) {
                prices[good] *= market->getPriceDecrement();
            }
        } else {
            if (lastSold[good] != 0) {
                if (prices[good] < market->getCosts().at(good)) {
                    prices[good] *= market->getPriceIncrement();
                } else {
                    prices[good] *= market->getPriceIncrement();
                }
            }
        }
    }
}

void ComplementsProducer::generateGoods() {
    std::string goodWithMaxProfit = market->getGoods()[0];
    float maxProfit = 0;
    for (auto good : market->getGoods()) {
        float profit = market->maxPrice(good) - market->getCosts().at(good);
        if (profit >= maxProfit) {
            maxProfit = profit;
            goodWithMaxProfit = good;
        }
        if (lastSold[good] > 0 && lastSold[good] > supplies[good]) {
            supplies[good] = lastSold[good];
        }
    }
    if (maxProfit > 0) {
        supplies[goodWithMaxProfit] += market->getSupplyIncrement();
    }
}

void ComplementsProducer::buyFrom(const std::string &good, int q) {
    lastSold[good] += q;
    supplies[good] -= q;
}

bool ComplementsProducer::hasSoldGood(const std::string &good) {
    return lastSold[good] > 0;
}

void ComplementsProducer::prepare() {
    for (auto good : market->getGoods()) {
        lastSold[good] = 0;
    }
}
