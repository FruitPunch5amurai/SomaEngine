#include "somapch.hpp"
#include "platform/opengl/OpenGLBuffer.hpp"
#include <glad/glad.h>
#include <core/memory.hpp>
namespace SOMA_ENGINE {
	/* Vertex Buffer*/
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32 size)
	{
		glCreateBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	/* Index Buffer*/
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);

		m_count = count;
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
	}
	void OpenGLIndexBuffer::Bind() const
	{
	}
	void OpenGLIndexBuffer::Unbind() const
	{
	}
	OpenGLUniformBuffer::OpenGLUniformBuffer(const void* data,
		uintptr dataSize)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferData(GL_UNIFORM_BUFFER, dataSize, data, GL_STATIC_DRAW); // TODO: make Usage Configurable
	}
	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		if (m_id == 0) {
			return;
		}
		glDeleteBuffers(1, &m_id);
	}
	void OpenGLUniformBuffer::Bind() const
	{
	}
	void OpenGLUniformBuffer::Unbind() const
	{
	}
	void OpenGLUniformBuffer::Update(const void* data, uintptr dataSize) const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		void* dest = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		Memory::memcpy(dest, data, dataSize);
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}
}