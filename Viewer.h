
class Viewer {
public:
	static void show_field(int ** field, int size);

	static void test(int ** field, int size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				std::cout << field[i][j] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

};