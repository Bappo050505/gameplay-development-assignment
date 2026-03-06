#include "entity.h"
#include "Object.h"

#include <iostream>
#include <fstream>
#include <sstream>

entity::entity(EntityConfig config): Object(config.m_imageFile, config.m_spawnX, config.m_spawnY, 50,75 ,true), m_type(config.m_type)
{
	
}

//void entity::SetStats(float health, float mana, float healthRegen, float manaRegen, float level, float damage, float speed, float cooldown,float range)
//{
//	m_health = health;
//	//m_level = level;
//	//m_healthRegen = healthRegen;
//	m_damage = damage;
//	m_speed = speed;
//	m_range = range;
//	m_cooldown = cooldown;
//	//m_mana = mana;
//	//m_manaRegen = manaRegen;
//}

void entity::Init()
{

}

void entity::Move()
{
}

std::vector<Object*> entity::getProjectiles()
{
	return m_projectiles;
}

std::vector<Object*> entity::BasicAttack()
{
	return m_projectiles;
}

float entity::GetOldX()
{
	return m_OX;

}
float entity::GetOldY() 
{
	return	m_OY;

}

void entity::Die(int m_level)
{
}

void entity::Spawn(int spawnX, int spawnY)
{
}
