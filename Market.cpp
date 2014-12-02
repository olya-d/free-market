//
//  Market.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

#include "Market.h"
#include "Constants.h"


Market::Market() {
    producers = std::vector<Producer*>();
    consumers = std::vector<Consumer*>();
    
    demandData.open("demand.txt");
    priceData.open("price.txt");
    supplyData.open("supply.txt");
    
    srand(time(nullptr));
    
    for (int i = 0; i < MarketConstants::NumOfProducers; i++) {
        Producer* p = new Producer();
        p->setPrice(MarketConstants::Cost + rand() % MarketConstants::MaxStartingProfit);
        p->setSupply(rand() % MarketConstants::MaxStartingSupply);
        
        producers.push_back(p);
    }
    
    for (int i = 0; i < MarketConstants::NumOfConsumers; i++) {
        consumers.push_back(new Consumer());
    }
}

int Market::supply() {
    int sum = 0;
    for (Producer* producer : producers) {
        sum += producer->getSupply();
    }
    return sum;
}

int Market::demand() {
    int sum = 0;
    for (Consumer* consumer : consumers) {
        sum += consumer->getDemand();
    }
    return sum;
}

float Market::averagePrice() {
    float sum = 0.0f;
    for (Producer* producer : producers) {
        sum += producer->getPrice();
    }
    return sum / producers.size();
}

void Market::writeData() {
    demandData << demand() << std::endl;
    supplyData << supply() << std::endl;
    priceData << averagePrice() << std::endl;
}

void Market::simulate(int times) {
    for (int i = 0; i < times; i++) {
        int generatedDemand = int(roundf((sinf(i) + 2)*20));
        for (Consumer* consumer : consumers) {
            consumer->setDemand(generatedDemand);
        }
        
        writeData();
        
        for (Producer* producer : producers) {
            producer->produce();
        }
        
        
        while (demand() > 0 && supply() > 0) {
            for (Consumer* consumer : consumers) {
                consumer->buy(producers);
            }
        }
    }
    writeData();
    
    demandData.close();
    priceData.close();
    supplyData.close();
}