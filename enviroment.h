#include "busket.h"

class enviroment {
private:
    int items_amount;
    std::vector<busket> buskets;

    void selection();

    void ranging();

    void rejection();

    bool check_solution();

    void reproduction();

public:
    enviroment(std::string file_path);

    void iteration();
}
