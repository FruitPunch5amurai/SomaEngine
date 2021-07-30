#include "somapch.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/RenderCommand.hpp"
namespace SOMA_ENGINE {

	Scope<Renderer::SceneData> Renderer::s_sceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::OnWindowResize(uint32 width, uint32 height)
	{
		RenderCommand::SetViewport(width,height);
	}
	void Renderer::Begin(Ref<SOMA_ENGINE::Camera>& camera)
	{
		//Do Camera Stuff

	}
	void Renderer::End()
	{
	}
	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<SOMA_ENGINE::Shader>& shader)
	{
		shader->Bind();

		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::Submit(const Ref<Model>& model)
	{
		for each (Mesh mesh in model->meshes)
		{
			mesh.Bind();

			RenderCommand::DrawIndexed(mesh.GetVertexArray());
			
			mesh.Unbind();
		}
	}
}