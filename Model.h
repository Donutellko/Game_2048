/*
 * Directions: 0-down, 1-left, 2-up, 3-right
 */

#include "Field.cpp"

class Game {
private:
	const double chance_of_2 = 0.909090909; // Шанс выпадения двойки, иначе четвёрка

	int field_size; // Размер поля NxN
	int goal; // Количество очков, необходимое для победы
	Field field = 0; // Массив игрового поля
	bool victory = false;

	int score = 0;

	int move_all(int direction); // Смещает все фишки в указанном направлении, возвращает количество начисленных очков

	void insert_new(int empty_count); // Генерирует новую фишку на случайном пустом месте по переданному количеству пустых

	int max_value(); // определяет наибольшее значение на поле
	int empty_count(); // определяет количество пустых клеток
	bool is_possible_to_move();

public:
	Game(int size, int goal) {
		this->field_size = size;
		this->goal = goal;
	}

	void begin(); // Метод создаёт поле и генерирует исходное состояние

	int make_move(int direction); // Метод, осуществляющий выполнения хода. Возвращает 0-закончилась, 1-продолжается, 2-победа

	int ** get_field() { return field.get(); }
	int get_size() { return field_size; }
	int get_score() { return score; }
	bool get_victory() { return victory; }

	~Game() {
		delete &field;
	}

	int move_line(int i, int dir);
};
