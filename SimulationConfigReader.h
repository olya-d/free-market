//
// Created by Olga on 3/17/15.
//

#ifndef _FREEMARKET_SIMULATIONCONFIG_H_
#define _FREEMARKET_SIMULATIONCONFIG_H_


#include <iostream>
#include "BaseSimulationConfig.h"


class SimulationConfigReader {
private:
    BaseSimulationConfig* config;
    std::string path_to_config = "config.json";
public:
    BaseSimulationConfig* getConfig();
};


#endif //_FREEMARKET_SIMULATIONCONFIG_H_
