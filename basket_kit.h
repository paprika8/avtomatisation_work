#pragma once
#include "basket.h"

class basket_kit {
private:
    int items_amount;
    std::vector<basket> baskets;

public:
    basket_kit(std::vector<item> items);

    int size();

    basket_kit trade(basket_kit other);
}