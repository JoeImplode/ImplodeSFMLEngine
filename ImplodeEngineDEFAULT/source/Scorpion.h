#pragma once
#include "Enemy.h"

class Scorpion : public Enemy
{
public:
	Scorpion();
	Scorpion(sf::Vector2f position, float attackRate, ENEMY_STATE state, bool facingDirection, Animation& animation, std::vector<ParticleEmitter>* emitters, sf::Color color, bool useColour);
	void Update(float deltaTime) override;
	void Update(float deltaTime, LightingManager& lManager) override;
	~Scorpion();
private:
protected:
};