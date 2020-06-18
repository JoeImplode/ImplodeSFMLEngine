#include "pch.h"
#include "ImplodeEngine.h"

void ImplodeEngine::Initialise()
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "My window", sf::Style::Default);
	m_window->setFramerateLimit(200.0f);
	ImplodeEngine::deltaTime = 0.0f;
	m_menu = new MenuState();
	m_splash = new SplashScreenState(m_menu);
	m_context = new GameContext(m_splash);
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
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
			Exit();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			m_window->close();
			Exit();
		}
		
	}
	m_context->Update(deltaTime);
}
void ImplodeEngine::Draw()
{
	m_context->Draw(m_window.get());
}

void ImplodeEngine::Exit()
{
	delete m_context;
}