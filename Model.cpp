#include <cstdlib>
#include "Model.h"

void Game::begin() {
	field = new int * [field_size];
	for (int i = 0; i < field_size; i++) {
		field[i] = new int[field_size];
	}

	insert_new(field_size * field_size);
	insert_new(field_size * field_size - 1);
	score = 0;
}

int Game::make_move(int direction) {
	int tmp = move_all(direction);
	if (tmp < 0) return 1; // ничего на поле не изменилось, если move_all вернул -1

	score += tmp;
	victory = max_value() >= goal;
	int empty = empty_count();
	insert_new(empty);
	return empty > 0 || is_possible_to_move() ? 1 + victory : 0;

}

void move(int ** field, int i_from, int j_from, int i_to, int j_to) {
	field[i_to][j_to] += field[i_from][j_from];
	field[i_from][j_from] = 0;
}

int Game::move_all(int direction) {
	int score = 0;
	bool nothing_changed = true;
	for (int i = 0; i < field_size; i++) {
		int tmp = move_line(i, direction);
		if (tmp >= 0) {
			nothing_changed = false;
			score += tmp;
		}
	}

	return nothing_changed ? -1 : score;
}

int Game::max_value() {
	int max = 0;
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (max < field[i][j]) max = field[i][j];
		}
	}
	return max;
}

int Game::empty_count() {
	int count = 0;
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[i][j] == 0) count++;
		}
	}
	return count;
}

void Game::insert_new(int empty_count) {
	/*
	 * генерируется число от 0 до количества свободных клеток][при обходе всего поля новая плитка является двойкой в 90.909090% случаев][в остальных четвёркой
	*/

	int val = rand_d() < chance_of_2 ? 2 : 4;
	int tmp = (int) (rand_d() * empty_count); // на какой остановимся

	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[i][j] == 0 && !(tmp--)) {
				field[i][j] = val;
				return;
			}
		}
	}
}

bool Game::is_possible_to_move() {
	if (empty_count() > 0) return true;
	for (int i = 0; i < field_size - 1; i++) {
		for (int j = 0; j < field_size - 1; j++) {
			int cur = field[i][j];
			if (cur == field[i + 1][j] || cur == field[i][j + 1]) return true;
		}
	}
}

int Game::move_line(int line, int dir) {
	int score = 0;
	bool nothing_moved = true;
	int i = 1, p = 0;
	while (i < field_size) {
		int cur = get_cell(line, i, dir);
		int pos = get_cell(line, p, dir);

		if (i == p) {
			i++;
		} else if (cur == 0) {
			i++;
		} else if (pos == 0) {
			set_cell(line, p, dir, cur);
			set_cell(line, i, dir, 0);
			i++;
			nothing_moved = false;
		} else if (cur == pos) {
			set_cell(line, p, dir, pos + cur);
			set_cell(line, i, dir, 0);
			i++;
			p++;
			score += pos * 2;
			nothing_moved = false;
		} else {
			p++;
		}
	}
	return nothing_moved ? -1 : score;
}

int Game::get_cell(int line, int i, int direction) {
	switch (direction) {
		case 0: return field[field_size - i - 1][line];
		case 1: return field[line][i];
		case 2: return field[i][line];
		case 3: return field[line][field_size - i - 1];
	}
}

void Game::set_cell(int line, int i, int direction, int value) {
	switch (direction) {
		case 0: field[field_size - i - 1][line] = value; break;
		case 1: field[line][i] = value; break;
		case 2: field[i][line] = value; break;
		case 3: field[line][field_size - i - 1] = value; break;
	}
}