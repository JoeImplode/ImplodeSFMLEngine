#pragma once
class BoundaryManager
{
public:
	BoundaryManager();
	void AddSprite(sf::Sprite* sprite);
	void DeleteSprite(sf::Sprite* sprite);
private:
	std::vector<sf::Sprite*> m_sprites;
protected:
};