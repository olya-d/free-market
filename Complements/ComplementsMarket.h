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


class ComplementsMarket :
        public MultipleGoodsMarket<ComplementsSimulationConfig, ComplementsProducer, ComplementsConsumer> {
public:
    ComplementsMarket(ComplementsSimulationConfig* config);
    void simulate(int times) override;
    int getTotalSupply() override;
    float getMaxPriceOf(const std::string &good);

    std::vector<ComplementsProducer*> &getProducers()  {
        return _producers;
    }

    std::map<std::string, int> const &getRatios() const {
        return _config->getRatios();
    }
};


#endif //_FREEMARKET_COMPLEMENTSMARKET_H_
