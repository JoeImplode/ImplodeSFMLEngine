#pragma once
#include "Animation.h"
#include "AssetPool.h"
#include "UIElement.h"
#include "PoolExample.h"
#include "Camera.h"

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
	sf::RenderTexture t;
	sf::RenderTexture gameWorld;
	sf::Sprite gameWorldSprite;
	sf::Sprite s;
	AssetPool* p;

	sf::Sprite banner;
	sf::Sprite crate;
	sf::Sprite fountain;
	sf::Sprite bricks;
	sf::Sprite crate2;
	sf::Sprite crate3;
	sf::Sprite crate4;
	sf::Sprite crate5;
	sf::Sprite crate6;
	sf::Text txt;
	Camera * m_cam;
	Camera* m_smallCam;
};