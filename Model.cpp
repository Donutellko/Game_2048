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
	score += move_all(direction);

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
	int new_scores = 0;
	for (int i = 0; i < field_size; i++) {
		move_line(i, direction);
	}

	return new_scores;
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
	double rand1 = 0.19, rand2 = 0.5; // TODO

	int val = rand1 < chance_of_2 ? 2 : 4;
	int tmp = (int) (rand2 * empty_count); // на какой остановимся

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
	return false;
}

void Game::move_line(int line, int dir) {
	int i = 1, p = 0;
	while (i < field_size) {
		int cur = get_cell(line, i, dir);
		int pos = get_cell(line, p, dir);

		if (cur == 0) i++;
		else if (pos == 0) {
			set_cell(line, p, dir, cur);
			set_cell(line, i, dir, 0);
			i++;
		} else if (cur == pos) {
			set_cell(line, p, dir, pos + cur);
			set_cell(line, i, dir, 0);
			i++;
			p++;
		} else {
			p++;
			continue;
		}
	}
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
		case 0: field[field_size - i - 1][line] = value;
		case 1: field[line][i] = value;
		case 2: field[i][line] = value;
		case 3: field[line][field_size - i - 1] = value;
	}
}