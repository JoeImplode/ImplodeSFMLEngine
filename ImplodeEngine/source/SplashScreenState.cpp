#include "pch.h"
#include "GameState.h"
#include "SplashScreenState.h"

SplashScreenState::SplashScreenState(GameContext* context, GameState* nextState) : GameState(context)
{
	m_splashText.setString("IMPLODE GAMES");
	m_splashText.setFont(m_font);
	m_splashText.setCharacterSize(24);
	m_splashText.setFillColor(sf::Color::Cyan);
	m_font.loadFromFile("resources/fonts/Roboto-Light.ttf");
	m_splashText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_nextState = nextState;
}


void SplashScreenState::Update(float deltaTime)
{
	if (m_timeElapsed.getElapsedTime().asSeconds() >= 3.0f)
		this->m_context->TransitionTo(m_nextState);
}

void SplashScreenState::Draw()
{
	this->m_context->GetWindow()->clear();
	this->m_context->GetWindow()->draw(m_splashText);
	this->m_context->GetWindow()->display();
}
