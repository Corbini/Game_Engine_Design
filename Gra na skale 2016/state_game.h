#pragma once

class gui;
class player;
class map;
class statusbar;

#include "states.h"
#include "fonts.h"



class game : public state_sample
{
public:

	~game();
	std::string name() { return "Game"; }

	void Run();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update();
	void Destroy();
	music* Music(){ return mmusic; };

private:
	friend class console;

	map* mmap;
	texture tex;
	music* mmusic;
	player* player_first;
	player* player_second;
	statusbar* hp;
	statusbar* mp;
	fonts font;
	std::vector<sf::Drawable*>stor;

};