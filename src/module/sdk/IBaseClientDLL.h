#pragma once

#ifndef IBASECLIENTDLL_H
#define IBASECLIENTDLL_H

class RecvTable;

class RecvProp
{
public:
	const char* m_pVarName;
	void* m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};

class RecvTable
{
public:
	RecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	const char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

class ClientClass
{
private:
	typedef void* (*CreateClientClassFn)(int entnum, int serialNum);
	typedef void* (*CreateEventFn)();
public:
	CreateClientClassFn m_pCreateFn;
	CreateEventFn m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses();
};

#endif // !IBASECLIENTDLL_H
