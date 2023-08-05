#ifndef STATE_MENU_H
#define STATE_MENU_H

class gui;
#include "fonts.h";

#include "states.h"

class menu : public state_sample
{
public:

	~menu();
	std::string name() { return "Menu"; }
	
	void Run();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update();
	void Destroy();

private:

	void buttons();

	fonts font;
};

#endif