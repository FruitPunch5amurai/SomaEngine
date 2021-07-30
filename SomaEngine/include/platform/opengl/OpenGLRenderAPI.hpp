#pragma once
#include "rendering/RenderAPI.hpp"

namespace SOMA_ENGINE {
	class OpenGLRenderAPI :public RenderAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void SetViewPort(uint32 width, uint32 height) override;
		virtual void DrawIndexed(const Ref<SOMA_ENGINE::VertexArray>& vertexArray) override;
		virtual void Init() override;
	private:

	};
}