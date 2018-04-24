#include "headers_which_you_need.h"
#include "Entity.h"
#include "Golem.h"
#include "map.h"
#include <vector>
//#include <sstream>
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

	std::vector<Golem> golems;
	//{
		Golem golem(monster_Image, 64, 170, 28, 34, "Golem1");
		golems.push_back(golem);
		Golem golem2(monster_Image, 150, 332, 28, 34, "Golem2");
		golems.push_back(golem2);
	//}


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

		
		for (int i = 0; i < golems.size(); i++) {
			golems[i].update(time, map);
		}
		hero.update(time, map, golems);
		//std::cout << hero.health << std::endl;
		window.setView(view);
		window.clear(Color(77, 83, 140));

		map.draw_map(window);
		window.draw(hero.get_sprite());
		hero.draw_bullet(time, map, window, golems);
		for (int i = 0; i < golems.size(); i++) {
			if (!golems[i].get_life()) {
				golems.erase(golems.begin() + i); i--;
			}
			//std::cout << "golem " << i << " - " << golems[i].health << std::endl;
		}
		if (golems.size() == 0) {
			Font font;//шрифт 
			font.loadFromFile("CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
			Text text("YOU WIN!", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
			text.setFillColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
			text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
			window.draw(text);
			text.setString("congrats");
			text.setPosition(0, 20);
			window.draw(text);
		}
		if (!hero.alive()) {
			Font font;//шрифт 
			font.loadFromFile("CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
			Text text("YOU DIED!", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
			text.setFillColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
			text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
			window.draw(text);
			text.setString("congrats");
			text.setPosition(0, 20);
			window.draw(text);
		}
		{
			Font font;//шрифт 
			font.loadFromFile("CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
			Text text("AMMO IS EMPTY!", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
			String str;
			str = "Bullets : ";
			str.insert(str.getSize(), std::to_string(hero.ammo()));
			text.setFillColor(Color::Red);
			if (hero.ammo() > 0) {
				text.setFillColor(Color::Black);
				text.setString(str);
			}
			text.setPosition(440, 00);
			text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
			window.draw(text);
			text.setString("congrats");
			text.setPosition(440, 20);
			window.draw(text);
		}
		for (int i = 0; i < golems.size(); i++) {
			window.draw(golems[i].get_sprite());
		}

	
		window.display();
	}
	return 0;
}