#include "pch.h"
#include "UIPool.h"

UIPool::UIPool()
{
	this->m_assetPool = new AssetPool();
	this->m_publisher = new Publisher();
}

void UIPool::Update(float deltaTime)
{
	this->m_publisher->Update(deltaTime);
}

void UIPool::Draw(sf::RenderTexture &txtr)
{
	this->m_publisher->Render(txtr);
}

void UIPool::ProcessEvents(sf::Event& e, sf::RenderWindow* window)
{
	this->m_publisher->ProcessInput(e, window);
}
