#include "pch.h"
#include "Demon.h"

Demon::Demon()
{
}

Demon::Demon(sf::Vector2f position, float attackRate, ENEMY_STATE state, bool facingDirection, Animation& animation, std::vector<ParticleEmitter>* emitters, sf::Color color, bool useColour) : Enemy(position,attackRate,state,facingDirection,animation, emitters, color, useColour)
{
}

void Demon::Update(float deltaTime)
{
}

void Demon::Update(float deltaTime, LightingManager& lManager)
{
}

Demon::~Demon()
{
}
