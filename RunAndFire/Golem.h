#ifndef GOLEM_H
#define GOLEM_H
#include "map.h"
#include "Monster.h"
#include "headers_which_you_need.h"
using namespace sf;

//������������ ����� �������
class Golem : public Monster {
public:
	//��������; ��������� ���������� (x,y); ������ �������; ��� ���������;
	Golem(Image &image, float X, float Y, int W, int H, String Name);
	virtual ~Golem() = default;
	void update(float, Map &);
	void check_collision(float, float, Map &);
	void change_direction();
	void set(Image &image, float X, float Y, int W, int H, String Name);
	bool get_right();
private:
	bool is_right;
	
};
#endif
