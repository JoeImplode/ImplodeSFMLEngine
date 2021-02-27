#pragma once
#include "GameState.h"
#include "Player.h"
#include "AssetPool.h"
#include "Skeleton.h"
class MainGame : public GameState
{
public:
	MainGame(GameContext* context);
	void Update(float deltaTime) override;
	void ProcessEvents(sf::Event& e) override;
	void Draw() override;
	void Initialise() override;
	void SetupAssets();
	~MainGame();
private:
	Player m_player;
	Skeleton m_skeleton;
	AssetPool m_pool;
	sf::Text m_mousePosition;
	sf::Shader m_enemyColourShader;
protected:
};

