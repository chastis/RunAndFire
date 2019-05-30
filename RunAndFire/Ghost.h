#ifndef GHOST_H
#define GHOST_H
#include "map.h"
#include "Monster.h"
#include "headers_which_you_need.h"
#include "functions.h"
using namespace sf;

class BadBullet
{
public:
	BadBullet(Texture &, float X, float Y);
	void update(float, Map &, float, float);
	Sprite getSprite();
//private:
	float x, y;
	int w, h;
	float speed;
	Sprite sprite;
};

//родительский класс существ
class Ghost : public Monster {
public:
	//Картинка; начальные координаты (x,y); размер спрайта; имя персонажа;
	Ghost(Image &image, float X, float Y, int W, int H, String Name);
	virtual ~Ghost() = default;
	virtual void update(float, Map &, float, float);
	void check_collision(float, float, Map &);
	void change_direction();
	void set(Image &image, float X, float Y, int W, int H, String Name);
	void draw(RenderWindow & window);
	bool get_right();
	float stepChange;
	void damaged();
	bool checkBullets(float heroX, float heroY, int heroW, int heroH);
	bool isDamaged();
private:
	bool weak;
	int sign;
	bool is_right;
	Clock timer;
	Texture bullet_texture;
	std::vector<BadBullet> bullets;
};

void ghosts_spawn(Image &image, int W, int H, std::vector<std::unique_ptr<Ghost>> &, Map &);
#endif
