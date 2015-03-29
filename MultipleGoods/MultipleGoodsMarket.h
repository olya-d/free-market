//
// Created by Olga on 3/28/15.
//

#ifndef FREEMARKET_MULTIPLEGOODSMARKET_H
#define FREEMARKET_MULTIPLEGOODSMARKET_H


#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <random>
#include <cmath>


template <class Config, class Producer, class Consumer>
class MultipleGoodsMarket {
protected:
    Config* _config;
    std::vector<Producer*> _producers;
    std::vector<Consumer*> _consumers;
    std::ofstream demandFile_;
    std::ofstream priceFile_;
    std::ofstream supplyFile_;

    virtual void _writeData();
    virtual void _setUp(Config* config);
public:
    virtual void simulate(int times) = 0;
    virtual int getSupplyOf(const std::string& good);
    virtual int getTotalDemand();
    virtual int getTotalSupply() = 0;
    Producer* getCheapestProducerOf(const std::string &good, bool ignoreZeroSupply);
    virtual float getAveragePriceOf(const std::string &good);
    std::vector<std::string> const & getGoods() const;
    std::map<std::string, int> const & getMaxAcceptablePrices() const;
    std::map<std::string, int> const & getCosts() const;
    int getSupplyIncrement() const;
    float getPriceIncrement() const;
    float getPriceDecrement() const;
};


template <class Config, class Producer, class Consumer>
void MultipleGoodsMarket<Config, Producer, Consumer>::_setUp(Config *config) {
    _config = config;
    _producers = std::vector<Producer*>();
    _consumers = std::vector<Consumer*>();

    demandFile_.open(_config->getDemandFile());
    priceFile_.open(_config->getPriceFile());
    supplyFile_.open(_config->getSupplyFile());

    std::string header = "";

    for (int i = 0; i < _config->getGoods().size(); ++i) {
        header += _config->getGoods().at(i);
        if (i != _config->getGoods().size() - 1) {
            header += ",";
        }
    }

    priceFile_ << header << std::endl;
    supplyFile_ << header << std::endl;
}

template <class Config, class Producer, class Consumer>
void MultipleGoodsMarket<Config, Producer, Consumer>::_writeData() {
    int demand = getTotalDemand();
    demandFile_ << demand << std::endl;
    std::cout << demand << std::endl;
    std::string supplyRow = "";
    std::string priceRow = "";
    int i = 0;
    for (auto good : getGoods()) {
        supplyRow += std::to_string(getSupplyOf(good));
        priceRow += std::to_string(getAveragePriceOf(good));
        if (i != getGoods().size() - 1) {
            supplyRow += ",";
            priceRow += ",";
        }
        i += 1;
    }

    std::cout << supplyRow << "\n";
    std::cout << priceRow << "\n\n";

    supplyFile_ << supplyRow << std::endl;
    priceFile_ << priceRow << std::endl;
}

template <class Config, class Producer, class Consumer>
int MultipleGoodsMarket<Config, Producer, Consumer>::getSupplyOf(const std::string &good) {
    int sum = 0;
    for (Producer* producer : _producers) {
        sum += producer->getSupply(good);
    }
    return sum;
}


template <class Config, class Producer, class Consumer>
int MultipleGoodsMarket<Config, Producer, Consumer>::getTotalDemand() {
    int sum = 0;
    for (Consumer* consumer : _consumers) {
        sum += consumer->getDemand();
    }
    return sum;
}

template <class Config, class Producer, class Consumer>
int MultipleGoodsMarket<Config, Producer, Consumer>::getTotalSupply() {
    int sum = 0;
    for (Producer* producer : _producers) {
        sum += producer->getTotalSupply();
    }
    return sum;
}

template <class Config, class Producer, class Consumer>
Producer* MultipleGoodsMarket<Config, Producer, Consumer>::getCheapestProducerOf(const std::string &good,
                                                                                 bool ignoreZeroSupply) {
    return *std::min_element(_producers.begin(), _producers.end(), [&](Producer* p1, Producer* p2) -> bool {
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

template <class Config, class Producer, class Consumer>
float MultipleGoodsMarket<Config, Producer, Consumer>::getAveragePriceOf(const std::string &good) {
    float sum = 0.0f;
    for (Producer* producer : _producers) {
        sum += producer->getPrice(good);
    }
    return sum / _producers.size();
}

template <class Config, class Producer, class Consumer>
std::vector<std::string> const &MultipleGoodsMarket<Config, Producer, Consumer>::getGoods() const {
    return _config->getGoods();
}

template <class Config, class Producer, class Consumer>
std::map<std::string, int> const &MultipleGoodsMarket<Config, Producer, Consumer>::getMaxAcceptablePrices() const {
    return _config->getMaxAcceptablePrices();
}

template <class Config, class Producer, class Consumer>
std::map<std::string, int> const &MultipleGoodsMarket<Config, Producer, Consumer>::getCosts() const {
    return _config->getCosts();
}

template <class Config, class Producer, class Consumer>
int MultipleGoodsMarket<Config, Producer, Consumer>::getSupplyIncrement() const {
    return _config->getSupplyIncrement();
}

template <class Config, class Producer, class Consumer>
float MultipleGoodsMarket<Config, Producer, Consumer>::getPriceIncrement() const {
    return _config->getPriceIncrement();
}

template <class Config, class Producer, class Consumer>
float MultipleGoodsMarket<Config, Producer, Consumer>::getPriceDecrement() const {
    return _config->getPriceDecrement();
}


#endif //FREEMARKET_MULTIPLEGOODSMARKET_H
