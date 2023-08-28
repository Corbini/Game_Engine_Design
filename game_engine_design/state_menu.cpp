#include "state_menu.h"

#include "SFML\Graphics.hpp"
#include <iostream>

#include "state_game.h"
#include "state_settings.h"



menu::~menu()
{
	
}

void menu::Run()
{

	texture* tref = g.tex();

	tref->loadTexture("bg", "bg.png");		
	tref->loadTexture("button", "test.png");	

	font.add("arial");

	g.block(0, 0, "bg");
	g.button(350, 250, "button", "Start Game", font.get("arial"));
	g.button(350, 350, "button", "Settings", font.get("arial"));
	g.button(350, 450, "button", "Quit", font.get("arial"));

}

void menu::Update()
{
	buttons();
}

void menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(g);
}

void menu::Destroy()
{

}

void menu::buttons()
{
	
	const sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	if (g.get(1)->collision(mouse))
		corestate->SetState(new game);
	
	else if (g.get(2)->collision(mouse))
		corestate->SetState(new settings);
	
	else if (g.get(3)->collision(mouse)){
		window->close();
	}
	/*
	action* col = g.collision();
	while (col != NULL){
		switch (col->x)
		{
		case 1:
			corestate->SetState(new game);
			break;
		case 2:
			corestate->SetState(new settings);
			break;
		case 3:
			window->close();
			break;
		default:
			break;
		}
		col =col->next;
	}*/
}