#pragma once
#include <iostream>
#include <string>
#include <SFML\System\Thread.hpp>
class id;

class console {
public:
	console(id* handle)
	 : thread(&console::update, this)
	{
		this->handle = handle;
		thread.launch();
	}

	void update();

	void kill()
	{
		thread.wait();
		thread.terminate();
	}
protected:
	id* handle;
	sf::Thread thread;
};