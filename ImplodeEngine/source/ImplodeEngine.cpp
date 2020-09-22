#include "pch.h"
#include "ImplodeEngine.h"


namespace ImplodeEngine
{
	std::shared_ptr<sf::RenderWindow> m_window;

	sf::Event* event;

	sf::RenderTexture m_gameWorldTxtr;
	sf::Sprite m_gameWorldSprite;

	sf::RenderTexture m_postProcessTxtr;
	sf::Sprite m_postProcessSprite;

	sf::RenderTexture m_camTxtr;
	sf::Sprite m_camSprite;

	sf::RenderTexture m_uiTxtr;
	sf::Sprite m_uiSprite;

	Camera m_gameCam;
}

void ImplodeEngine::Initialise()
{
	ImplodeEngine::m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), "Implode Engine", sf::Style::Default);
	ImplodeEngine::m_window->setFramerateLimit(200.0f);
	ImplodeEngine::m_window->setKeyRepeatEnabled(true);

	m_gameWorldSprite.setPosition(0.0f, 0.0f);
	m_gameWorldTxtr.create(m_window->getSize().x, m_window->getSize().y);

	ImplodeEngine::m_postProcessSprite.setPosition(0.0f, 0.0f);
	ImplodeEngine::m_postProcessTxtr.create(m_window->getSize().x, m_window->getSize().y);

	ImplodeEngine::m_camSprite.setPosition(0.0f, 0.0f);
	ImplodeEngine::m_camTxtr.create(m_window->getSize().x, m_window->getSize().y);

	ImplodeEngine::m_uiSprite.setPosition(0.0f, 0.0f);
	ImplodeEngine::m_uiTxtr.create(m_window->getSize().x, m_window->getSize().y);

	ImplodeEngine::m_gameCam.SetCam(sf::Vector2f(1280.0f, 720.0f), sf::Vector2f(640.0f, 360.0f), sf::Vector2f(0.0f, 0.0f));

	ImplodeEngine::deltaTime = 0.0f;
	ImplodeEngine::event = new sf::Event();
	ImplodeEngine::m_context = new GameContext(*event,*m_window,m_gameWorldTxtr);
	ImplodeEngine::m_menu = new MenuState(m_context);
	ImplodeEngine::m_splash = new SplashScreenState(m_context,m_menu);
	ImplodeEngine::m_context->TransitionTo(m_splash);
}

void ImplodeEngine::GameLoop()
{
	while (m_window->isOpen())
	{
		Update();
		deltaTime = ImplodeEngine::m_clock.restart().asSeconds();
		Draw();
	}
}

void ImplodeEngine::Update()
{
	while (m_window->pollEvent(*event))
	{
		m_context->ProcessEvents(*event);
		if (event->type == sf::Event::Closed)
		{
			m_window->close();
			Exit();
		}

		if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape)
		{
			m_window->close();
			Exit();
		}
	}
	m_context->Update(deltaTime);
}
void ImplodeEngine::Draw()
{
	m_window->clear(sf::Color(50.0f,50.0f,50.0f));
	ImplodeEngine::m_gameWorldTxtr.clear(sf::Color::Transparent);
	ImplodeEngine::m_postProcessTxtr.clear(sf::Color::Transparent);
	ImplodeEngine::m_camTxtr.clear(sf::Color::Transparent);
	ImplodeEngine::m_uiTxtr.clear(sf::Color::Transparent);

	m_context->Draw();
	
	ImplodeEngine::m_gameWorldTxtr.display();
	ImplodeEngine::m_gameWorldSprite.setTexture(m_gameWorldTxtr.getTexture());

	//Lighting render and more

	//Elemental effect and more

	ImplodeEngine::m_postProcessTxtr.draw(m_gameWorldSprite);
	ImplodeEngine::m_postProcessTxtr.display();
	ImplodeEngine::m_postProcessSprite.setTexture(m_postProcessTxtr.getTexture());

	ImplodeEngine::m_uiTxtr.display();
	ImplodeEngine::m_uiSprite.setTexture(m_uiTxtr.getTexture());
	
	ImplodeEngine::m_camTxtr.draw(m_gameCam.Draw(m_postProcessSprite, sf::Color::Blue));
	ImplodeEngine::m_camTxtr.draw(m_uiSprite);

	ImplodeEngine::m_camTxtr.display();
	ImplodeEngine::m_camSprite.setTexture(m_camTxtr.getTexture());

	ImplodeEngine::m_window->draw(m_camSprite);
	ImplodeEngine::m_window->draw(m_uiSprite);
	ImplodeEngine::m_window->display();
}

void ImplodeEngine::Exit()
{
	delete m_context;
}