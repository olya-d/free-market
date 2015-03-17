//
// Created by Olga on 3/17/15.
//

#ifndef _FREEMARKET_SUBSTITUTESSIMULATIONCONFIG_H_
#define _FREEMARKET_SUBSTITUTESSIMULATIONCONFIG_H_

#include "BaseSimulationConfig.h"
#include <json/json.h>


class SubstitutesSimulationConfig : public BaseSimulationConfig {
private:
    std::vector<std::string> goods;
    std::map<std::string, int> max_starting_profits;
    std::map<std::string, int> max_acceptable_prices;
    std::map<std::string, int> costs;

    void readConfig(std::string path);

public:
    SimulationType getSimulationType() {
        return SimulationType::SUBSTITUTES;
    }

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


#endif //_FREEMARKET_SUBSTITUTESSIMULATIONCONFIG_H_
