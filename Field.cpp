class Field {

private:
	int ** field;
	int size;
public:

	Field(int size) {
		this->size = size;
		field = new int * [size];
		for (int i = 0; i < size; i++) {
			field[i] = new int[size];
		}
	}

	int ** get() {
		return field;
	}


	void set(int i, int j, int direction, int value) {
		*coord(i, j, direction) = value;
	}

	void set(int i, int j, int value) {
		field[i][j] = value;
	}

	int get(int i, int j, int direction) {
		return *coord(i, j, direction);
	}

	int get(int i, int j) {
		return field[i][j];
	}

	int * coord(int i, int j, int direction) {
		switch (direction) {
			case 0: return &field[size - j - 1][i];
			case 1: return &field[i][j];
			case 2: return &field[j][i];
			case 3: return &field[i][size - j - 1];
		}
	}
	~Field() {
		for (int i = 0; i < size; i++) {
			delete[] field[i];
		}
		delete[] field;
	}
};