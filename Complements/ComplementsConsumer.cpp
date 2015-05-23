//
// Created by Olga on 3/24/15.
//

#include <vector>
#include "ComplementsConsumer.h"
#include "ComplementsMarket.h"


ComplementsConsumer::ComplementsConsumer(ComplementsMarket *market) {
    demand_ = 0;
    this->market_ = market;
}

int ComplementsConsumer::buyFromProducer(ComplementsProducer& producer, std::string good, int currentDemand) {
    int cheapestSupply = producer.getSupply(good);
    if (currentDemand > cheapestSupply) {
        currentDemand -= cheapestSupply;
        producer.sell(good, cheapestSupply);
    } else {
        producer.sell(good, currentDemand);
        currentDemand = 0;
    }
    return currentDemand;
}

void ComplementsConsumer::buy() {
    // Store the original values of supplies and prices for each producer,
    // to restore them after finding out the maximum number of each good the customer can buy.
    std::vector< std::map<std::string, int> > supplies = std::vector< std::map<std::string, int> >();
    std::vector< std::map<std::string, float> > prices = std::vector< std::map<std::string, float> >();

    for (ComplementsProducer* producer : market_->getProducers()) {
        std::map<std::string, int> producerSupply;
        std::map<std::string, float> producerPrices;
        for (auto good : market_->getGoods()) {
            producerSupply[good] = producer->getSupply(good);
            producerPrices[good] = producer->getPrice(good);
        }
        supplies.push_back(producerSupply);
        prices.push_back(producerPrices);
    }

    // Simulate the purchase for every good, to see how much can be bought (below the demand_).
    // minRatio: across all good, the minimum value of number of good that can be bought
    // divided by the ratio of the good = the maximum number of "total goods" that can be bought.
    int d = demand_;
    int minRatio = market_->getTotalSupply();
    for (auto good : market_->getGoods()) {
        int goodDemand = d * market_->getRatios().at(good);
        // Until the demand_ is satisfied or supply is finished.
        while (goodDemand > 0 && market_->getSupplyOf(good) > 0) {
            // Buy from the cheapest producer.
            ComplementsProducer* cheapestProducer = market_->getCheapestProducerOf(good, true);
            if (cheapestProducer->getSupply(good) > 0) {
                if (cheapestProducer->getPrice(good) > market_->getMaxAcceptablePrices().at(good)) {
                    demand_ /= 2;
                    goodDemand /= 2;
                    d /= 2;
                }
                goodDemand = buyFromProducer(*cheapestProducer, good, goodDemand);
            }
        }
        int ratios = demand_ - goodDemand / market_->getRatios().at(good);
        if (ratios < minRatio) {
            minRatio = ratios;
        }
    }

    // Return supplies and prices to the state before the last cycle (to the original values).
    int i = 0;
    for (ComplementsProducer* producer : market_->getProducers()) {
        for (auto good : market_->getGoods()) {
            producer->sell(good, producer->getSupply(good) - supplies[i].at(good));
            producer->setPrice(good, prices[i].at(good));
        }
        i += 1;
    }

    // Now actually buy the allowed number of "total goods".
    for (auto good : market_->getGoods()) {
        int goodDemand = minRatio * market_->getRatios().at(good);
        while (goodDemand > 0) {
            ComplementsProducer* cheapestProducer = market_->getCheapestProducerOf(good, true);
            if (cheapestProducer->getSupply(good) > 0) {
                goodDemand = buyFromProducer(*cheapestProducer, good, goodDemand);
            }
        }
    }
    demand_ -= minRatio;
}
