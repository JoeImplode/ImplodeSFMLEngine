#include "pch.h"
#include "Treant.h"

Treant::Treant()
{
}

Treant::Treant(sf::Vector2f position, float attackRate, ENEMY_STATE state, bool facingDirection, Animation& animation, std::vector<ParticleEmitter>* emitters, sf::Color color, bool useColour) : Enemy(position,attackRate,state,facingDirection,animation, emitters, color, useColour)
{
}

void Treant::Update(float deltaTime)
{
}

void Treant::Update(float deltaTime, LightingManager& lManager)
{
}

Treant::~Treant()
{
}
