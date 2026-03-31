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

basket_kit basket_kit::trade(basket_kit other) {
    basket_kit buffer = other;

    for (int i = 0; i < baskets.size() / 2; i++) {
        basket best1 = this->baskets[i];

        other.baskets.push_back(basket());
        basket* bask = &other.baskets[other.baskets.size() - 1];
        for (int i = 0; i < best1.store.size(); i++) {

            int id1 = best1.store[i].id;
            item other_i = other.items[id1];
            other_i.bask->remoteItem(other_i);
            bask->put(other_i);
        }
    }
    for (int i = 0; i < buffer.baskets.size() / 2; i++) {
        basket best1 = buffer.baskets[i];

        baskets.push_back(basket());
        basket* bask = &baskets[other.baskets.size() - 1];
        for (int i = 0; i < best1.store.size(); i++) {

            int id1 = best1.store[i].id;
            item other_i = items[id1];
            other_i.bask->remoteItem(other_i);
            bask->put(other_i);
        }
    }
}

void basket_kit::mutate() {
    int bask1_i = rand() % baskets.size();
    int bask2_i = rand() % baskets.size();

    basket buffer; 
    std::vector<item> buf_items = baskets[bask1_i].trade(baskets[bask2_i]);

    buffer.store = buf_items;

}
