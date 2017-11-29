#include <iostream>
#include "Viewer.h"

void Viewer::show_field(int ** field, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int cur = field[i][j];
			std::cout << cur << "\t";
		}
		std::cout << std::endl;
	}
}
