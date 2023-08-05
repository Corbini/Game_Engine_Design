
#include "id.h"
#include "block.h"
#include <iostream>

block::block(id* handle, sf::Vector2i size)
	: window(sf::VideoMode(size.x, size.y), "block", sf::Style::Default)
{
	//
	this->handle = handle;

	//window settings
	window.setFramerateLimit(30);
	window.setActive(false);

	//settings sprites for collisions
	block_sprite.setScale(sf::Vector2f(10., 10.));
	for (int n = 0; n < 50; n++) {
		for (int m = 0; m < 50; m++) {
			mini[n][m].setPosition(10 * n, 10 * m);
			mini[n][m].setColor(color[0]);
			mini[n][m].setTextureRect(sf::IntRect(0, 0, 10, 10));
		}
	}
}

bool block::update()
{
	if (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (block_handle != handle->selected()) {
			block_handle = handle->selected();
			block_sprite.setTexture(block_handle->texture);
			for (int n = 0; n < 50; n++) {
				for (int m = 0; m < 50; m++) {
					mini[n][m].setColor(color[block_handle->t[n][m]]);
				}
			}

			render();
		}
		return true;
	}
	else return false;
}

void block::render()
{
	window.clear();
	window.draw(block_sprite);
	//for (auto it : mini) window.draw(*it);
	window.display();
}