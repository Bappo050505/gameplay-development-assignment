#pragma once
#include "Gamewell_api.h"
#include "entity.h"
#include <vector>

class Object;
class Game
{
private:

	std::vector<entity*> m_entities;
	std::vector<Object*> m_walls;
	
	int m_playerIDX;
	int m_mainEnemyIDX;
	GameScreen* gameS;

	
	
	Input* m_InputManager;
	
	
	float m_deltatime = 1.0f;
	bool isdead = false;
	double score = 0;
	
	float p_x, p_y;
	float e_x, e_y;

	float clickX, clickY;

	TextObject* m_scoreCounter;
	TextObject* m_MovePrompt;
	TextObject* m_ExitPrompt;

protected:
	
public:
	
	Game();
	void initialize();
	bool IsRunning();
	void Update();
	void SpawnPlayer(std::istringstream& iss);
	void SpawnEnemy(std::istringstream& iss);
	void SpawnTower(std::istringstream& iss);
	void SpawnWalls();
	void ReadFile();
	void Render();
	void CheckCollisions();
	GameScreen* GetScreen();
	void UpdatingObjectUpdate();
	void CheckProjectileCollision(entity* ProjectileOwner);

	//void DeleteOnExit();

	int getScore();


	//void passtime();
	//void reset();
	//void gameover();
	void stop();
};

