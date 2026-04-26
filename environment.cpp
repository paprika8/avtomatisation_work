#include "environment.h"

#define LOFFSET log(RAND_MAX)
double getLrand(double l) {
    return (log(rand() + 1) - LOFFSET) / (-l);
}

void environment::ranging() {
    int n = basket_kits.size();
    for (int i = 0; i < n - 1; i++) {
        // Флаг для оптимизации: если обмена не было, массив уже отсортирован
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (basket_kits[j].size() > basket_kits[j + 1].size()) {
                // Меняем элементы местами
                std::swap(basket_kits[j], basket_kits[j + 1]);
                swapped = true;
            }
        }
        
        // Если за проход ни одного обмена не было — массив отсортирован
        if (!swapped) break;
    }
//    std::sort(basket_kits.begin(), basket_kits.end(), [](basket_kit &b1, basket_kit &b2) -> int {
//        return b2.size() - b1.size();
//        });
}

void environment::rejection() {
    for (int i = basket_kits.size() - 1; i >= rep_limit; i--) {
        basket_kits.pop_back();
    }
}

bool environment::check_solution() {
    return count;
}


void environment::reproduction() {
    for (int i = 0; i < rep_limit; i++) {
        int index1 = 0; // TO DO: random
        int index2 = 1;

        std::pair<basket_kit, basket_kit> new_ans = basket_kits[index1].trade(basket_kits[index2]);
        basket_kits.push_back(new_ans.first);
        basket_kits.push_back(new_ans.second);
    }
}


environment::environment(std::string file_path) {
    int items_amount;
    FILE* file = fopen(file_path.c_str(), "r");
    fscanf(file, "%lf", &basket::max_volume);
    fscanf(file, "%d", &items_amount);

    std::vector<item> items;
    for (int i = 0; i < items_amount; i++) {
        double volume;
        fscanf(file, "%lf", &volume);
        items.push_back(volume);
        items[i].id = i;
    }

    int kit_amount;
    fscanf(file, "%d", &kit_amount);
    for (int i = 0; i < kit_amount; i++) {
        basket_kits.push_back(basket_kit(items));
    }
}

int environment::iteration() {
    int min_basket_amount = basket_kits[0].size();
    basket_kit min_basket_kit = basket_kits[0];
    ranging();

    while (check_solution()) {
        reproduction();
        for (int i = 0; i< 10; i++){
            int index = rand() % basket_kits.size();
            basket_kits[index].mutate();
        }
        for (int i = 0; i< basket_kits.size(); i++){
            basket_kits[i].validate();
        }
        ranging();
        rejection();
        printf(" ==ITERATION %d==\n", count);
        for (int i = 0; i < basket_kits.size(); i++) {
            basket_kits[0].print();
        }

        if (basket_kits[0].size() < min_basket_amount) {
                min_basket_amount = basket_kits[0].size();
                min_basket_kit = basket_kits[0];
            }

        count--;
    }

    printf("Best kit!!!\n");
    min_basket_kit.print();
    return min_basket_amount;
}
