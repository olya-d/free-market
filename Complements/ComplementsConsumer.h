//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSCONSUMER_H_
#define _FREEMARKET_COMPLEMENTSCONSUMER_H_


#include <string>


class ComplementsMarket;
class ComplementsProducer;


class ComplementsConsumer {
private:
    ComplementsMarket* market;
    int demand;

    int buyFromProducer(ComplementsProducer& producer, std::string good, int currentDemand);
public:
    ComplementsConsumer(ComplementsMarket* market);

    int getDemand();

    void setDemand(int d);

    void buy();
};


#endif //_FREEMARKET_COMPLEMENTSCONSUMER_H_
