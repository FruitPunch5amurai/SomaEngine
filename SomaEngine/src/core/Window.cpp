#include "somapch.hpp"
#include "core/Window.hpp"

#ifdef SOMA_PLATFORM_GLFW
#include "platform/glfw/GLFWWindow.hpp"
#endif

namespace SOMA_ENGINE {
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef SOMA_PLATFORM_GLFW
		return CreateScope<GLFWWindow>(props);
#else
		return nullptr;
#endif
	}
}