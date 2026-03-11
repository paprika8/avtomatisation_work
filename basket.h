#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

class item {
private:
    double volume;
public:
    item(double v) {
        volume = v;
    }

    double get_volume() { return volume; }
};

class basket {
private:
    double cur_volume = 0;
    std::vector<item> store;

public:
    static double max_volume;

    basket() {};

    bool put(item i);

    void clear();

    void trade(basket& other);

    basket& mutate();

    double get_volume();
};