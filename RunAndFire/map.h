#ifndef MAP_H
#define MAP_H
#include "headers_which_you_need.h"
#include <fstream>
using namespace sf;

class Map
{
public:
	Map(Image & image,int H = 15,int W = 20) {
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		h = H;
		w = W;
		tittle = new char* [h];
		std::ifstream fin("maps/map1.txt");
		for (int i = 0; i < h; i++) {
			tittle[i] = new char[w];
			for (int j = 0; j < w; j++) {
				char temp;
				fin >> temp;
				tittle[i][j] = temp;
			}
		}

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				std::cout << tittle[i][j];
			}
			std::cout << std::endl;
		}

		fin.close();
	}
	~Map() {
		delete[] tittle;
	}
	void draw_map(RenderWindow & window) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if ((tittle[i][j] == 'w')) sprite.setTextureRect(IntRect(64, 0, 32, 32));
				if ((tittle[i][j] == '0')) sprite.setTextureRect(IntRect(192, 0, 32, 32));
				if ((tittle[i][j] == 'd')) sprite.setTextureRect(IntRect(161, 0, 32, 32));
				sprite.setPosition(j * 32, i * 32);//именно такой порядок, не веришь?

				window.draw(sprite);
			}
		}
	}
	char get(int x, int y) {
		if (x < 0 || x >= h || y < 0 || y >= w) { return '0'; }
		return tittle[x][y];
	}
	int get_w() {
		return w;
	}
	int get_h() {
		return h;
	}
	void set(int x, int y, char a) {
		tittle[x][y] = a;
	}
private:
	Texture texture;
	Sprite sprite;
	int h, w;
	char ** tittle;
};

#endif

