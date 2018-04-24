#ifndef ENTITY_H
#define ENTITY_H
#include "map.h"
#include "Golem.h"
#include "Bullet.h"
#include <vector>
#include "headers_which_you_need.h"
using namespace sf;

//родительский класс существ
class Entity {
public:
	//Картинка; начальные координаты (x,y); размер спрайта; имя персонажа;
	Entity(Image &image, float X, float Y, int W, int H, String Name);
	void control();
	void update(float,Map &, std::vector<Golem> &);
	void check_collision(float, float,Map &);
	void check_collision(std::vector<Golem> &);
	Sprite get_sprite();
	void fire();
	void draw_bullet(float time, Map & map, RenderWindow & window, std::vector<Golem> & golems);
	bool alive();
	void Restart();
	bool empty_ammo();
private:
	std::vector<Bullet> bul;
	int health, bullets_quantity;
	enum { right, left, up, down, jump, stay } state;
	float x, y;//координаты игрока х и у
	float dx, dy, speed , static_speed, static_jump, static_g;//скорость персонажа в текущий момент относительно осей, и стандартная скорость персонажа
	int w, h;//размеры спрайта и кол-во здоровья персонажа
	bool life, onGround, is_right, space_pressed, sprite_right, with_mob;
	Texture texture;
	Sprite sprite;
	String name;
	Texture bullet_texture;
};
#endif
