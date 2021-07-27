#include "somapch.hpp"
#include "rendering/Shader.hpp"
#include "rendering/Renderer.hpp"
#include "platform/opengl/OpenGLShader.hpp"

namespace SOMA_ENGINE {
	Ref<Shader> Shader::Create(const SOMA_String& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None: return nullptr; break;
		case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath); break;
		}
		return nullptr;
	}
	Ref<Shader> Shader::Create(const SOMA_String& name, const SOMA_String& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None: return nullptr; break;
		case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name,filepath); break;
		}
		return nullptr;
	}
	void ShaderLibrary::AddShader(const Ref<Shader>& s)
	{
		auto& name = s->GetName();
		AddShader(name, s);
	}
	void ShaderLibrary::AddShader(const SOMA_String& name, const Ref<Shader>& s)
	{
		SOMA_ASSERT(m_shaders.find(name) == m_shaders.end(), "Shader already added!");
		m_shaders[name] = s;
	}
	Ref<Shader> ShaderLibrary::Load(const SOMA_String& filepath)
	{
		auto shader = Shader::Create(filepath);
		AddShader(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const SOMA_String& name, const SOMA_String& filepath)
	{
		auto shader = Shader::Create(name,filepath);
		AddShader(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const SOMA_String& name)
	{
		SOMA_ASSERT(m_shaders.find(name) != m_shaders.end(), "Shader not found!");
		return m_shaders[name];
	}
}