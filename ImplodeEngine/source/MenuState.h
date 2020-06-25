#pragma once
#include "Animation.h"
#include "AssetPool.h"
class MenuState : public GameState
{
public:
	MenuState();
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow* window);
private:
	sf::RectangleShape rect;
	Animation * m_animation;
	AssetPool* m_assetPool;
};