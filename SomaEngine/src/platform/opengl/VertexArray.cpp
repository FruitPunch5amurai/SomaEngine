#include "somapch.hpp"
#include "platform/opengl/OpenGLVertexArray.hpp"
#include "rendering/Renderer.hpp"
namespace SOMA_ENGINE {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None: return nullptr; break;
			case RenderAPI::API::OpenGL: return new OpenGLVertexArray(); break;
		}
		return nullptr;
	}
}