#pragma once
#include "rendering/RenderAPI.hpp"

namespace SOMA_ENGINE {
	class OpenGLRenderAPI :public RenderAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<SOMA_ENGINE::VertexArray>& vertexArray) override;
	private:

	};
}