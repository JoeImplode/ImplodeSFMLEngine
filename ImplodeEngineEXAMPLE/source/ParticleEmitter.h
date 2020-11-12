#pragma once
#include "LightingManager.h"
class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(int count, sf::Texture & txtr, sf::Vector2f forwardDir);
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

	void Update(float deltaTime);
	void Update(float deltaTime, LightingManager& lightingManager);
	void Draw(sf::RenderTexture& txtr);
private:
	std::vector<Particle*> m_particles;
protected:
};

