//
//  Producer.h
//  FreeMarket
//
//  Created by Olga on 02.12.14.
//  Copyright (c) 2014 My Organization Name. All rights reserved.
//

#ifndef __FreeMarket__Producer__
#define __FreeMarket__Producer__

#include <stdio.h>

class Producer {
private:
    int supply;
    float price;
    
    void generateGoods();
    
public:
    Producer();
    
    int getSupply();
    float getPrice();
    
    void setSupply(int s);
    void setPrice(float p);
    
    void produce();
};

#endif /* defined(__FreeMarket__Producer__) */
