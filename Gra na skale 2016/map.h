#pragma once

#include "textures.h"
#include "SFML\Graphics.hpp"

struct id_block
{
	bool t[50][50];
	sf::Texture* texture;
	
};

struct map_block
{
	id_block* block;
	sf::Vector2i pos;
};

class map : public sf::Drawable
{
public:
	map(sf::RenderWindow*, std::string);
	~map();

	void draw(sf::Drawable*);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void cameralock(sf::Vector2f);
	void update();
	const short block_max = 256;
	sf::Vector2i& getSize() { return this->size; }

	bool collision(const sf::FloatRect&, sf::Vector2f&);
	void viewposition(const sf::Vector2f&);

	sf::RenderTexture* get_win() { return &map_text; }

	bool checkspot(sf::Vector2f, sf::Vector2f&);


	sf::Vector2i position() {
		return{ view.left, view.top };
	}

	const sf::Vector2f& gravity(){ return grav_froce; }

	const bool& is_load() { return loaded; }
private:

	bool checkx(sf::Vector2f, sf::Vector2f&);
	bool checky(sf::Vector2f, sf::Vector2f&);

	sf::Vector2f grav_froce = { 0, 1.5 };

	void print(short, short, short);
	void load(std::string);
	void addsprite(std::string, short);


	bool loaded = false;
	sf::RenderWindow* window;

	sf::IntRect view = { 0, 0, 800, 600 };
	sf::Sprite sprite;

	sf::Sprite  mapp;
	sf::Texture mappy;

	sf::RenderTexture map_text;
	sf::Vector2i size = { 0, 0 };

	sf::Sprite* block[256];
	short** block_collision;
	void block_set();
	void block_del();

	texture tstor;

	std::string id_name[2048] = { "air","grass","stone","dirt" };

	void load_id(int id);
	id_block id_stor[2048];

};

