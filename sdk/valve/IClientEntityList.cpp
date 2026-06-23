#include "IClientEntityList.h"

#include "../../utility/Memory.h"

void* IClientEntityList::GetClientEntity(int entnum)
{
	using fn = void* (*)(void*, int);
	return Memory::GetVFunc<fn>(this, 3)(this, entnum);
}
