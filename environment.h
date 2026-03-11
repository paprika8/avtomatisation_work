#pragma once
#include "basket.h"
#include <math.h>

class environment {
private:
    int items_amount;
    std::vector<basket> baskets;
    int rep_limit = 100;
    int count = 100;

    void ranging();

    void rejection();

    bool check_solution();

    void reproduction();

public:
    static std::vector<item> buffer;

    environment(std::string file_path);

    int iteration();
};
