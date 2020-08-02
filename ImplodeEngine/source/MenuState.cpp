#include "pch.h"
#include "GameState.h"
#include "MenuState.h"
#include "Animation.h"
#include "AssetPool.h"

MenuState::MenuState()
{
	this->m_assetPool = new AssetPool();
	this->m_assetPool->LoadTexture("resources/textures/sliderTest.png", "button");
	this->m_assetPool->LoadTexture("resources/textures/selectorTest.png", "slider");
	this->m_assetPool->LoadTexture("resources/textures/buttonBack.png", "aporva");
	this->m_assetPool->LoadTexture("resources/textures/saveIcon.png", "save");
	this->m_assetPool->LoadTexture("resources/textures/man.png", "man");
	this->m_assetPool->LoadTexture("resources/textures/Yes.png", "yes");
	this->m_assetPool->LoadTexture("resources/textures/No.png", "no");
	this->m_assetPool->LoadFont("resources/fonts/Roboto-Light.ttf", "font");

	this->m_button = new Button("", sf::Vector2f(100, 100), sf::Vector2f(0.2f, 0.2f), buttonState,true);
	this->m_button->SetTexture(m_assetPool->GetTexture("save"));
	this->m_button->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_button->SetLabelPos(sf::Vector2f(0, -100.0f));

	this->m_slider = new Slider("Slider",sf::Vector2f(400, 400), sf::Vector2f(0.7f,0.7f),sf::Vector2f(0.7f,0.7f),floatRef);
	this->m_slider->SetTextures(m_assetPool->GetTexture("button"),m_assetPool->GetTexture("slider"));

	this->m_buttonGroup = new ButtonGroup("Button Group", sf::Vector2f(300, 300), sf::Vector2f(1, 1), true, m_boolToCheck, m_assetPool->GetTexture("aporva")); //texture
	this->m_buttonGroup->SetButtons(m_assetPool->GetTexture("yes"), sf::Vector2f(0.8f,0.8f), m_assetPool->GetTexture("no"),sf::Vector2f(0.8f,0.8f));
	
	this->m_buttonGroup->SetLabelPos(sf::Vector2f(-100.0f, -100.0f));
	this->m_buttonGroup->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_buttonGroup->m_label.setString("Button Group");
	this->m_buttonGroup->m_label.setFillColor(sf::Color::White);

	this->m_publisher = new Publisher();
	this->m_publisher->AddElement(m_button);
	this->m_publisher->AddElement(m_slider);
	this->m_publisher->AddElement(m_buttonGroup);
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
	this->m_publisher->Render(this->m_context->GetWindow());
	this->m_context->GetWindow()->display();
}
