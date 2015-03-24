//
// Created by Olga on 3/24/15.
//

#include "ComplementsProducer.h"
#include "ComplementsMarket.h"


ComplementsProducer::ComplementsProducer(ComplementsMarket *market) {
    this->market = market;
    for (auto good : market->getGoods()) {
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
            prices[good] *= market->getPriceIncrement();
        }
    }
}

void ComplementsProducer::generateGoods() {
    std::pair<std::string, float> max = market->maxAveragePrice();
    if (prices[max.first] > market->getCosts().at(max.first)) {
        supplies[max.first] += market->getSupplyIncrement();
    }
}
