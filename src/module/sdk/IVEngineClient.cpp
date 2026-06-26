#include "IVEngineClient.h"

#include <Memory.h>
#include "../types/Vector.h"

void IVEngineClient::GetScreenSize(int& width, int& height)
{
	using fn = void(*)(void*, int&, int&);

	return Memory::GetVFunc<fn>(this, 5)(this, width, height);
}

std::string IVEngineClient::GetPlayerName(int ent_num)
{
	using fn = bool(*)(void*, int, player_info_t*);

	player_info_t pinfo;

	if (!Memory::GetVFunc<fn>(this, 8)(this, ent_num, &pinfo))
		return "";

	return std::string(pinfo.name);
}

bool IVEngineClient::IsInGame()
{
	using fn = bool(*)(void*);
	return Memory::GetVFunc<fn>(this, 26)(this);
}

bool IVEngineClient::IsConnected()
{
	using fn = bool(*)(void*);
	return Memory::GetVFunc<fn>(this, 27)(this);
}