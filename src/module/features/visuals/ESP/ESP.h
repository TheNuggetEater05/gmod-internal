#pragma once

#ifndef ESP_H
#define ESP_H

#include <Singleton.h>

class IVDebugOverlay;
class IVEngineClient;
class IClientEntityList;

class ESP : public Singleton<ESP>
{
	friend class Singleton<ESP>;
public:
	void Init();
	void Render();

private:
	IVEngineClient* m_EngineClient = nullptr;
	IClientEntityList* m_EntityList = nullptr;
	IVDebugOverlay* m_DebugOverlay = nullptr;
};

#endif // !ESP_H
