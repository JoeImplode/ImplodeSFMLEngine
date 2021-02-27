#include "pch.h"
#include "AIManager.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Demon.h"
#include "Treant.h"

AIManager::AIManager()
{
	
}

AIManager::AIManager(std::vector<Enemy*> enemies)
{
	this->m_enemies.insert(this->m_enemies.end(), enemies.begin(), enemies.end());
}

AIManager::~AIManager()
{
	this->m_enemies.clear();
}

void AIManager::AddEnemy(Enemy*enemy)
{
	this->m_enemies.push_back(enemy);
}

void AIManager::AddEnemy(std::vector<Enemy*> enemies)
{
	this->m_enemies.insert(this->m_enemies.end(),enemies.begin(), enemies.end());
}

void AIManager::EnemyCleanup()
{
	for (int i = 0; i < this->m_enemies.size(); i++)
	{
		if (!this->m_enemies[i]->GetDestroyStatus())
		{
			std::vector<Enemy*>::iterator it = std::find(this->m_enemies.begin(), this->m_enemies.end(), this->m_enemies[i]);
			this->m_enemies.erase(it);
		}
	}
}

void AIManager::Update(float deltaTime)
{
	for (int i = 0; i < this->m_enemies.size(); i++)
	{
		this->m_enemies[i]->Update(deltaTime);
	}
}

void AIManager::Attack()
{
	
}

void AIManager::Run()
{
}

void AIManager::Group()
{
}

void AIManager::Path()
{
}
