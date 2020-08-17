#include "pch.h"
#include "GameState.h"
#include "MenuState.h"
#include "Animation.h"
#include "AssetPool.h"

MenuState::MenuState(GameContext* context) : GameState(context)
{
	this->m_assetPool = new AssetPool();
	this->m_assetPool->LoadTexture("resources/textures/sliderTest.png", "button");
	this->m_assetPool->LoadTexture("resources/textures/selectorTest.png", "slider");
	this->m_assetPool->LoadTexture("resources/textures/buttonBack.png", "aporva");
	this->m_assetPool->LoadTexture("resources/textures/saveIcon.png", "save");
	this->m_assetPool->LoadTexture("resources/textures/man.png", "man");
	this->m_assetPool->LoadTexture("resources/textures/Yes.png", "yes");
	this->m_assetPool->LoadTexture("resources/textures/No.png", "no");
	this->m_assetPool->LoadTexture("resources/textures/ddSelect.png", "DropDown");
	this->m_assetPool->LoadTexture("Resources/textures/ddButton.png", "ddButton");
	this->m_assetPool->LoadFont("resources/fonts/Roboto-Light.ttf", "font");

	this->m_button = new Button("", sf::Vector2f(100, 100), sf::Vector2f(0.08f, 0.08f), buttonState,true,true);
	this->m_button->SetTexture(m_assetPool->GetTexture("save"));
	this->m_button->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_button->SetLabelPos(sf::Vector2f(0, -100.0f));

	this->m_slider = new Slider("Slider",sf::Vector2f(400, 400), sf::Vector2f(0.7f,0.7f),sf::Vector2f(0.7f,0.7f),floatRef,true);
	this->m_slider->SetTextures(m_assetPool->GetTexture("button"),m_assetPool->GetTexture("slider"));

	this->m_buttonGroup = new ButtonGroup("Button Group", sf::Vector2f(300, 300), sf::Vector2f(1.3f, 1.3f), true,this->m_slider->GetActivatedAddress(), m_assetPool->GetTexture("aporva"),true); //texture
	this->m_buttonGroup->SetButtons(m_assetPool->GetTexture("yes"), sf::Vector2f(1.0f,1.0f), m_assetPool->GetTexture("no"),sf::Vector2f(1.0f,1.0f));
	
	this->m_buttonGroup->SetLabelPos(sf::Vector2f(-100.0f, -100.0f));
	this->m_buttonGroup->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_buttonGroup->m_label.setFillColor(sf::Color::White);

	this->m_widgetGroup = new Widget("", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5, 9), m_assetPool->GetTexture("aporva"),true);
	this->m_widgetGroup->AddElement(this->m_buttonGroup, sf::Vector2f(0.1f, 0.4f));
	this->m_widgetGroup->AddElement(this->m_button, sf::Vector2f(0.5f, 0.5f));
	this->m_widgetGroup->AddElement(this->m_slider, sf::Vector2f(0.7f, 0.7f));
	
	this->m_textInput = new TextInput("Text Input", sf::Vector2f(250.0f, 20.0f), sf::Vector2f(0.7f, 0.5f), this->m_assetPool->GetTexture("DropDown"),
		this->m_assetPool->GetTexture("DropDown"), sf::Vector2f(0.3f, 0.5f), this->m_stringToSet, 20, 20, "Send", true,m_context->GetEvent(),*m_context->GetWindow(),this->m_assetPool->GetFont("font"));

	sf::Text txt;
	txt.setFillColor(sf::Color::Black);
	txt.setFont(this->m_assetPool->GetFont("font"));
	txt.setString("Selection");
	sf::Text newTxt;
	newTxt.setFillColor(sf::Color::Yellow);
	newTxt.setFont(this->m_assetPool->GetFont("font"));
	newTxt.setString("Antialiasing");
	this->m_dropDown = new DropDown("Drop Down", sf::Vector2f(250.0f, 20.0f), sf::Vector2f(0.5f, 0.5f),txt, m_assetPool->GetTexture("ddButton"),m_boolToCheck,true);
	this->m_dropDown->AddSelection(newTxt, "AntiAliasing",m_assetPool->GetTexture("DropDown"), sf::Vector2f(0.5f, 0.5f), m_boolToCheck);
	this->m_dropDown->AddSelection(newTxt, "V-Sync",m_assetPool->GetTexture("DropDown"), sf::Vector2f(0.5f, 0.5f), m_boolToCheck);
	this->m_dropDown->AddSelection(newTxt, "Motion Blur...eww", m_assetPool->GetTexture("DropDown"), sf::Vector2f(0.5f, 0.5f), m_boolToCheck);
	this->m_dropDown->AddSelection(newTxt, "Render Distance", m_assetPool->GetTexture("DropDown"), sf::Vector2f(0.5f, 0.5f), m_boolToCheck);
	this->m_dropDown->AddSelection(newTxt, "Aspect Ratio", m_assetPool->GetTexture("DropDown"), sf::Vector2f(0.5f, 0.5f), m_boolToCheck);

	this->m_widgetGroup->AddElement(this->m_dropDown,sf::Vector2f(0.3f,0.3f));
	this->m_publisher = new Publisher();
	//this->m_publisher->AddElement(m_button);
	//this->m_publisher->AddElement(m_slider);
	//this->m_publisher->AddElement(m_buttonGroup);
	//this->m_publisher->AddElement(m_widgetGroup);	
	//this->m_publisher->AddElement(m_dropDown);
	this->m_publisher->AddElement(m_textInput);

}

void MenuState::Update(float deltaTime)
{
	this->m_mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_context->GetWindow()));

	if (this->m_mousePos.x != this->m_prevMousePos.x || this->m_mousePos.y != this->m_prevMousePos.y)
		this->m_mouseMoved = true;
	else if (this->m_mousePos.x == this->m_prevMousePos.x && this->m_mousePos.y == this->m_prevMousePos.y)
		this->m_mouseMoved = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		m_mouseIsDown = true;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		m_mouseIsDown = false;

	if (m_mouseIsDown && !m_mouseWasDown)
	{
		this->m_publisher->Update(deltaTime, true,this->m_mouseMoved,this->m_mousePos);
		std::cout << "Updated" << std::endl;
	}

	else if (m_mouseIsDown && m_mouseWasDown && m_mouseMoved)
		this->m_publisher->Update(deltaTime, true, this->m_mouseMoved,this->m_mousePos);
	else
		this->m_publisher->Update(deltaTime, false, this->m_mouseMoved, this->m_mousePos);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		m_mouseWasDown = false;
	else
		m_mouseWasDown = true;

	this->m_prevMousePos = sf::Vector2f(sf::Mouse::getPosition(*m_context->GetWindow()));

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
