#pragma once
#include "GameState.h"
#include "MenuState.h"
#include "SplashScreenState.h"
//Here we'll include all of the engine files we need so animations, asset managers, shader management e.t.c
//We'll also define the different parts to pass to each engine file within this namespace, it'll either be a class or not
namespace ImplodeEngine
{
	static std::shared_ptr<sf::RenderWindow> m_window;
	static float deltaTime;
	static sf::Clock m_clock;

	static GameContext * m_context;
	static MenuState * m_menu;
	static SplashScreenState* m_splash;

	static sf::Event *event;

	sf::Event & GetEvent();
	sf::RenderWindow& GetWindow();
	void Initialise();
	void GameLoop();
	void Update(); //pass the "screens" into the update loop, they'll be passed the deltaTime and extras
	void Draw();
	void Exit();
}
	