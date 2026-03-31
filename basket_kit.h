#pragma once
#include "basket.h"
#include<map>

class basket_kit {
private:
    int items_amount;
    std::vector<basket> baskets;
    std::vector<item> items;

public:
    basket_kit(std::vector<item> items);

    int size();

    basket_kit trade(basket_kit other);

    void mutate();

    basket_kit& operator=(basket_kit& other){
        items_amount = other.items_amount;
        items = other.items;
        baskets = other.baskets;
    }


};