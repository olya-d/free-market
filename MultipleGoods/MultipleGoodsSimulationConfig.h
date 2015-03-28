//
// Created by Olga on 3/28/15.
//

#ifndef FREEMARKET_MULTIPLEGOODSSIMULATIONCONFIG_H
#define FREEMARKET_MULTIPLEGOODSSIMULATIONCONFIG_H

#include "../BaseSimulationConfig.h"
#include <json/json.h>


class MultipleGoodsSimulationConfig : public BaseSimulationConfig {
protected:
    std::vector<std::string> goods;
    std::map<std::string, int> max_starting_profits;
    std::map<std::string, int> max_acceptable_prices;
    std::map<std::string, int> costs;

    void readMultipleGoodsConfig(Json::Value root);
public:
    std::vector<std::string> const &getGoods() const {
        return goods;
    }

    std::map<std::string, int> const &getMaxStartingProfits() const {
        return max_starting_profits;
    }

    std::map<std::string, int> const &getMaxAcceptablePrices() const {
        return max_acceptable_prices;
    }

    std::map<std::string, int> const &getCosts() const {
        return costs;
    }

};

#endif //FREEMARKET_MULTIPLEGOODSSIMULATIONCONFIG_H
