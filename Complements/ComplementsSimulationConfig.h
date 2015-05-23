//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_
#define _FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_

#include "../BaseSimulationConfig.h"
#include <json/json.h>


// Reads and stores configuration for the market of complementary goods.
class ComplementsSimulationConfig : public BaseSimulationConfig {
private:
    std::vector<std::string> goods_;
    std::map<std::string, int> max_starting_profits_;
    std::map<std::string, int> max_acceptable_prices_;
    std::map<std::string, int> costs_;
    std::map<std::string, int> ratios_;

    void readConfig(std::string path);

public:
    ComplementsSimulationConfig(std::string path_to_config);

    std::vector<std::string> const &getGoods() const {
        return goods_;
    }

    std::map<std::string, int> const &getMaxStartingProfits() const {
        return max_starting_profits_;
    }

    std::map<std::string, int> const &getMaxAcceptablePrices() const {
        return max_acceptable_prices_;
    }

    std::map<std::string, int> const &getCosts() const {
        return costs_;
    }

    std::map<std::string, int> const &getRatios() const {
        return ratios_;
    }
};


#endif //_FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_