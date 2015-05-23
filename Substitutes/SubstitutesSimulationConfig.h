//
// Created by Olga on 3/17/15.
//

#ifndef _FREEMARKET_SUBSTITUTESSIMULATIONCONFIG_H_
#define _FREEMARKET_SUBSTITUTESSIMULATIONCONFIG_H_

#include "../BaseSimulationConfig.h"
#include <json/json.h>


// Reads and stores configuration for the market of substitutes.
class SubstitutesSimulationConfig : public BaseSimulationConfig {
private:
    std::vector<std::string> goods;
    std::map<std::string, int> max_starting_profits;
    std::map<std::string, int> max_acceptable_prices;
    std::map<std::string, int> costs;

    void argumentMissingExit(std::string name);
    void readConfig(std::string path);

public:
    SubstitutesSimulationConfig(std::string path_to_config);

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