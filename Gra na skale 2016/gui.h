#ifndef GUI_H
#define GUI_H

#include "mainobj.h"
#include "textures.h"
#include <SFML\Graphics\RenderWindow.hpp>

class sf::RenderWindow;

struct action{
	short x;
	action* next;
};


class gui : public sf::Drawable
{
public:
	gui();
	~gui();

	void set_window(sf::RenderWindow* window){ this->window = window; }
	void add(staticobj*);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void button(int, int, std::string);
	void button(int, int, std::string, std::string,const sf::Font&);
	void block (int, int, std::string);
	action* collision();

	staticobj* get(int id) { return stor[id]; }

	texture* tex(){return &tstor;}

private:

	std::vector<staticobj*> stor;
	texture tstor;
	sf::RenderWindow* window;
};

#endif