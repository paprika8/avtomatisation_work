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
    const int id;
    item(double v) : id(target_id++) {
        volume = v;
    }

    double get_volume() { return volume; }

    int operator == (item& o);
};

class basket {
private:
    double cur_volume = 0;

public:
    std::vector<item> store;
    static double max_volume;

    basket() {};

    bool put(item i);
    bool swap(item i, item other);

    void clear();

    std::vector<item>& trade(basket& other);

    void remoteItem(item i);

    basket& mutate();

    double get_volume();
};