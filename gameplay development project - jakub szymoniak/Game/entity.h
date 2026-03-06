#pragma once
#include <string>
#include "Object.h"


struct EntityConfig
{
	const char* m_imageFile;
	std::string m_tag, m_filepath;
	float m_spawnX, m_spawnY;
	float m_maxHealth;
	
	float m_damage;
	float m_range ;
	float m_cooldown ;

	bool isDead;
};

class TextObject;
class entity : public Object
{

protected:

	//common member variables of all entities
	//most made as floats for stats scaling with items later down the line

	std::string m_type;
	float m_spawnX, m_spawnY;
	float m_currentX, m_currentY;
	float m_health;
	float m_damage;
	float m_range;
	float m_cooldown;
	float m_OX, m_OY;
	float m_currentHealth;
	float m_maxHealth;

	bool m_canAttack = true;
	bool m_isDead = false;

	std::vector<Object*> m_projectiles;
	

protected:
	std::string textData;
	TextObject* healthObj;
	
public:
	
	//constructer for entities
	entity(EntityConfig config);
	//~entity();
	// 
	//common entity functions
	//virtual void SetStats(float health , float mana , float healthRegen , float manaRegen , float level, float damage, float speed, float cooldown, float range);
	virtual void Init();
	virtual void Move();
	virtual float GetDamage();
	virtual float GetCurrentHealth();
	virtual void TakeDamage(int damage);
	virtual float SetCurrentHealth(float currenthealth);
	virtual TextObject* GetHealthObj();
	std::vector<Object*> getProjectiles();
	virtual void BasicAttack(float clickX, float clickY);
	float GetXPos();
	float GetYPos();
	float GetOldX();
	float GetOldY();
	bool GetDead();
	void ProjectileUpdate();
	//float FindTargetDistance(float XPos, float YPos, float targetXPos, float targetYPos);
	//std::vector<float> FindTargetDirection(float vctLength, float targetXPos, float targetYPos);
	
	virtual void ReSpawn(int spawnX, int spawnY);

	
};

