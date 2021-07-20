#pragma once
#include "platform/opengl/VertexArray.hpp"
#include "rendering/Buffer.hpp"

namespace SOMA_ENGINE {
	class OpenGLVertexArray : public VertexArray{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void Unbind() const override;


		virtual void AddVertexBuffer(const std::shared_ptr <VertexBuffer>& buffer)override;
		virtual void SetIndexBuffer(const std::shared_ptr <IndexBuffer>& buffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_vertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_indexBuffer; }

	private:
		uint32 m_id;
		SOMA_Array< std::shared_ptr <VertexBuffer>> m_vertexBuffers;
		std::shared_ptr <IndexBuffer> m_indexBuffer;
	};
}