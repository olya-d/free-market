//
//  Constants.h
//  FreeMarket
//
//  Created by Olga on 03.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__Constants__
#define __FreeMarket__Constants__

#include <iostream>
#include <map>
#include <vector>


namespace MarketConstants {
    extern int SimulationDuration;
    extern int NumOfProducers;
    extern int NumOfConsumers;

    extern int MaxStartingSupply;
    extern int SupplyIncrement;

    extern std::vector<std::string> Goods;
    extern std::map<std::string, int> Costs;
    extern std::map<std::string, int> MaxAcceptablePrices;
    extern std::map<std::string, int> MaxStartingProfits;
    extern float PriceIncrement;
    extern float PriceDecrement;

    extern std::string DemandFile;
    extern std::string SupplyFile;
    extern std::string PriceFile;
}


#endif /* defined(__FreeMarket__Constants__) */
