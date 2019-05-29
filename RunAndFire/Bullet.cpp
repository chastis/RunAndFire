#include "Bullet.h"
using namespace sf;

Bullet::Bullet(Texture & texture, float X, float Y, int W, int H, String Name, Direcions dir) {
	x = X; y = Y; w = W; h = H; name = Name; damage = 25;
	switch (dir)
	{
	case Direcions::u:
		dy = -0.4f;
		dx = 0.f;
		sprite.rotate(-90.f);
		break;
	case Direcions::d:
		dy = 0.4f;
		dx = 0.f;
		sprite.rotate(90.f);
		break;
	case Direcions::l:
		dy = 0.f;
		dx = -0.4f;
		sprite.setScale(-1.f, 1.f);
		break;
	case Direcions::r:
		dy = 0.f;
		dx = 0.4f;
		break;
	case Direcions::ur:
		dy = -0.4f;
		dx = 0.4f;
		sprite.rotate(-45.f);
		break;
	case Direcions::ul:
		dy = -0.4f;
		dx = -0.4f;
		sprite.setScale(-1.f, 1.f);
		sprite.rotate(45.f);
		break;
	case Direcions::dr:
		dy = 0.4f;
		dx = 0.4f;
		sprite.rotate(-45.f);
		break;
	case Direcions::dl:
		dy = 0.4f;
		dx = -0.4f;
		sprite.setScale(-1.f, 1.f);
		sprite.rotate(45.f);
		break;
	}
	speed = 0.4f;
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
	x += dx * time;
	if (check_collision(map) == -1) return -1;
	if (check_collision(golems) == -1) return -1;

	y += dy * time;
	if (check_collision(map) == -1) return -1;
	if (check_collision(golems) == -1) return -1;

	sprite.setPosition(x + w / 2, y + h / 2);
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
			switch (golems[i]->get_type())
			{
			case Monsters::golem:
				if (dx > 0 && golems[i]->get_right() || dx < 0 && !golems[i]->get_right() || dx == 0) golems[i]->health = golems[i]->health - damage;
				break;
			case Monsters::bossGolem:
				if (dx == 0) golems[i]->health = golems[i]->health - damage;
				break;
			case Monsters::none:
				break;
			}
			return -1;
		}
	}
	return 0;
}