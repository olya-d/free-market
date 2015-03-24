//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSMARKET_H_
#define _FREEMARKET_COMPLEMENTSMARKET_H_


#include <fstream>
#include "ComplementsSimulationConfig.h"
#include "ComplementsProducer.h"


class ComplementsProducer;
class ComplementsConsumer;


class ComplementsMarket {
private:
    ComplementsSimulationConfig* _config;

    std::vector<ComplementsProducer*> producers;
    std::vector<ComplementsConsumer*> consumers;

    std::ofstream demandData;
    std::ofstream priceData;
    std::ofstream supplyData;

    std::string primaryGood;

    void writeData();
public:
    ComplementsMarket(ComplementsSimulationConfig* config);

    void simulate(int times);
    int supply(const std::string& good);
    int totalSupply();
    int totalDemand();
    float averagePrice(const std::string& good);
    std::pair<std::string, float> maxAveragePrice();

    ComplementsProducer* cheapestProducer(const std::string& good, bool ignoreZeroSupply);

    std::vector<std::string> const &getGoods() const {
        return _config->getGoods();
    }

    std::map<std::string, int> const &getMaxAcceptablePrices() const {
        return _config->getMaxAcceptablePrices();
    }

    std::vector<ComplementsProducer*> &getProducers()  {
        return producers;
    }

    std::map<std::string, int> const &getRatios() const {
        return _config->getRatios();
    }

    std::string &getPrimaryGood() {
        return primaryGood;
    }

    std::map<std::string, int> const &getCosts() const {
        return _config->getCosts();
    }

    int getSupplyIncrement() const {
        return _config->getSupplyIncrement();
    }

    float getPriceIncrement() const {
        return _config->getPriceIncrement();
    }

    float getPriceDecrement() const {
        return _config->getPriceDecrement();
    }

};


#endif //_FREEMARKET_COMPLEMENTSMARKET_H_
