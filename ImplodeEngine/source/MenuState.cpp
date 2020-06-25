#include "pch.h"
#include "GameState.h"
#include "MenuState.h"
#include "Animation.h"
#include "AssetPool.h"

MenuState::MenuState()
{
	this->m_assetPool = new AssetPool();
	this->m_assetPool->LoadTexture("resources/textures/link.png", "enemy");
	this->m_animation = new Animation(0.1f, sf::Vector2f(300.0f, 200.0f));
	this->m_animation->SetAnimationSheet(m_assetPool->GetTexture("enemy"), 8, 10);
	this->m_animation->SetScale(sf::Vector2f(2.0f, 2.0f));
	this->m_animation->SetRepeated(true);
	this->m_animation->SetRow(4);
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
