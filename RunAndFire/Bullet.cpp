#include "Bullet.h"
using namespace sf;

Bullet::Bullet(Texture & texture, float X, float Y, int W, int H, String Name, bool is_right, int Key) {
	x = X; y = Y; w = W; h = H; name = Name; key = Key;
	if (is_right) dx = 0.2; else dx = -0.2;
	speed = 0.2; dy = 0;
	onGround = false;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(103, 11, w, h));
	sprite.setOrigin(w / 2, h / 2);
	sprite.setPosition(x + w / 2, y + h / 2);
}

Sprite Bullet::get_sprite() {
	return sprite;
}

int Bullet::update(float time, Map & map) {
	int temp;
	x += dx*time;
	if (check_collision(dx, 0, map) == -1) return -1;
	y += dy*time;
	if (check_collision(0, dy, map) == -1) return -1;

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	return 0;
}

int Bullet::check_collision(float dx, float dy, Map & map) {
	for (int i = y / 32; i < (y + h) / 32; i++) {
		for (int j = x / 32; j < (x + w) / 32; j++) {
			if (map.get(i, j) == 'w')
			{
				return -1;
			}
		}
	}
	return 0;
}