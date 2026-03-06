#pragma once
#include "entity.h"

struct TowerConfig : EntityConfig
{

};

class tower : public entity
{
public:
	tower(TowerConfig tConfig);
};

