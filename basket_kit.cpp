#include "basket_kit.h"
#include <math.h>

basket_kit::basket_kit(std::vector<item> items) {
    std::random_shuffle(items.begin(), items.end(), [&items](int a) -> int {
        return rand() % items.size();
        });

    for (int i = 0; i <= items.size(); i++) {
        if (baskets.size() == 0 || !baskets.back().put(items[i])) {
            baskets.push_back(basket());
            baskets.back().put(items[i]);
        }
    }
}

int basket_kit::size() {
    return baskets.size();
}
