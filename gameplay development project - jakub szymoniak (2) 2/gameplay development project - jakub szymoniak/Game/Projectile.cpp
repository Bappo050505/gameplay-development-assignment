#include "Projectile.h"


Projectile::Projectile(std::string tag, const char* fileName, int spawnX, int spawnY) : Object(fileName, spawnX, spawnY, 50, 20, true)
, m_currentX(spawnX), m_currentY(spawnY), m_maxRange(300), m_spawnX(spawnX),m_spawnY(spawnY), m_deletable(false) , m_speed(3)
{
}



void Projectile::Update()
{
	GetPosition(m_currentX, m_currentY);

	if (m_maxRange >= FindTargetDistance(m_currentX , m_currentY, m_spawnX, m_spawnY)) 
	{
		
		Move(m_targetX,m_targetY);
	}
	else 
	{
		SetShouldCollide(false);
		m_deletable = true;
	}

	Object::Update();
}

void Projectile::Move(float targetX, float targetY)
{
	

	
	
	//gets current position
	GetPosition(m_currentX, m_currentY);

	//normalisation and direction setting
	

	//how much to move by in each direction
	float moveAmount[2]{ direction[0] * m_speed , direction[1] * m_speed };
		
	m_currentX += moveAmount[0];
	m_currentY += moveAmount[1];

	SetPosition(m_currentX, m_currentY);
	
}

void Projectile::SetTargetLocation(float targetX, float targetY)
{
	m_targetX = targetX;
	m_targetY = targetY;

	FindTargetDirection(0, targetX, targetY);

}










