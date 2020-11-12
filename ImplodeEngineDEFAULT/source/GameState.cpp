#include "GameState.h"
#include "pch.h"

sf::Event& GameState::GetEvent()
{
	return this->m_context->GetEvent();
}

sf::RenderWindow& GameState::GetRenderWindow()
{
	return *this->m_context->GetWindow();
}

sf::Event& GameContext::GetEvent()
{
	return this->m_event;
}

