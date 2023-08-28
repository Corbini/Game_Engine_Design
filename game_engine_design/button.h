#pragma once

#include "mainobj.h"

class sf::Window;

class button : public staticobj
{
public:
	button(int, int, sf::Texture&);
	button(int, int, sf::Texture&, std::string, const sf::Font&);
	~button();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void settitle(const std::string&);

	void setfont(const sf::Font&);

	bool collision(const sf::Vector2i&);

private:

	void setorgin();

	bool visible = true;
	bool active = false;

	sf::Text text;
};

