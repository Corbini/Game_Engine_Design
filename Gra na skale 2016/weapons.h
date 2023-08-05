#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Window\Mouse.hpp>
#include <math.h>
#include <iostream>

class bullets : public sf::Drawable{
public:
	bullets(sf::Vector2f, float, bool, sf::Texture*);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite, states);
	}
	bool update();

private:
	int dmg;
	sf::Vector2f move;
	int speed = 20;

	bool friendly_fire;
	sf::Sprite sprite;
	int t;
	int cooldown = 30;
};

class weapons : public sf::Drawable{
public:
	weapons() { std::cout << "created weapon\n"; }

	~weapons(){
		action* temp = bull_stor;
		while (temp->next != NULL) {
			bullets_del(temp->next->it);
		}
		delete temp;
		
	
	}

	void load(sf::Texture* text, sf::Texture* bul_tex);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (visable)target.draw(sprite, states);
		//if (bullet != NULL) target.draw(*bullet);
		action* temp = bull_stor;
		while (temp->next != NULL) {
			target.draw(*temp->next->it, states);
			temp = temp->next;
		}
	}
	void update(sf::Vector2f, sf::Vector2i);
	bool visable = false;
private:

	void shoot();

	sf::Sprite sprite;
	sf::IntRect rect;
	int t=0;

	bullets* bullet;
	struct action {
		bullets* it;
		action* next = NULL;
	};

	void bullets_add(bullets* it) {
		action* temp = bull_stor;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new action;
		temp->next->it = it;
	}

	void bullets_del(bullets* it) {
		action* temp = bull_stor;
		while (temp->next->it != it) temp = temp->next;
		action* del = temp->next;
		temp->next = temp->next->next;
		delete del->it;
		delete del;
	}

	action* bull_stor = new action;
	
	
	sf::Texture* bul_text;
	int cooldown = 0;
	bool can_shoot = true;
};
