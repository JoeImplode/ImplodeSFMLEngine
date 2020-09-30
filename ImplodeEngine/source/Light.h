#pragma once

class Light
{
public:
	Light();
	Light(float intensity, sf::Vector2f position, bool activated, sf::Color color);

	inline void SetActivated(bool activated) { this->m_activated = activated; }
	inline void SetPosition(sf::Vector2f pos) { this->m_position = pos; }
	inline void SetIntensity(float intensity) { this->m_intensity = intensity; }
	inline void SetColor(sf::Color color) { this->m_color = color; }

	inline bool GetActivated() { return this->m_activated; }
	inline sf::Vector2f GetPosition() { return this->m_position; }
	inline float GetIntensity() { return this->m_intensity; }
	inline sf::Color GetColor() { return this->m_color; }
private:
	float m_intensity;
	sf::Vector2f m_position;
	bool m_activated;
	sf::Color m_color;
protected:
};

