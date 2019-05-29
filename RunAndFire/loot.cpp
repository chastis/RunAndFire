#include "loot.h"

using namespace sf;

Loot::Loot(Image & image) {
	texture.loadFromImage(image);
	ammo_sprite.setTexture(texture);
	ammo_w = TITLE_SIZE; ammo_h = TITLE_SIZE;
	ammo_sprite.setTextureRect(IntRect(0, 0, static_cast<int>(ammo_w), static_cast<int>(ammo_h)));
	ammo_sprite.setOrigin(0, 0);
}

void Loot::ammo_add(float x, float y) {
	ammos.emplace_back(x, y);
}


Rect<float> Loot::get_rect()
{
	auto pos = ammo_sprite.getPosition();
	return Rect<float>(pos.x, pos.y, ammo_w, ammo_h);
}

void Loot::ammo_aword(int & a) {
	std::default_random_engine dre(std::random_device{}());
	std::uniform_int_distribution<int> uid(1, 3);
	a += uid(dre);
}

int Loot::ammo_aword() {
	return rand() % 3;
}

void Loot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	auto temp = ammo_sprite;
	for (size_t i = 0; i < ammos.size(); i++) {
		temp.setPosition(ammos[i].x, ammos[i].y);
		target.draw(temp, states);
	}
}

void Loot::clear()
{
	ammos.clear();
}