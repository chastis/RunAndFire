#include "Entity.h"
#include "functions.h"
using namespace sf;

bool bossSpawned;

Entity::Entity(Image &image, float X, float Y, int W, int H, String Name){
	doubleJump = false;
	up_pressed = false;
	up_pressed_second_time = false;
	clock.restart();
	x = X; y = Y; w = W; h = H; name = Name;
	bullets_quantity = PLAYET_BULLETS;
	speed = 0; health = PLAYER_HP ; dx = 0; dy = 0; static_speed = 0.2f; static_jump = 0.6f;
	life = true; onGround = false; space_pressed = false; sprite_right = true; with_mob = false;
	is_right = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(3, 18, w, h));
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(x + w / 2.f, x + h / 2.f);
	w /= 2; h /= 2;
	Image bullet_Image; bullet_Image.loadFromFile("images/bullets.png");
	bullet_Image.createMaskFromColor(Color(0, 0, 0));
	bullet_texture.loadFromImage(bullet_Image);

	Text text("HP: ", *font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пиксел€х);//сам объект текст (не строка)
	text.setFillColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	String str = HP_TEXT;
	str.insert(str.getSize(), std::to_string(health));
	text.setString(str);
	text.setPosition(440, 30);
	hp_text = text;
	
}

Sprite& Entity::get_sprite() {
	return sprite;
}

void Entity::Restart(Map & map, std::vector<std::unique_ptr<Golem>> & golems, Loot & loot) {
	if (Keyboard::isKeyPressed(Keyboard::R)) {
		bossSpawned = false;
		spawn(map);
		map.reset();
		dx = 0;
		dy = 0;
		health = PLAYER_HP;
		state = State::jump;
		//hp_text.setString(HP_TEXT + std::to_string(health));
		bullets_quantity = PLAYET_BULLETS;
		if (!life) if (is_right) sprite.rotate(-90);
				   else sprite.rotate(90);
		life = true;
		loot.clear();
		golems.clear();
		loot.ammo_add(96, 320);
		loot.ammo_add(576, 416);
		loot.ammo_add(500, 416);
		Image monster_Image; monster_Image.loadFromFile("images/Monster.png");
		monster_Image.createMaskFromColor(Color(255, 255, 255));
		golems_spawn(monster_Image, 28, 34, golems, map);
		
	}
}

//функци€ управлени€ персонажем
void Entity::control() {
	//467 53
	//493 100
	//34 47
	if (!with_mob) {//если нажата клавиша
		if (Keyboard::isKeyPressed(Keyboard::A)) {//лево
			state = State::left; speed = static_speed; is_right = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {//право
			state = State::right; speed = static_speed; is_right = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && !up_pressed && !up_pressed_second_time && !onGround)
		{
			up_pressed_second_time = true;
			up_pressed = true;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Space)) && (onGround || doubleJump)) {//если нажата клавиша вверх и мы на земле, то можем прыгать
			state = State::jump; dy = -static_jump; onGround = false; doubleJump = false; up_pressed = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			state = State::down;
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			state = State::up;
		}
		if (!Keyboard::isKeyPressed(Keyboard::Space) && up_pressed)
		{
			up_pressed = false;
			//up_pressed_second_time = false;  
		}
		//fire
		if ((Keyboard::isKeyPressed(Keyboard::Up)
			|| Keyboard::isKeyPressed(Keyboard::Down)
			|| Keyboard::isKeyPressed(Keyboard::Left)
			|| Keyboard::isKeyPressed(Keyboard::Right)))
		{
			if (!space_pressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left)) {
					is_right = false;
					dir = Directions::ul;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right)) {
					is_right = true;
					dir = Directions::ur;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left)) {
					is_right = false;
					dir = Directions::dl;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right)) {
					is_right = true;
					dir = Directions::dr;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up)) {
					dir = Directions::u;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down)) {
					dir = Directions::d;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					is_right = false;
					dir = Directions::l;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					is_right = true;
					dir = Directions::r;
				}
				if (bullets_quantity > 0) { fire(); }
				space_pressed = true;
			}
		}
		else if (space_pressed) space_pressed = false;

	}
	else {
		state = State::stay;
	}
	//Restart();
}

void Entity::update(float time, Map & map, std::vector<std::unique_ptr<Golem>> & golems, Loot & loot) {
	Restart(map, golems, loot);
	loot.update(map);
	if (life) {
		control();
		switch (state)//различные действи€ в зависимости от состо€ни€
		{
		case State::right: dx = speed; break;//состо€ние идти вправо
		case State::left: dx = -speed; break;//состо€ние идти влево	
		case State::down: dx = 0; break;
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
		dy = dy + STATIC_G*time;//посто€нно прит€гиваемс€ к земле
		if (health <= 0 || y > 500) {
			life = false;
			health = 0;
			if (is_right) sprite.rotate(90);
			else sprite.rotate(-90);
			dy = -0.5;
			//dy = 0;//персонаж не будет подпрыгивать если умирает над врагом
		}
		if (onGround) up_pressed_second_time = false;
	}
	else if (!onGround) {
		y += dy*time;
		//std::cout << dy << std::endl;
		check_collision(0, dy, map);
		sprite.setPosition(x + w / 2, y + h / 2);
		dy = dy + STATIC_G*time;
	}
}

void Entity::check_collision(float dx, float dy, Map & map) {
	for (int i = static_cast<int>(y / TITLE_SIZE); i < (y + h) / TITLE_SIZE; i++) {
		if (i < 0 || i >= map.get_h()) continue;
		for (int j = static_cast<int>(x / TITLE_SIZE); j < (x + w) / TITLE_SIZE; j++) {
			if (j < 0 || j >= map.get_w()) continue;
			onGround = false;
			if (map[i][j] == 'w' || map[i][j] == 'v' && !map.isInter())
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
			if (life)
			{
				if (map[i][j] == 'd' && up_pressed_second_time) {
					map[i][j] = '0';
					doubleJump = true;
					up_pressed_second_time = false;
					crates.push_back(std::make_pair(Point(i, j), std::chrono::high_resolution_clock::now()));
					//!!!!
					if (j == 2) map.move();
				}
				if (map[i][j] == 'h') {
					map[i][j] = '0';
					health += MED_KIT_HP_BOOST;
					if (health > PLAYER_HP) health = PLAYER_HP;
					//hp_text.setString(HP_TEXT + std::to_string(health));
				}
				if (map[i][j] == 's') {
					life = false;
					health = 0;
					dy = -static_jump / 4.f;
				}
			}
		}
	}
	if (!crates.empty()) {	
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - crates.front().second).count() > CRATES_RESPAWN) {
			map[crates.front().first.x][crates.front().first.y] = 'd';
			crates.erase(crates.begin());
		}
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
			square_in_square(gx, gy, gw, gh, x, y, static_cast<float>(w), static_cast<float>(h))) {

			if (!with_mob) health -= golems[i]->get_damage();
			if (health < 0) health = 0;
			if (golems[i]->get_right() && !this->is_right || !golems[i]->get_right() && this->is_right) golems[i]->change_direction();
			with_mob = true;

			if (golems[i]->get_right()) {
				dx = -static_speed * 1.5f;
				dy = -static_jump / 4.f;
			}
			else {
				dx = static_speed * 1.5f;
				dy = -static_jump / 4.f;
			}

		}
	}
	//hp_text.setString(HP_TEXT + std::to_string(health));
}


void Entity::fire() {

	int t_x, t_y;
	switch (dir)
	{
	case Directions::u:
		t_x = x + w / 2;
		t_y = y;
		break;
	case Directions::d:
		t_x = x + w / 2;
		t_y = y + h;
		break;
	case Directions::l:
		t_x = x;
		t_y = y + h / 3;
		break;
	case Directions::r:
		t_x = x + w;
		t_y = y + h / 3;
		break;
	case Directions::ur:
		t_x = x + w;
		t_y = y;
		break;
	case Directions::ul:
		t_x = x;
		t_y = y;
		break;
	case Directions::dr:
		t_x = x + w;
		t_y = y + h;
		break;
	case Directions::dl:
		t_x = x;
		t_y = y + h;
		break;
	}
	Bullet temp(bullet_texture, t_x, t_y, 13, 10, "piu", dir);
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

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

int Entity::hp() {
	return health;
}
void Entity::spawn(Map & map)
{
	for (int i = 0; i < map.get_h(); i++) {
		for (int j = 0; j < map.get_w(); j++) {
			if (map[i][j] == 'b')
			{
				x = j * TITLE_SIZE;
				y = i * TITLE_SIZE;
			}
		}
	}
}