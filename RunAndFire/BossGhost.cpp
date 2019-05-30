#include "BossGhost.h"

BossGhost::BossGhost(Image & image, float X, float Y, int W, int H, String Name) : Ghost(image, X, Y, W, H, Name) {
	type = Monsters::bossGhost;
	speed = 0.05f;
	dx = -speed;
	dy = -speed;
	health = 200;
	damage = 20;
	sprite.setScale(2.f, 2.f);
	w *= 2;
	h *= 2;
}

void BossGhost::update(float time, Map & map, float heroX, float heroY)
{
	if (timer.getElapsedTime().asSeconds() >= 2)
	{
		weak = false;
		timer.restart();
		sprite.setColor(sf::Color::White);
		bullets.emplace_back(bullet_texture, x, y);
		//for (auto & bul : bullets)
		//std::cout << health << std::endl;
	}
	dx = sign*std::sqrt(speed*speed + 0.0001f - dy*dy); dy += stepChange;
	if (stepChange > 0 && dy >= speed || stepChange < 0 && dy <= -speed) {
		if (stepChange > 0) dy = speed; else dy = -speed;
		stepChange = -stepChange;
		//sign = -sign;
	}
	x += dx*time;
	check_collision(dx, 0, map);
	y += dy*time;
	//check_collision(0, dy, map);

	switch (health)
	{
	case 200:
		break;
	case 150:
		//sprite.setTextureRect(IntRect(0, 222, w/2, h/2));
		break;
	case 100:
		//sprite.setTextureRect(IntRect(28, 223, w/2, h/2));
		break;
	case 50:
		//sprite.setTextureRect(IntRect(54, 225, w/2, h/2));
		break;
	default:
		break;

	}

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	if (health <= 0) { life = false; }
	//speed = 0;

	for (auto & bul : bullets)
		bul.update(time, map, heroX, heroY);
}

void BossGhost::reduse()
{
	std::cout << "switch " << health << std::endl;
	switch (health)
	{
	case 200:
		break;
	case 150:
		w /= 2;
		h /= 2;
		sprite.setTextureRect(IntRect(0, 222, w, h));
		sprite.setScale(1.5f, 1.5f);
		w *= 1.5;
		h *= 1.5;
		break;
	case 100:
		w /= 1.5;
		h /= 1.5;
		sprite.setTextureRect(IntRect(28, 223, w, h));
		sprite.setScale(1, 1);
		break;
	case 50:
		
		sprite.setTextureRect(IntRect(54, 225, w, h));
		sprite.setScale(0.5f, 0.5f);
		w *= 0.5;
		h *= 0.5;
		break;
	default:
		break;

	}
}

void BossGhost::check_collision(float dx, float dy, Map & map) {
	try
	{
		for (int i = static_cast<int>(y / TITLE_SIZE); i < (y + h) / TITLE_SIZE; i++) {
			if (i < 0 || i >= map.get_h()) continue;
			for (int j = static_cast<int>(x / TITLE_SIZE); j < (x + w) / TITLE_SIZE; j++) {
				if (j < 0 || j >= map.get_w()) continue;
				if (map[i][j] == 'w' || map[i][j] == 'v' && !map.isInter())
				{
					if (dx > 0)
					{
						x = static_cast<float>(j * TITLE_SIZE - w);
						change_direction();
					}
					if (dx < 0)
					{
						x = static_cast<float>(j * TITLE_SIZE + TITLE_SIZE);
						change_direction();
					}
				}
				if (map[i][j] == 's')
				{
					if (dx > 0)
					{
						x = static_cast<float>(j * TITLE_SIZE - w);
						change_direction();
					}
					if (dx < 0)
					{
						x = static_cast<float>(j * TITLE_SIZE + TITLE_SIZE);
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