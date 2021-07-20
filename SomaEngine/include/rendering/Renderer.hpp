#pragma once

#include "RenderAPI.hpp"
#include "camera/Camera.hpp"
#include <memory>
namespace SOMA_ENGINE {
	class Renderer {
	public:
		static void Begin(std::shared_ptr<SOMA_ENGINE::Camera>& camera);
		static void End();

		static void Submit(const std::shared_ptr<SOMA_ENGINE::VertexArray>& vertexArray);


		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}