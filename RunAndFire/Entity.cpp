#include "Entity.h"
#include "functions.h"
using namespace sf;

Entity::Entity(Image &image, float X, float Y, int W, int H, String Name) : doubleJump(false) {
	clock.restart();
	x = X; y = Y; w = W; h = H; name = Name; bullets_quantity = 3;	
	speed = 0; health = PLAYER_HP ; dx = 0; dy = 0; static_speed = 0.2f; static_jump = 0.6f; static_g = 0.0015f;
	life = true; onGround = false; space_pressed = false; sprite_right = true; with_mob = false; up_pressed = false, up_pressed_second_time = false;
	is_right = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(3, 18, w, h));
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(x + w / 2.f, x + h / 2.f);
	//
	w /= 2; h /= 2;
	//
	Image bullet_Image; bullet_Image.loadFromFile("images/bullets.png");
	bullet_Image.createMaskFromColor(Color(0, 0, 0));
	bullet_texture.loadFromImage(bullet_Image);
}

Sprite& Entity::get_sprite() {
	return sprite;
}

void Entity::Restart() {
	if (Keyboard::isKeyPressed(Keyboard::R)) {
		x = -13;
		y = 0;
		dx = 0;
		dy = 0;
		health = 100;
		bullets_quantity = 3;
		if (!life) if (is_right) sprite.rotate(-90);
				   else sprite.rotate(90);
		life = true;
		
	}
}

//функция управления персонажем
void Entity::control() {
	//467 53
	//493 100
	//34 47
	if (!with_mob) {//если нажата клавиша
		if (Keyboard::isKeyPressed(Keyboard::Left)) {//лево
			state = left; speed = static_speed; is_right = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {//право
			state = right; speed = static_speed; is_right = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && !up_pressed && !up_pressed_second_time && !onGround)
		{
			up_pressed_second_time = true;
			up_pressed = true;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround || doubleJump)) {//если нажата клавиша вверх и мы на земле, то можем прыгать
			state = jump; dy = -static_jump; onGround = false; doubleJump = false; up_pressed = true;
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && !space_pressed) {
			if (bullets_quantity > 0) { fire(); }
			space_pressed = true;
		}
		//тут шото не так
		// условие (1) не должно никогда выполняться
		if (!Keyboard::isKeyPressed(Keyboard::Space) && space_pressed) {
			space_pressed = false;
		}
		if (!Keyboard::isKeyPressed(Keyboard::Up) && up_pressed)
		{
			up_pressed = false;
			//up_pressed_second_time = false;	
		}
		
	}
	else {
		state = stay;
	}
	Restart();
}

void Entity::update(float time, Map & map, std::vector<std::unique_ptr<Golem>> & golems, Loot & loot) {
	Restart();
	/*
	if (clock.getElapsedTime().asMilliseconds() > 1000 / PLAYER_GUN_SPEED && space_pressed) {
		space_pressed = false;
		clock.restart();
	}
	*/
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
		check_collision(loot);

		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		speed = 0;
		dy = dy + static_g*time;//постоянно притягиваемся к земле
		if (health <= 0 || y > 500) {
			life = false;
			if (is_right) sprite.rotate(90);
			else sprite.rotate(-90);
			dy = -0.5;
			//dy = 0;//персонаж не будет подпрыгивать если умирает над врагом
		}
		if (onGround)
		{
			up_pressed_second_time = false;
		}
	}
	else if (!onGround) {
		y += dy*time;
		//up_pressed = false;
		//up_pressed_second_time = false;
		//std::cout << dy << std::endl;
		check_collision(0, dy, map);
		sprite.setPosition(x + w / 2, y + h / 2);
		dy = dy + static_g*time;
	}
}

void Entity::check_collision(float dx, float dy, Map & map) {
	try {
		for (int i = static_cast<int>(y / TITLE_SIZE); i < (y + h) / TITLE_SIZE; i++) {
			if (i < 0 || i >= map.get_h()) continue;
			for (int j = static_cast<int>(x / TITLE_SIZE); j < (x + w) / TITLE_SIZE; j++) {
				if (j < 0 || j >= map.get_w()) continue;
				onGround = false;
				if (map[i][j] == 'w')
				{

					if (dy > 0)
					{
						y = static_cast<float>(i * TITLE_SIZE - h);
						this->dy = 0;
						this->dx = 0;
						onGround = true;
						with_mob = false;
						return;
					}
					if (dy < 0)
					{
						y = static_cast<float>(i * TITLE_SIZE + TITLE_SIZE);
						this->dy = 0;
					}
					if (dx > 0)
					{
						x = static_cast<float>(j * TITLE_SIZE - w);
					}
					if (dx < 0)
					{
						x = static_cast<float>(j * TITLE_SIZE + TITLE_SIZE);
					}
				}
				if (map[i][j] == 'd' && up_pressed_second_time) {
					map[i][j] = '0';
					//bullets_quantity += 2;
					doubleJump = true;
					up_pressed_second_time = false;
					auto reset = [&](int i, int j)
					{
						std::cout << "thread " << i << " " << j << "start" << std::endl;
						std::this_thread::sleep_for(std::chrono::seconds(3));
						map[i][j] = 'd';
						std::cout << "thread " << i << " " << j << "end" << std::endl;
					};
					
					static int count = 0;
					if (count + 1 > MAX_DOUBLE_JUMP_POINTS)
					{
						std::cout << "try to do" << std::endl;
						threads[(count + 1) % MAX_DOUBLE_JUMP_POINTS]->join();
						//delete threads[(count + 1) % MAX_DOUBLE_JUMP_POINTS];
						threads[(count + 1) % MAX_DOUBLE_JUMP_POINTS].release();
						std::cout << "end to do" << std::endl;
					}
					std::cout << "hm1" << std::endl;
					if (threads[count % MAX_DOUBLE_JUMP_POINTS] != nullptr)
						threads[count % MAX_DOUBLE_JUMP_POINTS]->detach();
					threads[count % MAX_DOUBLE_JUMP_POINTS] = std::make_unique<std::thread>(reset, i, j);
					threads[count++ % MAX_DOUBLE_JUMP_POINTS]->detach();
					//threads[count++ % MAX_DOUBLE_JUMP_POINTS] = new std::thread(reset, i, j);
					//threads[(count + 1) % MAX_DOUBLE_JUMP_POINTS].join();
				}
			}
		}
	}
	catch (std::exception) {
		return;
	}
}

void Entity::check_collision(Loot & loot) {
	for (size_t i = 0; i < loot.ammos.size(); i++) {
		float gx = loot.ammos[i].x, gy = loot.ammos[i].y, gh = loot.get_rect().height, gw = loot.get_rect().width;
		if (square_in_square(x, y, static_cast<float>(w), static_cast<float>(h), gx, gy, gw, gh) ||
			square_in_square(gx, gy, gw, gh, x, y, static_cast<float>(w), static_cast<float>(h)) ){
				
			loot.ammo_aword(bullets_quantity);
			loot.ammos.erase(loot.ammos.begin() + i); i--;
		}
	}
}

void Entity::check_collision(std::vector<std::unique_ptr<Golem>> & golems) {
	for (size_t i = 0; i < golems.size(); i++) {
		float gx = golems[i]->get_x(), gy = golems[i]->get_y(), gh = static_cast<float>(golems[i]->get_h()), gw = static_cast<float>(golems[i]->get_w());
		if (square_in_square(x, y, static_cast<float>(w), static_cast<float>(h), gx, gy, gw, gh) ||
			square_in_square(gx, gy, gw, gh, x, y, w, h)) {

			if (!with_mob) health -= golems[i]->get_damage();
			if (golems[i]->get_right() && !this->is_right || !golems[i]->get_right() && this->is_right) golems[i]->change_direction();
			with_mob = true;

			if (golems[i]->get_right()) {
				dx = -static_speed * 1.5;
				dy = -static_jump / 4;
			}
			else {
				dx = static_speed * 1.5;
				dy = -static_jump / 4;
			}

		}
	}
}


void Entity::fire() {
	
	Bullet temp(bullet_texture, sprite_right ? x + w : x, y + h / 3, 13, 10, "piu", is_right);
	bullets_quantity--;
	bul.push_back(temp);
}

void Entity::draw_bullet(float time, Map & map, RenderWindow & window, std::vector<std::unique_ptr<Golem>> & golems) {
	for (size_t i = 0; i < bul.size(); i++) {
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

int Entity::ammo() {
	return bullets_quantity;
}