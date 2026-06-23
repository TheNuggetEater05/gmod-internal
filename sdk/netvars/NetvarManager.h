#pragma once

#ifndef NETVARMANAGER_H
#define NETVARMANAGER_H

#include "../../Includes.h"

#include "../valve/IClientBaseDLL.h"

namespace NVManager
{
	void Dump(RecvTable* pTable, uintptr_t offset = 0);
	void DumpClass(const std::string& name);
}

#endif