#pragma once

class MenuState : public GameState
{
public:
	MenuState() {}
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow* window);
private:
	sf::RectangleShape rect;
};