#pragma once
#include "Object.h"
#include "Input.h"
#include <string>

//creating projectile class for better managment of projectiles for entities
class Projectile : public Object
{
private:
	std::string tag;

protected:


public:
	Projectile(std::string tag , const char* fileName, int spawnX, int spawnY);
	//~Projectile();
	virtual void Update()override;
	void Move();
};

//either create a tag or add pointer to projectile owner (for collision so owners projectiles dont damage them)

//IN THE ENTITY CLASS create a checkcollisions function to compare the collisions of different entities
//this will let me check all entity collisions against eachother (for projectiles) without specifying specific entities by ID

