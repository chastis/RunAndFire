#ifndef BULLET_H
#define BULLET_H
#include "map.h"
#include "Golem.h"
#include "BossGolem.h"
#include "headers_which_you_need.h"
using namespace sf;

//родительский класс существ
class Bullet {
public:
	//Картинка; начальные координаты (x,y); размер спрайта; имя персонажа;
	Bullet(Texture & texture, float X, float Y, int W, int H, String Name, bool is_righty);
	int update(float, Map &, std::vector<std::unique_ptr<Golem>> & golems);
	int check_collision(Map &);
	int Bullet::check_collision(std::vector<std::unique_ptr<Golem>> & golems);
	Sprite get_sprite();
private:
	float x, y;
	float dx, dy, speed;
	int w, h, damage;
	bool onGround;
	Sprite sprite;
	String name;
};
#endif
