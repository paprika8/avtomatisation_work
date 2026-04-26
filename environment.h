#pragma once
#include "basket.h"
#include "basket_kit.h"
#include <math.h>

class environment {
private:
    std::vector<basket_kit> basket_kits;
    int rep_limit = 10;
    int count = 10;

    void ranging();

    void rejection();

    bool check_solution();

    void reproduction();

public:
    //static std::vector<item> buffer;

    environment(std::string file_path);

    int iteration();
};
