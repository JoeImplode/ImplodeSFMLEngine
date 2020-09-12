#pragma once
#include "Animation.h"
#include "AssetPool.h"
#include "UIElement.h"
#include "PoolExample.h"

class MenuState : public GameState
{
public:
	MenuState(GameContext* context);
	void Update(float deltaTime) override;
	void Draw() override;
	void ProcessEvents(sf::Event& e) override;
	void SetBools();
private:
	PoolExample* pool;
	bool m_myBool = false;
	std::string m_myString;
};