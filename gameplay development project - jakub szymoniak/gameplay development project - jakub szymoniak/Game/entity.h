#pragma once
#include <string>
#include "Object.h"
#include <vector>

struct EntityConfig
{
	const char* m_imageFile;
	std::string m_type, m_filepath;
	int m_spawnX, m_spawnY;
	float m_health;
	float m_damage;
	float m_range ;
	float m_cooldown ;
};


class entity : public Object
{

protected:

	//common member variables of all entities
	//most made as floats for stats scaling with items later down the line

	std::string m_type;
	int m_spawnX, m_spawnY;
	float m_health;
	float m_damage;
	float m_range;
	float m_cooldown;
	float m_OX, m_OY;
	
	bool m_canAttack = true;
	bool m_isDead = false;

	std::vector<Object*> m_projectiles;
	
public:
	
	//constructer for entities
	entity(EntityConfig config);
	//~entity();
	// 
	//common entity functions
	//virtual void SetStats(float health , float mana , float healthRegen , float manaRegen , float level, float damage, float speed, float cooldown, float range);
	virtual void Init();
	virtual void Move();
	std::vector<Object*> getProjectiles();
	virtual std::vector<Object*> BasicAttack();
	float GetOldX();
	float GetOldY();
	

	
	
	
	
	void Die(int m_level);
	void Spawn(int spawnX, int spawnY);

	
};

