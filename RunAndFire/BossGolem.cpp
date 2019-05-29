#include "BossGolem.h"

BossGolem::BossGolem(Image & image, float X, float Y, int W, int H, String Name) : Golem(image, X, Y, W, H, Name){
	type = Monsters::bossGolem;
	speed = 0.15f;
	health = 10;
	damage = 99;
	sprite.setScale(2.f, 2.f);
	w *= 2;
	h *= 2;
}

void BossGolem::update(float time, Map & map)
{
	//sprite.setScale(1.f, 1.f);
	switch (health)
	{
	case 100:
		x += dx*time;
		break;
	case 75:
		sprite.setTextureRect(IntRect(133, 84, w/2, h/2));
		x += 2*dx*time;
		break;
	case 50:
		sprite.setTextureRect(IntRect(194, 84, w/2, h/2));
		x += 4*dx*time;
		break;
	case 25:
		sprite.setTextureRect(IntRect(223, 85, w/2, h/2));
		x += 6*dx*time;
		break;
	default:
		x += dx*time;
		break;
		
	}
	//sprite.setScale(2.f, 2.f);
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