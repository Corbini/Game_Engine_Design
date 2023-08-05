#include "states.h"
#include <iostream>



mainState::mainState(sf::RenderWindow* window)
{
	this->window = window;
	running = true;
	main = NULL;
}


mainState::~mainState()
{
	Delete();
}


void mainState::Delete()
{
	if (main != NULL)
	{
		std::cout << "Deleting " << main->name() << ",\n";
		main->Destroy();
		delete main;
	}
}
void mainState::Set(state_sample* newstate)
{
	main = newstate;
	if (main != NULL)
	{
		main->set(window, this);
		std::cout << "Loading " << main->name() << ",\n";
		main->Run();
	}
}
void mainState::SetState(state_sample* newstate)
{
	Delete();
	Set(newstate);
}

void mainState::Update()
{
	if (main != NULL)
	{
		main->Update();
	}
}

void mainState::Render()
{
	if (main != NULL)
	{
		window->draw(*main);
	}
}
