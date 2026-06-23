#include "IClientBaseDLL.h"

#include "../../utility/Memory.h"

ClientClass* IClientBaseDLL::GetAllClasses()
{
	using fn = ClientClass * (*)(void*);
	return Memory::GetVFunc<fn>(this, 8)(this);
}
