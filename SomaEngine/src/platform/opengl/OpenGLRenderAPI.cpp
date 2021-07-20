#include "somapch.hpp"
#include "platform/opengl/OpenGLRenderAPI.hpp"
#include <glad/glad.h>
namespace SOMA_ENGINE {
	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g,color.b,color.a);

	}
	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<SOMA_ENGINE::VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}