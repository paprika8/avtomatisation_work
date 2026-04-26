#include "basket_kit.h"
#include <math.h>

basket_kit::basket_kit(std::vector<item> items) {
    this->items = items;
    std::random_shuffle(items.begin(), items.end(), [&items](int a) -> int {
        return rand() % items.size();
        });

    for (int i = 0; i < items.size(); i++) {
        if (baskets.size() == 0 || !baskets.back()->put(items[i])) {
            baskets.push_back(new basket());
            baskets.back()->put(items[i]);
        }
    }
}

basket_kit::basket_kit(const basket_kit& other)
{
    this->items = other.items;
    for (int i = 0; i < other.baskets.size(); i++) {
        basket* buf = new basket();
        for(int j = 0; j < other.baskets[i]->store.size(); ++j)
            buf->put(items[other.baskets[i]->store[j].id]);
        baskets.push_back(buf);
    }
}

basket_kit::basket_kit(basket_kit&& other)
{
    baskets = std::move(other.baskets);
    items = std::move(other.items);
}

int basket_kit::size() {
    return baskets.size();
}

std::pair<basket_kit, basket_kit> basket_kit::trade(basket_kit other) {
    basket_kit buffer = other;
    basket_kit buffer2 = *this;

    for (int i = 0; i < baskets.size() / 2; i++) {
        basket *best1 = this->baskets[i];

        buffer.baskets.push_back(new basket());
        basket* bask = buffer.baskets[buffer.baskets.size() - 1];
        for (int i = 0; i < best1->store.size(); i++) {

            int id1 = best1->store[i].id;
            item other_i = buffer.items[id1];
            other_i.bask->remoteItem(other_i);
            bask->put(other_i);
        }
    }
    for (int i = 0; i < other.baskets.size() / 2; i++) {
        basket *best1 = other.baskets[i];

        buffer2.baskets.push_back(new basket());
        basket* bask = buffer2.baskets[buffer2.baskets.size() - 1];
        for (int i = 0; i < best1->store.size(); i++) {

            int id1 = best1->store[i].id;
            item other_i = buffer2.items[id1];
            other_i.bask->remoteItem(other_i);
            bask->put(other_i);
        }
    }
    return std::pair(buffer, buffer2);
}

void basket_kit::mutate() {

    int bask1_i = rand() % baskets.size();
    int bask2_i;
    do {
        bask2_i = rand() % baskets.size();
    } while (bask1_i == bask2_i);

    basket *buffer = new basket();
    std::vector<item> buf_items = baskets[bask1_i]->trade(*baskets[bask2_i]);
    if (buf_items.empty()) return;

    buffer->store = buf_items;
    baskets.push_back(buffer);

}

void basket_kit::validate() {
    for (int i = baskets.size() - 1; i >= 0; --i) {
        if (baskets[i]->get_volume() == 0) {
            delete baskets[i];
            baskets.erase(baskets.begin() + i);
        }
    }
}

basket_kit& basket_kit::operator=(basket_kit& other) {
    for(int i = 0; i < baskets.size(); ++i) delete baskets[i];
    baskets.clear();
    this->items = other.items;
    for (int i = 0; i < other.baskets.size(); i++) {
        basket* buf = new basket();
        for(int j = 0; j < other.baskets[i]->store.size(); ++j)
            buf->put(items[other.baskets[i]->store[j].id]);
        baskets.push_back(buf);
    }
    return *this;
}

basket_kit& basket_kit::operator=(basket_kit&& other) {
    if (this != &other) {
        baskets = std::move(other.baskets);
        items = std::move(other.items);
    }
    return *this;
}

void basket_kit::print() {
    printf("=======================\n");
    for(int i = 0; i < baskets.size(); ++i){
        baskets[i]->print();
    }
    printf("=======================\n");
}
