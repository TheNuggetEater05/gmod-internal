#pragma once

#ifndef ICLIENTENTITYLIST_H
#define ICLIENTENTITYLIST_H

#include "../netvarmanager/NetvarManager.h"
#include "../types/Vector.h"

struct Vec3;

class IClientEntity
{
public:
	NETVAR(Health, "CBaseEntity->m_iHealth", int);
	NETVAR(MaxHealth, "CBaseEntity->m_iMaxHealth", int);
	NETVAR(LifeState, "CBaseEntity->m_lifeState", int);
	NETVAR(Origin, "CBaseEntity->m_vecOrigin", Vec3);
	NETVAR(nForceBone, "CBaseAnimating->m_nForceBone", void*)
};

class IClientEntityList
{
public:
	IClientEntity* GetClientEntity(int entnum);
};

#endif // !ICLIENTENTITYLIST_H
