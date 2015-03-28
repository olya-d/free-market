//
// Created by Olga on 3/17/15.
//

#ifndef _FREEMARKET_SUBSTITUTESSIMULATIONCONFIG_H_
#define _FREEMARKET_SUBSTITUTESSIMULATIONCONFIG_H_

#include "../BaseSimulationConfig.h"
#include "../MultipleGoods/MultipleGoodsSimulationConfig.h"
#include <json/json.h>


class SubstitutesSimulationConfig : public MultipleGoodsSimulationConfig {
    void readConfig(std::string path);
public:
    SubstitutesSimulationConfig(std::string path_to_config);
};


#endif //_FREEMARKET_SUBSTITUTESSIMULATIONCONFIG_H_
