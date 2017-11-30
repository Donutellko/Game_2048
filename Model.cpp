#include <cstdlib>
#include "Model.h"

void Game::begin() {
	field = Field(field_size);

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
			if (max < field.get(i, j)) max = field.get(i, j);
		}
	}
	return max;
}

int Game::empty_count() {
	int count = 0;
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field.get(i, j) == 0) count++;
		}
	}
	return count;
}

void Game::insert_new(int empty_count) {
	/*
	 * генерируется число от 0 до количества свободных клеток, при обходе всего поля новая плитка является двойкой в 90.909090% случаев, в остальных четвёркой
	*/
	double
			rand1 = ((double)rand()) / RAND_MAX,
			rand2 = ((double)rand()) / RAND_MAX; // рандом от 0 до 1

	int val = rand1 < chance_of_2 ? 2 : 4;
	int tmp = (int) (rand2 * empty_count); // на какой остановимся

	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field.get(i, j) == 0 && !(tmp--)) {
				field.set(i, j, val);
				return;
			}
		}
	}
}

bool Game::is_possible_to_move() {
	if (empty_count() > 0) return true;
	for (int i = 0; i < field_size - 1; i++) {
		for (int j = 0; j < field_size - 1; j++) {
			int cur = field.get(i, j);
			if (cur == field.get(i + 1, j) || cur == field.get(i, j + 1)) return true;
		}
	}
}

int Game::move_line(int line, int dir) {
	int score = 0;
	bool nothing_moved = true;
	int i = 1, p = 0;
	while (i < field_size) {
		int cur = field.get(line, i, dir);
		int pos = field.get(line, p, dir);

		if (i == p) {
			i++;
		} else if (cur == 0) {
			i++;
		} else if (pos == 0) {
			field.set(line, p, dir, cur);
			field.set(line, i, dir, 0);
			i++;
			nothing_moved = false;
		} else if (cur == pos) {
			field.set(line, p, dir, pos + cur);
			field.set(line, i, dir, 0);
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


