//
// Created by Olga on 3/17/15.
//

#ifndef _FREEMARKET_ISIMULATIONCONFIG_H_
#define _FREEMARKET_ISIMULATIONCONFIG_H_

#include <iostream>
#include <json/json.h>


class BaseSimulationConfig {
private:
    int simulation_duration = 150;
    int num_of_producers = 10;
    int num_of_consumers = 10;
    int max_starting_supply = 30;
    int supply_increment = 100;
    float price_increment = 1.1f;
    float price_decrement = 0.9f;

    std::string demand_file = "demand.txt";
    std::string supply_file = "supply.csv";
    std::string price_file = "price.csv";

    virtual void readConfig(std::string path) = 0;
protected:
    void readCommonConfig(Json::Value root);

public:
    enum SimulationType {ONE_GOOD, SUBSTITUTES};

    int getSimulationDuration() const {
        return simulation_duration;
    }

    int getNumOfProducers() const {
        return num_of_producers;
    }

    int getNumOfConsumers() const {
        return num_of_consumers;
    }

    int getMaxStartingSupply() const {
        return max_starting_supply;
    }

    int getSupplyIncrement() const {
        return supply_increment;
    }

    float getPriceIncrement() const {
        return price_increment;
    }

    float getPriceDecrement() const {
        return price_decrement;
    }

    std::string &getDemandFile() {
        return demand_file;
    }

    std::string &getSupplyFile() {
        return supply_file;
    }

    std::string &getPriceFile() {
        return price_file;
    }

};


#endif //_FREEMARKET_ISIMULATIONCONFIG_H_

