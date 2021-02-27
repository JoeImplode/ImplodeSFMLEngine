#include "pch.h"
#include "Animation.h"
#include "Enemy.h"
#include "ImplodeEngine.h"
#include "ParticleEmitter.h"
#include "Particle.h"

Enemy::Enemy()
{
	this->m_position = sf::Vector2f(0, 0);
	this->m_attackRate = 35;
	this->m_previousState = ENEMY_STATE::IDLE;
	this->m_facingDirection = true;
	this->m_prevPos = m_position;
	this->m_scale = sf::Vector2f(1.0f, 1.0f);
	//this->ColourShaderCalculator();
}

Enemy::Enemy(sf::Vector2f position, float attackRate, ENEMY_STATE state, bool facingDirection, Animation& animation, std::vector<ParticleEmitter>*emitters,sf::Color color, bool useColour)
{
	this->m_position = position;
	this->m_attackRate = attackRate;
	this->m_previousState = state;
	this->m_facingDirection = facingDirection;
	this->m_animationSheet = animation;
	this->m_scale = this->m_animationSheet.GetScale();
	this->m_bulletEmitters = new std::vector<ParticleEmitter>{};
	this->m_bulletEmitters = emitters;
	this->m_hitTimer.restart();
	this->m_startTimer.restart();

	this->m_prevPos = position;
	//some way of making it so we don't always use a colour shader calculator
	if (useColour)
	{
		this->m_shaderColour = color;
		this->m_normColour = this->m_shaderColour;
		this->m_hitColour = this->m_shaderColour;

		if (this->m_hitColour.r - this->m_darkerVal < 0)
			this->m_hitColour.r = 0;
		else
			this->m_hitColour.r -= this->m_darkerVal;

		if (this->m_hitColour.g - this->m_darkerVal < 0)
			this->m_hitColour.g = 0;
		else
			this->m_hitColour.g -= this->m_darkerVal;

		if (this->m_hitColour.b - this->m_darkerVal < 0)
			this->m_hitColour.b = 0;
		else
			this->m_hitColour.b -= this->m_darkerVal;
	}

	else
		this->ColourShaderCalculator();
}

void Enemy::CheckEmitters()
{
	//this may need a reprogramming since it's sorta flawed
	//it works yet with consistent checks against multiple enemies, the program is bound to slow down here

	//get the collision bounds
	for (int i = 0; i < this->m_bulletEmitters->size(); i++)
	{
		for (int j = 0; j < this->m_bulletEmitters->at(i).GetParticles().size() - 1; j++)
		{
			if (this->m_bulletEmitters->at(i).GetParticles().at(j)->GetActive() == false && i !=1)
				break;

			sf::Sprite s = this->m_bulletEmitters->at(i).GetParticles().at(j)->GetSprite();
			sf::Sprite thisSprite = this->m_animationSheet.GetAnimationSprite();

			if (s.getPosition().x > this->m_position.x - thisSprite.getOrigin().x / 2 && s.getPosition().x && s.getPosition().x + s.getLocalBounds().width < this->m_position.x - thisSprite.getOrigin().x / 2 + this->m_animationSheet.GetAnimationSprite().getLocalBounds().width / 2
				&& s.getPosition().y > this->m_position.y - thisSprite.getOrigin().y / 2 && s.getPosition().y + s.getLocalBounds().height < this->m_position.y - thisSprite.getOrigin().y / 2 + this->m_animationSheet.GetAnimationSprite().getLocalBounds().height 
				&& this->m_bulletEmitters->at(i).GetParticles().at(j)->GetActive())
			{
				this->m_bulletEmitters->at(i).GetParticles().at(j)->SetActive(false);
				this->m_hitTimer.restart();
			}
		}
	}
}

bool Enemy::SetUpAnimations(Animation& idle, Animation& running, Animation& attack, Animation& death)
{
	try
	{
		this->m_enemyAnimations.insert(std::pair<ENEMY_STATE, Animation>(ENEMY_STATE::IDLE, idle));
		this->m_enemyAnimations.at(ENEMY_STATE::IDLE).SetRepeated(true);
		this->m_enemyAnimations.at(ENEMY_STATE::IDLE).SetScale(sf::Vector2f(2.3, 2.3));
		this->m_enemyAnimations.at(ENEMY_STATE::IDLE).SetSpeed(0.16);

		this->m_enemyAnimations.insert(std::pair<ENEMY_STATE, Animation>(ENEMY_STATE::RUNNING, running));
		this->m_enemyAnimations.at(ENEMY_STATE::RUNNING).SetRepeated(true);
		this->m_enemyAnimations.at(ENEMY_STATE::RUNNING).SetScale(sf::Vector2f(2.3, 2.3));
		this->m_enemyAnimations.at(ENEMY_STATE::RUNNING).SetSpeed(0.1);

		this->m_enemyAnimations.insert(std::pair<ENEMY_STATE, Animation>(ENEMY_STATE::ATTACK, attack));
		this->m_enemyAnimations.at(ENEMY_STATE::ATTACK).SetRepeated(true);
		this->m_enemyAnimations.at(ENEMY_STATE::ATTACK).SetScale(sf::Vector2f(2.3, 2.3));
		this->m_enemyAnimations.at(ENEMY_STATE::ATTACK).SetSpeed(0.16);

		this->m_enemyAnimations.insert(std::pair<ENEMY_STATE, Animation>(ENEMY_STATE::DEATH, idle));
		this->m_enemyAnimations.at(ENEMY_STATE::DEATH).SetRepeated(false);
		this->m_enemyAnimations.at(ENEMY_STATE::DEATH).SetScale(sf::Vector2f(2.3, 2.3));
		this->m_enemyAnimations.at(ENEMY_STATE::DEATH).SetSpeed(0.16);

	}
	catch (std::exception e)
	{
		std::cout << "Error creating enemy animations!" << std::endl;
		return false;
	}
	return true;
}

void Enemy::CheckColourSwitch()
{
	if (this->m_hitTimer.getElapsedTime().asSeconds() < 0.2 && this->m_startTimer.getElapsedTime().asSeconds() > 0.2)
		this->m_shaderColour = this->m_hitColour;

	else if (this->m_hitTimer.getElapsedTime().asSeconds() > 0.2)
		this->m_shaderColour = this->m_normColour;
}

void Enemy::Move()
{
	if (this->m_previousState != ENEMY_STATE::RUNNING && this->m_prevPos != this->m_position)
	{
		this->m_animationSheet = this->m_enemyAnimations.at(ENEMY_STATE::RUNNING);
		this->m_previousState = ENEMY_STATE::RUNNING;
	}
	else if (this->m_previousState == ENEMY_STATE::RUNNING && this->m_prevPos == this->m_position)
	{
		this->m_animationSheet = this->m_enemyAnimations.at(ENEMY_STATE::IDLE);
		this->m_previousState = ENEMY_STATE::IDLE;
	}
	if (this->m_prevPos.x < this->m_position.x && !this->m_facingDirection)
	{
		this->m_facingDirection = true;
		this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
	}
	if (this->m_prevPos.x > this->m_position.x && this->m_facingDirection)
	{
		this->m_facingDirection = false;
		this->m_animationSheet.FlipSprite(sf::Vector2f(-this->m_scale.x, this->m_scale.y));
	}
	this->m_prevPos = this->m_position;
}

void Enemy::ColourShaderCalculator()
{
	srand((time(0)));
	this->m_primColour =  rand() % 4 + 1;

	if (this->m_primColour != 4)
	{
		this->m_shaderColour = sf::Color(0, 0, 0);
		if (this->m_primColour == 1)
		{
			this->m_shaderColour.r = rand() % 255 + 200;

			if (this->m_shaderColour.g > this->m_shaderColour.b)
				this->m_secColour = 2;
			else
				this->m_secColour = 3;
		}
		if (this->m_primColour == 2)
		{
			this->m_shaderColour.g = rand() % 255 + 200;

			if (this->m_shaderColour.r > this->m_shaderColour.b)
				this->m_secColour = 1;
			else
				this->m_secColour = 3;
		}
		if (this->m_primColour == 3)
		{
			this->m_shaderColour.b = rand() % 255 + 200;

			if (this->m_shaderColour.r > this->m_shaderColour.g)
				this->m_secColour = 1;
			else
				this->m_secColour = 2;
		}
	}
	else if (this->m_primColour == 4)
	{
		this->m_shaderColour = sf::Color(rand() % 30 + 0, rand() % 30 + 0, rand() % 30 + 0) ;
		this->m_secColour = 4;
	}

	this->m_normColour = this->m_shaderColour;
	this->m_hitColour = this->m_shaderColour;

	if (this->m_hitColour.r - 80 < 0)
		this->m_hitColour.r = 0;
	else
		this->m_hitColour.r -= 80;

	if (this->m_hitColour.g - 80 < 0)
		this->m_hitColour.g = 0;
	else
		this->m_hitColour.g -= 80;

	if (this->m_hitColour.b - 80 < 0)
		this->m_hitColour.b = 0;
	else
		this->m_hitColour.b -= 80;

}

sf::RectangleShape Enemy::GetCollisionBounds()
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(this->m_animationSheet.GetAnimationSprite().getLocalBounds().width, this->m_animationSheet.GetAnimationSprite().getLocalBounds().height));
	return rect;
}

Enemy::~Enemy()
{
}
