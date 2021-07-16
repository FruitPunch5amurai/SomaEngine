#include "somapch.hpp"
#include "rendering/Buffer.hpp"

#include "rendering/Renderer.hpp"
#ifdef SOMA_RENDER_OPENGL
	#include "platform/opengl/OpenGLBuffer.hpp"
#endif
namespace SOMA_ENGINE {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32 size) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: return nullptr; break;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size); break;
		}
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32* indices, uint32 count) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: return nullptr; break;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count); break;
		}
		return nullptr;
	}
}