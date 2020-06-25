#pragma once

class Animation
{
public:
	Animation();
	Animation(float speed, sf::Vector2f position, bool isSheet);

	void SetAnimationSheet(sf::Texture & texture, int rows, int columns);
	inline void AddToAnimationSprites(sf::Sprite sprite) { this->m_animationSprites.push_back(sprite); }

	inline void SetToSheet(bool sheet) { this->m_isSheet = sheet; } //set our sprites to load from a singular sheet
	inline void SetSpeed(float speed) { this->m_speed = speed; }

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	std::vector<sf::Sprite> m_animationSprites; //sometimes the sprites we load are loaded as singular PNG's if so, we load them into a vector of animation sprites
	sf::Sprite m_animationSheet;
	bool m_isSheet;

	sf::Vector2u m_size; //set the size of the sprite to be rendered
	sf::Vector2f m_position;
	sf::IntRect m_sourceRect;
	sf::Vector2f m_imageCount;
	sf::Vector2u m_currentFrame;
	float m_speed;
	float m_currentTime;

	
	
protected:
};