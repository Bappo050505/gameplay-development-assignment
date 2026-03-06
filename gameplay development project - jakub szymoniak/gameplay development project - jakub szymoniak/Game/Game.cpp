#include "Game.h"
#include "enemy.h"
#include "player.h"
#include "tower.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



Game::Game()
{
	int r = 0, g = 0, b = 0;

	//makes a new game screen and outputs a error if fails.
	gameS = new GameScreen;
	if (!gameS->CreateScreen("Def Not Aram"))
	{
		std::cout << "Fail";
	}
	gameS->Update();
	
}

void Game::initialize()
{
	m_InputManager = new Input;
	ReadFile();

	
	
}

#pragma region FileWork

void Game::ReadFile()
{
	std::ifstream file;
	file.open("config/entity config.txt");
	if (!file.is_open())
	{
		std::cout << "error opening file";
	}
	std::string line;
	//parse, read and assign file values to member variables
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string type;

		iss >> type;
		//player
		if (type == "player")
		{
			SpawnPlayer(iss);
		}
		//enemy
		if (type == "enemy")
		{
			SpawnEnemy(iss);
		}
		//tower
		if (type == "tower")
		{
			SpawnTower(iss);
		}	
	}
	file.close();

	SpawnWalls();
}
void Game::SpawnPlayer(std::istringstream& iss)
{
	PlayerConfig pConfig;

	iss >> pConfig.m_filepath >> pConfig.m_level >> pConfig.m_spawnX >> pConfig.m_spawnY >> pConfig.m_health >> pConfig.m_healthRegen >> pConfig.m_damage >> pConfig.m_mana
		>> pConfig.m_manaRegen >> pConfig.m_speed >> pConfig.m_range >> pConfig.m_cooldown;

	pConfig.m_imageFile = pConfig.m_filepath.c_str();

	m_playerIDX = m_entities.size();
	m_entities.push_back(new player(pConfig));
}
void Game::SpawnEnemy(std::istringstream& iss)
{
	EnemyConfig eConfig;

	iss >> eConfig.m_filepath >> eConfig.m_level >> eConfig.m_spawnX >> eConfig.m_spawnY >> eConfig.m_health >> eConfig.m_healthRegen >> eConfig.m_damage >>
		eConfig.m_speed >> eConfig.m_range >> eConfig.m_cooldown;

	eConfig.m_imageFile = eConfig.m_filepath.c_str();

	m_entities.push_back(new enemy(eConfig));
}
void Game::SpawnTower(std::istringstream& iss)
{
	TowerConfig tConfig;

	iss >> tConfig.m_filepath >> tConfig.m_spawnX >> tConfig.m_spawnY >> tConfig.m_health >> tConfig.m_damage >> tConfig.m_range >> tConfig.m_cooldown;

	tConfig.m_imageFile = tConfig.m_filepath.c_str();

	m_entities.push_back(new tower(tConfig));
}
void Game::SpawnWalls()
{
	m_walls.push_back(new Object("assets/wall.bmp", 0, 0, 1280, 50, true));
	m_walls.push_back(new Object("assets/wall.bmp", 0, 680, 1280, 50, true));
}

#pragma endregion

bool Game::IsRunning()
{
	return true;
}
void Game::Update() 
{
	
	if (m_InputManager->GetMouseDown(LEFTMOUSEBUTTON))
	{
		m_entities[m_playerIDX]->BasicAttack();
	}

	CheckCollisions();
	m_entities[m_playerIDX]->Move();

	Render();
}


void Game::Render()
{
	for (entity* e : m_entities)
	{
		e->Update();
	}
	for (Object* w : m_walls) 
	{
		w->Update();
	}
	
	gameS->Update();

}

void Game::CheckCollisions()
{
	//collisions with enemies
	for (entity* e : m_entities)
	{
		if (m_entities[m_playerIDX]->IsOverlapping(*e) && e != m_entities[m_playerIDX])
		{
			m_entities[m_playerIDX]->SetPosition(m_entities[m_playerIDX]->GetOldX(), m_entities[m_playerIDX]->GetOldY());
		}
	}
	//collisions with walls
	for (Object* w : m_walls) 
	{
		if (m_entities[m_playerIDX]->IsOverlapping(*w)) 
		{
			m_entities[m_playerIDX]->SetPosition(m_entities[m_playerIDX]->GetOldX(), m_entities[m_playerIDX]->GetOldY());
		}

	}
	for (Object* p : m_entities[m_playerIDX]->getProjectiles()) 
	{
		for (entity* e : m_entities)
		{
			if (p->IsOverlapping(*e) && e != m_entities[m_playerIDX])
			{
				std::cout << "collided" << std::endl;
				p->SetShouldCollide(false);
				p->SetShouldDraw(false);
				
				

			}
		
		}

		if (p->GetShouldDraw() == false)
		{
			delete p;
		}

	
	}
}
	

GameScreen* Game::GetScreen()
{
	return gameS;
}

void Game::stop()
{
	//m_InputManager->GetKeyDown('Q')

}

