#include "helpers.h"
#include "Entity.h"
#include "Golem.h"
#include "Ghost.h"
#include "BossGhost.h"
#include "map.h"
#include "loot.h"
#include "globals.h"
#include "functions.h"
#include "Menu.h"

using namespace sf;

bool gameOn;

void changeScene(RenderWindow & window)
{
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
}

int main()
{
	//auto gameStart = std::chrono::high_resolution_clock::now();
	sf::Clock gameTime;
	float time = -1;
	bossSpawned = false;
	gameOn = true;
	RenderWindow window(VideoMode(640, 480), "Run and Fire!");
	View view; view.reset(FloatRect(0, 0, 640, 480));

	init();

	Clock clock;

	Image hero_Image; hero_Image.loadFromFile("images/MilesTailsPrower.gif");
	hero_Image.createMaskFromColor(Color(0, 0, 0));
	Entity hero(hero_Image, -13, 190, 42, 31, "Hero");
	hero.get_sprite().setScale(0.5, 0.5);
	hero.spawn(*map);
	Image monster_Image; monster_Image.loadFromFile("images/Monster.png");
	monster_Image.createMaskFromColor(Color(255, 255, 255));

	std::vector<std::unique_ptr<Golem>> golems;
	std::vector<std::unique_ptr<Ghost>> ghosts;
	ghosts_spawn(monster_Image, 23, 28, ghosts, *map);
	golems_spawn(monster_Image, 29, 34, golems, *map);
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
			time = -1;
			gameOn = true;
			if (music.getStatus() == sf::Music::Status::Stopped) music.play();
			if (level_counter > 2)
			{
				gameOn = false;
				changeScene(window);
				menu.open(1);
			}
			if (level_counter == 2 && isLevelPassed) 
			{
				std::cout << "Hello! ";
				bool flag = false;
				music.stop();
				changeScene(window);
				std::cout << "lvl2" << std::endl;
				
				//std::this_thread::sleep_for(std::chrono::seconds(3));
				map->change("map2");
				hero.Restart( * map, golems, ghosts, loot);
				isLevelPassed = false;
				clock.restart();
				music.openFromFile("chut_menshe_gamno.wav");
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
					if (bossSpawned && level_counter == 1)
						loot.portal_add(golems[i]->get_x(), golems[i]->get_y());
					else loot.ammo_add(golems[i]->get_x(), golems[i]->get_y());
					golems.erase(golems.begin() + i); i--;
					if (golems.empty() && !bossSpawned && level_counter == 1) {
						golems.push_back(std::make_unique<BossGolem>(monster_Image, 500, -100, 28, 34, "Boss"));
						bossSpawned = true;
					}
				}
			}
			for (size_t i = 0; i < ghosts.size(); i++) {
				if (!ghosts[i]->get_life()) {
					if (bossSpawned && level_counter == 2)
						loot.portal_add(ghosts[i]->get_x(), ghosts[i]->get_y());
					else loot.ammo_add(ghosts[i]->get_x(), ghosts[i]->get_y());
					ghosts.erase(ghosts.begin() + i); i--;
					if (ghosts.empty() && !bossSpawned & level_counter == 2) {
						ghosts.push_back(std::make_unique<BossGhost>(monster_Image, 320, 240, 23, 28, "Boss"));
						bossSpawned = true;
						map->move();
					}
				}	
			}
			Text text("Level "s + std::to_string(level_counter), *font, FONT_SIZE);
			text.setPosition(20, 0);
			text.setFillColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
			text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
			if (golems.size() == 0 && ghosts.size() == 0) {
				text.setString("YOU WIN!");//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)	
				window.draw(text);
				text.setString("congrats");
				text.setPosition(20, 20);
				window.draw(text);
			}
			else if (!hero.alive()) {
				text.setString("YOU DIED!");//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
				text.setFillColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
				text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
				window.draw(text);
				text.setString("congrats");
				text.setPosition(20, 20);
				window.draw(text);
			}
			else
			{
				window.draw(text);
				if (level_counter == 1)
					if (bossSpawned) text.setString("Boss can be defeated only from the top");
					else text.setString("Golems can be defeated in behind");
				else if (bossSpawned) text.setString("You even can jump on boss ghost's head!");
					else text.setString("You can jump on ghost's head");
				text.setPosition(20, 20);
				window.draw(text);
			}
			{
				Text text("AMMO IS EMPTY!", *font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
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
			}
			int red = 255 * (1 - hero.hp() / static_cast<float>(PLAYER_HP));
			int green = 255 * (hero.hp() / static_cast<float>(PLAYER_HP));
			text.setFillColor(Color(red, green, 0));//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
			text.setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
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
			//gameOn = false;
			if (!gameOn)
			{
				
				sf::String str = "Your time is ";
				sf::Text text("", *font, FONT_SIZE);
				if (time == -1) time = gameTime.getElapsedTime().asSeconds();
				text.setString(str + std::to_string(time) + "s"s);
				text.setFillColor(sf::Color::White);
				text.setPosition(150, 300);
				window.draw(text);
			}
			if (gameOn)
			{
				gameTime.restart();
			}
			menu.draw(window);
			clock.restart();			
			isLevelPassed = false;
			music.openFromFile("gamno.wav");
		}
		window.display();
	}
	return 0;
}