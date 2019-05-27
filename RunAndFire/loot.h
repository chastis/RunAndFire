#ifndef LOOT_H
#define LOOT_H
#include "helpers.h"
#include <vector>
using namespace sf;

class Loot : public sf::Drawable{
public:
	Loot(Image & image);
	void ammo_draw(RenderWindow & window);
	void ammo_add(float x, float y);
	Rect<float> get_rect();
	void ammo_aword(int & );
	int ammo_aword();
	std::vector<Point> ammos;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	float ammo_w, ammo_h;
	Texture texture;
	Sprite ammo_sprite;
};

#endif
