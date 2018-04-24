#include "Entity.h"
#include "functions.h"
using namespace sf;

Entity::Entity(Image &image, float X, float Y, int W, int H, String Name) {
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0; health = 100; dx = 0; dy = 0; static_speed = 0.1; static_jump = 0.6; static_g = 0.0015;
	life = true; onGround = false; space_pressed = false; sprite_right = true; with_mob = false;
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

void Entity::Restart() {
	if (Keyboard::isKeyPressed(Keyboard::R)) {
		x = -13;
		y = 0;
		dx = 0;
		dy = 0;
		health = 100;
		if (!life) if (is_right) sprite.rotate(-90);
				   else sprite.rotate(90);
		life = true;
		
	}
}
//функция управления персонажем
void Entity::control() {
	
	if (Keyboard::isKeyPressed && !with_mob) {//если нажата клавиша
		if (Keyboard::isKeyPressed(Keyboard::Left)) {//лево
			state = left; speed = static_speed; is_right = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {//право
			state = right; speed = static_speed; is_right = true;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {//если нажата клавиша вверх и мы на земле, то можем прыгать
			state = jump; dy = -static_jump; onGround = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && !space_pressed) {
			fire();
			space_pressed = true;
		}
		//тут шото не так
		// условие (1) не должно никогда выполняться
		if (!Keyboard::isKeyPressed(Keyboard::Space) && space_pressed) {
			space_pressed = false;
		}
	}
	else {
		state = stay;
	}
	Restart();
}


void Entity::update(float time, Map & map, std::vector<Golem> & golems) {
	Restart();
	if (life) {
		control();
		switch (state)//различные действия в зависимости от состояния
		{
		case right: dx = speed; break;//состояние идти вправо
		case left: dx = -speed; break;//состояние идти влево	
		case down: dx = 0; break;
			//case stay: dx = 0; dy = 0; break;
		}
		if (is_right && !sprite_right || !is_right && sprite_right) {
			sprite.scale(-1, 1); sprite_right = !sprite_right;
		}
		x += dx*time;
		check_collision(dx, 0, map);
		y += dy*time;
		check_collision(0, dy, map);

		check_collision(golems);

		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		speed = 0;
		dy = dy + static_g*time;//постоянно притягиваемся к земле
		if (health <= 0) {
			life = false;
			if (is_right) sprite.rotate(90);
			else sprite.rotate(-90);
			//dy = 0;//персонаж не будет подпрыгивать если умирает над врагом
		}
	}
	else if (!onGround) {
		y += dy*time;
		check_collision(0, dy, map);
		sprite.setPosition(x + w / 2, y + h / 2);
		dy = dy + static_g*time;
	}
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
					if (with_mob) this->dx = 0;
					with_mob = false;
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

void Entity::check_collision(std::vector<Golem> & golems) {
	for (int i = 0; i < golems.size(); i++) {
		float gx = golems[i].get_x(), gy = golems[i].get_y(), gh = golems[i].get_h(), gw = golems[i].get_w();
		if (square_in_square(x, y, w, h, gx, gy, gw, gh) ||
			square_in_square(gx, gy, gw, gh, x, y, w, h) ){
			
			if (!with_mob) health -= golems[i].get_damage();
			golems[i].change_direction();
			with_mob = true;

			if (golems[i].get_right()) {
				dx = -static_speed * 2;
				dy = -static_jump / 2;
			}
			else {
				dx = static_speed * 2;
				dy = -static_jump / 2;
			}

		}
	}
}

void Entity::fire() {
	
	Bullet temp(bullet_texture, sprite_right ? x + w : x, y + h / 3, 13, 10, "piu", is_right);
	bul.push_back(temp);
}

void Entity::draw_bullet(float time, Map & map, RenderWindow & window, std::vector<Golem> & golems) {
	for (int i = 0; i < bul.size(); i++) {
		window.draw(bul[i].get_sprite());
		int temp = bul[i].update(time, map, golems);
		if (temp == -1) { 
   			bul.erase(bul.begin() + i); i--; }
		if (bul.size() == 0) return;
	}
}

bool Entity::alive() {
	return life;
}
