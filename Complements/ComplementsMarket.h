//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSMARKET_H_
#define _FREEMARKET_COMPLEMENTSMARKET_H_


#include <fstream>
#include "../MultipleGoods/MultipleGoodsMarket.h"
#include "ComplementsSimulationConfig.h"
#include "ComplementsProducer.h"
#include "ComplementsConsumer.h"


// Simulation of the market of perfect complements.
class ComplementsMarket :
        public MultipleGoodsMarket<ComplementsSimulationConfig, ComplementsProducer, ComplementsConsumer> {
public:
    // Constructor generates consumers and producers,
    // prices and supplies of each good for each producer, using config.json file.
    // Supply is set uniformly between 0 and max_starting supply,
    // price - between cost of the good and cost + max_starting_profit.
    ComplementsMarket(ComplementsSimulationConfig* config);
    // Simulation consists of the following steps:
    // 1. Generate demand_ using periodic function (sinf(i) + 2)*20. TODO: custom functions in the config.json
    // 2. Output values of demand_, supply and prices to the standard output and to the files
    // (demandFile_, supplyFile_ and priceFile_ in MultipleGoodsMarket). TODO: separate functions to specify the output of data.
    // 3. Producers produce.
    // 4. Customers buy.
    // 5. Producers change pricing and generate goods.
    void simulate(int times) override;
    // Returns total supply as the number of "total goods"
    // (the maximum value among total supply of the good divided by the ratio of the good for each good).
    int getTotalSupply() override;
    // Returns the maximum price among the producers for the good.
    float getMaxPriceOf(const std::string &good);

    std::vector<ComplementsProducer*> &getProducers()  {
        return producers_;
    }

    std::map<std::string, int> const &getRatios() const {
        return config_->getRatios();
    }
};


#endif //_FREEMARKET_COMPLEMENTSMARKET_H_
