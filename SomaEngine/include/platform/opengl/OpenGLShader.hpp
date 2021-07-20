#pragma once
#include "rendering/Shader.hpp"
namespace SOMA_ENGINE {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const SOMA_String& name);
		virtual ~OpenGLShader();
		virtual void Bind()const override;
		virtual void Unbind() const override;
		virtual void UploadUniformBuffer(const SOMA_String& uniformBufferName,
			SOMA_ENGINE::UniformBuffer* buffer)const override;

		virtual void UploadMat4(const SOMA_String& uniformName, const glm::mat4& value) const override;
	private:
		SOMA_String GetShaderVersion();
		uint32 GetVersion();

		Map<uint32, ShaderProgram> m_shaderProgramMap;
		uint32 m_version = 0;
		SOMA_String m_shaderVersion;
		uint32 m_id;
	};
}