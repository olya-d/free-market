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
#include <string>

#include "SubstitutesMarket.h"
#include "Constants.h"
#include "SubstitutesConsumer.h"


SubstitutesMarket::SubstitutesMarket() {
    producers = std::vector<SubstitutesProducer*>();
    consumers = std::vector<SubstitutesConsumer*>();
    
    demandData.open(MarketConstants::DemandFile);
    priceData.open(MarketConstants::PriceFile);
    supplyData.open(MarketConstants::SupplyFile);

    std::string header = "";

    for (int i = 0; i < MarketConstants::Goods.size(); ++i) {
        header += MarketConstants::Goods[i];
        if (i != MarketConstants::Goods.size() - 1) {
            header += ",";
        }
    }

    priceData << header << std::endl;
    supplyData << header << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> supplyDis(0, MarketConstants::MaxStartingSupply);


    for (int i = 0; i < MarketConstants::NumOfProducers; i++) {
        SubstitutesProducer* p = new SubstitutesProducer(this);
        for (const std::string& good : MarketConstants::Goods) {
            std::uniform_real_distribution<> priceDis(MarketConstants::Costs[good], MarketConstants::Costs[good] + MarketConstants::MaxStartingProfits[good]);
            p->setPrice(good, priceDis(gen));
            p->setSupply(good, supplyDis(gen));
        }
        producers.push_back(p);
    }
    
    for (int i = 0; i < MarketConstants::NumOfConsumers; i++) {
        consumers.push_back(new SubstitutesConsumer(this));
    }
}

int SubstitutesMarket::supply(const std::string& good) {
    int sum = 0;
    for (SubstitutesProducer* producer : producers) {
        sum += producer->getSupply(good);
    }
    return sum;
}

int SubstitutesMarket::totalDemand() {
    int sum = 0;
    for (SubstitutesConsumer* consumer : consumers) {
        sum += consumer->getDemand();
    }
    return sum;
}

int SubstitutesMarket::totalSupply() {
    int sum = 0;
    for (SubstitutesProducer* producer : producers) {
        sum += producer->getTotalSupply();
    }
    return sum;
}

float SubstitutesMarket::averagePrice(const std::string& good) {
    float sum = 0.0f;
    for (SubstitutesProducer* producer : producers) {
        sum += producer->getPrice(good);
    }
    return sum / producers.size();
}

void SubstitutesMarket::writeData() {
    demandData << totalDemand() << std::endl;
    std::cout << totalDemand() << std::endl;
    std::string supplyRow = "";
    std::string priceRow = "";
    for (int i = 0; i < MarketConstants::Goods.size(); ++i) {
        supplyRow += std::to_string(supply(MarketConstants::Goods[i]));
        priceRow += std::to_string(averagePrice(MarketConstants::Goods[i]));
        if (i != MarketConstants::Goods.size() - 1) {
            supplyRow += ",";
            priceRow += ",";
        }
    }

    std::cout << supplyRow << "\n";
    std::cout << priceRow << "\n\n";

    supplyData << supplyRow << std::endl;
    priceData << priceRow << std::endl;
}

void SubstitutesMarket::simulate(int times) {
    for (int i = 0; i < times; i++) {

        int generatedDemand = int(roundf((sinf(i) + 2)*20));
        for (SubstitutesConsumer* consumer : consumers) {
            consumer->setDemand(generatedDemand);
        }
        
        writeData();
        
        std::string goodToBuy = cheapestGood();
        
        while (totalDemand() > 0 && supply(goodToBuy) > 0) {
            for (SubstitutesConsumer* consumer : consumers) {
                consumer->buy(goodToBuy);
            }
        }
        
        for (SubstitutesProducer* producer : producers) {
            producer->produce();
        }

    }

    demandData.close();
    priceData.close();
    supplyData.close();
}

SubstitutesProducer* SubstitutesMarket::cheapestProducer(const std::string& good, bool ignoreZeroSupply) {
    return *std::min_element(producers.begin(), producers.end(), [&](SubstitutesProducer* p1, SubstitutesProducer* p2) -> bool {
        if (ignoreZeroSupply) {
            if (p1->getSupply(good) == 0) {
                return false;
            }
            if (p2-> getSupply(good) == 0) {
                return true;
            }           
        }
        return p1->getPrice(good) < p2->getPrice(good);
    });
}

std::string SubstitutesMarket::cheapestGood() {
    std::map<std::string, float> minPrices;
    for (auto good : MarketConstants::Goods) {
        if (supply(good) == 0) {
            continue;
        }
        minPrices[good] = cheapestProducer(good, false)->getPrice(good);
    }
    std::pair<std::string, float> min = *std::min_element(minPrices.begin(), minPrices.end(),
            [] (std::pair<std::string, float> p1, std::pair<std::string, float> p2) -> bool {
        return p1.second < p2.second;
    });
    return min.first;
}

std::pair<std::string, float> SubstitutesMarket::maxAveragePrice() {
    std::map<std::string, float> averagePrices;
    for (auto good : MarketConstants::Goods) {
        averagePrices[good] = averagePrice(good);
    }
    std::pair<std::string, float> max = *std::max_element(averagePrices.begin(), averagePrices.end(),
            [] (std::pair<std::string, float> p1, std::pair<std::string, float> p2) -> bool {
                return p1.second < p2.second;
            });
    return max;
}
