//
//  main.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#include "SimulationConfigReader.h"
#include "OneGood/OneGoodMarket.h"
#include "Substitutes/SubstitutesMarket.h"
#include "Complements/ComplementsMarket.h"


int main(int argc, const char *argv[]) {
    SimulationConfigReader reader = SimulationConfigReader();
    if (reader.getSimulationType() == BaseSimulationConfig::SimulationType::SUBSTITUTES) {
        SubstitutesSimulationConfig* config = new SubstitutesSimulationConfig(reader.getPathToConfig());
        SubstitutesMarket *market = new SubstitutesMarket(config);
        market->simulate(config->getSimulationDuration());
    }
    if (reader.getSimulationType() == BaseSimulationConfig::SimulationType::ONE_GOOD) {
        OneGoodSimulationConfig* config = new OneGoodSimulationConfig(reader.getPathToConfig());
        OneGoodMarket* market = new OneGoodMarket(config);
        market->simulate(config->getSimulationDuration());
    }
    if (reader.getSimulationType() == BaseSimulationConfig::SimulationType::COMPLEMENTS) {
        ComplementsSimulationConfig* config = new ComplementsSimulationConfig(reader.getPathToConfig());
        ComplementsMarket* market = new ComplementsMarket(config);
        market->simulate(config->getSimulationDuration());
    }
    return 0;
}
