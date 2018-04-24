#ifndef BULLET_H
#define BULLET_H
#include "map.h"
#include "headers_which_you_need.h"
using namespace sf;

//родительский класс существ
class Bullet {
public:
	//Картинка; начальные координаты (x,y); размер спрайта; имя персонажа;
	Bullet(Texture & texture, float X, float Y, int W, int H, String Name, bool is_right, int key);
	int update(float, Map &);
	int check_collision(float, float, Map &);
	Sprite get_sprite();
private:
	float x, y;
	float dx, dy, speed;
	int w, h, key;
	bool onGround;
	Sprite sprite;
	String name;
};
#endif
