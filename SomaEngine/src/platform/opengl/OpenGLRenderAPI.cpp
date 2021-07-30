#include "somapch.hpp"
#include "platform/opengl/OpenGLRenderAPI.hpp"
#include <glad/glad.h>
namespace SOMA_ENGINE {
	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	}
	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g,color.b,color.a);

	}
	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderAPI::SetViewPort(uint32 width, uint32 height)
	{
		glViewport(0, 0, width, height);
	}
	void OpenGLRenderAPI::DrawIndexed(const Ref<SOMA_ENGINE::VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}