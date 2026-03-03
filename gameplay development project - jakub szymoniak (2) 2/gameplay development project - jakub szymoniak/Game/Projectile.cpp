#include "Projectile.h"


Projectile::Projectile(std::string tag, const char* fileName, int spawnX, int spawnY) : Object(fileName, spawnX, spawnY, 50, 20, true)
, m_currentX(spawnX), m_currentY(spawnY), m_maxRange(300), m_spawnX(spawnX),m_spawnY(spawnY), m_deletable(false)
{
}



void Projectile::Update()
{
	GetPosition(m_currentX, m_currentY);

	if (m_currentX <= m_spawnX + m_maxRange) 
	{
		Move();
	}
	else 
	{
		SetShouldCollide(false);
		m_deletable = true;
	}
	
	
	Object::Update();
}

void Projectile::Move()
{
	float x = m_currentX;
	float y = m_currentY;
	GetPosition(x, y);
	x = x+2;
	SetPosition(x, y);
	
}










