#pragma once
#include "entity.h"



struct EnemyConfig : EntityConfig
{
	float m_currentX, m_currentY;
	float m_healthRegen;
	float m_range;
	int m_level;
	float m_speed;
};
class enemy : public entity
{
protected:
	//enemy states
	enum EnemyState
	{
		Idle,
		Seeking,
		Attacking,
		Fleeing,
		Dead,

	};
private:
	//member variables
	float m_speed;
	float m_range;
	float m_criticalHealth;
	bool m_isDead;

	//target variables
	entity* m_target;
	float m_targetX;
	float m_targetY;

	//state instance
	EnemyState e_state;

public:
	//setup/managment functions
	enemy(EnemyConfig eConfig);
	void Update() override;
	void Init() override;
	//stat based functions
	float GetCurrentHealth() override;
	float SetCriticalHealth(float health);
	void ReSpawn(int spawnX, int spawnY) override;
	//movement based functions
	void Seek();
	void Attack();
	void Flee();
	int getmove(int move, int dist);
	float FindTargetDistance(float XPos, float YPos, float targetXPos ,float targetYPos);

	//setters
	void SetTarget(entity* target);
	void setState();

	
	
};

