#include "Bullet.h"
using namespace sf;

Bullet::Bullet(Texture & texture, float X, float Y, int W, int H, String Name, bool is_right) {
	x = X; y = Y; w = W; h = H; name = Name; damage = 25;
	if (is_right) dx = 0.2f; else { dx = -0.2f; sprite.scale(-1.f, 1.f); }
	speed = 0.2f; dy = 0.f;
	onGround = false;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(280, 215, w, h));
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(x + w / 2.f, y + h / 2.f);
}

Sprite Bullet::get_sprite() {
	return sprite;
}

int Bullet::update(float time, Map & map, std::vector<std::unique_ptr<Golem>> & golems) {
	x += dx*time;
	if (check_collision(map) == -1) return -1;
	if (check_collision(golems) == -1) return -1;

	y += dy*time;
	if (check_collision(map) == -1) return -1;
	if (check_collision(golems) == -1) return -1;

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	return 0;
}

int Bullet::check_collision(Map & map) {
	try {
		for (int i = static_cast<int>(y / TITLE_SIZE); i < (y + h) / TITLE_SIZE; i++) {
			if (i < 0 || i >= map.get_h()) continue;
			for (int j = static_cast<int>(x / TITLE_SIZE); j < (x + w) / TITLE_SIZE; j++) {
				if (j < 0 || j >= map.get_w()) continue;
				if (map[i][j] == 'w')
				{
					return -1;
				}
			}
		}
	}
	catch (...) {
		return -1;
	}

	

	return 0;
}

int Bullet::check_collision(std::vector<std::unique_ptr<Golem>> & golems) {
	for (size_t i = 0; i < golems.size(); i++) {
		if (x >= golems[i]->get_x() && x <= golems[i]->get_x() + golems[i]->get_w() &&
			y >= golems[i]->get_y() && y <= golems[i]->get_y() + golems[i]->get_h()) {
			if (dx > 0 && golems[i]->get_right() || dx < 0 && !golems[i]->get_right()) golems[i]->health = golems[i]->health - damage;
			return -1;
		}
	}
	return 0;
}