#pragma once

class SplashScreenState : public GameState
{
public:
	SplashScreenState(GameContext *context,GameState* nextState);
	void Update(float deltaTime) override;
	void Draw() override;
	void ProcessEvents(sf::Event &e) override;
	~SplashScreenState() { m_nextState = nullptr; }
private:
	sf::Clock m_timeElapsed;
	sf::Text m_splashText;
	sf::Font m_font;
	GameState* m_nextState;
};