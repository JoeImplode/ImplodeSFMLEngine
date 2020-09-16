#include "pch.h"
#include "ImplodeEngine.h"

sf::Event &ImplodeEngine::GetEvent()
{
	return *ImplodeEngine::event;
}

sf::RenderWindow& ImplodeEngine::GetWindow()
{
	return *ImplodeEngine::m_window;
}

void ImplodeEngine::Initialise()
{
	ImplodeEngine::m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), "Implode Engine", sf::Style::Default);
	ImplodeEngine::m_window->setFramerateLimit(200.0f);
	ImplodeEngine::m_window->setKeyRepeatEnabled(true);
	ImplodeEngine::deltaTime = 0.0f;
	ImplodeEngine::event = new sf::Event();
	ImplodeEngine::m_context = new GameContext(*event,*m_window);
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
	m_context->Draw();
}

void ImplodeEngine::Exit()
{
	delete m_context;
}