#pragma once

//#include "weapons.h"
#include "map.h"
#include "weapons.h"

struct checks{
	sf::Vector2i v;
	bool b = false;
};


class player : public sf::Drawable
{
	
	typedef void(player::*pntr)();

	
	struct action{

		pntr it;
		action* next = NULL;
		action* back = NULL;
	};
	
public:
	
	player(int, int, sf::Texture*, sf::RenderWindow*, map*);
	~player();

	void render();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void settitle(std::string name);
	


	void update();
	void setgod(bool it){ godmode = it; }


	weapons& weapon_get() { return this->weapon; }

	const int& get_hp() {
		return hp;
	}
	void key_set(sf::Keyboard::Key* it);

	//actions
	bool action_is(pntr);
	void action_add(pntr);
	void action_del(pntr);
	//action func
	void key();
	void show();
	void center();
protected:

	//action storage
	action* actions=new action;
	
	//settings
	std::string name; // to be changed
	bool godmode = false;

	//colisions
	void checks_set(sf::Vector2f);
	checks checkpoint[8]; // check moves (will replace colision_map)
	int distance = 5;

	//jump
	void jump();
	void jumpoff();
	const int jump_up_time = 20;
	int jump_up;
	const int jump_off_time = 10;
	int jump_off=0;

	//keys
	sf::Keyboard::Key keys[8];

	//move
	void makemove();
	sf::Vector2f move; // speed
	float a = 0; // acceleration
	float b = 0; // acceleration
	int speed = 3;
	int run = 5;
	int run_max = 5;

	//hp
	int hp = 1000;

	weapons weapon;
	//sfml things
	sf::Sprite sprite;
	sf::RenderWindow* handle;
	map* map_handle;
	
	sf::Text text;
	sf::Font arial;
	sf::IntRect text_show;

};