#include "basket.h"
#include "environment.h"

double basket::max_volume = 100;

bool basket::put(item i) {
    if (cur_volume + i.get_volume() > max_volume) return false;
    this->store.push_back(i);
    cur_volume += i.get_volume();
    return true;

}

void basket::clear() {
    cur_volume = 0;
    store.clear();
}

void basket::trade(basket& other) {
    std::vector<item> items;

    for (int i = 0; i < store.size(); i++) {
        items.push_back(store[i]);
    }
    for (int i = 0; i < other.store.size(); i++) {
        items.push_back(other.store[i]);
    }

    std::random_shuffle(items.begin(), items.end(), [&items](int a) -> int {
        return rand() % items.size();
        });

    for (int i = 0; i < items.size(); i++) {
        if (!this->put(items[i]))
            if (!other.put(items[i]))
                environment::buffer.push_back(items[i]);
    }
}

basket& basket::mutate() {
    basket new_basket;

    int new_sz = rand() % store.size();

    std::random_shuffle(store.begin(), store.end(), [this](int a) -> int {
        return rand() % this->store.size();
        });

    for (int i = 0; i < new_sz; i++) {
        new_basket.put(store[i]);
    }

    return new_basket;
}

double basket::get_volume() {
    return cur_volume;
}
