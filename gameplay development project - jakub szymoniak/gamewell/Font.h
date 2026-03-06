#pragma once
#include "FontBase.h"

class Font : public FontBase
{
public:
	Font(const char* filepath, int size);
	Font(int fontID);
};

