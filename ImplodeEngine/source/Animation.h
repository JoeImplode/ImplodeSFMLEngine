#pragma once

class Animation
{
public:
	Animation();
	Animation(float speed, sf::Vector2f position,sf::Vector2f spriteScale = sf::Vector2f(1.0f,1.0f));

	void SetAnimationSheet(sf::Texture & texture, int rows, int columns);
	sf::Texture GetAnimationSheet() { return *this->m_animationSheet.getTexture(); }
	inline void SetPosition(sf::Vector2f pos) { this->m_position = pos; }
	inline void SetSpeed(float speed) { this->m_speed = speed; }
	inline void SetRepeated(bool repeated) { this->m_isRepeated = repeated; }
	inline void SetRow(int row) { this->m_row = row; }
	inline void SetScale(sf::Vector2f scale) { this->m_scale = scale; }
	inline void SetColumnNum(int num) { this->m_currentFrame.x = num; }
	inline void SetRowNum(int num) { this->m_row = num; }
	inline void NextRow() { this->m_row++; }
	inline void NextColumn() { this->m_currentFrame.x++; }
	inline void SetAutomaticRowLoop(bool loop) { this->m_rowLoop = loop; }
	sf::Sprite & GetAnimationSprite(){ return this->m_animationSheet; }
	int GetColumnNum();
	int GetRowNum();

	int GetColumnLim();
	int GetRowLim();

	void Update(float deltaTime);
	void Render(sf::RenderTexture& texture);
private:
	sf::Sprite m_animationSheet;
	bool m_isRepeated;

	sf::Vector2u m_size; //The size of each sprite that we render
	sf::Vector2f m_position; //the position of the sprite to render

	sf::IntRect m_sourceRect; //set the location within the sprite to actually render

	sf::Vector2f m_imageCount; //Set the count for how many images are in a row
	sf::Vector2u m_currentFrame; //set the current frame number we are on
	sf::Vector2f m_scale;

	bool m_rowLoop = false;
	float m_speed;
	float m_currentTime;
	int m_row;
protected:
};