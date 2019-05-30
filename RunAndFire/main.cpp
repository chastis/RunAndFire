#include "helpers.h"
#include "Entity.h"
#include "Golem.h"
#include "Ghost.h"
#include "map.h"
#include "loot.h"
#include "globals.h"
#include "functions.h"
#include "Menu.h"

using namespace sf;

bool gameOn;

int main()
{
	bossSpawned = false;
	gameOn = true;
	RenderWindow window(VideoMode(640, 480), "Run and Fire!");
	View view; view.reset(FloatRect(0, 0, 640, 480));

	init();

	Clock clock;

	Image hero_Image; hero_Image.loadFromFile("images/MilesTailsPrower.gif");
	hero_Image.createMaskFromColor(Color(0, 0, 0));
	Entity hero(hero_Image, -13, 190, 42, 33, "Hero");
	hero.get_sprite().setScale(0.5, 0.5);
	hero.spawn(*map);
	Image monster_Image; monster_Image.loadFromFile("images/Monster.png");
	monster_Image.createMaskFromColor(Color(255, 255, 255));

	std::vector<std::unique_ptr<Golem>> golems;
	std::vector<std::unique_ptr<Ghost>> ghosts;
	ghosts_spawn(monster_Image, 23, 28, ghosts, *map);
	golems_spawn(monster_Image, 28, 34, golems, *map);
	map->reset();
	Image lootImage; lootImage.loadFromFile("images/loot.png");
	lootImage.createMaskFromColor(Color(255, 255, 255));
	Loot loot(lootImage);
	loot.ammo_add(96, 320);
	loot.ammo_add(576, 416);
	loot.ammo_add(500, 416);

	sf::Music music;
	music.openFromFile("gamno.wav");
	music.play();
	music.setLoop(true);
	Menu menu;
	bool isWin = false;
	while (window.isOpen())
	{
		if (!menu.is_menu())
		{
			if (music.getStatus() == sf::Music::Status::Stopped) music.play();
			if (level_counter > 2) menu.open(1);
			if (level_counter == 2 && isLevelPassed) 
			{
				std::cout << "Hello! ";
				bool flag = false;
				long long red = 0, green = 0, blue = 0;
				int plus = 1;
				for (long long i = 0; i < 1000; i++)
				{
					
					window.clear(sf::Color(green, red, blue));
					if (red == -1)
					{
						red++;
						plus = 1;
					}
					else if (red == 128)
					{
						if (green == -1)
						{
							green++;
							red--;
						}
						else if (green == 128)
						{
							if (blue == -1)
							{
								blue++;
								green--;
							}
							else if (blue == 128)
							{
								plus = -1;
								blue--;
							}
							else blue += plus;
						}
						else green += plus;
					}
					else red += plus;
					window.display();
					//std::cout << i << std::endl;
				}
				std::cout << "lvl2" << std::endl;
				
				//std::this_thread::sleep_for(std::chrono::seconds(3));
				map->change("map2");
				hero.Restart( * map, golems, ghosts, loot);
				isLevelPassed = false;
				clock.restart();
			}
			auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds());

			clock.restart();
			time = time / 800;

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					menu.open();
					isWin = false;
				}


				

			}

			for (size_t i = 0; i < golems.size(); i++) {
				golems[i]->update(time, *map);
			}
			for (size_t i = 0; i < ghosts.size(); i++) {
				ghosts[i]->update(time, *map, hero.getX(), hero.getY());
			}
			hero.update(time, *map, golems, ghosts, loot);
			//std::cout << hero.health << std::endl;
			window.setView(view);
			window.clear(Color(77, 83, 140));

			window.draw(*map);
			//loot.ammo_draw(window);
			window.draw(loot);
			window.draw(hero);
			hero.draw_bullet(time, *map, window, golems, ghosts);
			for (size_t i = 0; i < golems.size(); i++) {
				if (!golems[i]->get_life()) {
					if (bossSpawned)
						loot.portal_add(golems[i]->get_x(), golems[i]->get_y());
					else loot.ammo_add(golems[i]->get_x(), golems[i]->get_y());
					golems.erase(golems.begin() + i); i--;
					if (golems.empty() && !bossSpawned) {
						golems.push_back(std::make_unique<BossGolem>(monster_Image, 500, -100, 28, 34, "Boss"));
						bossSpawned = true;
					}
				}
			}
			for (size_t i = 0; i < ghosts.size(); i++) {
				if (!ghosts[i]->get_life()) {
					loot.ammo_add(ghosts[i]->get_x(), ghosts[i]->get_y());
					ghosts.erase(ghosts.begin() + i); i--;
				}
			}
			Text text("Level "s + std::to_string(level_counter), *font, FONT_SIZE);
			text.setFillColor(Color::Black);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
			text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
			if (golems.size() == 0 && ghosts.size() == 0) {
				text.setString("YOU WIN!");//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)	
				window.draw(text);
				text.setString("congrats");
				text.setPosition(0, 20);
				window.draw(text);
			}
			else if (!hero.alive()) {
				text.setString("YOU DIED!");//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
				text.setFillColor(Color::Black);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
				text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
				window.draw(text);
				text.setString("congrats");
				text.setPosition(0, 20);
				window.draw(text);
			}
			else
			{
				window.draw(text);
				if (bossSpawned) text.setString("Boss can be defeated only from the top");
				else text.setString("Golems can be defeated in behind");
				text.setPosition(0, 20);
				window.draw(text);
			}
			{
				Text text("AMMO IS EMPTY!", *font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
				String str;
				str = "Bullets : ";
				str.insert(str.getSize(), std::to_string(hero.ammo()));
				text.setFillColor(Color::Red);
				if (hero.ammo() > 0) {
					text.setFillColor(Color::Black);
					text.setString(str);
				}
				text.setPosition(440, 00);
				text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
				window.draw(text);
			}
			int red = 255 * (1 - hero.hp() / static_cast<float>(PLAYER_HP));
			int green = 255 * (hero.hp() / static_cast<float>(PLAYER_HP));
			text.setFillColor(Color(red, green, 0));//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
			text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
			String str = "HP: ";
			str.insert(str.getSize(), std::to_string(hero.hp()));
			text.setString(str);
			text.setPosition(440, 25);
			window.draw(text);
			for (size_t i = 0; i < golems.size(); i++) {
				window.draw(golems[i]->get_sprite());
			}
			for (size_t i = 0; i < ghosts.size(); i++) {
				ghosts[i]->draw(window);
			}
		}
		else
		{
			music.stop();
			//menu;
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //coord of mouse (in px)
			sf::Vector2f pos = window.mapPixelToCoords(pixelPos); //coord of mous (transform)
			menu.change_colors(pos);
			Event event;
			while (window.pollEvent(event))
			{
				menu.change_colors(pos);
				//pressed left mouse
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						menu.work(pos, window, hero, *map, golems, ghosts, loot);
					}
				}
				
			}
			window.clear();
			menu.draw(window);
			clock.restart();
			isLevelPassed = false;
		}
		window.display();
	}
	gameOn = false;
	return 0;
}