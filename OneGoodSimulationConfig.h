//
// Created by Olga on 3/22/15.
//

#ifndef _FREEMARKET_ONEGOODSIMULATIONCONFIG_H_
#define _FREEMARKET_ONEGOODSIMULATIONCONFIG_H_


#include "BaseSimulationConfig.h"
#include <json/json.h>


class OneGoodSimulationConfig : public BaseSimulationConfig {
private:
    int max_starting_profit;
    int cost;
    int max_acceptable_price;

    void readConfig(std::string path);
public:
    OneGoodSimulationConfig(std::string path_to_config);

    int getMaxStartingProfit() const {
        return max_starting_profit;
    }

    int getCost() const {
        return cost;
    }

    int getMaxAcceptablePrice() const {
        return max_acceptable_price;
    }

};


#endif //_FREEMARKET_ONEGOODSIMULATIONCONFIG_H_
