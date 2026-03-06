#pragma once
#include "entity.h"
#include "Input.h"

//stats for player
struct PlayerConfig:EntityConfig
{
	float m_currentX, m_currentY;
	float m_healthRegen;
	int m_level;
	float m_mana, m_manaRegen;
	float m_speed;
	
};

class player : public entity
{
private:
	//members
	float m_mana, m_manaRegen;
	int m_mouseX, m_mouseY;
	int m_clickX;
	int m_clickY;
	float m_speed;
	float m_currentX;
	float m_currentY;

protected:
	
	Input* m_inputManager;

public:
	player(PlayerConfig pConfig);
	virtual void Update() override;
	void Init() override;
	float GetXPos();
	float GetYPos();
	std::vector<Object*> BasicAttack() override;
	int getmove(int move, int dist);
	void Move() override;
};

