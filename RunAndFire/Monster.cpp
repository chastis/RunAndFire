#include "Monster.h"
using namespace sf;

Monster::Monster(Image &image, float X, float Y, int W, int H, String Name) {
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0.05; health = 50; dx = 0.05; dy = 0;
	life = true; onGround = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 30, w, h));
	sprite.setOrigin(w / 2, h / 2);
	sprite.setPosition(x + w / 2, x + h / 2);
}

Sprite Monster::get_sprite() {
	return sprite;
}