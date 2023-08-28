#pragma once

#include "states.h"

class settings : public state_sample
{
public:

	~settings();
	std::string name() { return "Settings"; }

	void Run();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{}
	void Update();
	void Destroy();

};