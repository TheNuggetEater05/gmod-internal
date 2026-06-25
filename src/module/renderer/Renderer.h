#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include <Includes.h>
#include <Singleton.h>

#include <d3d9.h>

class Module;
struct ImDrawList;

struct Vec2;
struct Color;

class Renderer : public Singleton<Renderer>
{
	friend class Singleton<Renderer>;
public:
	bool Init();
	void Shutdown();

	void StartRender();

	void EndRender();

	bool IsInitialized() { return m_Initialized; }
	bool IsDestroying() { return m_Destroying; }
	bool IsMenuShown() { return m_MenuShown; }
	WNDPROC GetOWndProc() { return m_oWndProc; }

	void ToggleMenu() { m_MenuShown = !m_MenuShown; }

	void DrawText(const std::string& text, const Vec2& position, const Color& color);

private:
	void Menu();

private:
	Module* m_Global;

	bool m_Initialized = false;
	bool m_Destroying = false;
	bool m_MenuShown = true;

	ImDrawList* m_DrawList = nullptr;
	WNDPROC m_oWndProc = nullptr;
};

#endif // !RENDERER_H
