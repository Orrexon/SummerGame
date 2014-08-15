//View.h

#pragma once
#include <SFML\Graphics.hpp>

class View : public sf::View
{
public:
	View(sf::View vi):m_view(vi)
	{}
	~View(){}

	void update(float deltatime, sf::Vector2f position);
	void setView(int x, int y, int w, int h);
	void setView(sf::Vector2f center, sf::Vector2f size);
	sf::View getOwnView() { return m_view; }
private:
	sf::View m_view;
};