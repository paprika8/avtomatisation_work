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

extern std::vector<item> buffer;

class busket {
private:
    double cur_volume = 0;
    std::vector<item> store;

public:
    static double max_volume;

    busket() {};

    bool put(item i);

    void trade(busket& other);

    busket& mutate();
}