#include "somapch.hpp"
#include "imgui/ImGuiLayer.hpp"
#include "platform/opengl/OpenGLImGuiRenderer.h"

#include <core/game/IMainGame.hpp>
#include <core/Logger.hpp>
#include <input/KeyCode.hpp>
namespace SOMA_ENGINE {
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGui Layer")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags != ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags != ImGuiBackendFlags_HasSetMousePos;

		//Temporary
		io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
		io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
		io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
		io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
		io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
		io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
		io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = SDL_SCANCODE_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
		io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
		io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
		io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
		io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
		io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;

		// Load mouse cursors
		g_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		g_MouseCursors[ImGuiMouseCursor_TextInput] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
		g_MouseCursors[ImGuiMouseCursor_ResizeAll] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
		g_MouseCursors[ImGuiMouseCursor_ResizeNS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
		g_MouseCursors[ImGuiMouseCursor_ResizeEW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
		g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
		g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
		g_MouseCursors[ImGuiMouseCursor_Hand] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		g_MouseCursors[ImGuiMouseCursor_NotAllowed] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);

		ImGui::GetMainViewport()->PlatformHandle = IMainGame::Get().window->windowHandle;
		ImGui_ImplOpenGL3_Init("#version 410");
		io.DisplaySize = ImVec2(IMainGame::Get().window->getWidth(), IMainGame::Get().window->getHeight());

	}
	void ImGuiLayer::OnDetach()
	{
	}
	void ImGuiLayer::OnUpdate()
	{

		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplOpenGL3_NewFrame();

		static Uint64 frequency = SDL_GetPerformanceFrequency();
		Uint64 current_time = SDL_GetPerformanceCounter();	
		io.DeltaTime =  (float)(1.0f / 60.0f);
		m_time = current_time;


		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ImGuiLayer::OnEvent(Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		SOMA_ENGINE::EventDispatcher evtDispatcher(event);

		evtDispatcher.Dispatch<SOMA_ENGINE::MouseButtonPressedEvent>(SOMA_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		evtDispatcher.Dispatch<SOMA_ENGINE::MouseButtonReleasedEvent>(SOMA_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		evtDispatcher.Dispatch<SOMA_ENGINE::MouseMovedEvent>(SOMA_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		evtDispatcher.Dispatch<SOMA_ENGINE::MouseScrolledEvent>(SOMA_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		evtDispatcher.Dispatch<SOMA_ENGINE::KeyPressedEvent>(SOMA_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		evtDispatcher.Dispatch<SOMA_ENGINE::KeyReleasedEvent>(SOMA_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		evtDispatcher.Dispatch<SOMA_ENGINE::KeyTypedEvent>(SOMA_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		evtDispatcher.Dispatch<SOMA_ENGINE::WindowResizeEvent>(SOMA_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

		
	}
	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		SOMA_INFO("MouseButtonPressedEvent! {0}", e.GetMouseButton());
		return false;
	}
	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}
	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}
	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetXOffset();
		return false;
	}
	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[SDLK_LCTRL] || io.KeysDown[SDLK_RCTRL];
		io.KeyShift = io.KeysDown[SDLK_LSHIFT] || io.KeysDown[SDLK_RSHIFT];
		io.KeyAlt = io.KeysDown[SDLK_LALT] || io.KeysDown[SDLK_RALT];
		
		return false;
	}
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharactersUTF8(e.text);
		return false;
	}
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle(IMainGame::Get().window->windowHandle))
		{
			viewport->PlatformRequestResize = true;
		}
		return false;
	}
}