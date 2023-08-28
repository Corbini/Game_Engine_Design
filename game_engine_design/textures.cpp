#include "textures.h"

#include <map>
#include <iostream>


sf::Texture* texture::loadTexture(const std::string& name, const std::string &filename)
{
	std::cout << "Load texture: " << name << "\n";
	/* Load the texture */
	sf::Texture tex;
	tex.loadFromFile(filename);

	/* Add it to the list of textures */
	this->t_stor[name] = tex;

	return &t_stor[name];
}

void texture::showall()
{
	std::cout << "Textures:" << std::endl;
	for (auto it : t_stor)
	{
		std::cout << it.first << ",";
	}
	std::cout << std::endl;
}

sf::Texture& texture::getRef(const std::string& texture)
{
	return this->t_stor.at(texture);
}

texture::~texture()
{
	std::cout << "Delete textures\n";
}