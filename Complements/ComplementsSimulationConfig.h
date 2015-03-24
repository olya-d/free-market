//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_
#define _FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_

#include "../BaseSimulationConfig.h"
#include <json/json.h>


class ComplementsSimulationConfig : public BaseSimulationConfig {
private:
    std::vector<std::string> goods;
    std::map<std::string, int> max_starting_profits;
    std::map<std::string, int> max_acceptable_prices;
    std::map<std::string, int> costs;
    std::map<std::string, int> ratios;

    void readConfig(std::string path);

public:
    ComplementsSimulationConfig(std::string path_to_config);

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

    std::map<std::string, int> const &getRatios() const {
        return ratios;
    }
};


#endif //_FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_
