#pragma once

#include "SFML\Graphics\RenderStates.hpp"
#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Text.hpp"


class staticobj : public sf::Drawable
{
public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
	virtual bool collision(const sf::Vector2i&){ return false; }
protected:
	sf::Sprite sprite;
};

/*
class dynamicobj : public sf::Drawable
{
public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
	virtual int collision(const sf::Vector2i&){ return false; } // 0 no col, 1-max id 
	virtual void update();

protected:
	sf::Sprite sprite;
};
*/