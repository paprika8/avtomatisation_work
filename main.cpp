#include <iostream>
#include <math.h>
#include "environment.h"
#include "basket.h"

int main(int argc, char* argv[]) {

    basket::max_volume = 10;

    std::vector<item> v;


    item i1 = 3; i1.id = 0;
    item i2 = 4; i2.id = 1;
    item i3 = 5; i3.id = 2;
    item i4 = 6; i4.id = 3;

    v.push_back(i1);
    v.push_back(i2);
    v.push_back(i3);
    v.push_back(i4);

    basket_kit bask(v);
    basket_kit bask2(v);
    std::vector<basket_kit>basket_kits;

    basket_kits.push_back(basket_kit(v));

    int res1 = bask.baskets[0]->get_volume();
    int res2 = bask2.baskets[0]->get_volume();

    std::cout << "Res = " << res1 << "  " << res2;

    auto r = bask.trade(bask2);

    res1 = r.first.baskets[0]->get_volume();
    res2 = r.second.baskets[0]->get_volume();

    std::cout << "Res = " << res1 << "  " << res2;

	environment e1("input.txt");

    int res = e1.iteration();

    std::cout << "Res = " << res;
} 