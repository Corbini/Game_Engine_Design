#include "button.h"

#include <iostream>
#include "SFML\Window\Mouse.hpp"
#include "SFML\Graphics\Text.hpp"



button::button(int x, int y, sf::Texture& it)
{
	sprite.setPosition(x, y);
	sprite.setTexture(it, 1);

	text.setCharacterSize(24);

	sf::IntRect t = sprite.getTextureRect();
	text.setPosition(sf::Vector2f(sprite.getPosition().x + (t.width / 2), sprite.getPosition().y + (t.height / 2)));
}

button::button(int x, int y, sf::Texture& it, std::string title, const sf::Font& font)
{

	sprite.setPosition(x, y);
	sprite.setTexture(it, 1);

	text.setCharacterSize(24);

	sf::IntRect t = sprite.getTextureRect();
	text.setPosition(sf::Vector2f(sprite.getPosition().x + (t.width / 2), sprite.getPosition().y + (t.height / 2)));

	text.setFont(font);
	settitle(title);
}

button::~button()
{
	std::cout << "Delete button\n";

}

void button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (visible)
	{
		target.draw(sprite);
		target.draw(text);
	}
}


void button::settitle(const std::string& newtitle)
{
	text.setString(newtitle);
	setorgin();
}

void button::setfont(const sf::Font& font)
{
	text.setFont(font);
	setorgin();
}


bool button::collision(const sf::Vector2i& it)
{
	if (sprite.getGlobalBounds().contains(sf::Vector2f (it)))
	{
		sprite.setColor(sf::Color(255, 255, 255, 128));
		active = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) return true;
	}
	else if (active)
	{
		active = false;
		sprite.setColor(sf::Color::White);
	}
	return false;
}

void button::setorgin()
{
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
}