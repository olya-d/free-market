//
// Created by Olga on 3/24/15.
//

#ifndef _FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_
#define _FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_

#include "../MultipleGoods/MultipleGoodsSimulationConfig.h"
#include <json/json.h>


class ComplementsSimulationConfig : public MultipleGoodsSimulationConfig {
private:
    std::map<std::string, int> _ratios;
    void readConfig(std::string path);
public:
    ComplementsSimulationConfig(std::string path_to_config);
    std::map<std::string, int> const & getRatios() const;
};


#endif //_FREEMARKET_COMPLEMENTSSIMULATIONCONFIG_H_
