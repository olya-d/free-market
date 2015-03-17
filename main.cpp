//
//  main.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#include "SimulationConfigReader.h"
#include "SubstitutesMarket.h"


int main(int argc, const char *argv[]) {
    SimulationConfigReader reader = SimulationConfigReader();
    BaseSimulationConfig* config = reader.getConfig();
    if (config->getSimulationType() == config->SUBSTITUTES) {
        std::cout << config->getDemandFile();
        SubstitutesMarket *market = new SubstitutesMarket();
        market->simulate(config->getSimulationDuration());
    }

    return 0;
}
