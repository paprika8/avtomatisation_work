#pragma once
#include "basket.h"
#include<map>
#include <utility>

class basket_kit {
private:
    std::vector<item> items;

public:
    std::vector<basket*> baskets;
    
    basket_kit(std::vector<item> items);

    basket_kit(const basket_kit& other);

    basket_kit(basket_kit &&other);

    int size();

    std::pair<basket_kit, basket_kit> trade(basket_kit other);

    void mutate();

    void validate();

    basket_kit& operator=(basket_kit& other);

    basket_kit& operator=(basket_kit&& other);

    void print();
};