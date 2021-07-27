#include "somapch.hpp"
#include "rendering/Texture.hpp"
#include "core/common.hpp"
#include "rendering/Renderer.hpp"
#include "platform/opengl/OpenGLTexture.hpp"
namespace SOMA_ENGINE {
	Texture2D* Texture2D::Create(const SOMA_String& path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None: return nullptr; break;
		case RenderAPI::API::OpenGL: return new OpenGLTexture2D(path); break;
		}
		return nullptr;
	}
}