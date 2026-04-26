#include "basket.h"
#include "environment.h"

double basket::max_volume = 100;

basket::basket(const basket& other)
{
    cur_volume = 0;
    store.clear();
    for (int i = 0; i < other.store.size(); ++i)
    {
        item ii = other.store[i];
        put(ii);
    }
}

basket::basket() {
}

bool basket::put(item &i) {
    if (cur_volume + i.get_volume() > max_volume) return false;
    this->store.push_back(i);
    cur_volume += i.get_volume();
    i.bask = this;
    return true;

}

void basket::clear() {
    cur_volume = 0;
    store.clear();
}

std::vector<item> basket::trade(basket& other) {
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

    this->clear();
    other.clear();
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
        cur_volume = 0;
        store.clear();
        for (int i = 0; i < other.store.size(); ++i)
        {
            item ii = other.store[i];
            put(ii);
        }
    }
    return *this;
}


// Конструктор копирования
item::item(const item& other) 
    : id(other.id)           // Новый уникальный id для копии
    , volume(other.volume)      // Копируем объем
    , bask(other.bask)          // Копируем указатель на корзину (неглубоко)
{
    // Все поля скопированы
}

// Конструктор перемещения
item::item(item&& other)
    : id(other.id)                                    // Новый id для перемещённого объекта
    , volume(std::exchange(other.volume, 0.0))          // Забираем volume, у other оставляем 0
    , bask(std::exchange(other.bask, nullptr))          // Забираем указатель, у other оставляем nullptr
{
    // Ресурсы перемещены
}
item& item::operator=(const item& other) {
    id = other.id;
    volume = other.volume;
    bask = other.bask;
    return *this;
}
item& item::operator=(item&& other) {
    id = other.id;
    volume = other.volume;
    bask = other.bask;
    return *this;
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

item::item(double v, int _id) {
    volume = v;
    id = _id;
    if(id == -1) printf("!@!@#$$\n");
}

void basket::print() {
    printf("| ");
    for(int i = 0; i < store.size(); ++i){
        printf("%d-%lf ", store[i].id, store[i].get_volume());
    }
    printf("|\n");
}
