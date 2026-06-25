#include "IBaseClientDLL.h"

#include <Memory.h>

ClientClass* IBaseClientDLL::GetAllClasses()
{
	using fn = ClientClass * (*)(void*);
	return Memory::GetVFunc<fn>(this, 8)(this);
}