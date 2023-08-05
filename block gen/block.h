#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System\Thread.hpp>
class id;

class block {
public:
	block(id* handle, sf::Vector2i size = { 500,500 });
	bool update();


	void render();
	bool isOpen() { return window.isOpen(); }

protected:
	sf::Color color[2] = { sf::Color(255, 255, 255, 128), sf::Color(sf::Color::White)};
	sf::Sprite mini[50][50];

	sf::Sprite block_sprite;
	id_block* block_handle = NULL;


	id* handle;
	sf::RenderWindow window;
};