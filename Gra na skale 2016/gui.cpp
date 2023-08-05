#include "gui.h"

#include <iostream>
#include "button.h"
#include "block.h"
#include <SFML\Window\Mouse.hpp>

gui::gui()
:tstor()
{
}

gui::~gui()
{
	for (auto it : stor) delete it;
	stor.clear();
}

void gui::add(staticobj* it)
{
	if (it != NULL)stor.push_back(it);
	else std::cout << "Object can't be added to gui\n";
}

void gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (auto it : stor){
		target.draw(*it);
	}
}

action* gui::collision()
{
	action* x = NULL;
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	short m = 0;
	for (auto it : stor){
		if (it->collision(mouse)){
			x = new action { m, x};
		}
		m++;
	}
	return x;
}

void gui::button(int x, int y, std::string text, std::string title,const sf::Font& font)
{
	add(new class::button(x, y, tstor.getRef(text), title, font));

}

void gui::button(int x, int y, std::string text)
{
	add(new class::button(x, y, tstor.getRef(text)));

}

void gui::block(int x, int y, std::string text)
{
	this->add(new class::block(x, y, tstor.getRef(text)));
}