#pragma once
#include <glm/glm.hpp>
#include "platform/opengl/VertexArray.hpp"
#include <memory>

namespace SOMA_ENGINE {
	class RenderAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewPort(uint32 width, uint32 height) = 0;
		virtual void DrawIndexed(const Ref<SOMA_ENGINE::VertexArray>& vertexArray) = 0;
		virtual void Init() = 0;

		inline static API GetAPI() { return s_api; }
	private:
		static API s_api;
	};
}