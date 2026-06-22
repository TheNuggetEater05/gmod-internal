#pragma once

#ifndef ICLIENTENTITYLIST_H
#define ICLIENTENTITYLIST_H

#include "../../util/Memory.h"

class IClientEntity {};

class IClientEntityList
{
public:
	IClientEntity* GetClientEntity(int entnum)
	{
		typedef IClientEntity* (*fn)(void*, int);
		return Memory::GetVFunc<fn>(this, 3)(this, entnum);
	}

	int NumberOfEntities(bool bIncludeNonNetworkable)
	{
		typedef int (*fn)(void*, int);
		return Memory::GetVFunc<fn>(this, 5)(this, bIncludeNonNetworkable);
	}
};

#endif