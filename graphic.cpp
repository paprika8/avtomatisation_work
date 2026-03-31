/*#include <iostream>
#include <math.h>

#include "easy_plot.hpp"

void example(int argc, char* argv[]){
	printf("Hello word");
	ep::init(&argc, argv);

	std::vector<double> x = { 0, 1, 0, 1, 2, 0, 1 };
	ep::plot("X", x);

	// ставим красный цвет линии
	std::vector<double> y = { 0, 2, 3, 4, 2, 0, 1 };
	ep::plot("Y", y, ep::LineSpec(1, 0, 0));

	std::vector<double> x2 = { 0, 2, 6, 7, 8, 10, 12 };
	ep::plot("XY", x2, y, ep::LineSpec(1, 1, 0));

	ep::WindowSpec wstyle; // тут можно настроить стиль графика (цвет фона и пр.)
	// выводим три графика в одном
	ep::plot<double>("Y1Y2Y3", wstyle, 3, x, ep::LineSpec(1, 0, 0), x2, ep::LineSpec(1, 0, 1), y, ep::LineSpec(0, 1, 0));

	while (easy_plot::tools::Drawing::drawings.size()) { // ожидание окон графиков
		std::this_thread::yield();
	}
}*/