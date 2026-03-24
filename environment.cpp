#include "environment.h"

#define LOFFSET log(RAND_MAX)
double getLrand(double l) {
    return (log(rand() + 1) - LOFFSET) / (-l);
}

void environment::ranging() {
    std::sort(basket_kits.begin(), basket_kits.end(), [](basket_kit b1, basket_kit b2) -> {
        return b2.size() - b1.size();
    })
}

void environment::rejection() {
    for (int i = basket_kits.size() - 1; i >= rep_limit; i--) {
        basket_kits.pop_back();
    }
}

bool environment::check_solution() {
    return count;
}


void environment::reproduction() {
    for (int i = 0; i < rep_limit; i++) {
        int index1 = 0; // TO DO: random
        int index2 = 1;

        basket_kit new_ans = basket_kits[index1].trade(basket_kits[index2]);
        basket_kits.push_back(new_ans);
    }
}


environment::environment(std::string file_path) {
    int items_amount;
    FILE* file = fopen(file_path.c_str(), "r");
    fscanf(file, "%llf", &basket::max_volume);
    fscanf(file, "%d", &items_amount);

    std::vector<item> items;
    for (int i = 0; i < items_amount; i++) {
        double volume;
        fscanf(file, "%llf", &volume);
        items.push_back(volume);
    }

    int kit_amount;
    fscanf(file, "%d", &kit_amount);
    for (int i = 0; i < kit_amount; i++) {
        basket_kits.push_back(basket_kit(items));
    }
}

int environment::iteration() {
    int min_basket_amount = basket_kits.size();
    ranging();

    while (check_solution()) {
        reproduction();
        ranging();
        rejection();
        if (basket_kits.size() < min_basket_amount) {
            min_basket_amount = basket_kits.size();
        }
        count--;
    }

    return min_basket_amount;
}
