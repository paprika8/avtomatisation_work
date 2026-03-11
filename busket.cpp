#include "busket.h"

std::vector<item> buffer;

bool busket::put(item i) {
    if (cur_volume + i.get_volume() > max_volume) return false;
    this->store.push_back(i);
    return true;

}

void busket::trade(busket& other) {
    std::vector<item> items;

    for (int i = 0; i < store.size(); i++) {
        items.push_back(store[i]);
    }
    for (int i = 0; i < other.store.size(); i++) {
        items.push_back(other.store[i]);
    }

    std::_Random_shuffle1(items.begin(), items.end(), [&items]() -> int {
        return rand() % items.size();
        });

    for (int i = 0; i < items.size(); i++) {
        if (!this->put(items[i]))
            if (!other.put(items[i]))
                buffer.push_back(items[i]);
    }
}

busket& busket::mutate() {
    busket new_busket;

    int new_sz = rand() % store.size();

    std::_Random_shuffle1(store.begin(), store.end(), [this]() -> int {
        return rand() % this->store.size();
        });

    for (int i = 0; i < new_sz; i++) {
        new_busket.put(store[i]);
    }

    return new_busket;
}
