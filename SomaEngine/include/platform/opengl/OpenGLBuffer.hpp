#pragma once

#include "rendering/Buffer.hpp"
#include "rendering/RenderDevice.hpp"

namespace SOMA_ENGINE {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32 size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind()const;
		virtual void Unbind()const;

		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_layout; }


		RenderDevice* device;
	private:
		BufferLayout m_layout;
		uint32 m_id;
	};
	class OpenGLIndexBuffer: public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32* indices, uint32 count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind()const;
		virtual void Unbind()const;

		virtual uint32 GetCount() const { return m_count; }
		RenderDevice* device;
	private:
		uint32 m_id;
		uint32 m_count;
	};
}