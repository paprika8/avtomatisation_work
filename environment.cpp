#include "environment.h"

#define LOFFSET log(RAND_MAX)
double getLrand(double l) {
    return (log(rand() + 1) - LOFFSET) / (-l);
}

std::vector<item> environment::buffer;

void environment::ranging() {
    std::sort(baskets.begin(), baskets.end(), [](basket b1, basket b2) -> int {
        return b1.get_volume() - b2.get_volume();
        });
}

void environment::rejection() {
    for (int i = baskets.size() - 1; i >= 0; i--) {
        if (baskets[i].get_volume() == 0) {
            baskets.erase(baskets.begin() + i);
        }
    }
}

bool environment::check_solution() {
    return !count;
}

void environment::reproduction() {
    for (int i = 0; i < rep_limit; i++) {
        basket b1 = baskets[getLrand(baskets.size())];
        basket b2 = baskets[getLrand(baskets.size())];

        b1.trade(b2);
    }
}

environment::environment(std::string file_path) {
    FILE* file = fopen(file_path.c_str(), "r");
    fscanf(file, "%llf", &basket::max_volume);
    fscanf(file, "%d", &items_amount);
    for (int i = 0; i < items_amount; i++) {
        double volume;
        fscanf(file, "%llf", volume);
        basket b;
        b.put(volume); // Неявно создается объект item
        baskets.push_back(b);
    }
}

int environment::iteration() {
    int min_basket_amount = baskets.size();

    while (check_solution()) {
        ranging();

        reproduction();

        rejection();
        if (baskets.size() < min_basket_amount) {
            min_basket_amount = baskets.size();
        }
        count--;
    }

    return min_basket_amount;
}
