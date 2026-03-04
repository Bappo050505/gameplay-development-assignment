#pragma once
#include "Object.h"
#include "Input.h"
#include <string>;

//creating projectile class for better managment of projectiles for entities
class Projectile : public Object
{
private:
	std::string tag;
	float m_speed;
	float m_spawnX;
	float m_spawnY;
	float m_currentX;
	float m_currentY;
	float m_maxRange;
	bool m_deletable;
	float m_targetX, m_targetY;


protected:


public:
	Projectile(std::string tag , const char* fileName, int spawnX, int spawnY);
	//~Projectile();
	virtual void Update()override;
	void Move(float targetX , float targetY);
	void SetTargetLocation(float targetX, float targetY);
	
	
};

//either create a tag or add pointer to projectile owner (for collision so owners projectiles dont damage them)



