#include "somapch.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/RenderCommand.hpp"
namespace SOMA_ENGINE {
	void Renderer::Begin(std::shared_ptr<SOMA_ENGINE::Camera>&)
	{
		//Do Camera Stuff

	}
	void Renderer::End()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}