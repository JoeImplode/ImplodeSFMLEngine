#include "pch.h"
#include "GameState.h"
#include "MenuState.h"
#include "Animation.h"
#include "AssetPool.h"

MenuState::MenuState(GameContext* context) : GameState(context)
{
	this->m_cam = new Camera(sf::Vector2f(1024.0f, 576.0f), sf::Vector2f(979.0f, 291.0f));
	this->m_smallCam = new Camera(sf::Vector2f(1280.0f,720.0f), sf::Vector2f(700.0f, 300.0f), sf::Vector2f(400.0f, 225.0f));
	p = new AssetPool();
	p->LoadTexture("resources/textures/Banner.png", "Banner");
	p->LoadTexture("resources/textures/BigCrate.png", "Crate");
	p->LoadTexture("resources/textures/FountainBig.png", "Fountain");
	p->LoadTexture("resources/textures/RuinedBrickFormation.png", "Bricks");
	p->LoadFont("resources/fonts/Roboto-Light.ttf", "font");

	banner.setTexture(p->GetTexture("Banner"));
	banner.setPosition(sf::Vector2f(881, 87));
	crate.setTexture(p->GetTexture("Crate"));
	crate.setPosition(sf::Vector2f(600, 300));
	fountain.setTexture(p->GetTexture("Fountain"));
	fountain.setPosition(sf::Vector2f(1159, 287));
	bricks.setTexture(p->GetTexture("Bricks"));
	bricks.setPosition(sf::Vector2f(864, 507));
	crate2.setTexture(p->GetTexture("Crate"));
	crate2.setPosition(sf::Vector2f(1014, 386));
	crate3.setTexture(p->GetTexture("Crate"));
	crate3.setPosition(sf::Vector2f(827, 240));
	crate4.setTexture(p->GetTexture("Crate"));
	crate4.setPosition(sf::Vector2f(1014, 240));
	crate5.setTexture(p->GetTexture("Crate"));
	crate5.setPosition(sf::Vector2f(912, 311));
	crate6.setTexture(p->GetTexture("Crate"));
	crate6.setPosition(sf::Vector2f(827, 386));

	pool = new PoolExample();
	t.create(1280, 720);
	gameWorld.create(1280, 720);
	
	s.setPosition(0.0f, 0.0f);
	gameWorldSprite.setPosition(0.0f, 0.0f);

	txt.setCharacterSize(20);
	txt.setFont(p->GetFont("font"));
	txt.setFillColor(sf::Color::Green);
	txt.setPosition(sf::Vector2f(0.0f, 0.0f));
}

void MenuState::Update(float deltaTime)
{
	this->pool->Update(deltaTime);
	this->m_cam->Update(deltaTime, sf::Vector2f(sf::Mouse::getPosition(*this->m_context->GetWindow()).x, sf::Mouse::getPosition(*this->m_context->GetWindow()).y));
	std::string str = std::to_string(sf::Mouse::getPosition(*this->m_context->GetWindow()).x);
	std::string str2 = std::to_string(sf::Mouse::getPosition(*this->m_context->GetWindow()).y);
	txt.setString(std::string("X position: " + str + "Y position: " + str2 ));
}

void MenuState::Draw()
{
	sf::Sprite mySprite;
	sf::Sprite mapSprite;
	
	m_context->GetWindow()->clear(sf::Color(50,50,50,0));
	t.clear(sf::Color(50, 50, 50, 0));
	gameWorld.clear(sf::Color(50, 50, 50, 0));
	gameWorld.draw(banner);
	gameWorld.draw(crate);
	gameWorld.draw(crate2);
	gameWorld.draw(crate3);
	gameWorld.draw(crate4);
	gameWorld.draw(crate5);
	gameWorld.draw(crate6);
	gameWorld.draw(fountain);
	gameWorld.draw(bricks);
	gameWorld.display();
	gameWorldSprite.setTexture(gameWorld.getTexture());
	mySprite = this->m_cam->Draw(gameWorldSprite);
	mapSprite = this->m_smallCam->Draw(gameWorldSprite);
	mapSprite.setPosition(sf::Vector2f(900.0f, 0.0f));
	this->pool->Draw(t);
	t.display();
	s.setTexture(t.getTexture());
	this->m_context->GetWindow()->draw(mySprite);
	this->m_context->GetWindow()->draw(mapSprite);
	this->m_context->GetWindow()->draw(s);
	this->m_context->GetWindow()->draw(txt);
	this->m_context->GetWindow()->display();
}

void MenuState::ProcessEvents(sf::Event& e)
{
	this->pool->ProcessEvents(e, this->m_context->GetWindow());
	this->m_cam->ProcessInput(e);
}
