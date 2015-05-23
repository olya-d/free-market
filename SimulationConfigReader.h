//
// Created by Olga on 3/17/15.
//

#ifndef _FREEMARKET_SIMULATIONCONFIG_H_
#define _FREEMARKET_SIMULATIONCONFIG_H_


#include "BaseSimulationConfig.h"


// Determines the type of simulation.
class SimulationConfigReader {
private:
    std::string path_to_config = "config.json";
    BaseSimulationConfig::SimulationType simulationType;
public:
    SimulationConfigReader();
    BaseSimulationConfig::SimulationType getSimulationType() {
        return simulationType;
    }
    std::string &getPathToConfig() {
        return path_to_config;
    }
};


#endif //_FREEMARKET_SIMULATIONCONFIG_H_
