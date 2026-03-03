#include "entity.h"
#include "Object.h"
#include "TextObject.h"

#include <iostream>
#include <fstream>
#include <sstream>

entity::entity(EntityConfig config) : Object(config.m_imageFile, config.m_spawnX, config.m_spawnY, 50, 75, true), m_type(config.m_type),m_maxHealth(config.m_maxHealth) ,
m_currentHealth(config.m_maxHealth), m_currentX(config.m_spawnX), m_currentY(config.m_spawnY), m_damage(config.m_damage), m_isDead(false) , m_range(config.m_range)
, m_spawnX(config.m_spawnX), m_spawnY(config.m_spawnY)
{
	Init();
}

void entity::Init()
{
	Colour white;
	white.r = 255;
	white.g = 255;
	white.b = 255;

	textData = "health:" + std::to_string(GetCurrentHealth());
	healthObj = new TextObject(textData.c_str(), "assets/default.ttf", 15, m_currentX, m_currentY , white, true);
}

void entity::Move()
{
}

float entity::GetDamage()
{
	return 0.0f;
}

TextObject* entity::GetHealthObj()
{
	return healthObj;
}
float entity::GetCurrentHealth()
{
	return m_currentHealth;
}
void entity::TakeDamage(int damage)
{
	if (m_currentHealth >= 0.0f)
	{
		SetCurrentHealth(m_currentHealth - damage);
	}
	else
	{
		m_isDead = true;
	}
}

float entity::SetCurrentHealth(float currenthealth)
{

	m_currentHealth = currenthealth;
	textData = "health:" + std::to_string((int)GetCurrentHealth());
	healthObj->SetText(textData.c_str());

	healthObj->Update();

	return m_currentHealth;
}

std::vector<Object*> entity::getProjectiles()
{
	return m_projectiles;
}

std::vector<Object*> entity::BasicAttack()
{
	return m_projectiles;
}

//return current x pos
float entity::GetXPos()
{
	return m_currentX;
}
//return current y pos
float entity::GetYPos()
{
	return m_currentY;
}

float entity::GetOldX()
{
	return m_OX;

}
float entity::GetOldY() 
{
	return	m_OY;

}

bool entity::GetDead()
{
	return m_isDead;
}

void entity::ReSpawn(int spawnX, int spawnY)
{
	m_currentX = m_spawnX;
	m_currentY = m_spawnY;

	SetPosition(m_spawnX, m_spawnY);

	m_currentHealth = m_maxHealth;

	SetCurrentHealth(m_currentHealth);
	
}

