#include "pch.h"
#include "Light.h"
#include "BoundaryManager.h"

BoundaryManager::BoundaryManager()
{
	this->m_sprites = std::vector<sf::Sprite*>();
}

void BoundaryManager::AddSprite(sf::Sprite* sprite)
{
	for (int i = 0; i < this->m_sprites.size(); i++)
	{
		if (this->m_sprites[i] == nullptr || this->m_sprites[i] == NULL) //if we find a sprite is destroyed, then just set this memory to our new sprite passed in
		{
			this->m_sprites[i] = sprite;
			return;
		}
	}
	this->m_sprites.push_back(sprite);
}

void BoundaryManager::DeleteSprite(sf::Sprite* sprite)
{
	for (int i = 0; i < this->m_sprites.size(); i++)
	{
		if (this->m_sprites[i] == sprite)
			this->m_sprites[i] = nullptr;
	}
}
