#include "pch.h"
#include "Scorpion.h"

Scorpion::Scorpion()
{

}

Scorpion::Scorpion(sf::Vector2f position, float attackRate, ENEMY_STATE state, bool facingDirection, Animation& animation, std::vector<ParticleEmitter>* emitters, sf::Color color, bool useColour) : Enemy(position,attackRate,state,facingDirection,animation, emitters, color, useColour)
{

}

void Scorpion::Update(float deltaTime)
{

}

void Scorpion::Update(float deltaTime, LightingManager& lManager)
{

}

Scorpion::~Scorpion()
{

}
