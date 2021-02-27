#include "pch.h"
#include "Animation.h"
#include "Player.h"
#include "ImplodeEngine.h"
#include "ParticleEmitter.h"

Player::Player()
{
	this->m_previousState = PLAYER_STATE::IDLE;
	this->m_position = sf::Vector2f(400, 400);
	this->m_machineGunEmitter = ParticleEmitter();
	this->m_pistolEmitter = ParticleEmitter();
	this->m_shotgunEmitter = ParticleEmitter();
	this->m_dmrEmitter = ParticleEmitter();
	this->m_scale = sf::Vector2f(1.0, 0.0);
	this->m_facingDirection = true;
	this->m_mousePressed = false;
	this->m_mouseWasPressed = false;
	this->m_colour = "Green";
	this->m_weaponSelection = WEAPON::PISTOL;

	this->m_pistolFireClock.restart();
	this->m_machineGunClock.restart();
	this->m_dmrClock.restart();
	this->m_shotgunClock.restart();
}

void Player::Update(float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->m_mousePressed = true;

	else
	{
		this->m_mousePressed = false;
		this->m_mouseWasPressed = false;
	}

	this->Move();
	this->m_animationSheet.SetPosition(this->m_position);

	this->m_animationSheet.Update(deltaTime);
	this->m_pistolEmitter.Update(deltaTime);
	this->m_shotgunEmitter.Update(deltaTime);
	this->m_machineGunEmitter.Update(deltaTime);
	this->m_dmrEmitter.Update(deltaTime);
}

void Player::Update(float deltaTime, LightingManager& lManager)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->m_mousePressed = true;

	else
	{
		this->m_mousePressed = false;
		this->m_mouseWasPressed = false;
	}

	this->Move();
	this->m_animationSheet.SetPosition(this->m_position);
	this->m_animationSheet.Update(deltaTime, lManager);
	this->m_pistolEmitter.Update(deltaTime,lManager);
	this->m_shotgunEmitter.Update(deltaTime, lManager);
	this->m_machineGunEmitter.Update(deltaTime,lManager);
	this->m_dmrEmitter.Update(deltaTime,lManager);
}

void Player::ProcessEvents(sf::Event& e)
{
	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Num1)
	{
		this->m_colour = "Green";
		this->m_animationSheet = this->m_colours[this->m_colour].at(m_previousState);
		this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
	}

	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Num2)
	{
		this->m_colour = "Blue";
		this->m_animationSheet = this->m_colours[this->m_colour].at(m_previousState);
		this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
	}

	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Num3)
	{
		this->m_colour = "Black";
		this->m_animationSheet = this->m_colours[this->m_colour].at(m_previousState);
		this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
	}

	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Num4)
	{
		this->m_colour = "Red";
		this->m_animationSheet = this->m_colours[this->m_colour].at(m_previousState);
		this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
	}

	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Num5)
	{
		this->m_colour = "Yellow";
		this->m_animationSheet = this->m_colours[this->m_colour].at(m_previousState);
		this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
	}
	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::F)
	{
		if (this->m_weaponSelection == WEAPON::PISTOL)
			this->m_weaponSelection = WEAPON::MACHINEGUN;
		else if (this->m_weaponSelection == WEAPON::MACHINEGUN)
			this->m_weaponSelection = WEAPON::SHOTGUN;
		else if (this->m_weaponSelection == WEAPON::SHOTGUN)
			this->m_weaponSelection = WEAPON::DMR;
		else if (this->m_weaponSelection == WEAPON::DMR)
			this->m_weaponSelection = WEAPON::PISTOL;
	}
	
}

void Player::Move()
{
	bool forceClickDir = false;
	this->m_clickingDirection = 0;

	if (this->m_mousePressed)
	if (this->m_mousePressed)
	{
		sf::Vector2f mousePos;
		mousePos.x = sf::Mouse::getPosition(*ImplodeEngine::m_window).x;
		mousePos.y = sf::Mouse::getPosition(*ImplodeEngine::m_window).y;

		if (this->m_animationSheet.GetAnimationSprite().getPosition().x < mousePos.x)
		{
			forceClickDir = true;
			this->m_clickingDirection = 1;
		}
		if (this->m_animationSheet.GetAnimationSprite().getPosition().x > mousePos.x)
		{
			forceClickDir = false;
			this->m_clickingDirection = -1;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->m_position.y -= this->m_speed.y;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->m_position.y += this->m_speed.y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->m_position.x += this->m_speed.x;

		if (this->m_facingDirection == false && !this->m_mousePressed) //LOOKING TO LEFT
		{
			this->FlipAnimations();
			this->m_facingDirection = true;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->m_position.x -= this->m_speed.x;

		if (this->m_facingDirection == true && !this->m_mousePressed) //LOOKING TO RIGHT
		{
			this->FlipAnimations();
			this->m_facingDirection = false;
		}
		
	}

	if (m_mousePressed && this->m_facingDirection && !forceClickDir)
	{
		this->FlipAnimations();
		this->m_facingDirection = false;
	}
	if (m_mousePressed && !this->m_facingDirection && forceClickDir)
	{
		this->FlipAnimations();
		this->m_facingDirection = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && this->m_previousState != PLAYER_STATE::RUN)
	{
		this->m_animationSheet = this->m_colours[this->m_colour].at(PLAYER_STATE::RUN);
		this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
		this->m_previousState = PLAYER_STATE::RUN;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->m_previousState != PLAYER_STATE::IDLE)
	{
		this->m_animationSheet = this->m_colours[this->m_colour].at(PLAYER_STATE::IDLE);
		this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
		this->m_previousState = PLAYER_STATE::IDLE;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->CalculateShootPos();
		if (this->m_weaponSelection == WEAPON::PISTOL)
		{
			if (this->m_pistolFireClock.getElapsedTime().asMilliseconds() > this->m_pistolFireRate)
			{
				this->m_pistolFireClock.restart();
				this->m_pistolEmitter.CreateParticle(this->m_shootPos, sf::Vector2f(sf::Mouse::getPosition(*ImplodeEngine::m_window).x - this->m_shootPos.x, sf::Mouse::getPosition(*ImplodeEngine::m_window).y - this->m_shootPos.y), sf::Vector2f(1, 1),
					2000, 3, this->m_pistolTexture, sf::Vector2f(0.0f, -1.0f), false);
			}
		}
		if (this->m_weaponSelection == WEAPON::MACHINEGUN)
		{
			if (this->m_machineGunClock.getElapsedTime().asMilliseconds() > this->m_machineGunFireRate)
			{
				this->m_machineGunClock.restart();
				this->m_machineGunEmitter.CreateParticle(this->m_shootPos, sf::Vector2f(sf::Mouse::getPosition(*ImplodeEngine::m_window).x - this->m_shootPos.x, sf::Mouse::getPosition(*ImplodeEngine::m_window).y - this->m_shootPos.y), sf::Vector2f(1, 1),
					2000, 3, this->m_machineGunTexture, sf::Vector2f(0.0f, -1.0f), false);
			}
		}

		if (this->m_weaponSelection == WEAPON::DMR)
		{
			if (this->m_dmrClock.getElapsedTime().asMilliseconds() > this->m_dmrFireRate)
			{
				this->m_dmrClock.restart();
				this->m_dmrEmitter.CreateParticle(this->m_shootPos, sf::Vector2f(sf::Mouse::getPosition(*ImplodeEngine::m_window).x - this->m_shootPos.x, sf::Mouse::getPosition(*ImplodeEngine::m_window).y - this->m_shootPos.y), sf::Vector2f(1, 1),
					1900, 3, this->m_dmrTexture, sf::Vector2f(0.0f, -1.0f), false);
			}
		}

		if (this->m_weaponSelection == WEAPON::SHOTGUN)
		{
			if (this->m_shotgunClock.getElapsedTime().asMilliseconds() > this->m_shotgunFireRate)
			{
				sf::Vector2f generalDirection = sf::Vector2f(sf::Mouse::getPosition(*ImplodeEngine::m_window).x - this->m_shootPos.x, sf::Mouse::getPosition(*ImplodeEngine::m_window).y - this->m_shootPos.y);

				float magnitude = sqrt((generalDirection.x * generalDirection.x) + (generalDirection.y * generalDirection.y));

				generalDirection.x /= magnitude;
				generalDirection.y /= magnitude;

				this->m_shotgunEmitter.CreateParticle(this->m_shootPos, sf::Vector2f(generalDirection.x + 0.12,generalDirection.y -0.12), sf::Vector2f(1, 1),
					2197, 0.4, this->m_shotgunTexture, sf::Vector2f(0.0f, -1.0f), false);

				this->m_shotgunEmitter.CreateParticle(this->m_shootPos, sf::Vector2f(generalDirection.x - 0.1, generalDirection.y + 0.11), sf::Vector2f(1, 1),
					1897, 0.4, this->m_shotgunTexture, sf::Vector2f(0.0f, -1.0f), false);

				this->m_shotgunEmitter.CreateParticle(this->m_shootPos, sf::Vector2f(generalDirection.x ,generalDirection.y ), sf::Vector2f(1, 1),
					1700, 0.4, this->m_shotgunTexture, sf::Vector2f(0.0f, -1.0f), false);

				this->m_shotgunEmitter.CreateParticle(this->m_shootPos, sf::Vector2f(generalDirection.x - 0.12, generalDirection.y -0.12), sf::Vector2f(1, 1),
					1997, 0.4, this->m_shotgunTexture, sf::Vector2f(0.0f, -1.0f), false);

				this->m_shotgunEmitter.CreateParticle(this->m_shootPos, sf::Vector2f(generalDirection.x +0.1, generalDirection.y + 0.1), sf::Vector2f(1, 1),
					2097, 0.4, this->m_shotgunTexture, sf::Vector2f(0.0f, -1.0f), false);

				this->m_shotgunClock.restart();
			}
		}
	}
}

void Player::FlipAnimations()
{
	std::map<PLAYER_STATE, Animation>::iterator it;
	std::map<std::string, std::map<PLAYER_STATE, Animation>>::iterator colourIterator;
	
	this->m_scale.x = -this->m_scale.x;

	for(colourIterator = this->m_colours.begin(); colourIterator != this->m_colours.end(); colourIterator++)
	{
		for (it = this->m_animations.begin(); it != this->m_animations.end(); it++)
		{
			this->m_colours[colourIterator->first].at(it->first).SetScale(this->m_scale);
		}
	}
	this->m_animationSheet.FlipSprite(sf::Vector2f(this->m_scale));
	
}

void Player::CalculateShootPos()
{
	//get the pos of the animation sheet we're using
	sf::Vector2f gunPos;
	if (this->m_animationSheet.GetScale().x < 0)
	{
		gunPos.x = this->m_position.x - (this->m_animationSheet.GetOrigin().x*2);
		gunPos.y = this->m_position.y - 10;
	}
	else if (this->m_animationSheet.GetScale().x > 0)
	{ 
		gunPos.x = (this->m_position.x) + (this->m_animationSheet.GetOrigin().x*2);
		gunPos.y = this->m_position.y - 10;
	}
	this->m_shootPos = gunPos;
}

void Player::UpdateColours()
{
	this->m_animationSheet = this->m_colours[this->m_colour].at(m_previousState);
}

void Player::SetUpEmitters(sf::Texture& pistolTexture, sf::Texture& shotgunTexture, sf::Texture& mgTexture, sf::Texture& dmrTexture)
{
	this->m_pistolEmitter = ParticleEmitter(30, pistolTexture, sf::Vector2f(0, 1));
	this->m_pistolTexture = pistolTexture;
	this->m_shotgunEmitter = ParticleEmitter(30, shotgunTexture, sf::Vector2f(-1, 0.5));
	this->m_shotgunTexture = shotgunTexture;
	this->m_machineGunEmitter = ParticleEmitter(30, mgTexture, sf::Vector2f(-1, 0.5));
	this->m_machineGunTexture = mgTexture;
	this->m_dmrEmitter = ParticleEmitter(30, dmrTexture, sf::Vector2f(-1, 0.5));
	this->m_dmrTexture = dmrTexture;

	this->m_emitters.push_back(m_pistolEmitter);
	this->m_emitters.push_back(m_shotgunEmitter);
	this->m_emitters.push_back(m_machineGunEmitter);
	this->m_emitters.push_back(m_dmrEmitter);
}


