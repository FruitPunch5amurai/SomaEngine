#include "somapch.hpp"
#include "rendering/RenderCommand.hpp"
#include "platform/opengl/OpenGLRenderAPI.hpp"

namespace SOMA_ENGINE {
	RenderAPI* RenderCommand::s_renderAPI = new SOMA_ENGINE::OpenGLRenderAPI;
}