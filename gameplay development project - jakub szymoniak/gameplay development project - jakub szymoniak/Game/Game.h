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
	GameScreen* gameS;
	
	Input* m_InputManager;
	
	
	float m_deltatime = 1.0f;
	bool isdead = false;
	double score = 0;

	

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


	//void passtime();
	//void UpdatingObjectUpdate();
	//void reset();
	//void gameover();
	void stop();
};

