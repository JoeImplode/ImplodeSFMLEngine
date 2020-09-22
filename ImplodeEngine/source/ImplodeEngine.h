#pragma once
#include "GameState.h"
#include "MenuState.h"
#include "SplashScreenState.h"
#include "Camera.h"

//Here we'll include all of the engine files we need so animations, asset managers, shader management e.t.c
//We'll also define the different parts to pass to each engine file within this namespace, it'll either be a class or not
namespace ImplodeEngine
{
	extern std::shared_ptr<sf::RenderWindow> m_window;
	static float deltaTime;
	static sf::Clock m_clock;

	static GameContext * m_context;
	static MenuState * m_menu;
	static SplashScreenState* m_splash;

	extern sf::Event *event;

	extern sf::RenderTexture m_gameWorldTxtr;
	extern sf::Sprite m_gameWorldSprite;

	extern sf::RenderTexture m_postProcessTxtr;
	extern sf::Sprite m_postProcessSprite;

	extern sf::RenderTexture m_camTxtr;
	extern sf::Sprite m_camSprite;

	extern sf::RenderTexture m_uiTxtr;
	extern sf::Sprite m_uiSprite;
	
	extern Camera m_gameCam;

	void Initialise();
	void GameLoop();
	void Update(); //pass the "screens" into the update loop, they'll be passed the deltaTime and extras
	void Draw();
	void Exit();
}
	