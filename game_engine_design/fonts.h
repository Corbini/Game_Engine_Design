#pragma once

#include "SFML\Graphics\Font.hpp"


class fonts
{
public:
	fonts();
	~fonts();

	bool load(const std::string&);

	const sf::Font& get(const std::string&);// const;

	void add(const std::string&);

	void remove(const std::string&);

private:

	std::map <std::string, sf::Font> stor;
};

