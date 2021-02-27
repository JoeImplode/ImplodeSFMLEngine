#pragma once
#include "LightingManager.h"
#include "Animation.h"
#include "ParticleEmitter.h"

enum class PLAYER_STATE
{
	IDLE = 0,
	RUN = 1,
	JUMP = 2,
	DEATH = 3,
	CROUCH = 4
};

enum class WEAPON
{
	PISTOL = 0,
	MACHINEGUN = 1,
	SHOTGUN = 2,
	DMR = 3
};

class Player
{
public:
	Player();
	void Update(float deltaTime);
	void Update(float deltaTime, LightingManager& lManager);
	void ProcessEvents(sf::Event& e);
	void Move();
	inline void SetPosition(sf::Vector2f position) { this->m_position = position; }
	inline void SetSpeed(sf::Vector2f speed) { this->m_speed = speed; }
	inline void SetScale(sf::Vector2f scale) { this->m_scale = scale; }
	inline std::vector<ParticleEmitter>* GetParticleEmitters() { return &this->m_emitters; }
	void FlipAnimations();
	void CalculateShootPos();
	void UpdateColours();
	void SetUpEmitters(sf::Texture & pistolTexture, sf::Texture& shotgunTexture, sf::Texture& mgTexture, sf::Texture& dmrTexture);
	Animation m_animationSheet;
	WEAPON m_weaponSelection;
	ParticleEmitter m_machineGunEmitter;
	ParticleEmitter m_pistolEmitter;
	ParticleEmitter m_shotgunEmitter;
	ParticleEmitter m_dmrEmitter;

	std::vector<ParticleEmitter> m_emitters;

	std::map <PLAYER_STATE, Animation> m_animations;
	std::map <std::string, std::map <PLAYER_STATE, Animation>> m_colours;

	std::string m_colour;
private:
	sf::Vector2f m_position;
	bool m_mousePressed;
	bool m_mouseWasPressed;
	bool m_facingDirection; //false is equal to left, true is right
	int m_clickingDirection = 0;

	sf::Vector2f m_shootPos;
	sf::Vector2f m_speed;
	sf::Vector2f m_scale;

	PLAYER_STATE m_previousState;

	sf::Texture m_pistolTexture;
	sf::Texture m_machineGunTexture;
	sf::Texture m_shotgunTexture;
	sf::Texture m_dmrTexture;

	sf::Clock m_pistolFireClock;
	sf::Clock m_machineGunClock;
	sf::Clock m_shotgunClock;
	sf::Clock m_dmrClock;

	float m_pistolFireRate = 250; //pistolFireRate as seconds#]
	float m_shotgunFireRate = 400;
	float m_machineGunFireRate = 100;
	float m_dmrFireRate = 600;
protected:
};

