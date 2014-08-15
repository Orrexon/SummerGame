//View.cpp
#include "stdafx.h"
//#include "View.h"

void View::update(float deltatime, sf::Vector2f x)
{
	m_view.setCenter(x);
}
void View::setView(int x, int y, int w, int h)
{
	m_view.setCenter(sf::Vector2f(x, y));
	m_view.setSize(sf::Vector2f(w, h));
}
void View::setView(sf::Vector2f center, sf::Vector2f size)
{
	m_view.setCenter(center);
	m_view.setSize(size);
}