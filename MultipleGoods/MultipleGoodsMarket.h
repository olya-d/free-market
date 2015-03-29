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


// This template class is used for markets that have multiple goods (substitutes and complements).
// It is useful, because such operations as finding the cheapest producer can be defined indepentend of
// the type of the market.
template <class Config, class Producer, class Consumer>
class MultipleGoodsMarket {
protected:
    Config* config_;
    std::vector<Producer*> producers_;
    std::vector<Consumer*> consumers_;
    std::ofstream demandFile_;
    std::ofstream priceFile_;
    std::ofstream supplyFile_;

    // Output the current state of the market (supplies, prices and demand) to the standard output
    // and the files (demandFile_, priceFile_, supplyFile_).
    virtual void _writeData();
    // Set up the market
    // (initialize vectors producers_ and customers_, open files and write headers).
    // Consists of operations common to all types of market.
    virtual void _setUp(Config* config);
public:
    // Simulation is left to be implemented in each subclass.
    virtual void simulate(int times) = 0;
    virtual int getSupplyOf(const std::string& good);
    virtual int getTotalDemand();
    // Total supply can be defined in different untis, so implementation is left out.
    virtual int getTotalSupply() = 0;
    // If ignoreZeroSupply is true, procuders with zero supply are sorted to be in the end.
    Producer* getCheapestProducerOf(const std::string &good, bool ignoreZeroSupply);
    virtual float getAveragePriceOf(const std::string &good);
    std::vector<std::string> const & getGoods() const {
        return config_->getGoods();
    }
    std::map<std::string, int> const & getMaxAcceptablePrices() const {
        return config_->getMaxAcceptablePrices();
    }
    std::map<std::string, int> const & getCosts() const {
        return config_->getCosts();
    }
    int getSupplyIncrement() const {
        return config_->getSupplyIncrement();
    }
    float getPriceIncrement() const {
        return config_->getPriceIncrement();
    }
    float getPriceDecrement() const {
        return config_->getPriceDecrement();
    }
};


template <class Config, class Producer, class Consumer>
void MultipleGoodsMarket<Config, Producer, Consumer>::_setUp(Config *config) {
    config_ = config;
    producers_ = std::vector<Producer*>();
    consumers_ = std::vector<Consumer*>();

    demandFile_.open(config_->getDemandFile());
    priceFile_.open(config_->getPriceFile());
    supplyFile_.open(config_->getSupplyFile());

    std::string header = "";

    for (int i = 0; i < config_->getGoods().size(); ++i) {
        header += config_->getGoods().at(i);
        if (i != config_->getGoods().size() - 1) {
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
    for (Producer* producer : producers_) {
        sum += producer->getSupply(good);
    }
    return sum;
}


template <class Config, class Producer, class Consumer>
int MultipleGoodsMarket<Config, Producer, Consumer>::getTotalDemand() {
    int sum = 0;
    for (Consumer* consumer : consumers_) {
        sum += consumer->getDemand();
    }
    return sum;
}

template <class Config, class Producer, class Consumer>
int MultipleGoodsMarket<Config, Producer, Consumer>::getTotalSupply() {
    int sum = 0;
    for (Producer* producer : producers_) {
        sum += producer->getTotalSupply();
    }
    return sum;
}

template <class Config, class Producer, class Consumer>
Producer* MultipleGoodsMarket<Config, Producer, Consumer>::getCheapestProducerOf(const std::string &good,
                                                                                 bool ignoreZeroSupply) {
    return *std::min_element(producers_.begin(), producers_.end(), [&](Producer* p1, Producer* p2) -> bool {
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
    for (Producer* producer : producers_) {
        sum += producer->getPrice(good);
    }
    return sum / producers_.size();
}

#endif //FREEMARKET_MULTIPLEGOODSMARKET_H
