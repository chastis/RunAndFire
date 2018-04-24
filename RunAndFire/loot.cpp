#include "loot.h"
#include <time.h>
#include <stdlib.h>
using namespace sf;
Loot::Loot(Image & image) {
	texture.loadFromImage(image);
	ammo_sprite.setTexture(texture);
	ammo_w = 32; ammo_h = 32;
	ammo_sprite.setTextureRect(IntRect(0, 0, ammo_w, ammo_h));
	ammo_sprite.setOrigin(0, 0);
}
void Loot::ammo_draw(RenderWindow & window) {
	for (int i = 0; i < ammos.size(); i++) {
		ammo_sprite.setPosition(ammos[i].x, ammos[i].y);
		window.draw(ammo_sprite);
	}
}
void Loot::ammo_add(float x, float y) {
	point temp;
	temp.x = x; temp.y = y;
	ammos.push_back(temp);
}

float Loot::ammo_get_w() {
	return ammo_w;
}

float Loot::ammo_get_h() {
	return ammo_h;
}

void Loot::ammo_aword(int & a) {
	srand(time(0));
	a += rand() % 3;
}

int Loot::ammo_aword() {
	return rand() % 3;
}