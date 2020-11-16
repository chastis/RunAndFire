#ifndef ENTITY_H
#define ENTITY_H
#include "map.h"
#include "Golem.h"
#include "Ghost.h"
#include "Bullet.h"
#include "loot.h"
#include <vector>
#include "headers_which_you_need.h"

//родительский класс существ
class Entity : public sf::Drawable {
public:
	//Картинка; начальные координаты (x,y); размер спрайта; имя персонажа;
	Entity(sf::Image &image, float X, float Y, int W, int H, sf::String Name);
	void control();
	void update(float, Map &, std::vector<std::unique_ptr<Golem>> &, std::vector<std::unique_ptr<Ghost>> & , Loot & loot);
	void check_collision(float, float,Map &);
	void check_collision(std::vector<std::unique_ptr<Golem>> &, std::vector<std::unique_ptr<Ghost>> &);
	void check_collision(Loot &);
	sf::Sprite& get_sprite();
	void fire();
	void draw_bullet(float time, Map & map, RenderWindow & window, std::vector<std::unique_ptr<Golem>> & golems, std::vector<std::unique_ptr<Ghost>> & ghosts);
	bool alive();
	void Restart(Map &, std::vector<std::unique_ptr<Golem>> &, std::vector<std::unique_ptr<Ghost>> &, Loot & loot);
	int ammo();
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	int hp();
	float getX();
	float getY();
	void spawn(Map &);
private:
	std::vector<Bullet> bul;
	std::vector<std::pair<Point, std::chrono::high_resolution_clock::time_point>> crates;
	int health, bullets_quantity;
	State state;
	Directions dir;
	float x, y;//координаты игрока х и у
	float dx, dy, speed, static_speed, static_jump;//скорость персонажа в текущий момент относительно осей, и стандартная скорость персонажа
	int w, h;//размеры спрайта и кол-во здоровья персонажа
	bool life, onGround, is_right, space_pressed, sprite_right, with_mob, up_pressed, up_pressed_second_time, isFly;
	bool madeDoubleJumpOnThisTurn;
	sf::Texture texture;
	sf::Sprite sprite;
	String name;
	sf::Texture bullet_texture;
	bool doubleJump;
	sf::Clock clock;
	sf::Text hp_text;
};
#endif
