#include "state_settings.h"

#include <SFML\Window\Keyboard.hpp>
#include <iostream>

#include "state_menu.h"



settings::~settings()
{


}

void settings::Run()
{
}

void settings::Update()
{


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		corestate->SetState(new menu);
	
}

void settings::Destroy()
{
	this->~settings();

}