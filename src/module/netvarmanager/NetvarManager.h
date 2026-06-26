#pragma once

#ifndef NETVARMANAGER_H
#define NETVARMANAGER_H

#include <Includes.h>
#include <Singleton.h>

#include <fnv.h>

class RecvTable;
class IBaseClientDLL;

class NetvarManager : public Singleton<NetvarManager>
{
	friend class Singleton<NetvarManager>;
public:
	void Init();

	std::unordered_map<std::uint32_t, std::uint32_t> netvars;

	void PrintNetvar(const std::string& name);
private:
	void Dump(const std::string& baseclass, RecvTable* table, std::uint32_t offset, std::ofstream* file = nullptr);

private:
	IBaseClientDLL* m_BaseClient = nullptr;
};

#define NETVAR(fnName, netvar, type) type& fnName() \
{ \
	static auto offset = NetvarManager::Get().netvars[fnv::HashConst(netvar)]; \
	return *reinterpret_cast<type*>(std::uintptr_t(this) + offset); \
}

#endif // !NETVARMANAGER_H
