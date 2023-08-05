#pragma once

#include <iostream>
#include "SFML\Audio.hpp"




class music
{
public:
	music();
	~music();

	void play(std::string name);
	void play();
	void pause();
	void end();
	void volume(int vol);

private:

	sf::Sound sound;
	sf::SoundBuffer buffer;
};
