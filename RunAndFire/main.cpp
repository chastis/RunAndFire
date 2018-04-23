#include "headers_which_you_need.h"
#include "Entity.h"
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "Run and Fire!");
	View view; view.reset(FloatRect(0, 0, 640, 480));
	
	Image heroImage;
	heroImage.loadFromFile("images/MilesTailsPrower.gif");
	heroImage.createMaskFromColor(Color(0, 0, 0));
	Entity hero(heroImage, 0, 0, 42, 32, "Hero");


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

		hero.update(time);

		window.setView(view);
		window.clear(Color(77, 83, 140));

		window.draw(hero.get_sprite());

		window.display();
	}
	return 0;
}