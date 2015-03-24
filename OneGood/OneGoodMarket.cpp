//
//  OneGoodMarket.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "OneGoodMarket.h"
#include "OneGoodConsumer.h"
#include "OneGoodProducer.h"


OneGoodMarket::OneGoodMarket(OneGoodSimulationConfig* config) {
    _config = config;
    producers = std::vector<OneGoodProducer *>();
    consumers = std::vector<OneGoodConsumer *>();
    
    demandData.open(_config->getDemandFile());
    priceData.open(_config->getPriceFile());
    supplyData.open(_config->getSupplyFile());
    
    srand(time(nullptr));
    
    for (int i = 0; i < _config->getNumOfProducers(); i++) {
        OneGoodProducer * p = new OneGoodProducer(this);
        p->setPrice(_config->getCost() + rand() % _config->getMaxStartingProfit());
        p->setSupply(rand() % _config->getMaxStartingSupply());
        
        producers.push_back(p);
    }
    
    for (int i = 0; i < _config->getNumOfConsumers(); i++) {
        consumers.push_back(new OneGoodConsumer(this));
    }
}

int OneGoodMarket::supply() {
    int sum = 0;
    for (OneGoodProducer * producer : producers) {
        sum += producer->getSupply();
    }
    return sum;
}

int OneGoodMarket::demand() {
    int sum = 0;
    for (OneGoodConsumer * consumer : consumers) {
        sum += consumer->getDemand();
    }
    return sum;
}

float OneGoodMarket::averagePrice() {
    float sum = 0.0f;
    for (OneGoodProducer * producer : producers) {
        sum += producer->getPrice();
    }
    return sum / producers.size();
}

void OneGoodMarket::writeData() {
    demandData << demand() << std::endl;
    supplyData << supply() << std::endl;
    priceData << averagePrice() << std::endl;
}

void OneGoodMarket::simulate(int times) {
    for (int i = 0; i < times; i++) {
        int generatedDemand = int(roundf((sinf(i) + 2)*20));

        for (OneGoodConsumer * consumer : consumers) {
            consumer->setDemand(generatedDemand);
        }
        
        writeData();
        
        for (OneGoodProducer * producer : producers) {
            producer->produce();
        }
        
        
        while (demand() > 0 && supply() > 0) {
            for (OneGoodConsumer * consumer : consumers) {
                consumer->buy(producers);
            }
        }
    }

    demandData.close();
    priceData.close();
    supplyData.close();
}