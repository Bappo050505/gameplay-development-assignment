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

	ProjectileUpdate();

	healthObj->Update();

	if (m_currentHealth <= 0) 
	{
		ReSpawn(m_spawnX, m_spawnY);
	}

	//default entity update
	entity::Update();
}

void player::Init()
{
	
}



//allows the player to shoot out a projectile
void player::BasicAttack(float mouseX , float mouseY)
{
	//sets projectile limit to 4
	if (m_projectiles.size() < 4)
	{
		int pPosX = m_currentX;
		int pPosY = m_currentY;

		//creates projectile

		Projectile* projectile = new Projectile("Player", "assets/baguette.bmp", pPosX, pPosY);
		projectile->SetTargetLocation(mouseX, mouseY);
		m_projectiles.push_back(projectile);
		
		std::cout << "attacked" << std::endl;
		
	}
	else
	{
		//output if max attacks reached
		std::cout << "Max Attacks" << std::endl;
	}
	


}
void player::Move()
{
	//setting local variables
	bool ismoving = true;
	float  mouseX, mouseY;

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
	
	//normalisation and direction setting
	
	FindTargetDirection(FindTargetDistance(m_currentX, m_currentY, m_clickX, m_clickY) , m_clickX , m_clickY);

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



