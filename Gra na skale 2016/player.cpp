#include "player.h"
#include <math.h>
#include <SFML\Window\Mouse.hpp>
#include <string>


player::player(int x, int y, sf::Texture* text, sf::RenderWindow* it, map* map_handle)
{
	for (int n = 0; n < 8;n++)
		keys[n] = sf::Keyboard::Unknown;

	this->map_handle = map_handle;
	std::cout << "Create player\n";
	sprite.setPosition(x, y);
	sprite.setTexture(*text);

	text_show.width = text->getSize().x/3;
	text_show.height = text->getSize().y / 3;
	text_show.left = text_show.width;
	text_show.top = text_show.height;
	sprite.setTextureRect(text_show);


	sprite.setOrigin(text_show.width / 2, text_show.height / 2);
	checks_set(sprite.getOrigin());
	this->handle = it;

	move.x = 0;
	move.y = 0;
	arial.loadFromFile("arial.ttf");
	this->text.setFont(arial);
	this->text.setCharacterSize(24);
}

player::~player()
{
	std::cout << "Delete player\n";
	action* it = actions;
	while (it->next != NULL) it=it->next;
	it = it->back;
	while (it != NULL) {
		delete it->next;
		it = it->back;
	}
	delete actions;
}


void player::render()
{
}

void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
	target.draw(weapon);
	target.draw(text);
	
}


void player::settitle(std::string name)
{
	this->name = name;
}

void player::update()
{

	sf::Vector2f rect = sprite.getPosition();
	for (int n = 0; n < 8; n++)
		checkpoint[n].b = map_handle->checkspot(rect, sf::Vector2f(checkpoint[n].v));





	action* do_it = actions;
	while (do_it != NULL && do_it->next != NULL) {
		(this->*(do_it->next->it))();
		do_it = do_it->next;
	}


	//take move from accelerate
	makemove();
	//gravity
	if (!godmode &&(!checkpoint[3].b) && (!checkpoint[4].b)) {
		move += map_handle->gravity();
	}

	if ((checkpoint[3].b || checkpoint[4].b) && move.y > 0) {
		move.y = 0;
		sprite.setPosition(sprite.getPosition().x, int((sprite.getPosition().y / 50)) * 50 + sprite.getOrigin().y-0.1);
	}

	//choosing sprite
	text_show.left = text_show.width;
	if (move.x > 0.1)text_show.left += text_show.width;
	if (move.x < 0 - 0.1)text_show.left -= text_show.width;

	text_show.top = text_show.height;
	if (move.y < 0.1)text_show.top += text_show.height;
	if (0 - move.y < 0.1)text_show.top -= text_show.height;
	sprite.setTextureRect(text_show);
	
	
	//check collision and change move
	map_handle->collision(sprite.getGlobalBounds(), move);

	sprite.move(move);



	weapon.update(sprite.getPosition(), sf::Mouse::getPosition(*handle) + map_handle->position());
	text.setPosition(sf::Vector2f(map_handle->position()));

}

void player::checks_set(sf::Vector2f orgin){
	
	checkpoint[0].v.x = orgin.x;
	checkpoint[0].v.y = 0 - orgin.y - distance;

	checkpoint[1].v.x = orgin.x + distance;
	checkpoint[1].v.y = 0 - orgin.y +0.1;

	checkpoint[2].v.x = orgin.x + distance;
	checkpoint[2].v.y = orgin.y;

	checkpoint[3].v.x = orgin.x;
	checkpoint[3].v.y = orgin.y + distance;

	checkpoint[4].v.x = 0-orgin.x;
	checkpoint[4].v.y = orgin.y + distance;

	checkpoint[5].v.x = 0 -orgin.x - distance;
	checkpoint[5].v.y = orgin.y;

	checkpoint[6].v.x = 0 - orgin.x - distance;
	checkpoint[6].v.y = 0 - orgin.y+0.1;

	checkpoint[7].v.x = 0 - orgin.x;
	checkpoint[7].v.y = 0 - orgin.y - distance;


}



void player::makemove()
{
	

	if (a == 0) move.x -= move.x / 5;
	else move.x += a;
	
	if (b == 0) move.y -= move.y / 10;
	else move.y += b;

	a = 0;
	b = 0;


	float max = (speed + run);
	// check max speed
	if (move.x !=0 || move.y!=0)
	{
		if (move.x > max) move.x = max;
		if (move.x < 0 - max) move.x = 0 - max;

		if (move.y > speed + run_max) move.y = speed + run_max;
		if (move.y < 0 - max) move.y = 0 - max;

	}
}



void player::key_set(sf::Keyboard::Key* it)
{
	for (int i = 0; i < 8; i++)
		keys[i] = it[i];
}

bool player::action_is(pntr it)
{
	action* temp = actions->next;

	while (temp != NULL) {
		if (temp->it == it) return true;
		temp = temp->next;
	}
	return false;
}

void player::action_add(pntr it)
{
	action* new_one = actions;

	while (new_one->next != NULL) new_one = new_one->next;
	new_one->next = new action;
	new_one->next->it = it;
	new_one->next->back = new_one;
}

void player::action_del(pntr it)
{
	action* del_one = actions;
	while (del_one->it != it) del_one = del_one->next;

	del_one->back->next = del_one->next;
	if (del_one->next != NULL)del_one->next->back = del_one->back;
	delete del_one;
	
}

void player::jump()
{
	b -= 1.5;
	b -= .8f / (move.y*0.1 + 1);

	if (jump_up >0) jump_up--;
	else {
		jump_off = jump_off_time;
		action_del(&player::jump);
	}

}

void player::jumpoff() 
{
	if (jump_off)jump_off--;
	else action_del(&player::jumpoff);
}

void player::key()
{
	if (sf::Keyboard::isKeyPressed(keys[0]) && !checkpoint[6].b && !checkpoint[5].b)a -= 0.3f;
	if (sf::Keyboard::isKeyPressed(keys[1]) && !checkpoint[2].b && !checkpoint[1].b)a += 0.3f;

	if (jump_off)jump_off--;

	if (sf::Keyboard::isKeyPressed(keys[2])) {
		if (godmode) b -= 0.5f;
		else if ( !jump_off && (checkpoint[3].b || checkpoint[4].b)) {
			jump_up = jump_up_time;
			action_add(&player::jump);
			jump_off = jump_off_time;
			action_add(&player::jumpoff);
		}

	}
	if (sf::Keyboard::isKeyPressed(keys[3])) b += 0.5f;
	if (sf::Keyboard::isKeyPressed(keys[6])) {
		weapon.visable = !weapon.visable;
		if (run == 0)run = run_max;
		else run = 0;
	}
}

void player::show()
{
	text.setString(name + ":\n" +
		"move.x: " + std::to_string(move.x) + ", move.y: " + std::to_string(move.y) + "\n" +
		"c1: " + std::to_string(checkpoint[1].b) + ", c2: " + std::to_string(checkpoint[2].b) + "\n" +
		"c3: " + std::to_string(checkpoint[3].b) + ", c4: " + std::to_string(checkpoint[4].b) + "\n" +
		"c5: " + std::to_string(checkpoint[5].b) + ", c6: " + std::to_string(checkpoint[6].b) + "\n" +
		"c7: " + std::to_string(checkpoint[7].b) + ", c0: " + std::to_string(checkpoint[0].b) + "\n");

	text.setPosition(sf::Vector2f(map_handle->position()));
}

void player::center()
{
	map_handle->cameralock(sprite.getPosition()-sprite.getOrigin());

}

