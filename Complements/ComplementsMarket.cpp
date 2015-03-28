//
// Created by Olga on 3/24/15.
//
#include <random>
#include "ComplementsMarket.h"


ComplementsMarket::ComplementsMarket(ComplementsSimulationConfig *config) {
    _config = config;
    _producers = std::vector<ComplementsProducer*>();
    _consumers = std::vector<ComplementsConsumer*>();

    _demandFile.open(_config->getDemandFile());
    _priceFile.open(_config->getPriceFile());
    _supplyFile.open(_config->getSupplyFile());

    std::string header = "";

    for (int i = 0; i < _config->getGoods().size(); ++i) {
        std::string good = _config->getGoods()[i];
        header += good;
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
        ComplementsProducer *p = new ComplementsProducer(this);
        for (const std::string& good : _config->getGoods()) {
            std::uniform_real_distribution<> priceDis(_config->getCosts().at(good), _config->getCosts().at(good) + _config->getMaxStartingProfits().at(good));
            p->setPrice(good, priceDis(gen));
            p->setSupply(good, supplyDis(gen));
        }
        _producers.push_back(p);
    }

    for (int i = 0; i < _config->getNumOfConsumers(); i++) {
        _consumers.push_back(new ComplementsConsumer(this));
    }
}

void ComplementsMarket::simulate(int times) {
    for (int i = 0; i < times; i++) {

        int generatedDemand = int(roundf((sinf(i) + 2)*20));
        for (ComplementsConsumer* consumer : _consumers) {
            consumer->setDemand(generatedDemand);
        }

        _writeData();
        for (ComplementsProducer* producer : _producers) {
            producer->prepare();
        }

        while (getTotalDemand() > 0 && getTotalSupply() > 0) {
            for (ComplementsConsumer* consumer : _consumers) {
                consumer->buy();
            }
        }
        for (ComplementsProducer* producer : _producers) {
            producer->changePricing();
        }
        for (ComplementsProducer* producer : _producers) {
            producer->generateGoods();
        }

    }

    _demandFile.close();
    _priceFile.close();
    _supplyFile.close();
}

int ComplementsMarket::getTotalSupply() {
    std::vector<int> supplies = std::vector<int>();
    for (auto goodRatio : getRatios()) {
        int supplyNumber = 0;
        for (ComplementsProducer* producer : _producers) {
            supplyNumber += producer->getSupply(goodRatio.first);
        }
        supplies.push_back(supplyNumber / goodRatio.second);

    }
    return *std::min_element(supplies.begin(), supplies.end());
}

float ComplementsMarket::getMaxPriceOf(const std::string &good) {
    float max = 0.0f;
    for (ComplementsProducer* producer : _producers) {
        if (max < producer->getPrice(good) && producer->hasSoldGood(good)) {
            max = producer->getPrice(good);
        }
    }
    return max;
}
