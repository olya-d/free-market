//
//  main.cpp
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#include "Market.h"

int main(int argc, const char * argv[]) {
    Market* market = new Market();
    market->simulate(200);
    
    return 0;
}
