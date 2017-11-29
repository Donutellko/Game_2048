#include <iostream>
#include "Viewer.h"

void Viewer::show_field(int ** field, int size) {
	std::cout << std::endl;
	std::cout << "┌────────────────────────┐" << std::endl;

	for (int i = 0; i < size; i++) {
	std::cout << "│";
		for (int j = 0; j < size; j++) {
			int cur = field[i][j];
			if (cur == 0) {
				std::cout << "      ";
			} else {
				if (cur < 10) std::cout << "   ";
				else if (cur < 1000) std::cout << "  ";
				else std::cout << " ";
				std::cout << cur;
				if (cur < 100) std::cout << "  ";
				else std::cout << " ";

				// for (int t = cur; t < 1000; t *= 10) std::cout << " ";
			}

		}
		std::cout << "│" << std::endl;
	}
	std::cout << "└────────────────────────┘" << std::endl;
}

void Viewer::show_field(int ** field, int size, int score) {
	system("clear");
	std::cout << "Score: " << score << std::endl;
	show_field(field, size);
}
