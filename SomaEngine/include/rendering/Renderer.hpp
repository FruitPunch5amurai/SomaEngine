#pragma once

#include "RenderAPI.hpp"
#include "camera/Camera.hpp"
#include "rendering/Shader.hpp"
#include "rendering/Model.hpp"
#include <memory>
#include "rendering/FrameBuffer.hpp"
namespace SOMA_ENGINE {
	class Renderer {
	public:
		static void Init();
		static void OnWindowResize(uint32 width, uint32 height);
		static void Begin(Ref<SOMA_ENGINE::Camera>& camera);
		static void End();

		static void Submit(const Ref<SOMA_ENGINE::VertexArray>& vertexArray,
			const Ref<SOMA_ENGINE::Shader>& shader);

		static void Submit(const Ref<SOMA_ENGINE::Model>& model);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;

			Ref<FrameBuffer> frameBuffer;
		};
		static Scope<SceneData> s_sceneData;
	};
}