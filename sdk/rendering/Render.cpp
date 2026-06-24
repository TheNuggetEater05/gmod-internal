#include "Render.h"
#include "../../Global.h"

#include <imgui_impl_win32.h>
#include <imgui_impl_dx9.h>

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool Render::Init(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;
	G::pOutput->Log(LOG_SUCCESS, "Render: Device @ %p", m_pDevice);

	m_pDevice->GetCreationParameters(&m_Params);

	D3DXCreateFontA(m_pDevice, 14, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH || FF_DONTCARE, "Verdana", &m_Font);

	m_oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(m_Params.hFocusWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcess)));

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	
	ImGui_ImplWin32_Init(m_Params.hFocusWindow);
	ImGui_ImplDX9_Init(m_pDevice);

	m_Initialized = true;
	return true;
}

void Render::Destroy()
{
	m_Destroying = true;

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtrA(m_Params.hFocusWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_oWndProc));

	G::pOutput->Log("Render: Destroyed");
}

void Render::DrawMenu()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("gmod-internal menu");

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void Render::DrawString(Vec2 position, D3DCOLOR color, const std::string& text, bool outlined = true, bool centered = false)
{
	RECT rect = {};
	rect.left = (LONG)position.X;
	rect.top = (LONG)position.Y;
	rect.right = (LONG)(position.X + 500);
	rect.bottom = (LONG)(position.Y + 50);

	if (outlined)
	{
		D3DCOLOR outlineColor = D3DCOLOR_ARGB(255, 0, 0, 0);
		RECT outlineRect = rect;

		outlineRect.left--;
		outlineRect.top--;
		m_Font->DrawTextA(nullptr, text.c_str(), -1, &outlineRect, DT_LEFT | DT_WORDBREAK, outlineColor);

		outlineRect.left += 2;
		outlineRect.top++;
		m_Font->DrawTextA(nullptr, text.c_str(), -1, &outlineRect, DT_LEFT | DT_WORDBREAK, outlineColor);

		outlineRect.left--;
		outlineRect.top++;
		m_Font->DrawTextA(nullptr, text.c_str(), -1, &outlineRect, DT_LEFT | DT_WORDBREAK, outlineColor);

		outlineRect.left--;
		outlineRect.top--;
		m_Font->DrawTextA(nullptr, text.c_str(), -1, &outlineRect, DT_LEFT | DT_WORDBREAK, outlineColor);
	}

	m_Font->DrawTextA(nullptr, text.c_str(), -1, &rect, centered ? DT_CENTER : DT_LEFT | DT_WORDBREAK, color);
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		G::pRender->ToggleMenu();

	if (G::pRender->IsMenuOpen() && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}

	return CallWindowProcA(G::pRender->GetWndProc(), hWnd, msg, wParam, lParam);
}