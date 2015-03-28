//
//  Market.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include <math.h>
#include <iostream>
#include <random>

#include "SubstitutesMarket.h"


SubstitutesMarket::SubstitutesMarket(SubstitutesSimulationConfig* config) {
    _config = config;
    _producers = std::vector<SubstitutesProducer*>();
    _consumers = std::vector<SubstitutesConsumer*>();
    
    _demandFile.open(_config->getDemandFile());
    _priceFile.open(_config->getPriceFile());
    _supplyFile.open(_config->getSupplyFile());

    std::string header = "";

    for (int i = 0; i < _config->getGoods().size(); ++i) {
        header += _config->getGoods().at(i);
        if (i != _config->getGoods().size() - 1) {
            header += ",";
        }
    }

    _priceFile << header << std::endl;
    _supplyFile << header << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> supplyDis(0, _config->getMaxStartingSupply());


    for (int i = 0; i < _config->getNumOfProducers(); i++) {
        SubstitutesProducer* p = new SubstitutesProducer(this);
        for (const std::string& good : _config->getGoods()) {
            std::uniform_real_distribution<> priceDis(_config->getCosts().at(good), _config->getCosts().at(good) + _config->getMaxStartingProfits().at(good));
            p->setPrice(good, priceDis(gen));
            p->setSupply(good, supplyDis(gen));
        }
        _producers.push_back(p);
    }
    
    for (int i = 0; i < _config->getNumOfConsumers(); i++) {
        _consumers.push_back(new SubstitutesConsumer(this));
    }
}

void SubstitutesMarket::simulate(int times) {
    for (int i = 0; i < times; i++) {

        int generatedDemand = int(roundf((sinf(i) + 2)*20));
        for (SubstitutesConsumer* consumer : _consumers) {
            consumer->setDemand(generatedDemand);
        }
        
        _writeData();
        
        std::string goodToBuy = cheapestGood();
        
        while (getTotalDemand() > 0 && getSupplyOf(goodToBuy) > 0) {
            for (SubstitutesConsumer* consumer : _consumers) {
                consumer->buy(goodToBuy);
            }
        }
        
        for (SubstitutesProducer* producer : _producers) {
            producer->produce();
        }

    }

    _demandFile.close();
    _priceFile.close();
    _supplyFile.close();
}

std::string SubstitutesMarket::cheapestGood() {
    std::map<std::string, float> minPrices;
    for (auto good : _config->getGoods()) {
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

std::pair<std::string, float> SubstitutesMarket::maxAveragePrice() {
    std::map<std::string, float> averagePrices;
    for (auto good : _config->getGoods()) {
        averagePrices[good] = getAveragePriceOf(good);
    }
    std::pair<std::string, float> max = *std::max_element(averagePrices.begin(), averagePrices.end(),
            [] (std::pair<std::string, float> p1, std::pair<std::string, float> p2) -> bool {
                return p1.second < p2.second;
            });
    return max;
}
