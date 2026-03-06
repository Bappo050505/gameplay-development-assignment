#include "Game.h"
#include "enemy.h"
#include "player.h"
#include "tower.h"
#include "Projectile.h"
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

	iss >>  pConfig.m_filepath >> pConfig.m_level >> pConfig.m_spawnX >> pConfig.m_spawnY >> pConfig.m_maxHealth >> pConfig.m_healthRegen >> pConfig.m_damage >> pConfig.m_mana
		>> pConfig.m_manaRegen >> pConfig.m_speed >> pConfig.m_range >> pConfig.m_cooldown;

	pConfig.m_imageFile = pConfig.m_filepath.c_str();

	m_playerIDX = m_entities.size();
	m_entities.push_back(new player(pConfig));
}
void Game::SpawnEnemy(std::istringstream& iss)
{
	EnemyConfig eConfig;

	iss >> eConfig.m_filepath >> eConfig.m_level >> eConfig.m_spawnX >> eConfig.m_spawnY >> eConfig.m_maxHealth >> eConfig.m_healthRegen >> eConfig.m_damage >>
		eConfig.m_speed >> eConfig.m_range >> eConfig.m_cooldown;

	eConfig.m_imageFile = eConfig.m_filepath.c_str();
	
	//NOTE : Player always need to exist first for this to work
	m_mainEnemyIDX = m_entities.size();
	enemy* Enemy = new enemy(eConfig);
	Enemy->SetTarget(m_entities[m_playerIDX]);
	m_entities.push_back(Enemy);
}
void Game::SpawnTower(std::istringstream& iss)
{
	TowerConfig tConfig;

	iss >>  tConfig.m_filepath >> tConfig.m_spawnX >> tConfig.m_spawnY >> tConfig.m_maxHealth >> tConfig.m_damage >> tConfig.m_range >> tConfig.m_cooldown;

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
	score++;
	
	if (m_InputManager->GetMouseDown(LEFTMOUSEBUTTON))
	{
		m_InputManager->GetMousePos(clickX, clickY);

		m_entities[m_playerIDX]->BasicAttack(clickX, clickY);
	}

	CheckCollisions();
	m_entities[m_playerIDX]->Move();

	UpdatingObjectUpdate();

	if (m_InputManager->GetKeyDown('#'))
	{
		stop();
	}
	else 
	{
		Render();
	}
	
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
	if (m_InputManager->GetKeyDown('Q')) 
	{
		stop();
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
		if (m_entities[m_mainEnemyIDX]->IsOverlapping(*e) && e != m_entities[m_mainEnemyIDX]) 
		{
			m_entities[m_mainEnemyIDX]->SetPosition(m_entities[m_mainEnemyIDX]->GetOldX(), m_entities[m_mainEnemyIDX]->GetOldY());
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
	//projectil collisions
	
	for (entity* e : m_entities) 
	{
		CheckProjectileCollision(e);
	}
	
}
	

GameScreen* Game::GetScreen()
{
	return gameS;
}
//updates objects that will have values changed, mainly for text objects.
void Game::UpdatingObjectUpdate()
{
	Colour white;
	white.r = 255;
	white.g = 255;
	white.b = 255;

	std::string ScoreToText = "Score:" + std::to_string(getScore());
	m_scoreCounter = new TextObject(ScoreToText.c_str(), "assets/default.ttf", 30, 10, 100, white, true);
	m_scoreCounter->Update();

	m_MovePrompt = new TextObject("Right mb to move, Left mb to shoot", "assets/default.ttf", 30, 10, 50, white, true);
	m_MovePrompt->Update();

	m_ExitPrompt = new TextObject("Press # to Exit", "assets/default.ttf", 30, 1000, 50, white, true);
	m_ExitPrompt->Update();
	//"magic" numbers to offset the health objectr so its not blocked by the entity
	m_entities[m_playerIDX]->GetPosition(p_x, p_y);
	m_entities[m_playerIDX]->GetHealthObj()->SetPosition(p_x, p_y  -20);

	m_entities[m_mainEnemyIDX]->GetPosition(e_x, e_y);
	m_entities[m_mainEnemyIDX]->GetHealthObj()->SetPosition(e_x , e_y -20);
}

//checks collisions between entity projetciles (owner of projectile against target)
void Game::CheckProjectileCollision(entity* ProjectileOwner)
{
	for (Object* p : ProjectileOwner->getProjectiles())
	{
		for (entity* e : m_entities)
		{
			if (p->IsOverlapping(*e) && e != ProjectileOwner)
			{
				std::cout << "collided" << std::endl;

				p->SetShouldCollide(false);
				p->SetShouldDraw(false);

				e->TakeDamage(ProjectileOwner->GetDamage());

			}
		}
	}
}

//void Game::DeleteOnExit()
//{
//	for (int i = m_projectiles.size() - 1; i >= 0; i--)
//	{
//		//updates the projectile at index i
//		if (m_projectiles[i]->GetShouldCollide())
//		{
//			m_projectiles[i]->Update();
//		}
//		//checks if it can collide and if not delete the projectile
//		else {
//			m_projectiles.erase(m_projectiles.begin() + i);
//		}
//
//	}
//}

int Game::getScore()
{
	//returns current score
	return score;

}



void Game::stop()
{
	gameS->CloseScreen();

}

