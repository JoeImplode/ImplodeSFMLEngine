#include "pch.h"
#include "GameState.h"
#include "MenuState.h"

void MenuState::Update(float deltaTime)
{

}

void MenuState::Draw(sf::RenderWindow* window)
{
	rect.setPosition(sf::Vector2f(100.0f, 100.0f));
	rect.setSize(sf::Vector2f(200.0f, 200.0f));
	rect.setFillColor(sf::Color::Cyan);

	window->clear();
	window->draw(rect);
	window->display();
}
