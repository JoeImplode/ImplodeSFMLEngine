#pragma once

class Animation
{
public:
	Animation();
	Animation(float speed, sf::Vector2f position);

	void SetAnimationSheet(sf::Texture & texture, int rows, int columns);

	inline void SetSpeed(float speed) { this->m_speed = speed; }
	inline void SetRepeated(bool repeated) { this->m_isRepeated = repeated; }
	inline void SetRow(int row) { this->m_row = row; }
	inline void SetScale(sf::Vector2f scale) { this->m_scale = scale; }

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

private:
	sf::Sprite m_animationSheet;
	bool m_isRepeated;

	sf::Vector2u m_size; //The size of each sprite that we render
	sf::Vector2f m_position; //the position of the sprite to render

	sf::IntRect m_sourceRect; //set the location within the sprite to actually render

	sf::Vector2f m_imageCount; //Set the count for how many images are in a row
	sf::Vector2u m_currentFrame; //set the current frame number we are on
	sf::Vector2f m_scale;

	float m_speed;
	float m_currentTime;
	int m_row;
protected:
};