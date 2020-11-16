#include "Ghost.h"
using namespace sf;

Ghost::Ghost(Image &image, float X, float Y, int W, int H, String Name) : Monster(image, X, Y, W, H, Name) {
	type = Monsters::ghost;
	weak = false;
	sign = 1;
	//23 28
	name = Name;
	sprite.setTextureRect(IntRect(0, 80, w, h));
	if (name == "g")
	speed = 0.05f;
	else speed = 0.075f;
	dx = -speed;
	dy = -speed;
	is_right = 0;
	damage = GHOST_DMG;
	health = 50;
	stepChange = 0.0005f;

	Image bullet_Image; bullet_Image.loadFromFile("images/bullets.png");
	bullet_Image.createMaskFromColor(Color(0, 0, 0));
	bullet_texture.loadFromImage(bullet_Image);
}

void Ghost::set(Image &image, float X, float Y, int W, int H, String Name) {
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0.05f; health = 50; damage = GHOST_DMG;
	dx = -0.05f;
	dy = -0.05f;
	life = true; onGround = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(x + w / 2, x + h / 2);

	sprite.setTextureRect(IntRect(0, 80, w, h));
	is_right = 0;
}

void Ghost::update(float time, Map & map, float heroX, float heroY)
{
	if (timer.getElapsedTime().asSeconds() >= 3)
	{
		weak = false;
		timer.restart();
		sprite.setColor(sf::Color::White);
		bullets.emplace_back(bullet_texture, x, y);
		if (bullets.size() >= 4) change_direction();
		if (bullets.size() >= 5) bullets.erase(bullets.begin());
		//for (auto & bul : bullets)
		//std::cout << health << std::endl;
	}
	dy = sign*std::sqrt(speed*speed + 0.0001f - dx*dx); dx += stepChange;
	if (stepChange > 0 && dx >= speed|| stepChange < 0 && dx <= -speed) {
		if (stepChange > 0) dx = speed; else dx = -speed;
		stepChange = -stepChange;
		sign = -sign;		
	}
	x += dx*time;
	//check_collision(dx, 0, map);
	y += dy*time;
	//check_collision(0, dy, map);

	switch (health)
	{
	case 50:
		break;
	case 25:
		sprite.setTextureRect(IntRect(0, 222, w, h));
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

void Ghost::check_collision(float dx, float dy, Map & map) {
	try
	{
		for (int i = static_cast<int>(y / TITLE_SIZE); i < (y + h) / TITLE_SIZE; i++) {
			if (i < 0 || i >= map.get_h()) continue;
			for (int j = static_cast<int>(x / TITLE_SIZE); j < (x + w) / TITLE_SIZE; j++) {
				if (j < 0 || j >= map.get_w()) continue;
				if (map[i][j] == 'w' || map[i][j] == 'v' && !map.isInter())
				{
					if (dy > 0)
					{
						y = static_cast<float>(i * TITLE_SIZE - h);
						this->dy = 0;
						onGround = true;
					}
					if (dy < 0)
					{
						y = static_cast<float>(i * TITLE_SIZE + TITLE_SIZE);
					}
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

void Ghost::change_direction() {
	dx = -dx;
	sign = -sign;
	sprite.scale(-1, 1);
	is_right = !is_right;
}

bool Ghost::get_right() {
	return is_right;
}
void ghosts_spawn(Image &image, int W, int H, std::vector<std::unique_ptr<Ghost>> & ghosts, Map & map)
{
	ghosts.clear();
	for (int i = 0; i < map.get_h(); i++) {
		for (int j = 0; j < map.get_w(); j++) {
			if (map[i][j] == 'g')
			{
				ghosts.push_back(std::make_unique<Ghost>(image, j * TITLE_SIZE, (i - 2) * TITLE_SIZE, W, H, "g"));
			}
			if (map[i][j] == 'G')
			{
				ghosts.push_back(std::make_unique<Ghost>(image, j * TITLE_SIZE, (i - 2) * TITLE_SIZE, W, H, "G"));
			}
		}
	}
	//ghosts.resize(1);
}

void Ghost::damaged()
{
	weak = true;
	timer.restart();
	sprite.setColor(sf::Color::Red);
}

bool Ghost::isDamaged()
{
	return weak;
}
void Ghost::draw(RenderWindow & window)
{
	window.draw(sprite);
	for (auto & bul : bullets)
		window.draw(bul.getSprite());
}

bool Ghost::checkBullets(float heroX, float heroY, int heroW, int heroH)
{
	bool answer = false;
	for (int i = 0; i < bullets.size(); i++)
	{
		BadBullet bul = bullets[i];
		if (square_in_square(bul.x, bul.y,bul.w, bul.h, heroX, heroY, heroW, heroH)
			|| square_in_square(heroX, heroY,heroW, heroH, bul.x, bul.y, bul.w, bul.h))
		{
			answer = true;
			bullets.erase(bullets.begin() + i--);
		}
	}
	return answer;
}
BadBullet::BadBullet(Texture &texture, float X, float Y) {
	speed = 0.02f;
	sprite.setTexture(texture);
	w = h = 11;
	x = X; y = Y;
	sprite.setTextureRect(IntRect(173, 157, w, h));
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(x + w / 2.f, y + h / 2.f);
}
void BadBullet::update(float time, Map & map, float heroX, float heroY)
{
	float dx, dy;
	if (heroX > x + w) dx = speed;
	else if (heroX < x - w) dx = -speed;
	else dx = 0;
	if (heroY > y + h) dy = speed;
	else if (heroY < y - h) dy = -speed;
	else dy = 0;
	x += dx*time;
	y += dy*time;
	sprite.setPosition(x + w / 2.f, y + h / 2.f);
}

Sprite BadBullet::getSprite()
{
	return sprite;
}
void Ghost::reduse()
{

}