#pragma once

#ifndef RENDER_H
#define RENDER_H

#include "../../utility/Singleton.h"

#include "../../Includes.h"

class Render : public Singleton<Render>
{
	friend class Singleton<Render>;
public:
	bool Init(IDirect3DDevice9* pDevice);
	void Destroy();

	void DrawMenu();

	void DrawString(Vec2 position, D3DCOLOR color, const std::string& text, bool outlined, bool centered);

	WNDPROC GetWndProc()
	{
		return m_oWndProc;
	}

	void ToggleMenu()
	{
		m_MenuOpen = !m_MenuOpen;
	}

	bool IsInit()
	{
		return m_Initialized;
	}

	bool IsMenuOpen()
	{
		return m_MenuOpen;
	}

	bool IsDestroying()
	{
		return m_Destroying;
	}

private:
	bool m_Initialized = false;
	bool m_Destroying = false;

	bool m_MenuOpen = true;

	WNDPROC m_oWndProc;

	IDirect3DDevice9* m_pDevice;
	D3DDEVICE_CREATION_PARAMETERS m_Params = {};
	ID3DXFont* m_Font;
};

#endif