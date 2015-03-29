//
// Created by Olga on 3/24/15.
//

#include "ComplementsProducer.h"
#include "ComplementsMarket.h"


ComplementsProducer::ComplementsProducer(ComplementsMarket *market) {
    this->market_ = market;
    for (auto good : market->getGoods()) {
        lastSold_[good] = 0;
        supplies_[good] = 0;
        prices_[good] = 0;
    }
}

void ComplementsProducer::setSupply(const std::string &good, int s) {
    supplies_[good] = s;
}

void ComplementsProducer::setPrice(const std::string &good, float p) {
   prices_[good] = p;
}

int ComplementsProducer::getSupply(const std::string &good) const {
    return supplies_.at(good);
}

float ComplementsProducer::getPrice(const std::string &good) const {
    return prices_.at(good);
}

void ComplementsProducer::changePricing() {
    for (const std::string good : market_->getGoods()) {
        if (supplies_[good] > 0) {
            if (prices_[good] > market_->getCosts().at(good)) {
                prices_[good] *= market_->getPriceDecrement();
            }
        } else {
            if (lastSold_[good] != 0) {
                prices_[good] *= market_->getPriceIncrement();
            }
        }
    }
}

void ComplementsProducer::generateGoods() {
    std::string goodWithMaxProfit = market_->getGoods()[0];
    float maxProfit = market_->getAveragePriceOf(goodWithMaxProfit) - market_->getCosts().at(goodWithMaxProfit);
    for (auto good : market_->getGoods()) {
        float profit = market_->getAveragePriceOf(good) - market_->getCosts().at(good);
        if (profit >= maxProfit) {
            maxProfit = profit;
            goodWithMaxProfit = good;
        }
        if (lastSold_[good] > 0 && lastSold_[good] > supplies_[good]) {
            supplies_[good] = lastSold_[good];
        }
    }
    if (maxProfit > 0) {
        supplies_[goodWithMaxProfit] += market_->getSupplyIncrement();
    }
}

void ComplementsProducer::sell(const std::string &good, int q) {
    lastSold_[good] += q;
    supplies_[good] -= q;
}

bool ComplementsProducer::hasSoldGood(const std::string &good) {
    return lastSold_[good] > 0;
}

void ComplementsProducer::prepare() {
    for (auto good : market_->getGoods()) {
        lastSold_[good] = 0;
    }
}
