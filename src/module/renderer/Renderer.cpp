#include "Renderer.h"

#include "../hookmanager/hooks/D3D/D3D.h" // for pDevice and pParams
#include "../logger/Logger.h"
#include "../types/Vector.h"
#include "../types/Color.h"
#include "../features/visuals/Visuals.h"

#include "../Settings.h"

#include <Includes.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool Renderer::Init()
{
	// hook game's WndProc
	m_oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(D3D::creationParams.hFocusWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcess)));

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(D3D::creationParams.hFocusWindow);
	ImGui_ImplDX9_Init(D3D::pDevice);

	m_DrawList = ImGui::GetBackgroundDrawList();

	Logger::Get().Log(LOG_SUCCESS, "Renderer: Initialized");
	m_Initialized = true;
	return true;
}

void Renderer::Shutdown()
{
	m_Destroying = true;

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// unhook game's WndProc
	SetWindowLongPtrA(D3D::creationParams.hFocusWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_oWndProc));

	Logger::Get().Log(LOG_SUCCESS, "Renderer: Shutdown");
}

void Renderer::StartRender()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (m_MenuShown)
	{
		Renderer::Menu();
	}

	Visuals::Get().Render();
}

void Renderer::EndRender()
{
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::Menu()
{
	if (ImGui::Begin("gmod-internal menu"))
	{
		if (ImGui::BeginTabBar("main_tabbar"))
		{
			if (ImGui::BeginTabItem("Visuals"))
			{
				ImGui::Checkbox("Watermark", &g_Settings.Visuals.Watermark.enabled);
				ImGui::SameLine();
				ImGui::ColorEdit4("Color", &g_Settings.Visuals.Watermark.color.r);
				
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Combat"))
			{

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Exploits"))
			{

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Lua"))
			{

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Settings"))
			{

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
	
}

void Renderer::DrawText(const std::string& text, const Vec2& position, const Color& color)
{
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x, position.y), ImColor(color.r, color.g, color.b, color.a), text.c_str());
}


LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		Renderer::Get().ToggleMenu();

	if (Renderer::Get().IsMenuShown() && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return CallWindowProcA(Renderer::Get().GetOWndProc(), hWnd, msg, wParam, lParam);
}