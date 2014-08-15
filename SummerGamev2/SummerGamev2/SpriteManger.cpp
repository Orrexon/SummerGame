//spritemanager.cpp
#include "stdafx.h"
//#include "SpriteManager.h"

SpriteManager::SpriteManager(const std::string& directory)
{
	m_directory = directory;
}

bool SpriteManager::LoadFromFile(const std::string& filename)
{
	std::string path = m_directory + filename;
	sf::Texture tex;
	if (!tex.loadFromFile(path.c_str()))
	{
		printf("SpriteManager::LoadFromFile() texture not loading correctly\n");
		return false;
	}
	m_sprites.insert(std::pair<std::string, sf::Texture>(filename, tex));
	return true;
}

sf::Sprite SpriteManager::load(const std::string& filename, int x, int y, int w, int h)
{
	std::map<std::string,sf::Texture>::iterator it = m_sprites.find(filename);
	if (it == m_sprites.end())
	{
		if (!LoadFromFile(filename))
		{
			printf("SpriteManager::load() Sprite not loaded\n");
		}
		it = m_sprites.find(filename);
	}
	return sf::Sprite(it->second, sf::IntRect(x, y, w, h));
}