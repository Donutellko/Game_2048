#include <iostream>
#include "Model.h"
#include "Viewer.h"

int size = 10;
int goal = 2048;

int main() {

	Game game(size, goal);

	game.begin();

	int prev_result = -1;
	while (prev_result) {
		Viewer().show_field(game.get_field(), size);

		int dir;
		char dir_c;
		std::cin >> dir_c;
		dir_c = tolower(dir_c);
		switch (dir_c) {
			case 'w': dir = 0; break;
			case 'd': dir = 1; break;
			case 's': dir = 2; break;
			case 'a': dir = 3; break;
			default: continue;
		}
		prev_result = game.make_move(dir);
	}

	std::cout << std::endl << "Игра завершилась. " << (game.get_victory() ? "Победа! " : "Поражение! ") << "Очков: " << game.get_score();

	return 0;
}