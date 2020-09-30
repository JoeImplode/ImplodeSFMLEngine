#include "pch.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "ImplodeEngine.h"

ParticleEmitter::ParticleEmitter()
{
	this->m_particles = std::vector<Particle*>{};
}

ParticleEmitter::ParticleEmitter(int count, sf::Texture & txtr, sf::Vector2f forwardDir)
{
	this->m_particles = std::vector<Particle*>{};

	for (int i = 0; i < count; i++)
	{
		this->m_particles.push_back(new Particle(txtr,forwardDir));
	}
}

ParticleEmitter::~ParticleEmitter()
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		this->m_particles[i] = nullptr;
	}
}

void ParticleEmitter::SetParticleTxtr(Animation & txtr)
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		this->m_particles[i]->SetNewTexture(txtr);
	}
}

void ParticleEmitter::SetParticleTxtr(sf::Texture & txtr)
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		this->m_particles[i]->SetNewTexture(txtr);
	}
}

void ParticleEmitter::CreateParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit, sf::Texture &txtr,sf::Vector2f txtrForward,bool forceIn)
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		if (!this->m_particles[i]->GetActive())
		{
			this->m_particles[i]->SetForward(txtrForward);
			this->m_particles[i]->SetNewTexture(txtr);
			this->m_particles[i]->StartParticleStartEndPos(startPos, endPos, speed, timeLimit);
			return;
		}
	}
	if (forceIn == true)
	{
		this->m_particles[0]->Reset();
		this->m_particles[0]->SetForward(txtrForward);
		this->m_particles[0]->SetNewTexture(txtr);
		this->m_particles[0]->StartParticleStartEndPos(startPos, endPos, speed, timeLimit);
	}

}

void ParticleEmitter::CreateParticleStartEndPos(sf::Vector2f startPos, sf::Vector2f endPos, float speed, float timeLimit, Animation& txtr, sf::Vector2f txtrForward, bool forceIn)
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		if (!this->m_particles[i]->GetActive())
		{
			this->m_particles[i]->SetForward(txtrForward);
			this->m_particles[i]->SetNewTexture(txtr);
			this->m_particles[i]->StartParticleStartEndPos(startPos, endPos, speed, timeLimit);
			return;
		}
	}
	if (forceIn == true)
	{
		this->m_particles[0]->Reset();
		this->m_particles[0]->SetForward(txtrForward);
		this->m_particles[0]->SetNewTexture(txtr);
		this->m_particles[0]->StartParticleStartEndPos(startPos, endPos, speed, timeLimit);
	}
}

void ParticleEmitter::CreateParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float speed, float timeLimit, sf::Texture& txtr, sf::Vector2f txtrForward, bool forceIn)
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		if (!this->m_particles[i]->GetActive())
		{
			this->m_particles[i]->SetForward(txtrForward);
			this->m_particles[i]->SetNewTexture(txtr);
			this->m_particles[i]->StartParticle(position,velocity,acceleration,speed,timeLimit);
			return;
		}
	}

	if (forceIn == true)
	{
		this->m_particles[0]->Reset();
		this->m_particles[0]->SetForward(txtrForward);
		this->m_particles[0]->SetNewTexture(txtr);
		this->m_particles[0]->StartParticle(position, velocity, acceleration, speed, timeLimit);
	}
}

void ParticleEmitter::CreateParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float speed, float timeLimit, Animation& txtr, sf::Vector2f txtrForward, bool forceIn)
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		if (!this->m_particles[i]->GetActive())
		{
			this->m_particles[i]->SetForward(txtrForward);
			this->m_particles[i]->SetNewTexture(txtr);
			this->m_particles[i]->StartParticle(position, velocity, acceleration, speed, timeLimit);
			return;
		}
	}

	if (forceIn == true)
	{
		this->m_particles[0]->Reset();
		this->m_particles[0]->SetForward(txtrForward);
		this->m_particles[0]->SetNewTexture(txtr);
		this->m_particles[0]->StartParticle(position, velocity, acceleration, speed, timeLimit);
	}
}

void ParticleEmitter::Update(float deltaTime)
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		if (this->m_particles[i]->GetActive())
		{
			this->m_particles[i]->Update(deltaTime);
		}
	}
}

void ParticleEmitter::Draw(sf::RenderTexture& txtr)
{
	for (int i = 0; i < this->m_particles.size(); i++)
	{
		if (this->m_particles[i]->GetActive())
		{
			this->m_particles[i]->Draw(txtr);
		}
	}
}
