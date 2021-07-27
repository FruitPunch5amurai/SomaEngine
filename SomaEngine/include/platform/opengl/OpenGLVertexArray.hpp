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


		virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer)override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_vertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_indexBuffer; }

	private:
		uint32 m_id;
		SOMA_Array< Ref<VertexBuffer>> m_vertexBuffers;
		Ref<IndexBuffer> m_indexBuffer;
	};
}