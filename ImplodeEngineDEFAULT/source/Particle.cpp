#include "pch.h"
#include "Particle.h"
#include "ImplodeEngine.h"

Particle::Particle()
{
	this->m_pSpeed = 0.0f;
	this->m_pVelocity = sf::Vector2f(0.0f, 0.0f);
	this->m_pAcceleration = sf::Vector2f(0.0f, 0.0);
	this->m_timeLimit = 0.0f;
	this->m_active = false;
}

Particle::Particle(Animation texture, sf::Vector2f forwardDir)
{
	this->m_active = false;
	this->m_texture = texture;
	this->m_forward = forwardDir;
	this->m_texture.GetAnimationSprite().setOrigin(sf::Vector2f(this->m_texture.GetAnimationSprite().getLocalBounds().width / 2, this->m_texture.GetAnimationSprite().getLocalBounds().height / 2));
}

Particle::Particle(sf::Texture & txtr, sf::Vector2f forwardDir)
{
	this->m_active = false;
	Animation animation(0.0f, sf::Vector2f(0.0f,0.0f), sf::Vector2f(1.0f, 1.0f));
	animation.SetAnimationSheet(txtr, 1, 1);
	animation.SetRow(0);
	animation.SetColumnNum(0);
	animation.SetRepeated(true);
	this->m_texture = animation;
	this->m_texture.GetAnimationSprite().setOrigin(sf::Vector2f(this->m_texture.GetAnimationSprite().getLocalBounds().width / 2, this->m_texture.GetAnimationSprite().getLocalBounds().height / 2));
	this->m_forward = forwardDir;
}

void Particle::Update(float deltaTime)
{
	if (this->m_time.getElapsedTime().asSeconds() > this->m_timeLimit)
	{
		this->m_active = false;
		this->Reset();
	}

	if (this->m_active && !m_moveToPos)
	{
		sf::Vector2f newPos;
		newPos.x = this->m_position.x + (this->m_pVelocity.x * (m_pSpeed * deltaTime ));
		newPos.y = this->m_position.y + (this->m_pVelocity.y * (m_pSpeed * deltaTime ));
		this->m_position = newPos;
		this->m_texture.SetPosition(m_position);
		this->m_texture.Update(deltaTime);
	}
	else if (this->m_active && m_moveToPos)
	{
		float dist = CalculateDistance();
		this->m_distCovered -= this->m_distCovered - dist;

			if (this->m_distCovered > 1.0f)
			{
				sf::Vector2f newPos;

				newPos.x = this->m_position.x + (this->m_pVelocity.x * (m_pSpeed * deltaTime));
				newPos.y = this->m_position.y + (this->m_pVelocity.y * (m_pSpeed * deltaTime));

				this->m_position = newPos;
				this->m_texture.SetPosition(m_position);
			}
		this->m_texture.Update(deltaTime);
	}
}

void Particle::Draw(sf::RenderTexture & txtr)
{
	if(this->m_active)
		this->m_texture.Render(txtr);
}

void Particle::StartParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration,float speed,float timeLimit)
{
	float magnitude = sqrt(pow((velocity.x), 2) + pow((velocity.y), 2));

	this->m_position = position;
	this->m_texture.SetPosition(m_position);
	this->m_pVelocity = sf::Vector2f(velocity.x / magnitude,velocity.y / magnitude);
	this->m_pSpeed = speed;
	this->m_active = true;
	this->m_time.restart();
	this->m_timeLimit = timeLimit;

	float angle = ((this->m_forward.x * m_pVelocity.x) + (m_forward.y * m_pVelocity.y));
	float sqrt1;
	float sqrt2;
	sqrt1 = sqrt((m_forward.x * m_forward.x) + (m_forward.y * m_forward.y));
	sqrt2 = sqrt((m_pVelocity.x * m_pVelocity.x) + (m_pVelocity.y * m_pVelocity.y));
	int j = 1;

	angle = angle / (sqrt1 * sqrt2);

	this->m_texture.GetAnimationSprite().rotate(CalculateRotationAngle(velocity, angle));

}

void Particle::StartParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit)
{
	this->m_dist.x = endPos.x - startPos.x;
	this->m_dist.y = endPos.y - startPos.y;

	float distance = sqrt(pow((m_dist.x), 2)) + pow((m_dist.y), 2);
	this->m_distCovered = distance;

	sf::Vector2f dirVect = sf::Vector2f(endPos.x - startPos.x, endPos.y - startPos.y);

	float magnitude1 = sqrt((dirVect.x * dirVect.x) + (dirVect.y * dirVect.y));

	sf::Vector2f velocity = sf::Vector2f(dirVect.x / magnitude1, dirVect.y / magnitude1);

	this->m_position = startPos;
	this->m_pVelocity = velocity;
	this->m_pSpeed = speed;
	this->m_moveToPos = true;
	this->m_active = true;
	this->m_endPos = endPos;
	this->m_timeLimit = timeLimit;
	this->m_time.restart();

	float angle = ((this->m_forward.x * m_pVelocity.x) + (m_forward.y * m_pVelocity.y));

	float sqrt1;
	float sqrt2;
	sqrt1 = sqrt((m_forward.x * m_forward.x) + (m_forward.y * m_forward.y));
	sqrt2 = sqrt((m_pVelocity.x * m_pVelocity.x) + (m_pVelocity.y * m_pVelocity.y));

	angle = angle / (sqrt1 * sqrt2);

	this->m_texture.GetAnimationSprite().rotate(CalculateRotationAngle(velocity,angle));

}

void Particle::SetNewTexture(sf::Texture & texture)
{
	Animation animation(0.0f, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 1.0f));
	animation.SetAnimationSheet(texture, 1, 1);
	animation.SetRow(0);
	animation.SetColumnNum(0);
	animation.SetRepeated(true);
	this->m_texture = animation;
	this->m_texture.GetAnimationSprite().setOrigin(sf::Vector2f(this->m_texture.GetAnimationSprite().getLocalBounds().width / 2, this->m_texture.GetAnimationSprite().getLocalBounds().height / 2));
}

void Particle::SetNewTexture(Animation& animation)
{
	this->m_texture = animation;
	this->m_texture.GetAnimationSprite().setOrigin(sf::Vector2f(this->m_texture.GetAnimationSprite().getLocalBounds().width / 2, this->m_texture.GetAnimationSprite().getLocalBounds().height / 2));
}

void Particle::Reset()
{
	this->m_position = sf::Vector2f(0.0f, 0.0f);
	this->m_pVelocity = sf::Vector2f(0.0f, 0.0f);
	this->m_pSpeed = 0.0f;
	this->m_moveToPos = false;
	this->m_active = false;
	this->m_endPos = sf::Vector2f(0.0f, 0.0f);
	this->m_timeLimit = 0.0f;
	this->m_dist = sf::Vector2f(0.0f, 0.0f);
	
	this->m_time.restart();
}

float Particle::CalculateRotationAngle(sf::Vector2f velocity, float angle)
{
	float finalAngle = (acos(angle) * 180.0f) / 3.141592653589793238463f;

	if (velocity.x > 0.0f && velocity.y < 0.0f)
		return finalAngle;
	else if (velocity.x < 0 && velocity.y < 0)
		return -finalAngle;
	else if (velocity.x > 0 && velocity.y > 0)
		return finalAngle;
	else if (velocity.x < 0 && velocity.y > 0)
		return -finalAngle;
	else if (std::signbit(angle) && velocity.x == 0.0f && angle == 0.0f)
		return -90.0f;
	else if (velocity.y == 0.0f && !std::signbit(velocity.y) && angle == 0.0f)
		return 90;
	else if (angle == -1.0f)
		return 180;
	else
		return 0.0f;
}

float Particle::CalculateDistance()
{
	this->m_dist.x = this->m_endPos.x - this->m_position.x;
	this->m_dist.y = this->m_endPos.y - this->m_position.y;
	float distance = sqrt(pow((m_dist.x), 2)) + pow((m_dist.y), 2);

	return distance;
}



