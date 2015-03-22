//
// Created by Olga on 3/17/15.
//

#ifndef _FREEMARKET_SIMULATIONCONFIG_H_
#define _FREEMARKET_SIMULATIONCONFIG_H_


#include <iostream>
#include "BaseSimulationConfig.h"
#include "SubstitutesSimulationConfig.h"


class SimulationConfigReader {
private:
    BaseSimulationConfig* config;
    std::string path_to_config = "/Users/olga_andreyeva/FreeMarket/FreeMarket/config.json";
public:
    SimulationConfigReader();
    BaseSimulationConfig::SimulationType getSimulationType();
    std::string &getPathToConfig() {
        return path_to_config;
    }
};


#endif //_FREEMARKET_SIMULATIONCONFIG_H_
