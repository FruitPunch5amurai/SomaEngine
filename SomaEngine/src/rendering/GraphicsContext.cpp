#include "somapch.hpp"
#include "rendering/GraphicsContext.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/RenderAPI.hpp"

#include "platform/opengl/OpenGLContext.hpp"

namespace SOMA_ENGINE {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:    return nullptr;
		case RenderAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		return nullptr;
	}

}