#include "somapch.hpp"
#include "rendering/Shader.hpp"
#include "rendering/Renderer.hpp"
#include "platform/opengl/OpenGLShader.hpp"

namespace SOMA_ENGINE {
	Shader* Shader::Create(const SOMA_String& name)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None: return nullptr; break;
		case RenderAPI::API::OpenGL: return new OpenGLShader(name); break;
		}
		return nullptr;
	}
}