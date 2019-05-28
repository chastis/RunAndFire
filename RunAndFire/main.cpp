#include "headers_which_you_need.h"
#include "Entity.h"
#include "Golem.h"
#include "map.h"
#include "loot.h"
#include <vector>
//#include <sstream>

#undef _ITERATOR_DEBUG_LEVEL
#define _ITERATOR_DEBUG_LEVEL 0

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "Run and Fire!");
	View view; view.reset(FloatRect(0, 0, 640, 480));
	
	Clock clock;

	Image hero_Image; hero_Image.loadFromFile("images/MilesTailsPrower.gif");
	hero_Image.createMaskFromColor(Color(0, 0, 0));
	Entity hero(hero_Image, -13, 190, 42, 33, "Hero");
	hero.get_sprite().setScale(0.5, 0.5);

	Image monster_Image; monster_Image.loadFromFile("images/Monster.png");
	monster_Image.createMaskFromColor(Color(255, 255, 255));

	std::vector<std::unique_ptr<Golem>> golems;
	golems.push_back(std::make_unique<Golem>(monster_Image, 64, 170, 28, 34, "Golem1"));
	golems.push_back(std::make_unique<Golem>(monster_Image, 150, 332, 28, 34, "Golem2"));


	Image mapImage; mapImage.loadFromFile("images/map.png");
	mapImage.createMaskFromColor(Color(255, 255, 255));
	Map map(mapImage, 30, 40);

	Image lootImage; lootImage.loadFromFile("images/loot.png");
	lootImage.createMaskFromColor(Color(255, 255, 255));
	Loot loot(lootImage);
	loot.ammo_add(96, 320);
	loot.ammo_add(576, 416);
	loot.ammo_add(500, 416);

	bool bossSpawned = false;
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
			golems[i]->update(time, map);
		}
		hero.update(time, map, golems, loot);
		//std::cout << hero.health << std::endl;
		window.setView(view);
		window.clear(Color(77, 83, 140));

		window.draw(map);
		//loot.ammo_draw(window);
		window.draw(loot);
		window.draw(hero.get_sprite());
		hero.draw_bullet(time, map, window, golems);
		for (int i = 0; i < golems.size(); i++) {
			if (!golems[i]->get_life()) {
				golems.erase(golems.begin() + i); i--;
				if (golems.empty() && !bossSpawned) {
					golems.push_back(std::make_unique<BossGolem>(monster_Image, 150, 332, 28, 34, "Boss"));
					bossSpawned = true;
				}
			}
		}
		if (golems.size() == 0) {
			Font font;//шрифт 
			font.loadFromFile("terminal.TTF");//передаем нашему шрифту файл шрифта
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
			font.loadFromFile("terminal.TTF");//передаем нашему шрифту файл шрифта
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
			font.loadFromFile("terminal.TTF");//передаем нашему шрифту файл шрифта
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
			if (hero.ammo() == 0) window.draw(text);
		}
		for (int i = 0; i < golems.size(); i++) {
			window.draw(golems[i]->get_sprite());
		}

	
		window.display();
	}
	return 0;
}