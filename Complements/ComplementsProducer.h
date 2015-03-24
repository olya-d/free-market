//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSPRODUCER_H_
#define _FREEMARKET_COMPLEMENTSPRODUCER_H_


#include <map>


class ComplementsMarket;

class ComplementsProducer {
private:
    std::map<std::string, int> supplies;

    std::map<std::string, float> prices;
    ComplementsMarket* market;



public:
    ComplementsProducer(ComplementsMarket* market);

    void setSupply(const std::string& good, int s);
    void setPrice(const std::string& good, float p);

    int getSupply(const std::string& good) const;
    float getPrice(const std::string& good) const;

    void generateGoods();
    void changePricing();
    void produce();

    std::map<std::string, int> getSupplies() {
        return supplies;
    }

    std::map<std::string, float> const &getPrices() const {
        return prices;
    }

};


#endif //_FREEMARKET_COMPLEMENTSPRODUCER_H_
