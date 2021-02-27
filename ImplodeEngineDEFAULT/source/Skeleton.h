#pragma once
#include "LightingManager.h"
#include "Animation.h"
#include "ParticleEmitter.h"
#include "Enemy.h"

class Skeleton : public Enemy
{
public:
	Skeleton();
	Skeleton(const Skeleton&) = default;
	Skeleton& operator = (const Skeleton&) = default;
	Skeleton(sf::Vector2f position, float attackRate, ENEMY_STATE state, bool facingDirection, Animation& animation, std::vector<ParticleEmitter>* emitters, sf::Color color, bool useColour);
	void Update(float deltaTime) override;
	void Update(float deltaTime, LightingManager& lManager) override;
	~Skeleton();
private:
protected:
};