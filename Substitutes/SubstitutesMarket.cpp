//
//  Market.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include <math.h>
#include <iostream>
#include "SubstitutesMarket.h"


SubstitutesMarket::SubstitutesMarket(SubstitutesSimulationConfig* config) {
    _setUp(config);
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> supplyDis(0, config_->getMaxStartingSupply());

    for (int i = 0; i < config_->getNumOfProducers(); i++) {
        SubstitutesProducer* p = new SubstitutesProducer(this);
        for (const std::string& good : config_->getGoods()) {
            std::uniform_real_distribution<> priceDis(
                    config_->getCosts().at(good), config_->getCosts().at(good) + config_->getMaxStartingProfits().at(good));
            p->setPrice(good, priceDis(gen));
            p->setSupply(good, supplyDis(gen));
        }
        producers_.push_back(p);
    }

    for (int i = 0; i < config_->getNumOfConsumers(); i++) {
        consumers_.push_back(new SubstitutesConsumer(this));
    }
}

void SubstitutesMarket::simulate(int times) {
    for (int i = 0; i < times; i++) {

        int generatedDemand = int(roundf((sinf(i) + 2)*20));
        for (SubstitutesConsumer* consumer : consumers_) {
            consumer->setDemand(generatedDemand);
        }
        
        _writeData();
        
        std::string goodToBuy = cheapestGood();

        while (getTotalDemand() > 0 && getSupplyOf(goodToBuy) > 0) {
            for (SubstitutesConsumer* consumer : consumers_) {
                consumer->buy();
            }
        }
        
        for (SubstitutesProducer* producer : producers_) {
            producer->changePricing();
        }
        for (SubstitutesProducer* producer : producers_) {
            producer->generateGoods();
        }

    }

    demandFile_.close();
    priceFile_.close();
    supplyFile_.close();
}

std::string SubstitutesMarket::cheapestGood() {
    std::map<std::string, float> minPrices;
    for (auto good : config_->getGoods()) {
        if (getSupplyOf(good) == 0) {
            continue;
        }
        minPrices[good] = getCheapestProducerOf(good, false)->getPrice(good);
    }
    std::pair<std::string, float> min = *std::min_element(minPrices.begin(), minPrices.end(),
            [] (std::pair<std::string, float> p1, std::pair<std::string, float> p2) -> bool {
        return p1.second < p2.second;
    });
    return min.first;
}

int SubstitutesMarket::getTotalSupply() {
    int sum = 0;
    for (SubstitutesProducer* producer : producers_) {
        sum += producer->getTotalSupply();
    }
    return sum;
}
