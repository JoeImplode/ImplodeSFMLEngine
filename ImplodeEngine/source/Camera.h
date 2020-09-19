#pragma once
class Camera
{
public:
	Camera(sf::Vector2f scale, sf::Vector2f pos, sf::Vector2f spritePosition);
	void Update(float deltaTime);
	void ProcessInput(sf::Event& e);
	sf::Sprite Draw(sf::Sprite sprite, sf::Color clearColour);
private:
	sf::RenderTexture m_camTxtr;
	sf::Sprite m_finalisedSprite;
	sf::View m_camView;
	sf::Vector2f m_scale;
	sf::Vector2f m_pos;
	sf::Vector2f m_spritePosition;
protected:
};