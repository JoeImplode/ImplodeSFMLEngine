#pragma once
class Camera
{
public:
	Camera(sf::Vector2f scale, sf::Vector2f pos, sf::Vector2f spriteSize);
	Camera(sf::Vector2f scale, sf::Vector2f pos);
	void Update(float deltaTime, sf::Vector2f mousePos);
	void ProcessInput(sf::Event& e);
	sf::Sprite Draw(sf::Sprite sprite);
private:
	sf::RenderTexture m_worldTxtr;
	sf::RenderTexture m_camTxtr;
	sf::Sprite m_finalisedSprite;
	sf::View m_camView;
	sf::Vector2f m_scale;
	sf::Vector2f m_pos;
protected:
};