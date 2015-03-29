//
//  Market.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__SubstitutesMarket__
#define __FreeMarket__SubstitutesMarket__

#include <stdio.h>
#include <vector>
#include <fstream>
#include "SubstitutesSimulationConfig.h"
#include "../MultipleGoods/MultipleGoodsMarket.h"
#include "SubstitutesConsumer.h"


// Simulates the market of substitutes.
class SubstitutesMarket :
        public MultipleGoodsMarket<SubstitutesSimulationConfig, SubstitutesProducer, SubstitutesConsumer> {
public:
    // Constructor generates consumers and producers,
    // prices and supplies of each good for each producer, using config.json file.
    // Supply is set uniformly between 0 and max_starting supply,
    // price - between cost of the good and cost + max_starting_profit.
    SubstitutesMarket(SubstitutesSimulationConfig *config);
    // Returns the good with maximum average price.
    std::pair<std::string, float> maxAveragePrice();
    // Simulation consists of the following steps:
    // 1. Generate demand_ using periodic function (sinf(i) + 2)*20. TODO: custom functions in the config.json
    // 2. Output values of demand_, supply and prices to the standard output and to the files
    // (demandFile_, supplyFile_ and priceFile_ in MultipleGoodsMarket). TODO: separate functions to specify the output of data.
    // 3. Producers produce.
    // 4. Find the cheapest good.
    // 5. While there is some demand and supply of the cheapest good, consumers buy.
    // 6. Producers change pricing and generate goods.
    // TODO: unify with complements simulation and put in MultipleGoodsMarket implementation.
    void simulate(int times) override;
    int getTotalSupply() override;
    // Returns the cheapest good with non-zero supply.
    std::string cheapestGood();
};


#endif /* defined(__FreeMarket__SubstitutesMarket__) */
