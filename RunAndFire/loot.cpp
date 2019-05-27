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
	Point temp;
	temp.x = x; temp.y = y;
	ammos.push_back(temp);
}


Rect<float> Loot::get_rect()
{
	auto pos = ammo_sprite.getPosition();
	return Rect<float>(pos.x, pos.y, ammo_w, ammo_h);
}

void Loot::ammo_aword(int & a) {
	srand(time(0));
	a += 1 + rand() % 3;
}

int Loot::ammo_aword() {
	return rand() % 3;
}

void Loot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	auto temp = ammo_sprite;
	for (int i = 0; i < ammos.size(); i++) {
		temp.setPosition(ammos[i].x, ammos[i].y);
		target.draw(temp, states);
	}
}
