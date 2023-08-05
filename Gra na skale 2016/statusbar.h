#pragma once

#include <SFML\Graphics.hpp>
#include "mainobj.h"
#include <iostream>

class statusbar : public sf::Drawable {
public:
	statusbar(sf::Texture* text)
	{
		std::cout << "added hp\n";

		sprite.setTexture(*text);
		sprite.setOrigin(text->getSize().x / 2, text->getSize().y );

	}

	void scale(sf::Vector2f scale) {
		sprite.setScale(scale);
	}

	void orgin(bool it) {
		if (it) {
			sprite.setOrigin(sprite.getTexture()->getSize().x / 2,
				sprite.getTexture()->getSize().y / 2);
		}
		else sprite.setOrigin(0, 0);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}

	void update(int hp, sf::Vector2f pos) {
		sf::IntRect temp = sprite.getTextureRect();
		temp.width = (hp / 1000.)*sprite.getTexture()->getSize().x;
		sprite.setTextureRect(temp);
		sprite.setPosition(pos);
	}

	void color(sf::Color color) {
		sprite.setColor(color);
	}

private:
	sf::Sprite sprite;

};