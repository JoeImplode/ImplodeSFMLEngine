#pragma once
#include "Animation.h"

class Particle
{
public:
	Particle();
	Particle(Animation texture, sf::Vector2f forwardDir);
	Particle(sf::Texture &texture, sf::Vector2f forwardDir);
	void Update(float deltaTime);
	void Draw(sf::RenderTexture & txtr);
	void StartParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration,float speed, float timeLimit);
	void StartParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit);

	inline void SetSpeed(float speed) { this->m_pSpeed = speed; }
	inline void SetVelocity(sf::Vector2f velocity) { this->m_pVelocity = velocity; }
	inline void SetAcceleration(sf::Vector2f acceleration) { this->m_pAcceleration; }
	inline void SetTimeLim(float timeLimSeconds) { this->m_timeLimit = timeLimSeconds; }
	inline void SetNewTexture(Animation texture) { this->m_texture = texture; }
	inline void SetActive(bool active) { this->m_active = active; }
	void SetNewTexture(sf::Texture & texture);

	inline float GetSpeed() { return this->m_pSpeed; }
	inline sf::Vector2f GetVelocity() { return this->m_pVelocity; }
	inline sf::Vector2f GetAcceleration() { return this->m_pAcceleration; }
	inline float GetTimeLim() { return this->m_timeLimit; }
	inline sf::Vector2f GetPosition() { return this->m_position; }
	inline Animation GetTextureAnim() { return this->m_texture; }
	inline sf::Texture GetTextureTxtr() { return this->m_texture.GetAnimationSheet(); }
private:
	float m_pSpeed;
	sf::Vector2f m_pVelocity;
	sf::Vector2f m_pAcceleration;
	sf::Clock m_time;
	float m_timeLimit;
	sf::Vector2f m_position;
	Animation m_texture;
	bool m_active;
	sf::Vector2f m_forward;
	bool m_moveToPos = false;
	sf::Vector2f m_endPos;
protected:

};