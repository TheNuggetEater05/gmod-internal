#include "ESP.h"
#include "../../../logger/Logger.h"
#include "../../../renderer/Renderer.h"

#include "../../../types/Vector.h"
#include "../../../types/Color.h"
#include "../../../types/Matrix.h"

#include "../../../Settings.h"

#include "../../../sdk/IVEngineClient.h"
#include "../../../sdk/IClientEntityList.h"
#include "../../../sdk/IVDebugOverlay.h"

#include "../../../interfacemanager/InterfaceManager.h"

#include <Memory.h>

void ESP::Init()
{
	m_EntityList = InterfaceManager::Get().GetI<IClientEntityList>("client.dll", "VClientEntityList0");
	m_EngineClient = InterfaceManager::Get().GetI<IVEngineClient>("engine.dll", "VEngineClient0");
	m_DebugOverlay = InterfaceManager::Get().GetI<IVDebugOverlay>("engine.dll", "VDebugOverlay0");
}

void ESP::Render()
{
	if (m_EngineClient->IsInGame())
	{
		for (int i = 1; i < 64; i++)
		{
			IClientEntity* entity = m_EntityList->GetClientEntity(i);
			if (!entity)
				continue;

			std::string name = m_EngineClient->GetPlayerName(i);
			if (name == "")
				continue;

			Vec2 foot{};
			Vec2 head{};
			Vec3 origin = entity->Origin();

			foot = m_DebugOverlay->WorldToScreen(origin);
			head = m_DebugOverlay->WorldToScreen(Vec3(origin.x, origin.y, origin.z + 72));

			if (foot.x > 0 && foot.y > 0)
				Renderer::Get().DrawRect(Vec2(head.x - 25, head.y - 10), Vec2(foot.x + 25, foot.y + 10), g_Settings.Visuals.ESP.color, 1.0f, true);
		}
	}
}
