#pragma once
#include "RenderAPI.hpp"

namespace SOMA_ENGINE {
	class RenderCommand {
	public:
		inline static void SetClearColor(const glm::vec4& color) {
			s_renderAPI->SetClearColor(color);
		}
		inline static void Clear() {
			s_renderAPI->Clear();
		}
		inline static void DrawIndexed(const std::shared_ptr<SOMA_ENGINE::VertexArray>& vertexArray)
		{
			s_renderAPI->DrawIndexed(vertexArray);
		}
	private:
		static RenderAPI* s_renderAPI;
	};

}