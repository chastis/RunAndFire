#include "BossGolem.h"

BossGolem::BossGolem(Image & image, float X, float Y, int W, int H, String Name) : Golem(image, X, Y, W, H, Name) {
	speed = 0.15f;
	health = 100;
	damage = 200;
}
