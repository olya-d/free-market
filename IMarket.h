#ifndef __FreeMarket__IMarket__
#define __FreeMarket__IMarket__

#include <stdio.h>
#include <iostream>
#include <map>


class Producer;


class IMarket {
public:
    virtual std::pair<std::string, float> maxAveragePrice() = 0;
    virtual int supply(const std::string& good) = 0;
    virtual int totalDemand() = 0;
    virtual int totalSupply() = 0;
    virtual void simulate(int times) = 0;
    virtual Producer* cheapestProducer(const std::string& good, bool ignoreZeroSupply) = 0;
    virtual std::string cheapestGood() = 0;
};

#endif /* defined(__FreeMarket__IMarket__) */
