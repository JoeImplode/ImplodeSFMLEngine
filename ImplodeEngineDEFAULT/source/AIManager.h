	#pragma once
#include "Enemy.h"
class AIManager
{
public:
	//functions for checking enemies and changing their states to if they should attack, run, group, path
	//functions for grouping enemies
	//functions for directing enemies and pathing them correctly
	AIManager();
	AIManager(std::vector<Enemy*>enemies);
	~AIManager();

	void AddEnemy(Enemy * enemy);
	void AddEnemy(std::vector<Enemy*>enemies);
	void EnemyCleanup(); //perform cleanup operations
	void Update(float deltaTime);

	void Attack();
	void Run();
	void Group();
	void Path();

	inline std::vector<Enemy*> GetEnemies() { return this->m_enemies; }

private:
	std::vector<Enemy*> m_enemies;

protected:

};