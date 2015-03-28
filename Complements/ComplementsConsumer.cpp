//
// Created by Olga on 3/24/15.
//

#include <vector>
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
        producer.buyFrom(good, cheapestSupply);
    } else {
        producer.buyFrom(good, currentDemand);
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

    int minRations = market->getTotalSupply();
    int d = demand;
    for (auto good : market->getGoods()) {
        int goodDemand = d * market->getRatios().at(good);
        while (goodDemand > 0 && market->getSupplyOf(good) > 0) {
            ComplementsProducer* cheapestProducer = market->getCheapestProducerOf(good, true);
            if (cheapestProducer->getSupply(good) > 0) {
                if (cheapestProducer->getPrice(good) > market->getMaxAcceptablePrices().at(good)) {
                    goodDemand = demand * market->getRatios().at(good);
                    break;
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
            producer->buyFrom(good, producer->getSupply(good) - supplies[i].at(good));
            producer->setPrice(good, prices[i].at(good));
        }
        i += 1;
    }

    for (auto good : market->getGoods()) {
        int goodDemand = minRations * market->getRatios().at(good);
        while (goodDemand > 0) {
            ComplementsProducer* cheapestProducer = market->getCheapestProducerOf(good, true);
            if (cheapestProducer->getSupply(good) > 0) {
                goodDemand = buyFromProducer(*cheapestProducer, good, goodDemand);
            }
        }
    }
    demand -= minRations;
}
