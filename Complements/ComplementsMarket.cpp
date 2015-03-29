//
// Created by Olga on 3/24/15.
//
#include <random>
#include "ComplementsMarket.h"


ComplementsMarket::ComplementsMarket(ComplementsSimulationConfig *config) {
    _setUp(config);
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> supplyDis(0, config_->getMaxStartingSupply());

    for (int i = 0; i < config_->getNumOfProducers(); i++) {
        ComplementsProducer *p = new ComplementsProducer(this);
        for (const std::string& good : config_->getGoods()) {
            std::uniform_real_distribution<> priceDis(
                    config_->getCosts().at(good), config_->getCosts().at(good) + config_->getMaxStartingProfits().at(good));
            p->setPrice(good, priceDis(gen));
            p->setSupply(good, supplyDis(gen));
        }
        producers_.push_back(p);
    }

    for (int i = 0; i < config_->getNumOfConsumers(); i++) {
        consumers_.push_back(new ComplementsConsumer(this));
    }
}

void ComplementsMarket::simulate(int times) {
    for (int i = 0; i < times; i++) {

        int generatedDemand = int(roundf((sinf(i) + 2)*20));
        for (ComplementsConsumer* consumer : consumers_) {
            consumer->setDemand(generatedDemand);
        }

        _writeData();
        for (ComplementsProducer* producer : producers_) {
            producer->prepare();
        }

        while (getTotalDemand() > 0 && getTotalSupply() > 0) {
            for (ComplementsConsumer* consumer : consumers_) {
                consumer->buy();
            }
        }
        for (ComplementsProducer* producer : producers_) {
            producer->changePricing();
        }
        for (ComplementsProducer* producer : producers_) {
            producer->generateGoods();
        }

    }

    demandFile_.close();
    priceFile_.close();
    supplyFile_.close();
}

int ComplementsMarket::getTotalSupply() {
    std::vector<int> supplies = std::vector<int>();
    for (auto goodRatio : getRatios()) {
        int supplyNumber = 0;
        for (ComplementsProducer* producer : producers_) {
            supplyNumber += producer->getSupply(goodRatio.first);
        }
        supplies.push_back(supplyNumber / goodRatio.second);

    }
    return *std::min_element(supplies.begin(), supplies.end());
}

float ComplementsMarket::getMaxPriceOf(const std::string &good) {
    float max = 0.0f;
    for (ComplementsProducer* producer : producers_) {
        if (max < producer->getPrice(good) && producer->hasSoldGood(good)) {
            max = producer->getPrice(good);
        }
    }
    return max;
}
