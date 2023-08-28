#pragma once

#include <map>
#include "SFML\Graphics\Texture.hpp"


class texture
{
private:

	/* Array of textures used */
	std::map<std::string, sf::Texture> t_stor;

public:

	/* Add a texture from a file */
	sf::Texture* loadTexture(const std::string& name, const std::string &filename);

	void showall();

	/* Translate an id into a reference */
	sf::Texture& getRef(const std::string& texture);

	~texture();
};

