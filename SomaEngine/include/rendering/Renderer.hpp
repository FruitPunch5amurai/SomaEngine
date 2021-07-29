#pragma once

#include "RenderAPI.hpp"
#include "camera/Camera.hpp"
#include "rendering/Shader.hpp"
#include "rendering/Model.hpp"
#include <memory>
namespace SOMA_ENGINE {
	class Renderer {
	public:
		static void Init();
		static void Begin(Ref<SOMA_ENGINE::Camera>& camera);
		static void End();

		static void Submit(const Ref<SOMA_ENGINE::VertexArray>& vertexArray,
			const Ref<SOMA_ENGINE::Shader>& shader);

		static void Submit(const Ref<SOMA_ENGINE::Model>& model);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}