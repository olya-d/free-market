//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSPRODUCER_H_
#define _FREEMARKET_COMPLEMENTSPRODUCER_H_


#include <map>


class ComplementsMarket;

// Simulates the behaviour of producer in the market of complementary goods.
class ComplementsProducer {
private:
    // The number of items sold in the current iteration for each good.
    std::map<std::string, int> lastSold_;
    // The number of items available for sell for each good.
    std::map<std::string, int> supplies_;
    // Current prices.
    std::map<std::string, float> prices_;
    // Used to access configuration and the current state of the market (e.g. current average prices).
    ComplementsMarket* market_;

public:
    ComplementsProducer(ComplementsMarket* market);
    // Sell q items of the good (decrease supplies_[good], increase lastSold_[good] by q).
    void sell(const std::string &good, int q);
    // Producer changes pricing according to the following rules:
    // 1. If the leftover supply is non-zero, and the price of good set by producer
    // is greater than the cost of the good, decrement the price by multiplying by market.price_decrement.
    // 2. If the leftover supply is zero, and the number of goods that was sold is non-zero,
    // increment the price by multiplying by market.price_increment.
    void changePricing();
    // Producer generates goods according to the following rules:
    // 1. Increase supply of each good up to the number of sold items in the current iteration.
    // 2. Find the good with maximum profit (= average price - cost) and increase its supply
    // by market.supply_increment.
    // THIS METHOD SHOULD BE CALLED AFTER changePricing().
    // TODO: implement one method that will perform both change of prices and generation of goods by (probably), calculating and storing needed parameters in the market before each call to this method.
    // REMARK: this method will create more and more items of each good.
    void generateGoods();
    // Ask if this producer has sold any number of the good in this iteration.
    bool hasSoldGood(const std::string& good);
    // Prepare the producer to the next iteration (set lastSold_ to 0).
    // TODO: incorporate this method somehow in one `produce` method of the producer.
    void prepare();

    void setSupply(const std::string& good, int s);
    void setPrice(const std::string& good, float p);
    int getSupply(const std::string& good) const;
    float getPrice(const std::string& good) const;
};


#endif //_FREEMARKET_COMPLEMENTSPRODUCER_H_
