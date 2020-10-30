#include "pch.h"
#include "ImplodeEngine.h"
#include "Camera.h"


Camera::Camera(sf::Vector2f scale, sf::Vector2f pos, sf::Vector2f spritePosition)
{
	this->m_scale = scale;
	this->m_pos = pos;
	this->m_camView = sf::View(pos, scale);
	this->m_finalisedSprite.setPosition(spritePosition);
	this->m_camTxtr.create(scale.x,scale.y);
}

Camera::Camera()
{

}

void Camera::Update(float deltaTime)
{

}

void Camera::ProcessInput(sf::Event& e)
{

}

sf::Sprite Camera::Draw(sf::Sprite sprite, sf::Color clearColour)
{
	this->m_camTxtr.clear(clearColour);
	this->m_camTxtr.setView(this->m_camView);
	this->m_camTxtr.draw(sprite);
	this->m_camTxtr.display();
	this->m_finalisedSprite.setTexture(this->m_camTxtr.getTexture());
	return this->m_finalisedSprite;
}

void Camera::SetCam(sf::Vector2f scale, sf::Vector2f pos, sf::Vector2f spritePosition)
{
	this->m_scale = scale;
	this->m_pos = pos;
	this->m_camView = sf::View(pos, scale);
	this->m_finalisedSprite.setPosition(spritePosition);
	this->m_camTxtr.create(scale.x, scale.y);
}
