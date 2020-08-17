#include "pch.h"
#include "ImplodeEngine.h"

sf::Event &ImplodeEngine::GetEvent()
{
	return *ImplodeEngine::event;
}

void ImplodeEngine::Initialise()
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Implode Engine", sf::Style::Default);
	m_window->setFramerateLimit(200.0f);
	m_window->setKeyRepeatEnabled(true);
	ImplodeEngine::deltaTime = 0.0f;
	ImplodeEngine::event = new sf::Event();
	m_context = new GameContext(*event,*m_window);
	m_menu = new MenuState(m_context);
	m_splash = new SplashScreenState(m_context,m_menu);
	m_context->TransitionTo(m_splash);
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
	m_context->Update(deltaTime);
	while (m_window->pollEvent(*event))
	{
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
}
void ImplodeEngine::Draw()
{
	m_context->Draw();
}

void ImplodeEngine::Exit()
{
	delete m_context;
}