#include "states.h"
#include "state_intro.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include <iostream>



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "The Game", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);


	mainState corestate(&window);

	//console con;
	corestate.SetState(new intro);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close(); 
			}
		}

		window.clear();
		
		corestate.Update();
		corestate.Render();

		window.display();
	}


	return 0;
}
