#include "fonts.h"

#include <fstream>


fonts::fonts()
{



}

fonts::~fonts()
{
	stor.clear();
}

bool fonts::load(const std::string& name)
{
	std::fstream file;
	file.open(name + ".txt", std::ios::in);
	if (!file.is_open())return false;

	while (file.eof())
	{
		std::string name;
		file >> name;
		add(name);
	}

	file.close();
	return true;
}

const sf::Font& fonts::get(const std::string& id)// const
{
	return stor[id];
}

void fonts::add(const std::string& name)
{
	sf::Font newfont;
	newfont.loadFromFile(name + ".ttf");
	stor[name] = newfont;
}

void fonts::remove(const std::string& name)
{
	stor.erase(stor.find(name));
}