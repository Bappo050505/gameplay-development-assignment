#include "enemy.h"
#include "TextObject.h"
#include "player.h"

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
		Seek();
		break;
	case Attacking:
		//Attack(m_player);
		break;
	case Fleeing:
		//Flee(m_player);
	case Dead:
		ReSpawn(m_spawnX, m_spawnY);
		break;
	default:
		break;
	}

	SetCriticalHealth(m_maxHealth);

	setState();
	
	healthObj->Update();

	/*if (m_currentHealth <= 0.0f)
	{
		ReSpawn(m_spawnX, m_spawnY);
	}*/

	entity::Update();
}

float enemy::FindTargetDistance(float XPos, float YPos, float targetXPos, float targetYPos)
{
	//calculating the diagonal from the enemy to the target
	float xDifferance = XPos - targetXPos;
	float yDifferance = YPos - targetYPos;

	float diagLength = abs(sqrt(pow(xDifferance, 2) + pow(yDifferance, 2)));

	
	//return distance from taget
	return diagLength;
}

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

void enemy::ReSpawn(int spawnX, int spawnY)
{
	m_currentX = m_spawnX;
	m_currentY = m_spawnY;

	SetPosition(m_spawnX, m_spawnY);

	m_currentHealth = m_maxHealth;

	SetCurrentHealth(m_currentHealth);
}

void enemy::Seek()
{

	bool ismoving = true;

	int  XPos, Ypos;

	XPos = m_target->GetXPos();
	XPos += 25;
	Ypos = m_target->GetYPos();
	Ypos += 25;

	GetPosition(m_currentX, m_currentY);

	float speed = 2.0f;

	int xdif = (XPos - m_currentX);
	int ydif = (Ypos - m_currentY);

	float vctLength = sqrt((xdif * xdif) + (ydif * ydif));


	float direction[2]{ (xdif / vctLength) , (ydif / vctLength) };

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


int enemy::getmove(int move, int dist)
{
	if (std::abs(move) > std::abs(dist))
	{

		return dist;
	}
	return move;
}

//void enemy::Attack(player* player)
//{
//}
//
//void enemy::Flee(player* player)
//{
//}


