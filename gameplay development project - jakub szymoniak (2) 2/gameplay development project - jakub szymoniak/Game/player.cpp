#include "player.h"
#include "Projectile.h"
#include "TextObject.h"
#include <iostream>

player::player(PlayerConfig pConfig) : entity(pConfig), m_mana(pConfig.m_mana), m_manaRegen(pConfig.m_manaRegen), m_speed(pConfig.m_speed)
, m_clickX(pConfig.m_spawnX), m_clickY(pConfig.m_spawnY)
{
	

}
//overiden update to let player update its self
void player::Update()
{
	//updates the projectile / deletes it if it has collided or traveled past its max range
	for (int i = m_projectiles.size() -1; i >= 0;i--)
	{
		if (m_projectiles[i]->GetShouldCollide())
		{
			m_projectiles[i]->Update();
		}
		else if (!m_projectiles[i]->GetShouldCollide())
		{
			m_projectiles.erase(m_projectiles.begin() + i);
		}
		else 
		{
			m_projectiles.erase(m_projectiles.begin() + i);
		}
			
	}

	healthObj->Update();

	//default entity update
	entity::Update();
}

void player::Init()
{
	
}
//returns damage amount
float player::GetDamage()
{
	return m_damage;
}


//returns current health
float player::GetCurrentHealth()
{
	return m_currentHealth;
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
	//setting local variables
	bool ismoving = true;
	int  mouseX, mouseY;

	//gets current position
	GetPosition(m_currentX, m_currentY);

	//gets mouse position
	m_inputManager->GetMousePos(mouseX, mouseY);

	//checks mouse input and assignes the click location to the mouse location
	if (m_inputManager->GetMouseHeld(RIGHTMOUSEBUTTON))
	{

		m_clickX = mouseX;
		m_clickY = mouseY;

	}
	//calculating the distance between player and mouse click
	int xdif = (m_clickX - m_currentX);
	int ydif = (m_clickY - m_currentY);

	//normalisation and direction setting
	float vctLength = sqrt((xdif * xdif) + (ydif * ydif));

	float direction[2]{ (xdif / vctLength) , (ydif / vctLength) };

	//how much to move by in each direction
	int moveAmount[2] { direction[0] * m_speed , direction[1] * m_speed };


	//checks if the player has reached the click location and sets moving flag to false
	if (m_currentX == m_clickX && m_currentY == m_clickY)
	{
		ismoving = false;
	}
	//move the player to its destination as long as moving flag is true
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
