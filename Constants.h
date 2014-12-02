//
//  Constants.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef FreeMarket_Constants_h
#define FreeMarket_Constants_h

namespace MarketConstants {
    const int SimulationDuration = 150;
    const int NumOfProducers = 10;
    const int NumOfConsumers = 10;
    
    const int MaxStartingSupply = 20;
    const int SupplyIncrement = 80;
    
    const int Cost = 5;
    const int MaxAcceptablePrice = Cost*10;
    const int MaxStartingProfit = 5;
    const float PriceIncrement = 1.1f;
    const float PriceDecrement = 0.9f;
}

#endif
