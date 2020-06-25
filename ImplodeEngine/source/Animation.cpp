#include "pch.h"
#include "Animation.h"

Animation::Animation() : m_speed(0),m_isSheet(false)
{
	this->m_animationSprites = {};
	this->m_size = sf::Vector2u(0.0f,0.0f);
	this->m_position = sf::Vector2f(100.0f, 100.0f);
	this->m_currentFrame = sf::Vector2u(0.0f, 0.0f);
	this->m_imageCount = sf::Vector2f(0.0f, 0.0f);
}

Animation::Animation(float speed, sf::Vector2f position, bool isSheet)
{
	this->m_isSheet = isSheet;
	this->m_speed = speed;
	this->m_size = sf::Vector2u(0.0f, 0.0f);
	this->m_position = position;
	this->m_animationSprites = {};
	this->m_currentFrame = sf::Vector2u(0.0f, 0.0f);
	this->m_imageCount = sf::Vector2f(0.0f, 0.0f);
}

void Animation::SetAnimationSheet(sf::Texture & texture, int rows, int columns)
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	this->m_animationSheet = sprite;
	this->m_size.x = rows/(sprite.getTexture()->getSize().x); //the size of each sprite
	this->m_size.y = columns/(sprite.getTexture()->getSize().y);

	this->m_imageCount.x = columns;
	this->m_imageCount.y = rows;

	this->m_sourceRect.width = sprite.getTexture()->getSize().x / float(m_imageCount.x);
	this->m_sourceRect.height = sprite.getTexture()->getSize().y / float(m_imageCount.y);
}

void Animation::Update(float deltaTime)
{
	this->m_currentTime += deltaTime;
	if (this->m_currentTime >= this->m_speed)
	{
		this->m_currentTime -= deltaTime;
		this->m_currentFrame.x++;
		this->m_currentTime = 0.0f;

		if (this->m_currentFrame.x >= this->m_imageCount.x)
			this->m_currentFrame.x = 0;
	}
	this->m_sourceRect.left = m_currentFrame.x * this->m_sourceRect.width;
	this->m_sourceRect.top = m_currentFrame.y * this->m_sourceRect.height;
	
	this->m_animationSheet.setTextureRect(this->m_sourceRect);
	this->m_animationSheet.setPosition(this->m_position);
}

void Animation::Render(sf::RenderWindow * window)
{
	window->draw(this->m_animationSheet);
}
