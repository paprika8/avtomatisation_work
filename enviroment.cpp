#include "enviroment.h"

void enviroment::selection() {

}

void enviroment::ranging() {

}

void enviroment::rejection() {

}

bool enviroment::check_solution() {
    return false;
}

void enviroment::reproduction() {

}

enviroment::enviroment(std::string file_path) {
    FILE* file = fopen(file_path.c_str(), "r");
    fscanf(file, "%llf", &busket::max_volume);
    fscanf(file, "%d", &items_amount);
    for (int i = 0; i < items_amount; i++) {
        double volume;
        fscanf(file, "%llf", volume);
        busket b;
        b.put(volume); // Неявно создается объект item
        buskets.push_back(b);
    }
}

void enviroment::iteration() {
    if (!check_solution()) {
        return;
    }

    ranging();

    rejection();

    reproduction();

}
