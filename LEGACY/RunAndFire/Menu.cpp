#include <time.h>
#include "Menu.h"


Buttons::Buttons()
{
	_name = "";
	_texture; _sprite;
}

Buttons::~Buttons()
{

}

Buttons::Buttons(std::string name, int x, int y, bool visible)
{
	_visible = visible;
	_shine = false;
	_name = name;
	_texture.loadFromFile("images/" + name);
	_sprite.setTexture(_texture);
	//take center
	_sprite.setPosition(x - _texture.getSize().x / 2, y - _texture.getSize().y / 2);
}

bool Buttons::is_visible()
{
	return _visible;
}

bool Buttons::contain(int x, int y)
{
	if (_sprite.getPosition().x <= x && x <= _sprite.getPosition().x + _texture.getSize().x &&
		_sprite.getPosition().y <= y && y <= _sprite.getPosition().y + _texture.getSize().y) return true;
	return false;
}
//turquoise
void Buttons::change_color()
{
	_sprite.setColor(sf::Color(102, 255, 153));
}
//purple
void Buttons::shine_color()
{
	_sprite.setColor(sf::Color(140, 102, 255));
}
//white
void Buttons::return_color()
{
	if (_sprite.getColor() != sf::Color::White) _sprite.setColor(sf::Color::White);
}

void Buttons::draw(sf::RenderWindow &window)
{
	window.draw(_sprite);
}

bool Buttons::is_shine()
{
	return _shine;
}

Menu::Menu()
{
	_is_menu = true;
	Buttons * b_exit = new Buttons("exit.png", 320, 250, true);			//0
	Buttons * b_new_game = new Buttons("newgame.png", 320, 150, true);	//1
	Buttons * b_tutorial = new Buttons("tutorial.png", 320, 350, true);	//2
	Buttons * b_win = new Buttons("win.png", 320, 150, true);			//3
	Buttons * b_controls = new Buttons("controls.png", 320, 240, true); //4
	_buttons.push_back(b_exit);
	_buttons.push_back(b_new_game);
	_buttons.push_back(b_tutorial);
	_buttons.push_back(b_win);
	_buttons.push_back(b_controls);
	reset();
}

Menu::~Menu()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		delete _buttons[i];
	}
}

bool Menu::is_menu()
{
	return _is_menu;
}

void Menu::open(bool isWin)
{
	if (isWin) winReset();
	else reset();
	_is_menu = true;
}

void Menu::close()
{
	_is_menu = false;
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->is_visible())
		{
			//da budet svet
			if (_buttons[i]->is_shine()) _buttons[i]->shine_color();
			_buttons[i]->draw(window);
		}
	}
	//if (_buttons[3]->_visible == true)
		//Text text("Your time is "s + std::to_string(gameTime.getElapsedTime().asSeconds()) + "s"s, *font, FONT_SIZE);
}

void Menu::change_colors(sf::Vector2f pos)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		//button 5 is "map's size". it;s not a button!!!
		if (_buttons[i]->contain(pos.x, pos.y) && i != 5)
		{
			_buttons[i]->change_color();
		}
		else
		{
			_buttons[i]->return_color();
		}
	}
}

void Menu::reset()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (i <= 2)
			//new game //0
			//ext //1
			_buttons[i]->_visible = true;
		else
			//another are not visible
			_buttons[i]->_visible = false;
	}
}

void Menu::winReset()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (i == 3)
			_buttons[i]->_visible = true;
		else
			//another are not visible
			_buttons[i]->_visible = false;
	}
}

void Menu::work(sf::Vector2f pos, sf::RenderWindow &window, Entity & player, Map & map, std::vector<std::unique_ptr<Golem>> & golems, std::vector<std::unique_ptr<Ghost>> & ghosts, Loot & loot)
{
	//button's functions
	auto to_do = [&](int n)
	{
		switch (n)
		{
		//exit
		case 0:
		{
			//game.~Game();
			window.close();

			break;
		}
		//newgame
		case 1:
		{
			level_counter = 1;
			map.change("map1");
			player.Restart(map, golems, ghosts, loot);
			
			_is_menu = false;
			break;
		}
		case 2:
		{
			
			_buttons[0]->_visible = false;
			_buttons[1]->_visible = false;
			_buttons[2]->_visible = false;
			_buttons[4]->_visible = true;
			_buttons[3]->_visible = false;
			break;
		}
		case 3:
		{
			_buttons[0]->_visible = true;
			_buttons[1]->_visible = true;
			_buttons[2]->_visible = true;
			_buttons[3]->_visible = false;
			_buttons[4]->_visible = false;
		}
		case 4:
		{
			_buttons[0]->_visible = true;
			_buttons[1]->_visible = true;
			_buttons[2]->_visible = true;
			_buttons[3]->_visible = false;
			_buttons[4]->_visible = false;
		}
		}

	};
	for (int i = 0; i < _buttons.size(); i++)
	{
		//if we presssed correct button, let it work
		if (_buttons[i]->is_visible() && _buttons[i]->contain(pos.x, pos.y))
		{
			to_do(i);
			return;
		}
	}
}