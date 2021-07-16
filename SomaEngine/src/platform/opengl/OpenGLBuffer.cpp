#include "somapch.hpp"
#include "platform/opengl/OpenGLBuffer.hpp"
#include <glad/glad.h>
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
}