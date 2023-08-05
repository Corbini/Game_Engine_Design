#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window\Mouse.hpp>

struct id_block
{
	bool t[50][50];
	std::string name;
	sf::Texture texture;
	sf::Sprite sprite;
};


class id {
public:
	id();
	void kill();


	void update();
	bool id_load(int id = -1, std::string name = "");



	id_block* selected() { return select; }

	sf::RenderWindow window;
protected:

	void render();
	void select_id(int);

	id_block* select;
	id_block* miniselect;

	//thread
	sf::Thread thread;

	//position
	sf::Vector2i last = {20,20};
	sf::Vector2i move[2] = { {70,0}, {-70,70} };
	int n = 0; //how many we have blocks;

	//blocks
	id_block* id_stor[2048];

};


