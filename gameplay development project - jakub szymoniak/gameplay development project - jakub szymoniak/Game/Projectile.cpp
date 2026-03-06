#include "Projectile.h"


Projectile::Projectile(std::string tag, const char* fileName, int spawnX, int spawnY) : Object(fileName, spawnX, spawnY, 50, 20, true)
{
}



void Projectile::Update()
{
	Move();
	Object::Update();
}

void Projectile::Move()
{
	float x, y;
	GetPosition(x, y);
	x++;
	SetPosition(x, y);
}






