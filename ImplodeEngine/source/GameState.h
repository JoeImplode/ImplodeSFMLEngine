#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class GameContext; //The current state we're using

class GameState //A parent class to define how gamestates should work
{
protected:
	GameContext *m_context;
public:
	inline GameState(GameContext* context) { this->m_context = context; }
	void SetContext(GameContext* context) { this->m_context = context; }
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	sf::Event& GetEvent();
	sf::RenderWindow& GetRenderWindow();
	~GameState() { m_context = nullptr; }
};

class GameContext
{
private:
	GameState * m_state;
	sf::RenderWindow* m_renderWindow;
	sf::Event& m_event;
public:
	GameContext(sf::Event& event,sf::RenderWindow &window) : m_event(event),m_renderWindow(&window)
	{

	}
	GameContext(GameState *state,sf::Event & event) : m_state(state),m_event(event)
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
	sf::Event& GetEvent();
	~GameContext() { m_state = nullptr; }
};