#include <iostream>
#include <fstream>
#include "id.h"

id::id()
	: window(sf::VideoMode(160, 480), "tools", sf::Style::Default),
	thread(&id::update, this)
{
	window.setActive(false);
	window.setFramerateLimit(30);


	for (int n = 0; n < 2048; n++) id_stor[n] = NULL;

	id_stor[0] = new id_block;
	id_stor[0]->name = "air";
	id_stor[0]->sprite.setPosition(sf::Vector2f(last));


	id_load(1, "dirt");
	id_load(2, "stone");
	select_id(2);

	window.clear(sf::Color::Magenta);
	window.display();

	thread.launch();
}

void::id::kill()
{
	thread.wait();
	thread.terminate();
}

void id::update()
{
	window.setActive(false);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				kill();
				break;

			case sf::Event::MouseWheelScrolled:
				//sf::Vector2f pos = ;
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Button::Left
					&&event.mouseButton.x % 70 > 20 && event.mouseButton.y % 70 > 20)
				{
					int b = (2 * (event.mouseButton.y / 70)) + (event.mouseButton.x / 90);
					select_id(b);
				}
				break;

			default:
				break;
			}
		}

		sf::Vector2i pos = sf::Mouse::getPosition(window);
		if (pos.x> 20 && pos.y % 70 > 20)
		{
			int b = (2 * (pos.y / 70)) + (pos.x / 90);
			if (id_stor[b] != NULL)
			{
				if (miniselect!=NULL && miniselect!=select)miniselect->sprite.setColor(sf::Color::White);
				miniselect = id_stor[b];
				if (miniselect != select)miniselect->sprite.setColor(sf::Color(255, 255, 255, 200));
			}
		}
		else
		{
			if (miniselect != NULL && miniselect != select)miniselect->sprite.setColor(sf::Color::White);
			miniselect = NULL;
		}
		render();

	}
}

void id::select_id(int id)
{
	if (id_stor[id] == NULL) return;
	std::cout << "selected: " << id << "\n";
	if (select != NULL)select->sprite.setColor(sf::Color::White);
	select = id_stor[id];
	select->sprite.setColor(sf::Color(255, 255, 255, 128));
	render();
}

bool id::id_load(int id, std::string name)
{
	//thread.wait();
	if (id == -1)
	{
		std::cout << "wpisz id tekstury: ";
		int id;
		std::cin >> id;
		if (std::cin.fail() || id < 0 || id >= 2048) {
			std::cout << "zle podano id\n";
			return 0;
		}
	}
	/*
	if (id_stor[id] != NULL) {
		std::cout << "id jest juz wykorzystane\n";
		return 0;
	}
	*/

	id_stor[id] = new id_block;
	for (int n = 0; n < 50; n++) {
		for (int m = 0; m < 50; m++) {
			id_stor[id]->t[n][m] = false;
		}
	}

	if (name == "")
	{
		std::cout << "wpisz nazwe tekstury: ";
		std::cin >> id_stor[id]->name;
	}
	else id_stor[id]->name = name;

	if (id_stor[id]->texture.loadFromFile(id_stor[id]->name + ".png")) {
		id_stor[id]->sprite.setTexture(id_stor[id]->texture);
		std::cout << "wczytano teksture\n";

		last = last + move[n % 2];
		id_stor[id]->sprite.setPosition(sf::Vector2f(last));
		n++;
		return 1;
	}
	else {
		std::cout << "problem z wczytaniem tekstury\n";
		delete id_stor[id];
		return 0;
	}
}

void id::render()
{
	window.setActive(true);
	window.clear(sf::Color::Magenta);


	for (int n = 0; n < 1024; n++)
		if (id_stor[n] != NULL)window.draw(id_stor[n]->sprite);
	window.display();
	window.setActive(false);
}