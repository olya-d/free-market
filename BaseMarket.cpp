//
//  BaseMarket.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

#include "BaseMarket.h"
#include "Constants.h"


BaseMarket::BaseMarket() {
    producers = std::vector<BaseProducer *>();
    consumers = std::vector<BaseConsumer *>();
    
    demandData.open(MarketConstants::DemandFile);
    priceData.open(MarketConstants::PriceFile);
    supplyData.open(MarketConstants::SupplyFile);
    
    srand(time(nullptr));
    
    for (int i = 0; i < MarketConstants::NumOfProducers; i++) {
        BaseProducer * p = new BaseProducer();
        p->setPrice(MarketConstants::Cost + rand() % MarketConstants::MaxStartingProfit);
        p->setSupply(rand() % MarketConstants::MaxStartingSupply);
        
        producers.push_back(p);
    }
    
    for (int i = 0; i < MarketConstants::NumOfConsumers; i++) {
        consumers.push_back(new BaseConsumer());
    }
}

int BaseMarket::supply() {
    int sum = 0;
    for (BaseProducer * producer : producers) {
        sum += producer->getSupply();
    }
    return sum;
}

int BaseMarket::demand() {
    int sum = 0;
    for (BaseConsumer * consumer : consumers) {
        sum += consumer->getDemand();
    }
    return sum;
}

float BaseMarket::averagePrice() {
    float sum = 0.0f;
    for (BaseProducer * producer : producers) {
        sum += producer->getPrice();
    }
    return sum / producers.size();
}

void BaseMarket::writeData() {
    demandData << demand() << std::endl;
    supplyData << supply() << std::endl;
    priceData << averagePrice() << std::endl;
}

void BaseMarket::simulate(int times) {
    for (int i = 0; i < times; i++) {
        int generatedDemand = int(roundf((sinf(i) + 2)*20));

        for (BaseConsumer * consumer : consumers) {
            consumer->setDemand(generatedDemand);
        }
        
        writeData();
        
        for (BaseProducer * producer : producers) {
            producer->produce();
        }
        
        
        while (demand() > 0 && supply() > 0) {
            for (BaseConsumer * consumer : consumers) {
                consumer->buy(producers);
            }
        }
    }

    demandData.close();
    priceData.close();
    supplyData.close();
}