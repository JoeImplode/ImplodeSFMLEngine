#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class GameContext; //The current state we're using

class GameState //A parent class to define how gamestates should work
{
protected:
	GameContext *m_context;
public:
	void SetContext(GameContext *context) { this->m_context = context; }
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	~GameState() { m_context = nullptr; }
};

class GameContext
{
private:
	GameState * m_state;
	sf::RenderWindow* m_renderWindow;
public:
	GameContext(GameState *state) : m_state(state)
	{
		this->TransitionTo(state);
	}

	void TransitionTo(GameState* state)
	{
		this->m_state = state;
		this->m_state->SetContext(this);
	}
	void SetWindow(sf::RenderWindow* renderWindow) { this->m_renderWindow = renderWindow; }
	sf::RenderWindow* GetWindow() { return this->m_renderWindow; }
	void Update(float deltaTime) { this->m_state->Update(deltaTime); }
	void Draw() { this->m_state->Draw(); }

	~GameContext() { m_state = nullptr; }
};