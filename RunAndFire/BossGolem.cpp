#include "BossGolem.h"

BossGolem::BossGolem(Image & image, float X, float Y, int W, int H, String Name) : Golem(image, X, Y, W, H, Name){
	type = Monsters::bossGolem;
	speed = 0.15f;
	health = 100;
	damage = 99;
	sprite.setScale(2.f, 2.f);
	w *= 2;
	h *= 2;
}

void BossGolem::update(float time, Map & map)
{
	switch (health)
	{
	case 100:
		x += dx*time;
		break;
	case 75:
		x += 2*dx*time;
		break;
	case 50:
		x += 4*dx*time;
		break;
	case 25:
		x += 6*dx*time;
		break;
	default:
		x += dx*time;
		break;
		
	}
	//std::cout << health << std::endl;
	//x += dx*time;
	check_collision(dx, 0, map);
	y += dy*time;
	check_collision(0, dy, map);

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	if (health <= 0) { life = false; }
	//speed = 0;
	dy = dy + 0.0015f * time;//постоянно притягиваемся к земле
}