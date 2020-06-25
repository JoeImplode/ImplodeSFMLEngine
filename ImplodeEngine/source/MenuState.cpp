#include "pch.h"
#include "GameState.h"
#include "MenuState.h"
#include "Animation.h"
#include "AssetPool.h"

MenuState::MenuState()
{
	this->m_assetPool = new AssetPool();
	this->m_assetPool->LoadTexture("resources/textures/chest.png", "chest");
	this->m_animation = new Animation(0.1f, sf::Vector2f(100.0f, 100.0f), true);
	this->m_animation->SetAnimationSheet(m_assetPool->GetTexture("chest"), 1, 8);
}

void MenuState::Update(float deltaTime)
{
	this->m_animation->Update(deltaTime);
}

void MenuState::Draw(sf::RenderWindow* window)
{
	rect.setPosition(sf::Vector2f(100.0f, 100.0f));
	rect.setSize(sf::Vector2f(200.0f, 200.0f));
	rect.setFillColor(sf::Color::Cyan);

	window->clear();
	window->draw(rect);
	this->m_animation->Render(window);
	window->display();
}
