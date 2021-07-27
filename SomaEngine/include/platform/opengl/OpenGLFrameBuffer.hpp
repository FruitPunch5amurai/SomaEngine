#pragma once
#include "rendering/FrameBuffer.hpp"
namespace SOMA_ENGINE {
	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void Resize();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32 GetColorAttachmentID() const override { return m_colorAttachment; };
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_spec; };

	private:
		uint32 m_id;
		uint32 m_colorAttachment;
		uint32 m_depthAttachment;
		FrameBufferSpecification m_spec;

	};
}