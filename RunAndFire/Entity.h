#ifndef ENTITY_H
#define ENTITY_H
#include "map.h"
#include "Golem.h"
#include "Bullet.h"
#include "loot.h"
#include <vector>
#include "headers_which_you_need.h"
using namespace sf;

//������������ ����� �������
class Entity {
public:
	//��������; ��������� ���������� (x,y); ������ �������; ��� ���������;
	Entity(Image &image, float X, float Y, int W, int H, String Name);
	void control();
	void update(float,Map &, std::vector<std::unique_ptr<Golem>> &, Loot & loot);
	void check_collision(float, float,Map &);
	void check_collision(std::vector<std::unique_ptr<Golem>> &);
	void check_collision(Loot &);
	Sprite& get_sprite();
	void fire();
	void draw_bullet(float time, Map & map, RenderWindow & window, std::vector<std::unique_ptr<Golem>> & golems);
	bool alive();
	void Restart();
	int ammo();
private:
	std::vector<Bullet> bul;
	int health, bullets_quantity;
	State state;
	float x, y;//���������� ������ � � �
	float dx, dy, speed , static_speed, static_jump, static_g;//�������� ��������� � ������� ������ ������������ ����, � ����������� �������� ���������
	int w, h;//������� ������� � ���-�� �������� ���������
	bool life, onGround, is_right, space_pressed, sprite_right, with_mob, up_pressed, up_pressed_second_time;
	Texture texture;
	Sprite sprite;
	String name;
	Texture bullet_texture;
	bool doubleJump;
	Clock clock;
};
#endif
