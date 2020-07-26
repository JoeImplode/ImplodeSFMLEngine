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
	this->m_assetPool->LoadTexture("resources/textures/newButton.png", "aporva");
	this->m_assetPool->LoadFont("resources/fonts/Roboto-Light.ttf", "font");

	sf::Text m_text;

	m_text.setPosition(100, 50);
	m_text.setString("Config and anti aliasing"); //take string lines make changes for size based on width and how many lines there are
	m_text.setFont(this->m_assetPool->GetFont("font"));
	m_text.setCharacterSize(10);
	m_text.setFillColor(sf::Color::Black);

	sf::Text m_buttonText = m_text;
	m_buttonText.setString("Inner Button");

	this->m_button = new Button("Configure Antialias", sf::Vector2f(50, -25), sf::Vector2f(100, 100), sf::Vector2f(0.2f, 0.2f), buttonState,true);
	this->m_button->SetTexture(m_assetPool->GetTexture("aporva"));
	this->m_button->m_label.setString("Config"); //take string lines make changes for size based on width and how many lines there are
	this->m_button->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_button->m_label.setCharacterSize(20);
	this->m_button->m_label.setFillColor(sf::Color::Yellow);

	std::vector<std::string> strings;
	strings.push_back("Save");
	this->m_button->SetButtonText(strings,m_text);

	this->m_slider = new Slider("Slider", sf::Vector2f(300, 100), sf::Vector2f(400, 400), sf::Vector2f(0.7f,0.7f),sf::Vector2f(0.7f,0.7f),floatRef);
	this->m_slider->SetTextures(m_assetPool->GetTexture("button"),m_assetPool->GetTexture("slider"));

	this->m_yesButton = new Button("Yes", sf::Vector2f(100, 100), sf::Vector2f(0, 0), sf::Vector2f(0.1, 0.1), m_boolToCheck, true);
	this->m_yesButton->SetTexture(m_assetPool->GetTexture("aporva"));
	this->m_yesButton->m_label.setString("Yes"); //take string lines make changes for size based on width and how many lines there are
	this->m_yesButton->m_label.setFont(this->m_assetPool->GetFont("font"));

	this->m_noButton = new Button("No", sf::Vector2f(50, 100), sf::Vector2f(0, 0), sf::Vector2f(0.1, 0.1), m_boolToCheck, true);
	this->m_noButton->SetTexture(m_assetPool->GetTexture("aporva"));
	this->m_noButton->m_label.setString("No"); //take string lines make changes for size based on width and how many lines there are
	this->m_noButton->m_label.setFont(this->m_assetPool->GetFont("font"));

	this->m_buttonGroup = new ButtonGroup("Button Group", sf::Vector2f(200, 200), sf::Vector2f(300, 300), sf::Vector2f(0.6, 0.6), true, m_boolToCheck);
	this->m_buttonGroup->SetTexture(m_assetPool->GetTexture("button"));
	this->m_buttonGroup->SetButtons(*m_yesButton, *m_noButton);

	this->m_publisher = new Publisher();
	this->m_publisher->AddElement(m_button);
	this->m_publisher->AddElement(m_slider);
	this->m_publisher->AddElement(m_buttonGroup);
}

void MenuState::Update(float deltaTime)
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_context->GetWindow()));
	this->m_publisher->Update(deltaTime,sf::Mouse::isButtonPressed(sf::Mouse::Button::Left),mousePos);
	std::cout << sizeof(Button) << std::endl;
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
