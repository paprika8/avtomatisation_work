#include "basket.h"
#include "environment.h"

double basket::max_volume = 100;
int item::target_id = 1;

basket::basket(const basket& other)
    : cur_volume(other.cur_volume)
    , store(other.store)  // Вектор копируется (глубокая копия всех item)
{
    // При копировании вектора вызывается конструктор копирования item,
    // который создаёт новые id для каждого скопированного item
}

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

std::vector<item> &basket::trade(basket& other) {
    std::vector<item> buffer;
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
                buffer.push_back(items[i]);
    }
    return buffer;
}

void basket::remoteItem(item i) {
    store.erase(std::find(store.begin(), store.end(), i));
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


basket& basket::operator=(const basket& other) {
    if (this != &other) {
        cur_volume = other.cur_volume;
        store = other.store;  // При копировании вектора вызывается конструктор копирования item
    }
    return *this;
}


// Конструктор копирования
item::item(const item& other) 
    : id(target_id++)           // Новый уникальный id для копии
    , volume(other.volume)      // Копируем объем
    , bask(other.bask)          // Копируем указатель на корзину (неглубоко)
{
    // Все поля скопированы
}

// Конструктор перемещения
item::item(item&& other)
    : id(target_id++)                                    // Новый id для перемещённого объекта
    , volume(std::exchange(other.volume, 0.0))          // Забираем volume, у other оставляем 0
    , bask(std::exchange(other.bask, nullptr))          // Забираем указатель, у other оставляем nullptr
{
    // Ресурсы перемещены
}
item& item::operator=(const item& other) {
    id = other.id;
    volume = other.volume;
    bask = other.bask;
}
item& item::operator=(item&& other) {
    id = other.id;
    volume = other.volume;
    bask = other.bask;
}
int item::operator==(const item& o) {
    return id == o.id;
}

basket::basket(basket&& other)
    : cur_volume(std::exchange(other.cur_volume, 0))
    , store(std::move(other.store))
{
    // other.cur_volume теперь 0
    // other.store теперь пуст
}

basket& basket::operator=(basket&& other) {
    if (this != &other) {
        cur_volume = std::exchange(other.cur_volume, 0);
        store = std::move(other.store);
    }
    return *this;
}