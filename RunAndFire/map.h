#ifndef MAP_H
#define MAP_H
#include "helpers.h"
using namespace sf;

class Map
{
public:
	Map(Image & image,int H = 15,int W = 20) : tittle(H, std::vector<char>(W, 0)){
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		h = H;
		w = W;
		//tittle = new char* [h];

		std::ifstream fin("maps/map1.txt");
		for (int i = 0; i < h; i++) {
			//tittle[i] = new char[w];
			for (int j = 0; j < w; j++) {
				//char temp;
				//fin >> temp;
				fin >> tittle[i][j];
				//tittle[i][j] = temp;
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
	/*~Map() {
		delete[] tittle;
	}*/

	~Map() = default;

	void draw_map(RenderWindow & window) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				switch (tittle[i][j]) {
				case 'w': sprite.setTextureRect(IntRect(64, 0, TITLE_SIZE, TITLE_SIZE)); break;
				case '0': sprite.setTextureRect(IntRect(192, 0, TITLE_SIZE, TITLE_SIZE)); break;
				case 'd': sprite.setTextureRect(IntRect(161, 0, TITLE_SIZE, TITLE_SIZE)); break;
				}
				/*if ((tittle[i][j] == 'w')) sprite.setTextureRect(IntRect(64, 0, 32, 32));
				if ((tittle[i][j] == '0')) sprite.setTextureRect(IntRect(192, 0, 32, 32));
				if ((tittle[i][j] == 'd')) sprite.setTextureRect(IntRect(161, 0, 32, 32));*/
				sprite.setPosition(j * TITLE_SIZE, i * TITLE_SIZE);//именно такой порядок, не веришь?

				window.draw(sprite);
			}
		}
	}
	/*char get(int x, int y) {
		if (x < 0 || x >= h || y < 0 || y >= w) { return '0'; }
		return tittle[x][y];
	}*/
	int get_w() {
		return w;
	}
	int get_h() {
		return h;
	}
	/*void set(int x, int y, char a) {
		tittle[x][y] = a;
	}*/
	std::vector<char>& operator[](size_t index) {
		if (index >= tittle.size() || index < 0) throw std::length_error(std::to_string(index) + " is bigger than size of map");
		return tittle[index];
	}
private:
	Texture texture;
	Sprite sprite;
	int h, w;
	//char ** tittle;
	std::vector<std::vector<char>> tittle;
};

#endif

