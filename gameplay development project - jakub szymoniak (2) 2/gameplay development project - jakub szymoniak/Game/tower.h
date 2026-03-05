#pragma once
#include "entity.h"
//ran our of time to implement
struct TowerConfig : EntityConfig
{

};

class tower : public entity
{
public:
	tower(TowerConfig tConfig);
};

