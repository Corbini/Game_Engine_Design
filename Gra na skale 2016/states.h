#pragma once

#include "SFML\Graphics\RenderWindow.hpp"
#include <SFML\Graphics\Drawable.hpp>
#include "gui.h"

class music;
class mainState;



class state_sample : public sf::Drawable
{
public:
	state_sample(){};
	void set(sf::RenderWindow* newwindow, mainState* state) {
		window = newwindow;
		g.set_window(window);
		corestate = state;
	}
	virtual std::string name(){ return "no_name"; }
	virtual void Run(){}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void Update(){}
	virtual void Destroy(){}
	virtual music* Music(){ return NULL; }
	texture* Texture(){ return NULL; }
protected:
	sf::RenderWindow* window; 
	mainState* corestate;
	gui g;
	
private:
	friend class console;


};




class mainState
{
public:
	bool running;

	mainState(sf::RenderWindow*);
	~mainState();

	void Delete();
	void Set(state_sample* newstate);
	void SetState(state_sample* newstate);
	void Update();
	void Render();

private:

	friend class console;

	sf::RenderWindow* window;
	state_sample* main;
};

//extern mainState corestate;