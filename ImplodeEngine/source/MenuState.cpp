#include "pch.h"
#include "GameState.h"
#include "MenuState.h"
#include "Animation.h"
#include "AssetPool.h"

MenuState::MenuState(GameContext* context) : GameState(context)
{
	pool = new PoolExample();
	t.create(1280, 720);
}

void MenuState::Update(float deltaTime)
{
	this->pool->Update(deltaTime);
}

void MenuState::Draw()
{
	m_context->GetWindow()->clear(sf::Color(50,50,50,0));
	this->pool->Draw(m_context->GetWindow());
	this->m_context->GetWindow()->display();
}

void MenuState::ProcessEvents(sf::Event& e)
{
	this->pool->ProcessEvents(e, this->m_context->GetWindow());
}
