//SpriteManager.h

#pragma once
#include <map>
#include <string>
#include <SFML\Graphics.hpp>
class SpriteManager
{
public:
	SpriteManager(const std::string& directory);
	~SpriteManager(){}

	bool LoadFromFile(const std::string& filename);

	sf::Sprite load(const std::string& filename, int x, int y, int w, int h);

private:
	std::string m_directory;
	std::map<std::string, sf::Texture> m_sprites;
};