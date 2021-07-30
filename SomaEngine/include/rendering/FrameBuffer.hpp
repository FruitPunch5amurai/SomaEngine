#pragma once

#include "core/common.hpp"
namespace SOMA_ENGINE {

	struct FrameBufferSpecification {
		uint32 width, height;
		uint32 samples = 1;

		bool swapChainTarget = false;
	};

	class FrameBuffer {
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32 GetColorAttachmentID() const = 0;

		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};
}
