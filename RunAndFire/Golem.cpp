#include "Golem.h"
using namespace sf;

Golem::Golem(Image &image, float X, float Y, int W, int H, String Name) : Monster(image, X, Y, W, H, Name) {
	sprite.setTextureRect(IntRect(130, 3, w, h));
}


void Golem::update(float time, Map & map) {

	x += dx*time;
	check_collision(dx, 0, map);
	y += dy*time;
	check_collision(0, dy, map);

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	if (health <= 0) { life = false; }
	//speed = 0;
	dy = dy + 0.0015*time;//постоянно притягиваемся к земле
}

void Golem::check_collision(float dx, float dy, Map & map) {
	for (int i = y / 32; i < (y + h) / 32; i++) {
		for (int j = x / 32; j < (x + w) / 32; j++) {
			if (map.get(i, j) == 'w')
			{
				if (dy>0)
				{
					y = i * 32 - h;
					this->dy = 0;
					onGround = true;
				}
				if (dy<0)
				{
					y = i * 32 + 32;
				}
				if (dx>0)
				{
					x = j * 32 - w;
					this->dx = -speed;
				}
				if (dx < 0)
				{
					x = j * 32 + 32;
					this->dx = speed;
				}
			}
		}
	}
}