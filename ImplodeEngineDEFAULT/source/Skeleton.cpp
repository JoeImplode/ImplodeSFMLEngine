#include "pch.h"
#include "Animation.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "ImplodeEngine.h"
#include "ParticleEmitter.h"

Skeleton::Skeleton() : Enemy()
{

}

Skeleton::Skeleton(sf::Vector2f position, float attackRate, ENEMY_STATE state, bool facingDirection, Animation& animation, std::vector<ParticleEmitter>* emitters, sf::Color color, bool useColour) : Enemy(position, attackRate, state, facingDirection, animation, emitters, color, useColour)
{
	this->m_animationSheet.SetRepeated(true);
	this->m_animationSheet.SetScale(sf::Vector2f(2.3, 2.3));
	this->m_animationSheet.SetSpeed(0.16);
}

void Skeleton::Update(float deltaTime)
{
	this->m_animationSheet.SetPosition(this->m_position);
	this->m_animationSheet.Update(deltaTime);
	this->CheckEmitters();
	this->CheckColourSwitch();
	this->m_position.x += this->m_moveVal;
	this->Move();
}

void Skeleton::Update(float deltaTime, LightingManager& lManager)
{
	this->m_animationSheet.SetPosition(this->m_position);
	this->m_animationSheet.Update(deltaTime,lManager);
	this->CheckEmitters();
	this->CheckColourSwitch();
	this->m_position.x += this->m_moveVal;
	this->Move();
}

Skeleton::~Skeleton()
{
}
