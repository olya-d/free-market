//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSCONSUMER_H_
#define _FREEMARKET_COMPLEMENTSCONSUMER_H_


#include <string>


class ComplementsMarket;
class ComplementsProducer;


// Simulates the behaviour of a consumer in a market of perfect complementary goods.
class ComplementsConsumer {
private:
    // Used to access configuration of the market (e.g. maximum acceptable prices for consumers)
    ComplementsMarket* market_;
    // Demand of the consumer - number of "total goods" the consumer wants to buy.
    // For example, if the ratios are 2 and 3, and demand_ equals to 4, then the consumer
    // wants to buy 8 units of the first good and 12 units of the second good.
    int demand_;

    // Buy as much as possible from the producer, but not exceeding currentDemand, decreasing
    // the supply of producer.
    // Returns the number of units of the good bought.
    int buyFromProducer(ComplementsProducer& producer, std::string good, int currentDemand);
public:
    ComplementsConsumer(ComplementsMarket* market);
    // Performs one buying round.
    // For each good consumer tries to satisfy his/her demand_ by sequentially selecting the cheapest producer,
    // and then buying the maximum amount keeping the ratio of complementary goods.
    // Say there is good1 and good2 and the ratios are 1 and 2. If the customer can buy 10 units of good1 and
    // 15 units of good2, he/she will buy 7 units of good1 and 14 units of good2.
    void buy();


    int getDemand() const {
        return demand_;
    };
    void setDemand(int d) {
        demand_ = d;
    }
};


#endif //_FREEMARKET_COMPLEMENTSCONSUMER_H_
