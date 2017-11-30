#include <cstdlib>
#include <iostream>
#include <termios.h>
#include "Model.h"
#include "Viewer.h"

int size = 4;
int goal = 2048;

void set_keypress(void);
void reset_keypress(void);
static struct termios stored_settings;

int main() { // программа правильно работает при запуске в терминале, но может и в дебаге.

	std::cout << "Размер поля: ";
	std::cin >> size;

	set_keypress();

	Game game(size, goal);

	game.begin();

	Viewer().show_field(game.get_field(), game.get_size(), game.get_score());

	int prev_result = -1;
	while (prev_result) {

		int dir;
		char dir_c;
		std::cin >> dir_c;

		switch (dir_c) {
			case 'w': case 'A': dir = 2; break;
			case 'd': case 'C': dir = 3; break;
			case 's': case 'B': dir = 0; break;
			case 'a': case 'D': dir = 1; break;
			default: continue;
		}
		prev_result = game.make_move(dir);

		std::cout << std::endl << "\t";
		Viewer().show_field(game.get_field(), game.get_size(), game.get_score());
	}

	std::cout << std::endl << "Игра завершилась. " << (game.get_victory() ? "Победа! " : "Поражение! ") << "Очков: " << game.get_score();

	return 0;
}

void set_keypress(void) { // Устанавливает ввод одного символа за раз (без нажатия Enter)
	struct termios new_settings;

	tcgetattr(0,&stored_settings);

	new_settings = stored_settings;

	/* Disable canonical mode, and set buffer size to 1 byte */
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;

	tcsetattr(0,TCSANOW,&new_settings);
	return;
}

void reset_keypress(void) { // отменяет действие set_keypressed
	tcsetattr(0,TCSANOW,&stored_settings);
	return;
}