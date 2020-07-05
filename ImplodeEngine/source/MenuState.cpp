#include "pch.h"
#include "GameState.h"
#include "MenuState.h"
#include "Animation.h"
#include "AssetPool.h"

MenuState::MenuState()
{
	this->m_assetPool = new AssetPool();
	this->m_assetPool->LoadTexture("resources/textures/man.png", "button");
	this->m_button = new Button("A simple Button", sf::Vector2f(300, 100), sf::Vector2f(100, 100), sf::Vector2f(1, 1), buttonState);
	this->m_button->SetTexture(m_assetPool->GetTexture("button"));
	this->m_slider = new Slider("Slider", sf::Vector2f(300, 100), sf::Vector2f(400, 400), sf::Vector2f(3, 1), floatRef);
	this->m_slider->SetTextures(m_assetPool->GetTexture("button"),m_assetPool->GetTexture("button"));
	this->m_publisher = new Publisher();
	this->m_publisher->AddElement(m_button);
	this->m_publisher->AddElement(m_slider);
}

void MenuState::Update(float deltaTime)
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_context->GetWindow()));
	this->m_publisher->Update(deltaTime,sf::Mouse::isButtonPressed(sf::Mouse::Button::Left),mousePos);
}

void MenuState::Draw()
{
	rect.setPosition(sf::Vector2f(100.0f, 100.0f));
	rect.setSize(sf::Vector2f(200.0f, 200.0f));
	rect.setFillColor(sf::Color::Cyan);

	this->m_context->GetWindow()->clear();
	this->m_context->GetWindow()->draw(rect);
	this->m_publisher->Render(this->m_context->GetWindow());
	this->m_context->GetWindow()->display();
}
