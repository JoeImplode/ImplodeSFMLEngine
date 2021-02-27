#pragma once
#include "LightingManager.h"
#include "Animation.h"
#include "ParticleEmitter.h"

enum class ENEMY_STATE
{
	IDLE = 0,
	RUNNING = 1,
	ATTACK = 2,
	DEATH = 3
};

class Enemy
{
public:
	Enemy(); //default constructor doesn't set animation sheet nor animation sheet map vector
	Enemy(sf::Vector2f position, float attackRate, ENEMY_STATE state, bool facingDirection, Animation & animation, std::vector<ParticleEmitter>*emitters, sf::Color color, bool useColour); //facing direction: - false = left, true = right
	virtual void Update(float deltaTime) = 0;
	virtual void Update(float deltaTime, LightingManager& lManager) = 0;
	inline void SetAttackRate(float attackRate) { this->m_attackRate = attackRate; }

	void CheckEmitters();
	bool SetUpAnimations(Animation & idle, Animation & running, Animation & attack, Animation & death);
	void CheckColourSwitch();
	void Move();
	void ColourShaderCalculator();
	inline sf::Color GetShaderColour() { return this->m_shaderColour; }
	inline bool GetDestroyStatus() { return this->m_destroy; }

	sf::RectangleShape GetCollisionBounds();
	Animation m_animationSheet;
	std::map <ENEMY_STATE, Animation> m_enemyAnimations;
	std::vector<ParticleEmitter>* m_bulletEmitters;
	~Enemy();
	
private:
protected:
	sf::Vector2f m_position;
	float m_attackRate;
	ENEMY_STATE m_previousState;
	bool m_facingDirection;
	sf::Color m_normColour;
	sf::Color m_hitColour;
	sf::Clock m_hitTimer;
	sf::Clock m_startTimer;
	sf::Vector2f m_prevPos;
	sf::Vector2f m_scale;
	float m_darkerVal = 80;
	float m_moveVal = 0.3f;
	int m_primColour = 0;
	int m_secColour = 0;
	bool m_destroy = true;
	sf::Color m_shaderColour;
	sf::Shader* m_enemyColourShader;
};