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
	Buttons * b_exit = new Buttons("exit.png", 320, 300, true);
	Buttons * b_new_game = new Buttons("newgame.png", 320, 200, true);
	_buttons.push_back(b_exit);
	_buttons.push_back(b_new_game);
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

void Menu::open()
{
	_is_menu = true;
	reset();
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
		if (i <= 1)
			//new game //0
			//ext //1
			_buttons[i]->_visible = true;
		else
			//another are not visible
			_buttons[i]->_visible = false;
	}
}

void Menu::work(sf::Vector2f pos, sf::RenderWindow &window, Entity & player, Map & map, std::vector<std::unique_ptr<Golem>> & golems, Loot & loot)
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
			player.Restart(map, golems, loot);
			_is_menu = false;
			break;
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