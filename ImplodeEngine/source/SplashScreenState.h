#pragma once
#include "GameState.h"
#include "SplashScreenState.h"
#include "Animation.h"
#include "AssetPool.h"

class SplashScreenState : public GameState
{
public:
	SplashScreenState(GameContext *context,GameState* nextState);
	void Update(float deltaTime) override;
	void Draw() override;
	void ProcessEvents(sf::Event &e) override;
	void Initialise() override;
	~SplashScreenState() { m_nextState = nullptr; }
private:
	sf::Clock m_timeElapsed;
	sf::Text m_splashText;
	sf::Font m_font;
	GameState* m_nextState;
};