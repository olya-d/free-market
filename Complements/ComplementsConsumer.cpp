//
// Created by Olga on 3/24/15.
//

#include <vector>
#include <DiscRecording/DiscRecording.h>

#include "ComplementsConsumer.h"
#include "ComplementsMarket.h"


ComplementsConsumer::ComplementsConsumer(ComplementsMarket *market) {
    demand = 0;
    this->market = market;
}

int ComplementsConsumer::getDemand() {
    return demand;
}

void ComplementsConsumer::setDemand(int d) {
    demand = d;
}

int ComplementsConsumer::buyFromProducer(ComplementsProducer& producer, std::string good, int currentDemand) {
    int cheapestSupply = producer.getSupply(good);
    if (currentDemand > cheapestSupply) {
        currentDemand -= cheapestSupply;
        producer.setSupply(good, 0);
    } else {
        producer.setSupply(good, cheapestSupply - currentDemand);
        currentDemand = 0;
    }
    return currentDemand;
}

void ComplementsConsumer::buy() {
    std::vector< std::map<std::string, int> > supplies = std::vector< std::map<std::string, int> >();
    std::vector< std::map<std::string, float> > prices = std::vector< std::map<std::string, float> >();

    for (ComplementsProducer* producer : market->getProducers()) {
        std::map<std::string, int> producerSupply;
        std::map<std::string, float> producerPrices;
        for (auto good : market->getGoods()) {
            producerSupply[good] = producer->getSupply(good);
            producerPrices[good] = producer->getPrice(good);
        }
        supplies.push_back(producerSupply);
        prices.push_back(producerPrices);
    }

    int minRations = market->totalSupply();
    int d = demand;
    for (auto good : market->getGoods()) {
        int goodDemand = d * market->getRatios().at(good);
        while (goodDemand > 0 && market->supply(good) > 0) {
            ComplementsProducer* cheapestProducer = market->cheapestProducer(good, true);
            if (cheapestProducer->getSupply(good) > 0) {
                if (cheapestProducer->getPrice(good) > market->getMaxAcceptablePrices().at(good)) {
                    d /= 2;
                    goodDemand /= 2;
                }
                goodDemand = buyFromProducer(*cheapestProducer, good, goodDemand);
            }
        }
        int rations = demand - goodDemand / market->getRatios().at(good);
        if (rations < minRations) {
            minRations = rations;
        }
    }

    int i = 0;
    for (ComplementsProducer* producer : market->getProducers()) {
        for (auto good : market->getGoods()) {
            producer->setSupply(good, supplies[i].at(good));
            producer->setPrice(good, prices[i].at(good));
        }
        i += 1;
    }

    for (auto good : market->getGoods()) {
        int goodDemand = minRations * market->getRatios().at(good);
        while (goodDemand > 0) {
            ComplementsProducer* cheapestProducer = market->cheapestProducer(good, true);
            if (cheapestProducer->getSupply(good) > 0) {
                if (cheapestProducer->getPrice(good) > market->getMaxAcceptablePrices().at(good)) {
                    demand /= 2;
                    goodDemand /= 2;
                }
                goodDemand = buyFromProducer(*cheapestProducer, good, goodDemand);
            }
        }
    }
    demand -= minRations;
}
