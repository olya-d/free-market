//
// Created by Olga on 3/17/15.
//

#include "SubstitutesSimulationConfig.h"
#include <fstream>


SubstitutesSimulationConfig::SubstitutesSimulationConfig(std::string path_to_config) {
    readConfig(path_to_config);
}

void SubstitutesSimulationConfig::readConfig(std::string path) {
   readMultipleGoodsConfig(path);
}
