#include "somapch.hpp"
#include "platform/opengl/OpenGLContext.hpp"

#include <GLFW/glfw3.h>

#include <glad/glad.h>
#include <core/Logger.hpp>
namespace SOMA_ENGINE {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SOMA_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SOMA_ASSERT(status, "Failed to initialize Glad!");

		SOMA_CORE_INFO("OpenGL Info:");
		SOMA_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		SOMA_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		SOMA_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		SOMA_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}