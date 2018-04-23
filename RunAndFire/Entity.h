#ifndef ENTITY_H
#define ENTITY_H
#include "headers_which_you_need.h"
using namespace sf;

//родительский класс существ
class Entity {
public:
	//Картинка; начальные координаты (x,y); размер спрайта; имя персонажа;
	Entity(Image &image, float X, float Y, int W, int H, String Name);
	Sprite get_sprite();
	void control();
	void update(float);
private:
	enum { right, left, up, down, jump, stay } state;
	float x, y;//координаты игрока х и у
	float dx, dy, speed;//скорость персонажа в текущий момент относительно осей, и стандартная скорость персонажа
	int w, h, health;//размеры спрайта и кол-во здоровья персонажа
	bool life, onGround;
	Texture texture;
	Sprite sprite;
	String name;
};
#endif
