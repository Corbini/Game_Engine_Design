#pragma once

#include "states.h"

class intro : public state_sample
{
public:

	~intro();
	std::string name() { return "Intro"; }

	void Run();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{}
	void Update();
	void Destroy();

};
