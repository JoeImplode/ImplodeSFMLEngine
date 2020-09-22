#pragma once
class Camera
{
public:
	Camera(sf::Vector2f scale, sf::Vector2f pos, sf::Vector2f spritePosition);
	Camera();
	void Update(float deltaTime);
	void ProcessInput(sf::Event& e);
	sf::Sprite Draw(sf::Sprite sprite, sf::Color clearColour);
	inline void SetScale(sf::Vector2f scale) { this->m_scale = scale; }
	inline void SetPos(sf::Vector2f pos) { this->m_spritePosition = pos; }
	inline void SetOrigin(sf::Vector2f origin) { this->m_pos = origin; }
	void SetCam(sf::Vector2f scale, sf::Vector2f pos, sf::Vector2f spritePosition);
private:
	sf::RenderTexture m_camTxtr;
	sf::Sprite m_finalisedSprite;
	sf::View m_camView;
	sf::Vector2f m_scale;
	sf::Vector2f m_pos;
	sf::Vector2f m_spritePosition;
protected:
};