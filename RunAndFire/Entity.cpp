#include "Entity.h"
using namespace sf;

Entity::Entity(Image &image, float X, float Y, int W, int H, String Name) {
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0; health = 100; dx = 0; dy = 0;
	life = true; onGround = false;
	is_right = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(3, 18, w, h));
	sprite.setOrigin(w / 2, h / 2);
	sprite.setPosition(x + w / 2, x + h / 2);

	Image bullet_Image; bullet_Image.loadFromFile("images/bullets.png");
	bullet_Image.createMaskFromColor(Color(0, 0, 0));
	bullet_texture.loadFromImage(bullet_Image);
}

Sprite Entity::get_sprite() {
	return sprite;
}

//функция управления персонажем
void Entity::control() {
	if (Keyboard::isKeyPressed) {//если нажата клавиша
		if (Keyboard::isKeyPressed(Keyboard::Left)) {//лево
			state = left; speed = 0.1; is_right = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {//право
			state = right; speed = 0.1; is_right = true;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {//если нажата клавиша вверх и мы на земле, то можем прыгать
			state = jump; dy = -0.6; onGround = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
		}
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			x = 0;
			y = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			fire();
		}
	}
	else {
		state = stay;
	}
}

void Entity::update(float time, Map & map) {
	control();
	switch (state)//различные действия в зависимости от состояния
	{
	case right: dx = speed; break;//состояние идти вправо
	case left: dx = -speed; break;//состояние идти влево	
	case down: dx = 0; break;
	//case stay: dx = 0; dy = 0; break;
	}
	x += dx*time;
	check_collision(dx, 0, map);
	y += dy*time;
	check_collision(0, dy, map);

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	if (health <= 0) { life = false; }
	speed = 0;
	dy = dy + 0.0015*time;//постоянно притягиваемся к земле
}

void Entity::check_collision(float dx, float dy, Map & map) {
	for (int i = y / 32; i < (y + h) / 32; i++) {
		for (int j = x / 32; j < (x + w) / 32; j++) {
			if (map.get(i,j) == 'w')
			{
				if (dy>0)
				{
					y = i * 32 - h;
					this->dy = 0;
					onGround = true;
				}
				if (dy<0)
				{
					y = i * 32 + 32;
					this->dy = 0;
				}
				if (dx>0)
				{
					x = j * 32 - w;
				}
				if (dx < 0)
				{
					x = j * 32 + 32;
				}
			}
		}
	}
}

void Entity::fire() {
	
	Bullet temp(bullet_texture, x, y, 12, 12, "piu",is_right,bul.size());
	bul.push_back(temp);
}

void Entity::draw_bullet(float time, Map & map, RenderWindow & window) {
	for (int i = 0; i < bul.size(); i++) {
		window.draw(bul[i].get_sprite());
		int temp = bul[i].update(time, map);
		if (temp == -1) { 
   			bul.erase(bul.begin() + i); i--; }
		if (bul.size() == 0) return;
	}
}