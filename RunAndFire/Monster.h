#ifndef MONSTER_H
#define MONSTER_H
#include "map.h"
#include "headers_which_you_need.h"
using namespace sf;

//родительский класс существ
class Monster {
public:
	int health;
	//Картинка; начальные координаты (x,y); размер спрайта; имя персонажа;
	Monster(Image &image, float X, float Y, int W, int H, String Name);
	Sprite get_sprite();
	float get_x();
	float get_y();
	int get_w();
	int get_h();
	bool get_life();
	int get_damage();
	Monsters get_type();
	//virtual void spawm_loot() = 0;
protected:
	float x, y;
	float dx, dy, speed;
	int w, h;
	int damage;
	bool life, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	LootType loot;
	Monsters type;
};
#endif
