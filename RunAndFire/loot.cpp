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

void Loot::portal_add(float x, float y) {
	portals.emplace_back(x, y);
}

Rect<float> Loot::get_rect()
{
	auto pos = ammo_sprite.getPosition();
	return Rect<float>(pos.x, pos.y, ammo_w, ammo_h);
}

void Loot::ammo_aword(int & a) {
	std::default_random_engine dre(std::random_device{}());
	std::uniform_int_distribution<int> uid(level_counter, 2 + level_counter);
	a += uid(dre);
}

int Loot::ammo_aword() {
	return (rand() % 3)* level_counter;
}

void Loot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	auto temp = ammo_sprite;
	for (size_t i = 0; i < ammos.size(); i++) {
		temp.setPosition(ammos[i].x, ammos[i].y);
		target.draw(temp, states);
	}
	temp.setTextureRect(IntRect(16, 0, ammo_w, ammo_h));
	for (size_t i = 0; i < portals.size(); i++) {
		temp.setPosition(portals[i].x, portals[i].y);
		target.draw(temp, states);
	}
	temp.setTextureRect(IntRect(0, 0, ammo_w, ammo_h));
}

void Loot::clear() {
	ammos.clear();
	portals.clear();
}

void Loot::update(Map & map) {
	for (size_t i = 0; i < ammos.size(); i++)
	{
		if (map[static_cast<int>(ammos[i].y + ammo_h) / TITLE_SIZE][static_cast<int>(ammos[i].x + ammo_w / 2) / TITLE_SIZE] != 'w')
			if (map[static_cast<int>(ammos[i].y + ammo_h) / TITLE_SIZE][static_cast<int>(ammos[i].x + ammo_w / 2) / TITLE_SIZE] != 's')
			{
				if (map[static_cast<int>(ammos[i].y + ammo_h) / TITLE_SIZE][static_cast<int>(ammos[i].x + ammo_w / 2) / TITLE_SIZE] != 'v' ||
					map[static_cast<int>(ammos[i].y + ammo_h) / TITLE_SIZE][static_cast<int>(ammos[i].x + ammo_w / 2) / TITLE_SIZE] == 'v' && map.isInter())
				{
					ammos[i].y += 0.1;
				}
			
			}
		
		
		
	}
	for (size_t i = 0; i < portals.size(); i++)
	{
		if (map[static_cast<int>(portals[i].y + ammo_h) / TITLE_SIZE][static_cast<int>(portals[i].x + ammo_w / 2) / TITLE_SIZE] != 'w')
			if (map[static_cast<int>(portals[i].y + ammo_h) / TITLE_SIZE][static_cast<int>(portals[i].x + ammo_w / 2) / TITLE_SIZE] != 's')
			{
				if (map[static_cast<int>(portals[i].y + ammo_h) / TITLE_SIZE][static_cast<int>(portals[i].x + ammo_w / 2) / TITLE_SIZE] != 'v' ||
					map[static_cast<int>(portals[i].y + ammo_h) / TITLE_SIZE][static_cast<int>(portals[i].x + ammo_w / 2) / TITLE_SIZE] == 'v' && map.isInter())
				{
					portals[i].y += 0.1;
				}
			
			}
		
	}
}

void loot_spawn(Loot &loot, Map & map)
{
	loot.clear();
	for (int i = 0; i < map.get_h(); i++) {
		for (int j = 0; j < map.get_w(); j++) {
			if (map[i][j] == 'l')
			{
				loot.ammo_add(j * TITLE_SIZE, (i - 2) * TITLE_SIZE);
			}
		}
	}
}