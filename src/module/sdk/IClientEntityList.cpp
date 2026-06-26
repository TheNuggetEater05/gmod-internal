#include "IClientEntityList.h"

#include <Memory.h>

#include "../types/Vector.h"

IClientEntity* IClientEntityList::GetClientEntity(int entnum)
{
	using fn = IClientEntity * (*)(void*, int);
	return Memory::GetVFunc<fn>(this, 3)(this, entnum);
}