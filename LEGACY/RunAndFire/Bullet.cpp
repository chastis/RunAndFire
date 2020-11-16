#include "Bullet.h"
using namespace sf;

Bullet::Bullet(Texture & texture, float X, float Y, int W, int H, String Name, Directions dir) {
	x = X; y = Y; w = W; h = H; name = Name; damage = 25;
	switch (dir)
	{
	case Directions::u:
		dy = -0.4f;
		dx = 0.f;
		sprite.rotate(-90.f);
		break;
	case Directions::d:
		dy = 0.4f;
		dx = 0.f;
		sprite.rotate(90.f);
		break;
	case Directions::l:
		dy = 0.f;
		dx = -0.4f;
		sprite.setScale(-1.f, 1.f);
		break;
	case Directions::r:
		dy = 0.f;
		dx = 0.4f;
		break;
	case Directions::ur:
		dy = -0.4f;
		dx = 0.4f;
		sprite.rotate(-45.f);
		break;
	case Directions::ul:
		dy = -0.4f;
		dx = -0.4f;
		sprite.setScale(-1.f, 1.f);
		sprite.rotate(45.f);
		break;
	case Directions::dr:
		dy = 0.4f;
		dx = 0.4f;
		sprite.rotate(-45.f);
		break;
	case Directions::dl:
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

int Bullet::update(float time, Map & map, std::vector<std::unique_ptr<Golem>> & golems, std::vector<std::unique_ptr<Ghost>> & ghosts) {
	x += dx * time;
	if (check_collision(map) == -1) return -1;
	if (check_collision(golems, ghosts) == -1) return -1;

	y += dy * time;
	if (check_collision(map) == -1) return -1;
	if (check_collision(golems, ghosts) == -1) return -1;

	sprite.setPosition(x + w / 2, y + h / 2);
	return 0;
}

int Bullet::check_collision(Map & map) {
	try {
		for (int i = static_cast<int>(y / TITLE_SIZE); i < (y + h) / TITLE_SIZE; i++) {
			if (i < 0 || i >= map.get_h()) continue;
			for (int j = static_cast<int>(x / TITLE_SIZE); j < (x + w) / TITLE_SIZE; j++) {
				if (j < 0 || j >= map.get_w()) continue;
				if (map[i][j] == 'w' || map[i][j] == 'v' && !map.isInter())
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

int Bullet::check_collision(std::vector<std::unique_ptr<Golem>> & golems, std::vector<std::unique_ptr<Ghost>> & ghosts) {
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
	for (size_t i = 0; i < ghosts.size(); i++) {
		if (ghosts[i]->isDamaged() &&
			x >= ghosts[i]->get_x() && x <= ghosts[i]->get_x() + ghosts[i]->get_w() &&
			y >= ghosts[i]->get_y() && y <= ghosts[i]->get_y() + ghosts[i]->get_h()) {
			ghosts[i]->health -= damage;
			if (ghosts[i]->get_type() == Monsters::bossGhost)
				ghosts[i]->reduse();
			return -1;
		}
	}
	return 0;
}