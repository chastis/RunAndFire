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
