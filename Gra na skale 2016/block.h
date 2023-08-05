#pragma once

#include "mainobj.h"

class block : public staticobj
{
public:
	block(int x, int y, const sf::Texture& it)
	{
		sprite.setTexture(it, 1);
		sprite.setPosition(x, y);
	}

};