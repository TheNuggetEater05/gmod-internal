#include "IVEngineClient.h"

#include <Memory.h>
#include "../types/Vector.h"

void IVEngineClient::GetScreenSize(int& width, int& height)
{
	using fn = void(*)(void*, int&, int&);

	return Memory::GetVFunc<fn>(this, 5)(this, width, height);
}

bool IVEngineClient::GetPlayerName(int ent_num, player_info_t* pinfo)
{

}