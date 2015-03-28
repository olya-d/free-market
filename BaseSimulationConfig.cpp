#include "BaseSimulationConfig.h"


void BaseSimulationConfig::readCommonConfig(Json::Value root) {
    simulation_duration = root.get("duration", simulation_duration).asInt();
    num_of_producers = root.get("number_of_producers", num_of_producers).asInt();
    max_starting_supply = root.get("max_starting_supply", max_starting_supply).asInt();
    supply_increment = root.get("supply_increment", supply_increment).asInt();
    price_increment = root.get("price_increment", price_increment).asFloat();
    price_decrement = root.get("price_decrement", price_decrement).asFloat();
    num_of_consumers = root.get("number_of_consumers", num_of_consumers).asInt();
    demand_file = root.get("demand_file", demand_file).asString();
    supply_file = root.get("supply_file", supply_file).asString();
    price_file = root.get("price_file", price_file).asString();
}

void BaseSimulationConfig::argumentMissingExit(std::string name) {
    std::cout << "Please specify key \"" << name << "\" in the configuration file (config.json by default)";
    exit(1);
}