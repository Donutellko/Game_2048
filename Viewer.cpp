#include <iostream>
#include "Viewer.h"

void Viewer::show_field(int ** field, int size) {
	std::cout << std::endl;

	std::cout << "╔";
	for (int i = 0; i < size; i++)
		if (i > 0) std::cout << "╤══════";
		else std::cout << "══════";
	std::cout << "╗" << std::endl;

	for (int i = 0; i < size; i++) {

		if (i != 0) {
			std::cout << "║" << std::endl;
			std::cout << "╟";
			for (int i = 0; i < size; i++)
				if (i > 0) std::cout << "┼──────";
				else std::cout << "──────";
			std::cout << "╢" << std::endl;
		}

		std::cout << "║";
		for (int j = 0; j < size; j++) {
			int cur = field[i][j];
			if (j != 0) std::cout << "│";
			if (cur == 0) {
				std::cout << "      ";
			} else {
				if (cur < 10) std::cout << "   ";
				else if (cur < 1000) std::cout << "  ";
				else std::cout << " ";

				switch (cur) {
					case 2   : std::cout << "\033[1;31m"; break;
					case 4   : std::cout << "\033[1;32m"; break;
					case 8   : std::cout << "\033[1;33m"; break;
					case 16  : std::cout << "\033[1;34m"; break;
					case 32  : std::cout << "\033[1;35m"; break;
					case 64  : std::cout << "\033[1;36m"; break;
					case 128 : std::cout << "\033[1;31m"; break;
					case 256 : std::cout << "\033[1;32m"; break;
					case 512 : std::cout << "\033[1;33m"; break;
					case 1024: std::cout << "\033[1;34m"; break;
					case 2048: std::cout << "\033[1;35m"; break;
				}


				std::cout << cur;
				if (cur < 100) std::cout << "  ";
				else std::cout << " ";

				// for (int t = cur; t < 1000; t *= 10) std::cout << " ";
			}

		}
	}
	std::cout << "║" << std::endl;
	std:: cout << "╚";
	for (int i = 0; i < size; i++)
		if (i > 0) std::cout << "╧══════";
		else std::cout << "══════";
	std::cout << "╝" << std::endl;
}
//┌─┐
//└─┘"
void Viewer::show_field(int ** field, int size, int score) {
	system("clear");
	std::cout << "Score: " << score << std::endl;
	show_field(field, size);
}
