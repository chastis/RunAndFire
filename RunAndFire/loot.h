#ifndef LOOT_H
#define LOOT_H
#include "headers_which_you_need.h"
#include <vector>
using namespace sf;

struct point {
	float x;//320
	float y;//96
};

class Loot {
public:
	Loot(Image & image);
	void ammo_draw(RenderWindow & window);
	void ammo_add(float x, float y);
	float ammo_get_w();
	float ammo_get_h();
	void ammo_aword(int & );
	int ammo_aword();
	std::vector<point> ammos;
private:
	float ammo_w, ammo_h;
	Texture texture;
	Sprite ammo_sprite;
};

#endif
