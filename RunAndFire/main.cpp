#include "headers_which_you_need.h"
#include "Entity.h"
#include "Monster.h"
#include "map.h"
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "Run and Fire!");
	View view; view.reset(FloatRect(0, 0, 640, 480));
	//view.setCenter(200, 240);
	
	Image hero_Image; hero_Image.loadFromFile("images/MilesTailsPrower.gif");
	hero_Image.createMaskFromColor(Color(0, 0, 0));
	Entity hero(hero_Image, -13, 190, 42, 33, "Hero");

	Image monster_Image; monster_Image.loadFromFile("images/Monster.png");
	monster_Image.createMaskFromColor(Color(255, 255, 255));
	Monster golem(monster_Image, 20, 20, 28, 34, "Golem");

	Image mapImage; mapImage.loadFromFile("images/map.png");
	mapImage.createMaskFromColor(Color(255, 255, 255));
	Map map(mapImage);


	Clock clock;
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		hero.update(time,map);
		golem.update(time, map);

		window.setView(view);
		window.clear(Color(77, 83, 140));

		map.draw_map(window);
		window.draw(hero.get_sprite());
		window.draw(golem.get_sprite());
		hero.draw_bullet(time, map, window);
		window.display();
	}
	return 0;
}