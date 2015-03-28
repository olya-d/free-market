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


class SubstitutesMarket :
        public MultipleGoodsMarket<SubstitutesSimulationConfig, SubstitutesProducer, SubstitutesConsumer> {
public:
    SubstitutesMarket(SubstitutesSimulationConfig *config);
    std::pair<std::string, float> maxAveragePrice();
    void simulate(int times) override;
    int getTotalSupply() override;
    std::string cheapestGood();
};


#endif /* defined(__FreeMarket__SubstitutesMarket__) */
