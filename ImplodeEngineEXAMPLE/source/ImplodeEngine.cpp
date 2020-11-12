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

	sf::RenderTexture m_lightTxtr;
	sf::Sprite m_lightSprite;

	Camera m_gameCam;
	std::vector<Camera*> m_multiCams;

	sf::RenderTexture m_multiCamTxtr;
	sf::Sprite m_multiCamSprite;
}

void ImplodeEngine::Initialise()
{
	ImplodeEngine::m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), "Implode Engine", sf::Style::Default);
	ImplodeEngine::m_window->setFramerateLimit(1000.0f);
	ImplodeEngine::m_window->setKeyRepeatEnabled(true);

	ImplodeEngine::m_multiCams = std::vector<Camera*>();

	m_gameWorldSprite.setPosition(0.0f, 0.0f);
	m_gameWorldTxtr.create(m_window->getSize().x, m_window->getSize().y);

	ImplodeEngine::m_postProcessSprite.setPosition(0.0f, 0.0f);
	ImplodeEngine::m_postProcessTxtr.create(m_window->getSize().x, m_window->getSize().y);

	ImplodeEngine::m_camSprite.setPosition(0.0f, 0.0f);
	ImplodeEngine::m_camTxtr.create(m_window->getSize().x, m_window->getSize().y);
	
	ImplodeEngine::m_uiSprite.setPosition(0.0f, 0.0f);
	ImplodeEngine::m_uiTxtr.create(m_window->getSize().x, m_window->getSize().y);

	ImplodeEngine::m_gameCam.SetCam(sf::Vector2f(1280.0f, 720.0f), sf::Vector2f(640.0f, 360.0f), sf::Vector2f(0.0f, 0.0f));

	ImplodeEngine::m_multiCamTxtr.create(m_window->getSize().x, m_window->getSize().y);
	ImplodeEngine::m_multiCamSprite.setPosition(0.0f,0.0f);

	ImplodeEngine::m_lightTxtr.create(m_window->getSize().x, m_window->getSize().y);
	ImplodeEngine::m_lightSprite.setPosition(0.0f, 0.0f);

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
		}

		if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape)
		{
			m_window->close();
		}
	}
	m_context->Update(deltaTime);
}
std::vector<sf::Sprite> ImplodeEngine::CreateTextureFromCams(std::vector<Camera*> cams, sf::Sprite texture)
{
	std::vector<sf::Sprite> sprites;
	for (int i = 0; i < cams.size(); i++)
	{
		sf::Sprite s = cams[i]->Draw(texture, sf::Color::Transparent);
		sprites.push_back(s);
	}
	return sprites;
}
void ImplodeEngine::Draw()
{
	m_window->clear(sf::Color(50.0f,50.0f,50.0f));
	ImplodeEngine::m_gameWorldTxtr.clear(sf::Color::Transparent);
	ImplodeEngine::m_postProcessTxtr.clear(sf::Color::Transparent);
	ImplodeEngine::m_camTxtr.clear(sf::Color::Transparent);
	ImplodeEngine::m_uiTxtr.clear(sf::Color::Transparent);
	ImplodeEngine::m_multiCamTxtr.clear(sf::Color::Transparent);
	ImplodeEngine::m_lightTxtr.clear(sf::Color::Transparent);

	m_context->Draw();
	
	ImplodeEngine::m_gameWorldTxtr.display();
	ImplodeEngine::m_gameWorldSprite.setTexture(m_gameWorldTxtr.getTexture());

	ImplodeEngine::m_lightTxtr.display();
	ImplodeEngine::m_lightSprite.setTexture(m_lightTxtr.getTexture());

	ImplodeEngine::m_postProcessTxtr.draw(m_gameWorldSprite);
	ImplodeEngine::m_postProcessTxtr.draw(m_lightSprite);
	ImplodeEngine::m_postProcessTxtr.display();
	ImplodeEngine::m_postProcessSprite.setTexture(m_postProcessTxtr.getTexture());

	ImplodeEngine::m_uiTxtr.display();
	ImplodeEngine::m_uiSprite.setTexture(m_uiTxtr.getTexture());
	
	ImplodeEngine::m_camTxtr.draw(m_gameCam.Draw(m_postProcessSprite, sf::Color::Transparent));

	if (ImplodeEngine::m_multiCams.size() > 0)
	{
		std::vector<sf::Sprite> sprites;
		sprites = ImplodeEngine::CreateTextureFromCams(ImplodeEngine::m_multiCams, m_postProcessSprite);

		for (int i = 0; i < sprites.size(); i++)
		{
			ImplodeEngine::m_multiCamTxtr.draw(sprites[i]);
		}
		m_multiCamTxtr.display();
		m_multiCamSprite.setTexture(m_multiCamTxtr.getTexture());
	}

	ImplodeEngine::m_camTxtr.draw(m_multiCamSprite);
	ImplodeEngine::m_camTxtr.draw(m_uiSprite);
	ImplodeEngine::m_camTxtr.display();

	ImplodeEngine::m_camSprite.setTexture(m_camTxtr.getTexture());

	ImplodeEngine::m_window->draw(m_camSprite);
	ImplodeEngine::m_window->draw(m_uiSprite);
	ImplodeEngine::m_window->display();
}

void ImplodeEngine::Exit()
{
	m_context = nullptr;
}