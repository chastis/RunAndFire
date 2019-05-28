#include "map.h"

Map::Map(Image & image, int H, int W) : tittle(H, std::vector<char>(W, 0)) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	h = H;
	w = W;

	std::ifstream fin("maps/map1.txt");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			fin >> tittle[i][j];
		}
	}

	std::cout << h << " " << w << std::endl;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			std::cout << tittle[i][j];
		}
		std::cout << std::endl;
	}
	fin.close();
}

void Map::draw(RenderTarget& window, RenderStates state) const {
	auto temp_strite = sprite;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			switch (tittle[i][j]) {
			case 'w': temp_strite.setTextureRect(IntRect(64, 0, TITLE_SIZE, TITLE_SIZE)); break;
			case '0': temp_strite.setTextureRect(IntRect(192, 0, TITLE_SIZE, TITLE_SIZE)); break;
			case 'd': temp_strite.setTextureRect(IntRect(161, 0, TITLE_SIZE, TITLE_SIZE)); break;
			}
			temp_strite.setPosition(j * TITLE_SIZE, i * TITLE_SIZE);//именно такой порядок, не веришь?
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