#include "pch.h"
#include "Light.h"
#include "ImplodeEngine.h"

Light::Light()
{
	this->m_intensity = 0.0f;
	this->m_position = sf::Vector2f(0.0f,0.0f);
	this->m_activated = false;
	this->m_color = sf::Color(0, 0, 0);
}

Light::Light(float intensity, sf::Vector2f position, bool activated, sf::Color color)
{
	this->m_intensity = intensity;
	this->m_position = position;
	this->m_activated = activated;
	this->m_color = color;
}
