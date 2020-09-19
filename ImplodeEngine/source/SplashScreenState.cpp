#include "pch.h"
#include "GameState.h"
#include "SplashScreenState.h"
#include "Animation.h"
#include "AssetPool.h"
#include "ImplodeEngine.h"
SplashScreenState::SplashScreenState(GameContext* context, GameState* nextState) : GameState(context)
{
	m_splashText.setString("IMPLODE GAMES");
	m_splashText.setFont(m_font);
	m_splashText.setCharacterSize(24);
	m_splashText.setFillColor(sf::Color::Cyan);
	m_font.loadFromFile("resources/fonts/Roboto-Light.ttf");
	m_splashText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_timeElapsed.restart();
	m_nextState = nextState;
}


void SplashScreenState::Update(float deltaTime)
{
	if (m_timeElapsed.getElapsedTime().asSeconds() >= 3.0f)
		this->m_context->TransitionTo(m_nextState);
	
}

void SplashScreenState::Draw()
{
	ImplodeEngine::GetGameWorld().draw(m_splashText);
}

void SplashScreenState::ProcessEvents(sf::Event& e)
{
}
