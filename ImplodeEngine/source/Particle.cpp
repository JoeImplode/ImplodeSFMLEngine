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
	this->m_forward = forwardDir;
}

void Particle::Update(float deltaTime)
{
	if (this->m_time.getElapsedTime().asSeconds() > this->m_timeLimit)
		this->m_active = false;

	if (this->m_active && !m_moveToPos)
	{
		sf::Vector2f newPos;
		newPos.x = this->m_position.x + (this->m_pVelocity.x * (m_pSpeed * deltaTime));
		newPos.y = this->m_position.y + (this->m_pVelocity.y * (m_pSpeed * deltaTime));
		this->m_position = newPos;
		this->m_texture.SetPosition(m_position);
		this->m_texture.Update(deltaTime);
	}
	else if (this->m_active && m_moveToPos)
	{
		if (!((int)this->m_position.x == (int)this->m_endPos.x && (int)this->m_position.y == (int)m_endPos.y))
		{
			std::cout << "End Pos Y: " << m_endPos.y << std::endl;
			std::cout << "Current Pos Y: "<< m_position.y << std::endl;

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
	this->m_position = position;
	this->m_texture.SetPosition(m_position);
	this->m_pVelocity = velocity;
	this->m_pSpeed = speed;
	this->m_active = true;
	this->m_time.restart();
	this->m_timeLimit = timeLimit;
	float angle = ((this->m_forward.x * m_pVelocity.x) + (m_forward.y * m_pVelocity.y));
	float sqrt1;
	float sqrt2;
	sqrt1 = sqrt((m_forward.x * m_forward.x) + (m_forward.y * m_forward.y));
	sqrt2 = sqrt((m_pVelocity.x * m_pVelocity.x) + (m_pVelocity.y * m_pVelocity.y));

	angle = angle / (sqrt1 * sqrt2);
	float rads = acos(angle);
	float degs = rads * (180.0 / 3.141592653589793238463);

	this->m_texture.GetAnimationSprite().rotate(degs);

}

void Particle::StartParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit)
{
	float magnitude1 = sqrt(pow((startPos.x), 2) + pow((startPos.y), 2));
	float magnitude2 = sqrt(pow((endPos.x), 2) + pow((endPos.y), 2));

	sf::Vector2f velocity = sf::Vector2f((endPos.x - startPos.x) / magnitude1, (endPos.y - startPos.y)/magnitude1);

	float dotProduct = (startPos.x * endPos.x) + (startPos.y * endPos.y);

	float angle = dotProduct / (magnitude1);

	std::cout << atan(angle) << std::endl;
	std::cout << acos(angle) << std::endl;

	float x = endPos.x - startPos.x;
	float y = endPos.y - startPos.y;

	std::cout <<"A tan 2: "<< atan2(x,y) << std::endl;

	float test = atan2(x,y);

	this->m_position = startPos;
	this->m_pVelocity = velocity;
	this->m_pSpeed = speed;
	this->m_moveToPos = true;
	this->m_active = true;
	this->m_endPos = endPos;
	this->m_timeLimit = timeLimit;
	this->m_time.restart();

	std::cout << atan(angle) << std::endl;

	float degs = (atan(angle) * 180.0f) / 3.1459f;

	std::cout << degs << std::endl;

	float finalAngle = (test > 0 ? test : (2 * 3.1415 + test)) * 360 / (2 * 3.1415);

	std::cout << "Test val: " << (test > 0 ? test : (2 * 3.1415 + test)) * 360 / (2 * 3.1415) << std::endl;
	this->m_texture.GetAnimationSprite().rotate(finalAngle);
}

void Particle::SetNewTexture(sf::Texture & texture)
{
	Animation animation(0.0f, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(texture.getSize().x, texture.getSize().y));
	animation.SetAnimationSheet(texture, 1, 1);
	animation.SetRow(0);
	animation.SetColumnNum(0);
	animation.SetRepeated(true);
	this->m_texture = animation;
}

