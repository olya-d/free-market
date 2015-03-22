//
//  main.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#include "SimulationConfigReader.h"
#include "SubstitutesSimulationConfig.h"
#include "SubstitutesMarket.h"


int main(int argc, const char *argv[]) {
    SimulationConfigReader reader = SimulationConfigReader();
    if (reader.getSimulationType() == BaseSimulationConfig::SimulationType::SUBSTITUTES) {
        SubstitutesSimulationConfig* config = new SubstitutesSimulationConfig(reader.getPathToConfig());
        std::cout << config->getDemandFile();
        SubstitutesMarket *market = new SubstitutesMarket(config);
        market->simulate(config->getSimulationDuration());
    }

    return 0;
}
