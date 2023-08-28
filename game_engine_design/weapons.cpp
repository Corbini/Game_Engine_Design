#include "weapons.h"


bullets::bullets(sf::Vector2f pos, float rotation, bool friendly_fire, sf::Texture* text)
{
	sprite.setPosition(pos);
	sprite.setRotation(rotation);
	this->friendly_fire = friendly_fire;
	if (text != NULL)sprite.setTexture(*text);
	sprite.setScale(sf::Vector2f(0.5,0.5));

	int rot = rotation;
	short quarters[4][2] = { { 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 } };
	move.x = quarters[(rot / 90)%4][0]*speed;
	move.y = quarters[(rot / 90)%4][1]*speed;
	if (move.x == move.y){
		move.x *= (float(90 - (rot % 90)) / 90.);
		move.y *= (float(rot % 90) / 90.);
	}
	else {
		move.x *= (float(rot % 90) / 90.);
		move.y *= (float(90 - (rot % 90)) / 90.);
	}
}

bool bullets::update()
{
	sprite.move(move);
	if (cooldown)cooldown--;
	else return true;
	return false;

}

void weapons::load(sf::Texture* text, sf::Texture* bul_text)
{
	this->bul_text = bul_text;

	sprite.setTexture(*text);
	rect = sprite.getTextureRect();
	rect.width = rect.width / 2;

	sprite.scale(sf::Vector2f(0.1, 0.1));
	sprite.setOrigin(0, rect.height / 2);
}

void weapons::update(sf::Vector2f pos, sf::Vector2i mouse)
{
	sprite.setPosition(pos);
	if (mouse.x != 0)
	{

		sprite.setRotation(atan((pos.y - mouse.y) / (pos.x - mouse.x)) * 180 / 3.14);
		if ((pos.x > mouse.x)) {
			rect.left = 0;
			sprite.setOrigin(rect.width, rect.height / 2);
			t = 180;
		}
		else {
			rect.left = rect.width;
			sprite.setOrigin(0, rect.height / 2);
			t = 0;
		}
		sprite.setTextureRect(rect);
	}
	else sprite.setRotation(180*(mouse.y < 0));

	action* temp = bull_stor;
	while (temp->next != NULL) {
		if (temp->next->it->update()) bullets_del(temp->next->it);
		else temp = temp->next;
	}
	//if (bullet != NULL) bullet->update();

	if (cooldown) cooldown--;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && visable) shoot();

}

void weapons::shoot()
{
	//delete bullet;
	bullet = new bullets(sprite.getPosition(), sprite.getRotation()+t , true, bul_text);
	bullets_add(bullet);
	cooldown = 5;
}