#pragma once
#include "rendering/Shader.hpp"
namespace SOMA_ENGINE {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const SOMA_String& filepath);
		OpenGLShader(const SOMA_String& name,const SOMA_String& filepath);
		virtual ~OpenGLShader();
		virtual void Bind()const override;
		virtual void Unbind() const override;
		virtual void BindUniformBuffer(const SOMA_String& uniformBufferName,
			SOMA_ENGINE::UniformBuffer* buffer) override;

		virtual void UploadUniformBuffer(const SOMA_String& uniformName, const void* data,
			uint32 dataSize, uint32 offset) const override;

		virtual void UploadInt(const SOMA_String& uniformName, const int& value) const override;
		virtual void UploadFloat4(const SOMA_String& uniformName, const glm::vec4& value) const override;
		virtual void UploadFloat3(const SOMA_String& uniformName, const glm::vec3& value) const override;
		virtual void UploadMat4(const SOMA_String& uniformName, const glm::mat4& value) const override;

		virtual const SOMA_String& GetName() const override { return m_name; }

	private:
		SOMA_String GetShaderVersion();
		uint32 GetVersion();

		Map<uint32, ShaderProgram> m_shaderProgramMap;
		uint32 m_version = 0;
		SOMA_String m_shaderVersion;
		uint32 m_id;
		SOMA_String m_name;
	};
}