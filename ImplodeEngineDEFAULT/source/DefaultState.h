#pragma once
#include "GameState.h"
class DefaultState : public GameState
{
public:
	DefaultState(GameContext* context);
	void Update(float deltaTime) override;
	void ProcessEvents(sf::Event& e) override;
	void Draw() override;
	void SetBools();
	void Initialise() override;
	~DefaultState();
private:

protected:
};