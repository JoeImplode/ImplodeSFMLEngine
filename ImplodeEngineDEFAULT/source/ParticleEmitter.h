#pragma once
#include "LightingManager.h"
#include "Particle.h"
class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(int count, sf::Texture & txtr, sf::Vector2f txtrNormal);
	~ParticleEmitter();

	void SetParticleTxtr(Animation & txtr);
	void SetParticleTxtr(sf::Texture & txtr);

	void CreateParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit, sf::Texture & txtr, sf::Vector2f txtrForward, LightingManager& lightingManager, bool forceIn = false);
	void CreateParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit, sf::Texture& txtr, sf::Vector2f txtrForward, bool forceIn = false);
	void CreateParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit, Animation& txtr, sf::Vector2f txtrForward, bool forceIn = false);
	void CreateParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit, Animation& txtr, sf::Vector2f txtrForward, LightingManager& lightingManager, bool forceIn = false);

	void CreateParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float speed, float timeLimit, sf::Texture & txtr, sf::Vector2f txtrForward, bool forceIn = false);
	void CreateParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float speed, float timeLimit, sf::Texture& txtr, sf::Vector2f txtrForward, LightingManager& lightingManager,  bool forceIn = false);
	void CreateParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float speed, float timeLimit, Animation& txtr, sf::Vector2f txtrForward, bool forceIn = false);
	void CreateParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float speed, float timeLimit, Animation& txtr, sf::Vector2f txtrForward, LightingManager& lightingManager, bool forceIn = false);

	void CreateParticles(int count, sf::Texture & txtr, sf::Vector2f forwardDir);

	void Update(float deltaTime);
	void Update(float deltaTime, LightingManager& lightingManager);
	void Draw(sf::RenderTexture& txtr);
	inline std::vector<Particle*> GetParticles() { return this->m_particles; }
private:
	std::vector<Particle*> m_particles;
protected:
};

