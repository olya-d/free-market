//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSPRODUCER_H_
#define _FREEMARKET_COMPLEMENTSPRODUCER_H_


#include <map>


class ComplementsMarket;

class ComplementsProducer {
private:
    std::map<std::string, int> lastSold;
    std::map<std::string, int> supplies;

    std::map<std::string, float> prices;
    ComplementsMarket* market;


public:
    ComplementsProducer(ComplementsMarket* market);

    void setSupply(const std::string& good, int s);
    void setPrice(const std::string& good, float p);
    void buyFrom(const std::string& good, int q);

    int getSupply(const std::string& good) const;
    float getPrice(const std::string& good) const;

    void generateGoods();
    void changePricing();
    bool hasSoldGood(const std::string& good);
    void prepare();
    void produce();

};


#endif //_FREEMARKET_COMPLEMENTSPRODUCER_H_
