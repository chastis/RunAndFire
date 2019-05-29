#include "Golem.h"
using namespace sf;

Golem::Golem(Image &image, float X, float Y, int W, int H, String Name) : Monster(image, X, Y, W, H, Name) {
	type = Monsters::golem;
	sprite.setTextureRect(IntRect(130, 3, w, h));
	dx = -dx;
	is_right = 0;
	damage = GOLEM_DMG;
}

void Golem::set(Image &image, float X, float Y, int W, int H, String Name){
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0.05f; health = 50; dx = -0.05f; dy = 0.f; damage = GOLEM_DMG;
	life = true; onGround = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(x + w / 2, x + h / 2);

	sprite.setTextureRect(IntRect(130, 3, w, h));
	is_right = 0;
}

void Golem::update(float time, Map & map)
{

	switch (health)
	{
	case 50:	
		x += dx*time;
		break;
	case 25:
		sprite.setTextureRect(IntRect(133, 84, w, h));
		x += 2 * dx*time;
		break;
	default:	
		x += dx*time;
		break;

	}
	check_collision(dx, 0, map);
	y += dy*time;
	check_collision(0, dy, map);

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	if (health <= 0) { life = false; }
	//speed = 0;
	dy = dy + 0.0015f * time;//постоянно притягиваемся к земле
}

void Golem::check_collision(float dx, float dy, Map & map) {
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

void Golem::change_direction() {
	dx = -dx;
	sprite.scale(-1, 1);
	is_right = !is_right;
}

bool Golem::get_right() {
	return is_right;
}
void golems_spawn(Image &image, int W, int H, std::vector<std::unique_ptr<Golem>> & golems, Map & map)
{
	golems.clear();
	for (int i = 0; i < map.get_h(); i++) {
		for (int j = 0; j < map.get_w(); j++) {
			if (map[i][j] == 'p')
			{
				golems.push_back(std::make_unique<Golem>(image, j * TITLE_SIZE, (i - 2) * TITLE_SIZE, W, H, "Golem"));
			}
		}
	}
}