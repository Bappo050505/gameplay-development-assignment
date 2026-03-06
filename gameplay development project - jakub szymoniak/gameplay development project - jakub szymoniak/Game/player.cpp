#include "player.h"
#include"Projectile.h"
#include <iostream>

player::player(PlayerConfig pConfig) : entity(pConfig), m_mana(pConfig.m_mana), m_manaRegen(pConfig.m_manaRegen), m_speed(pConfig.m_speed)
, m_currentX(pConfig.m_spawnX), m_currentY(pConfig.m_spawnY), m_clickX(pConfig.m_spawnX), m_clickY(pConfig.m_spawnY)
{
	

}
//overiden update to let player update its self
void player::Update()
{
	for (Object* p : m_projectiles)
	{

		for (Object* p : m_projectiles)
		{
			if (p->GetShouldCollide() == false)
			{
				m_projectiles.erase(m_projectiles.begin() + 1);
			}
		}
		p->Update();
		
	}

	entity::Update();
}

void player::Init()
{
	
}

//return current x pos
float player::GetXPos()
{
	return m_currentX;
}
//return current y pos
float player::GetYPos()
{
	return m_currentY;
}
//allows the player to shoot out a projectile
std::vector<Object*> player::BasicAttack()
{
	//sets projectile limit to 4
	if (m_projectiles.size() < 4)
	{
		int pPosX = m_currentX;
		int pPosY = m_currentY;

		//creates projectile
		m_projectiles.push_back(new Projectile("Player" , "assets/baguette.bmp", pPosX, pPosY));

		std::cout << "attacked" << std::endl;
		
	}
	else
	{
		//output if max attacks reached
		std::cout << "Max Attacks" << std::endl;
	}
	

	return m_projectiles;
}
void player::Move()
{
	bool ismoving = true;
	int  mouseX, mouseY;

	GetPosition(m_currentX, m_currentY);

	m_inputManager->GetMousePos(mouseX, mouseY);

	if (m_inputManager->GetMouseDown(RIGHTMOUSEBUTTON))
	{

		m_clickX = mouseX;
		m_clickY = mouseY;

	}
	int xdif = (m_clickX - m_currentX);
	int ydif = (m_clickY - m_currentY);

	float vctLength = sqrt((xdif * xdif) + (ydif * ydif));

	float direction[2]{ (xdif / vctLength) , (ydif / vctLength) };

	int moveAmount[2] { direction[0] * m_speed , direction[1] * m_speed };



	if (m_currentX == m_clickX && m_currentY == m_clickY)
	{
		ismoving = false;
	}

	if (ismoving)
	{
		m_OX = m_currentX;
		m_OY = m_currentY;

		m_currentX += getmove(moveAmount[0], (m_clickX - m_currentX));
		m_currentY += getmove(moveAmount[1], (m_clickY - m_currentY));

		

		SetPosition(m_currentX, m_currentY);
	}
}

int player::getmove(int move, int dist)
{
	if (std::abs(move) > std::abs(dist))
	{

		return dist;
	}
	return move;
}
