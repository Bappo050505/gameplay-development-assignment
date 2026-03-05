#include "enemy.h"
#include "TextObject.h"
#include "player.h"
#include "Projectile.h"

enemy::enemy(EnemyConfig eConfig) :entity(eConfig), m_speed(eConfig.m_speed), e_state(Idle), m_isDead(false) , m_range(eConfig.m_range)
{

}

void enemy::Update()
{
	//switch state for enemy
	switch (e_state) 
	{
	case Idle:
		break;
	case Seeking:
		Seek(FindTargetDistance(m_currentX, m_currentY, m_target->GetXPos(), m_target->GetYPos()));
		break;
	case Attacking:
		Attack(FindTargetDistance(m_currentX, m_currentY, m_target->GetXPos(), m_target->GetYPos()));
		break;
	case Fleeing:
		//Flee(m_player);
	case Dead:
		ReSpawn(m_spawnX, m_spawnY);
		break;
	default:
		break;
	}

	ProjectileUpdate();

	SetCriticalHealth(m_maxHealth);

	setState();
	
	healthObj->Update();

	entity::Update();
}

//sets the target the enemy will be attacking
void enemy::SetTarget(entity* target)
{
	m_target = target;
}

void enemy::setState()
{
	//checks if the enemy is dead
	if (GetDead()) 
	{
		e_state = Dead;
	}
	//default none moving state
	//used if player dies etc...
	else if(m_target->GetDead())
	{
		e_state = Idle;
	}
	//checks the enemy current health against cirtical threshold and flees is true
	else if (m_currentHealth <= m_criticalHealth) 
	{
		e_state = Fleeing;
	}
	//setting states for the enemy
	//checks distance from enemy to target + the enemy range and moves untill its within range
	else if ((FindTargetDistance(m_currentX, m_currentY, m_target->GetXPos(), m_target->GetYPos()) > m_range))
	{
		e_state = Seeking;
	}
	//checks if its in range of target and enteres attack mode if it is
	else
	{
		e_state = Attacking;
	}
}

void enemy::Init()
{

}
//grabs current enemy health
float enemy::GetCurrentHealth()
{
	return m_currentHealth;
}
//calculating critical health threshold (made for future when scaling health is implemented)
float enemy::SetCriticalHealth(float health)
{
	m_criticalHealth = health *0.2f;
	return m_criticalHealth;
}
//respawn overload
void enemy::ReSpawn(int spawnX, int spawnY)
{
	m_currentX = m_spawnX;
	m_currentY = m_spawnY;

	SetPosition(m_spawnX, m_spawnY);

	m_currentHealth = m_maxHealth;

	SetCurrentHealth(m_currentHealth);
}
//1st state for the enemy, will move towards the target when out of attacking range
void enemy::Seek(float distanceFromTarget)
{
	bool ismoving = true;
	int  XPos, Ypos;

	XPos = m_target->GetXPos();
	XPos += 25;
	Ypos = m_target->GetYPos();
	Ypos += 25;

	GetPosition(m_currentX, m_currentY);

	float speed = 2.0f;

	if ((distanceFromTarget) > (m_range))
	{
		int xdif = (XPos - m_currentX);
		int ydif = (Ypos - m_currentY);

		FindTargetDirection(FindTargetDistance(m_currentX, m_currentY, m_target->GetXPos() , m_target->GetYPos()), m_target->GetXPos() , m_target->GetYPos());

		int moveAmount[2]{ direction[0] * speed , direction[1] * speed };

		if (m_currentX == XPos && m_currentY == Ypos)
		{
			ismoving = false;
		}

		if (ismoving)
		{
			m_OX = m_currentX;
			m_OY = m_currentY;
			m_currentX += getmove(moveAmount[0], (XPos - m_currentX));
			m_currentY += getmove(moveAmount[1], (Ypos - m_currentY));

			SetPosition(m_currentX, m_currentY);
		}

	}
	else
	{
		ismoving = false;
	}

}



//2nd enemy state, attacks when in range
void enemy::Attack(float distanceFromTarget)
{
	if (std::abs(distanceFromTarget < m_range)) 
	{
		if (m_projectiles.size() < 4)
		{
			int pPosX = m_currentX;
			int pPosY = m_currentY;

			//creates projectile
			Projectile* projectile = new Projectile("Player", "assets/baguette.bmp", pPosX, pPosY);
			projectile->SetTargetLocation(m_target->GetOldX(), m_target->GetOldY());
			m_projectiles.push_back(projectile);

		}
			
	}
	
}
//3rd state not implemented
//void enemy::Flee(player* player)
//}


