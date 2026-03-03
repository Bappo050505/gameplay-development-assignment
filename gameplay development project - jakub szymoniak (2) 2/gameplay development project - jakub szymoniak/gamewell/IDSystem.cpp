#include "IDSystem.h"

BaseID::BaseID() : id (-1), filePath("")
{
}
bool BaseID::IsValid()
{
	return id != -1;
}