#include "somapch.hpp"
#include "rendering/Renderer.hpp"

#ifdef SOMA_RENDER_OPENGL
#include "platform/opengl/OpenGLBuffer.hpp"
#include "..\..\include\rendering\FrameBuffer.hpp"
#include "platform/opengl/OpenGLFrameBuffer.hpp"
#endif

namespace SOMA_ENGINE {
	FrameBuffer* FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None: return nullptr; break;
		case RenderAPI::API::OpenGL: return new OpenGLFrameBuffer(spec); break;
		}
		return nullptr;
	}
}