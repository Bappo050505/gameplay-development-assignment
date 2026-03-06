#pragma once
#include "entity.h"

struct EnemyConfig : EntityConfig
{
	float m_currentX, m_currentY;
	float m_healthRegen;
	int m_level;
	float m_speed;
};

class enemy : public entity
{
private:
	float m_speed;

public:
	enemy(EnemyConfig eConfig);
	
};

