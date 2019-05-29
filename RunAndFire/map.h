#ifndef CLASS_MAP_H
#define CLASS_MAP_H
#include "helpers.h"
using namespace sf;

class Map : public Drawable
{
public:
	Map(Image&, int = 15, int = 20);
	virtual ~Map() = default;
	virtual void draw(RenderTarget& window, RenderStates state) const;
	int get_w();
	int get_h();
	std::vector<char>& operator[](size_t);

private:
	Texture texture;
	Sprite sprite;
	int h, w;
	std::vector<std::vector<char>> tittle;
};

#endif

