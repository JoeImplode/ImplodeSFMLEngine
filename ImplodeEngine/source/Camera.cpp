#include "ImplodeEngine.h"
#include "Camera.h"
#include "pch.h"
Camera::Camera(sf::Vector2f scale, sf::Vector2f pos, sf::Vector2f spriteSize)
{
	this->m_scale = scale;
	this->m_pos = pos;
	this->m_camView = sf::View(pos, scale);
	this->m_finalisedSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	this->m_camTxtr.create(spriteSize.x,spriteSize.y);
}

Camera::Camera(sf::Vector2f scale, sf::Vector2f pos)
{
	this->m_scale = scale;
	this->m_pos = pos;
	this->m_camView = sf::View(pos, scale);
	this->m_finalisedSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	this->m_camTxtr.create(ImplodeEngine::GetWindow().getSize().x, ImplodeEngine::GetWindow().getSize().y);
}

void Camera::Update(float deltaTime,sf::Vector2f mousePos)
{
	
}

void Camera::ProcessInput(sf::Event& e)
{

}

sf::Sprite Camera::Draw(sf::Sprite sprite)
{
	this->m_camTxtr.clear(sf::Color(50, 50, 50, 0));
	this->m_camTxtr.setView(this->m_camView);
	this->m_camTxtr.draw(sprite);
	this->m_camTxtr.display();
	this->m_finalisedSprite.setTexture(this->m_camTxtr.getTexture());
	return this->m_finalisedSprite;
}
