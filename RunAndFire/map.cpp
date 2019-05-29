#include "map.h"

Map::Map(Image & image, int H, int W) : tittle(H, std::vector<char>(W, 0)) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	h = H;
	w = W;

	//auto start = std::chrono::high_resolution_clock::now();
	std::ifstream fin("maps/map1.txt");
	for (int i = 0; i < h; i++) {
		std::string line;
		std::getline(fin, line);
		for (int j = 0; j < w; j++) {
			tittle[i][j] = line[j];
			//fin >> tittle[i][j];
		}
	}

	std::cout << h << " " << w << std::endl;
	std::string str;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			str.push_back(tittle[i][j]);
			//std::cout << tittle[i][j];
		}
		//std::cout << std::endl;
		str.push_back('\n');
	}
	std::cout << str;

	//auto finish = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
	//std::cout << "map loaded in " << finish.count() << " ms" << std::endl;
	fin.close();
}

void Map::draw(RenderTarget& window, RenderStates state) const {
	auto temp_strite = sprite;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			switch (tittle[i][j]) {
			case 'w': temp_strite.setTextureRect(IntRect(0, 0, TITLE_SIZE, TITLE_SIZE)); break;
			case '0': temp_strite.setTextureRect(IntRect(81, 0, TITLE_SIZE, TITLE_SIZE)); break;
			case 'd': temp_strite.setTextureRect(IntRect(49, 0, TITLE_SIZE, TITLE_SIZE)); break;
			case 'b': temp_strite.setTextureRect(IntRect(65, 0, TITLE_SIZE, TITLE_SIZE)); break;
			case 'p': temp_strite.setTextureRect(IntRect(81, 0, TITLE_SIZE, TITLE_SIZE)); break;
			case 's': temp_strite.setTextureRect(IntRect(33, 0, TITLE_SIZE, TITLE_SIZE)); break;
			}
			temp_strite.setPosition(static_cast<float>(j * TITLE_SIZE), static_cast<float>(i * TITLE_SIZE));//именно такой порядок, не веришь?
			window.draw(temp_strite);
		}
	}
}

int Map::get_w() {
	return w;
}

int Map::get_h() {
	return h;
}

std::vector<char>& Map::operator[](size_t index) {
	if (index >= tittle.size() || index < 0) throw std::length_error(std::to_string(index) + " is bigger than size of map");
	return tittle[index];
}