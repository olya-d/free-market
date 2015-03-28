//
// Created by Olga on 3/24/15.
//
#include <random>
#include <DiscRecording/DiscRecording.h>

#include "ComplementsMarket.h"
#include "ComplementsConsumer.h"


ComplementsMarket::ComplementsMarket(ComplementsSimulationConfig *config) {
    _config = config;
    producers = std::vector<ComplementsProducer*>();
    consumers = std::vector<ComplementsConsumer*>();

    demandData.open(_config->getDemandFile());
    priceData.open(_config->getPriceFile());
    supplyData.open(_config->getSupplyFile());

    std::string header = "";

    for (int i = 0; i < _config->getGoods().size(); ++i) {
        std::string good = _config->getGoods()[i];
        header += good;
        if (i != _config->getGoods().size() - 1) {
            header += ",";
        }
    }

    priceData << header << std::endl;
    supplyData << header << std::endl;

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
        producers.push_back(p);
    }

    for (int i = 0; i < _config->getNumOfConsumers(); i++) {
        consumers.push_back(new ComplementsConsumer(this));
    }
}

void ComplementsMarket::simulate(int times) {
    for (int i = 0; i < times; i++) {

        int generatedDemand = int(roundf((sinf(i) + 2)*20));
        for (ComplementsConsumer* consumer : consumers) {
            consumer->setDemand(generatedDemand);
        }

        writeData();
        for (ComplementsProducer* producer : producers) {
            producer->prepare();
        }

        while (totalDemand() > 0 && totalSupply() > 0) {
            for (ComplementsConsumer* consumer : consumers) {
                consumer->buy();
            }
        }
        for (ComplementsProducer* producer : producers) {
            producer->changePricing();
        }
        for (ComplementsProducer* producer : producers) {
            producer->generateGoods();
        }

    }

    demandData.close();
    priceData.close();
    supplyData.close();
}

int ComplementsMarket::totalSupply() {
    std::vector<int> supplies = std::vector<int>();
    for (auto goodRatio : getRatios()) {
        int supplyNumber = 0;
        for (ComplementsProducer* producer : producers) {
            supplyNumber += producer->getSupply(goodRatio.first);
        }
        supplies.push_back(supplyNumber / goodRatio.second);

    }
    return *std::min_element(supplies.begin(), supplies.end());
}

ComplementsProducer* ComplementsMarket::cheapestProducer(const std::string &good, bool ignoreZeroSupply) {
    return *std::min_element(producers.begin(), producers.end(), [&](ComplementsProducer* p1, ComplementsProducer* p2) -> bool {
        if (ignoreZeroSupply) {
            if (p1->getSupply(good) == 0) {
                return false;
            }
            if (p2->getSupply(good) == 0) {
                return true;
            }
        }
        return p1->getPrice(good) < p2->getPrice(good);
    });
}

int ComplementsMarket::supply(const std::string &good) {
    int sum = 0;
    for (ComplementsProducer* producer : producers) {
        sum += producer->getSupply(good);
    }
    return sum;
}

void ComplementsMarket::writeData() {
    int demand = totalDemand();
    demandData << demand << std::endl;
    std::cout << demand << std::endl;
    std::string supplyRow = "";
    std::string priceRow = "";
    int i = 0;
    for (auto good : getGoods()) {
        supplyRow += std::to_string(supply(good));
        priceRow += std::to_string(maxPrice(good));
        if (i != _config->getGoods().size() - 1) {
            supplyRow += ",";
            priceRow += ",";
        }
        i += 1;
    }

    std::cout << supplyRow << "\n";
    std::cout << priceRow << "\n\n";

    supplyData << supplyRow << std::endl;
    priceData << priceRow << std::endl;
}

int ComplementsMarket::totalDemand() {
    int sum = 0;
    for (ComplementsConsumer* consumer : consumers) {
        sum += consumer->getDemand();
    }
    return sum;
}

float ComplementsMarket::averagePrice(const std::string &good) {
    float sum = 0.0f;
    for (ComplementsProducer* producer : producers) {
        sum += producer->getPrice(good);
    }
    return sum / producers.size();
}

std::string ComplementsMarket::maxPricedGood() {
    std::map<std::string, float> maxPrices;
    for (auto good : _config->getGoods()) {
        maxPrices[good] = maxPrice(good);
    }
    std::pair<std::string, float> max = *std::max_element(maxPrices.begin(), maxPrices.end(),
            [] (std::pair<std::string, float> p1, std::pair<std::string, float> p2) -> bool {
                return p1.second < p2.second;
            });
    return max.first;
}

float ComplementsMarket::maxPrice(const std::string &good) {
    float max = 0.0f;
    for (ComplementsProducer* producer : producers) {
        if (max < producer->getPrice(good) && producer->hasSoldGood(good)) {
            max = producer->getPrice(good);
        }
    }
    return max;
}
