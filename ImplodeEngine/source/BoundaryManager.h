#pragma once
class BoundaryManager
{
public:
	BoundaryManager();
	void AddSprite(sf::Sprite* sprite);
	void DeleteSprite(sf::Sprite* sprite);
	std::vector<sf::Sprite*> m_sprites;
private:
protected:
};