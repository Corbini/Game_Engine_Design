#include "map.h"

#include <fstream>
#include <iostream>



map::map(sf::RenderWindow* win, std::string name)
{
	for (int n = 0; n < block_max; n++) block[n] = NULL;
	if (win != NULL) window = win;
	std::cout << "Create map\n";
	
	std::cout << "Adding text sprite\n";

	map_text.setActive(true);
	map_text.setSmooth(true);
	sprite.setColor(sf::Color(230,230,255,200));

	addsprite("grass",1);
	addsprite("stone", 2);
	addsprite("dirt", 3);
	//block[1].setColor(sf::Color(96, 64, 60, 250));
	//block[2].setColor(sf::Color(96, 64, 60, 250));
	//block[3].setColor(sf::Color(96, 64, 60, 250));
	load(name);


}

map::~map()
{
	block_del();

}


void map::draw(sf::Drawable* it)
{
	map_text.draw(*it);

}

void map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void map::cameralock(sf::Vector2f it)
{

	it.x -= view.width / 2;
	it.y -= view.height / 2;
	
	int space_x = view.width / 6;
	int space_y = view.height / 6;

	if (it.x - view.left > space_x) {
		it.x -= space_x;
		int new_x = size.x - view.width;
		if (it.x < 0) it.x = 0;
		else if (it.x - new_x > 0) it.x = new_x;
		view.left = it.x;
	}
	else if (view.left - it.x > space_x) {
		it.x += space_x;
		int new_x = size.x - view.width;
		if (it.x < 0) it.x = 0;
		else if (it.x - new_x > 0) it.x = new_x;
		view.left = it.x;
	}

	if (it.y - view.top > space_y) {
		it.y -= space_y;
		int new_y = size.y - view.height;
		if (it.y < 0) it.y = 0;
		else if (it.y - new_y > 0) it.y = new_y;
		view.top = it.y;
	}
	else if (view.top - it.y > space_y) {
		it.y += space_y;
		int new_y = size.y - view.height;
		if (it.y < 0) it.y = 0;
		else if (it.y - new_y > 0) it.y = new_y;
		view.top = it.y;
	}
}
void map::update()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		if (view.left >0)view.left-=5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		if (view.left <800)view.left+=5;
	}

	sprite.setTextureRect(view);
	map_text.draw(mapp);
}

void map::viewposition(const sf::Vector2f& it)
{
	/*
	sf::Vector2i newpos = { size.x, size.y };

	newpos.x /= 2;
	newpos.y /= 2;

	if (it.x < newpos.x) newpos.x += it.x;
	if (it.y < newpos.y) newpos.y += it.y;

	if (newpos.x > mapp.getTextureRect().left) newpos.x = mapp.getTextureRect().left - (sprite.getTextureRect().left / 2);
	if (newpos.y > mapp.getTextureRect().top) newpos.y = mapp.getTextureRect().top - (sprite.getTextureRect().top / 2);

	sprite.setTextureRect(sf::IntRect(newpos.x, newpos.y, sprite.getTextureRect().width, sprite.getTextureRect().height));
	*/
}

bool map::collision(const sf::FloatRect& object, sf::Vector2f& move)
{
	bool test = false;
	if (checkspot({ object.left, object.top }, move)) test = true;
	if (checkspot({ object.left, object.top + object.height }, move)) test = true;
	if (checkspot({ object.left + object.width, object.top }, move)) test = true;
	if (checkspot({ object.left + object.width, object.top + object.height }, move)) test = true;
	return test;
}

bool map::checkspot(sf::Vector2f object, sf::Vector2f& move)
{
	bool test = false;
	if (move.x!=0 && move.y == 0 && move.x / move.y > 2. / 5.){
		test = (checkx(object, move));
		object.x += move.x;
		test = test || (checky(object, move));
	}
	else {
		test = (checky(object, move));
		object.y += move.y;
		test = test || (checkx(object, move));
	}
	return test;
}


bool map::checkx(sf::Vector2f object, sf::Vector2f& move) // 0-x, 1-y
{
	sf::Vector2i check = { int(object.x + move.x) / 50, int(object.y) / 50 };

	if (object.x + move.x < 0 || object.x + move.x > size.x - view.width) {
		move.x = 0;
		return true;
	}

	if (block_collision[check.x][check.y])
	{
		if (object.x / 50 >= check.x && move.x <= 0){
			move.x = 0;// check.x * 50 - (int)object.x + 50;
			return true;
		}
		else if (object.x / 50 <= check.x && move.x >= 0){
			move.x = 0;// check.x * 50 - object.x + move.x;
			return true;
		}
	}
	return false;
}

bool map::checky(sf::Vector2f object, sf::Vector2f& move) 
{
	sf::Vector2i check = { int(object.x) / 50, int(object.y+move.y) / 50 };

	if (object.y + move.y < 0 || object.y + move.y > size.y - view.height) {
		move.y = 0;
		return true;
	}

	if (block_collision[check.x][check.y])
	{
		if (object.y / 50 >= check.y && move.y <= 0){
			move.y = 0;// check.y * 50 - object.y;
			return true;
		}
		else if (object.y / 50 <= check.y && move.y >= 0){
			move.y = 0;// check.y * 50 - object.y - 1;
			return true;
		}
	}
	return false;
}

void map::addsprite(std::string name, short id)
{
	tstor.loadTexture(name, name + ".png");

	block[id] = new sf::Sprite(tstor.getRef(name));
}

void map::block_set()
{
	block_collision = new short*[size.x / 50];

	for (int x = 0; x * 50 < size.x; x++)
	{
		block_collision[x] = new short[size.y/50];
		for (int y = 0; y * 50 < size.y; y++){
			block_collision[x][y] = 0;
		}
	}

}

void map::block_del()
{
	for (int n = 0; n < block_max; n++) delete block[n];

	for (int x = 0; x * 50 < size.x; x++){
		delete block_collision[x];
	}

	delete block_collision;
}

void map::load(std::string name)
{
	std::cout << "Loading map\n";
	std::ifstream file;
	file.open(name + ".sav", std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		file.read((char*)&size.x, sizeof(int));
		file.read((char*)&size.y, sizeof(int));


		std::cout << size.x << "\n";
		std::cout << size.y << "\n";

		block_set(); // create 2 dim tabel

		map_text.create(size.x, size.y);
		map_text.clear(sf::Color(137, 207, 240, 255));

		short it[3];
		while (!(file.eof()))
		{
			file.read((char*)(&it[0]), sizeof(short));
			std::cout << it[0];
			file.read((char*)(&it[1]), sizeof(short));
			std::cout << it[1];
			file.read((char*)(&it[2]), sizeof(short));
			std::cout << it[2] << " ";
			print(it[0], it[1], it[2]);
			block_collision[ it[0]][it[1]] =it[2];
		}
		map_text.display();
		mappy = map_text.getTexture();
		mapp.setTexture(mappy);
		sprite.setTexture(map_text.getTexture());

		loaded = true;
	}

	file.close();
}

void map::print(short x, short y, short id)
{
	if (id != 0)
	{

		block[id]->setPosition(x * 50, y * 50);
		map_text.draw(*block[id]);

	}
}
