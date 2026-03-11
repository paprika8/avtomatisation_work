#include <iostream>
#include <math.h>
#include "environment.h"
#include "basket.h"

int main(int argc, char* argv[]) {
	environment e1("input.txt");

    int res = e1.iteration();

    std::cout << "Res = " << res;
} 