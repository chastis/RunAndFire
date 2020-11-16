#ifndef LOOT_H
#define LOOT_H
#include "helpers.h"
#include "map.h"
#include <vector>
using namespace sf;

class Loot : public sf::Drawable{
public:
	Loot(Image & image);
	void ammo_add(float x, float y);
	void portal_add(float x, float y);
	Rect<float> get_rect();
	void ammo_aword(int & );
	int ammo_aword();
	std::vector<Point> ammos;
	std::vector<Point> portals;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void clear();
	void update(Map &);
private:
	float ammo_w, ammo_h;
	Texture texture;
	Sprite ammo_sprite;
};

void loot_spawn(Loot &loot, Map & map);

#endif
