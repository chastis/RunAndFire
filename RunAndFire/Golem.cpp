#include "Golem.h"
using namespace sf;

Golem::Golem(Image &image, float X, float Y, int W, int H, String Name) : Monster(image, X, Y, W, H, Name) {
	sprite.setTextureRect(IntRect(130, 3, w, h));
	dx = -dx;
	is_right = 0;
	damage = GOLEM_DMG;
}

void Golem::set(Image &image, float X, float Y, int W, int H, String Name){
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0.05f; health = 50; dx = -0.05f; dy = 0.f; damage = GOLEM_DMG;
	life = true; onGround = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(x + w / 2, x + h / 2);

	sprite.setTextureRect(IntRect(130, 3, w, h));
	is_right = 0;
}

void Golem::update(float time, Map & map)
{

	x += dx*time;
	check_collision(dx, 0, map);
	y += dy*time;
	check_collision(0, dy, map);

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	if (health <= 0) { life = false; }
	//speed = 0;
	dy = dy + 0.0015f * time;//постоянно притягиваемся к земле
}

void Golem::check_collision(float dx, float dy, Map & map) {
	try
	{
		for (int i = y / TITLE_SIZE; i < (y + h) / TITLE_SIZE; i++) {
			for (int j = x / TITLE_SIZE; j < (x + w) / TITLE_SIZE; j++) {
				if (map[i][j] == 'w')
				{
					if (dy > 0)
					{
						y = i * TITLE_SIZE - h;
						this->dy = 0;
						onGround = true;
					}
					if (dy < 0)
					{
						y = i * TITLE_SIZE + TITLE_SIZE;
					}
					if (dx > 0)
					{
						x = j * TITLE_SIZE - w;
						change_direction();
					}
					if (dx < 0)
					{
						x = j * TITLE_SIZE + TITLE_SIZE;
						change_direction();
					}
				}
			}
		}
	}
	catch (...)
	{
		return;
	}
}

void Golem::change_direction() {
	dx = -dx;
	sprite.scale(-1, 1);
	is_right = !is_right;
}

bool Golem::get_right() {
	return is_right;
}