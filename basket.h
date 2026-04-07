#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

class basket;

class item {
private:
    static int target_id;

    double volume;

public:
    basket* bask;
    int id;
    item(double v) : id(target_id++) {
        volume = v;
    }

    item(const item& other);

    double get_volume() { return volume; }

    int operator == (const item& o);

    item(item&& other) noexcept;

    item& operator=(const item& other); // Копирующее присваивание невозможно из-за const id

    item& operator=(item&& other);      // Перемещающее присваивание тоже невозможно
};

class basket {
private:
    double cur_volume = 0;

public:
    std::vector<item> store;
    static double max_volume;

    basket() {};


    basket(const basket& other);

    bool put(item i);

    void clear();

    std::vector<item>& trade(basket& other);

    void remoteItem(item i);

    basket& mutate();

    double get_volume();

    basket(basket&& other);

    basket& operator=(const basket& other);

    basket& operator=(basket&& other);
};