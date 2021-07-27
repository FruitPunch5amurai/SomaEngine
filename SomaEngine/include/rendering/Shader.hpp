#pragma once

#include "rendering/RenderDevice.hpp"
#include "rendering/Buffer.hpp"
#include "rendering/Texture.hpp"
#include "rendering/Sampler.hpp"
#include "dataStructures/string.hpp"
#include <glm/glm.hpp>
namespace SOMA_ENGINE {
	struct ShaderProgram
	{
		SOMA_Array<uint32>      shaders;
		Map<SOMA_String, int32> uniformMap;
		Map<SOMA_String, int32> uniformBinding;
		Map<SOMA_String, int32> samplerMap;
	};

	class Shader {
	public:
		virtual ~Shader() {}
		virtual void Bind()const = 0;
		virtual void Unbind() const = 0;				
		virtual void UploadInt(const SOMA_String& uniformName, const int& value) const = 0;
		virtual void UploadUniformBuffer(const SOMA_String& uniformBufferName, SOMA_ENGINE::UniformBuffer* buffer)const = 0;
		virtual void UploadMat4(const SOMA_String& uniformName, const glm::mat4& value) const = 0;
		virtual void UploadFloat4(const SOMA_String& uniformName, const glm::vec4& value) const = 0;
		virtual void UploadFloat3(const SOMA_String& uniformName, const glm::vec3& value) const = 0;
		virtual const SOMA_String& GetName() const = 0;

		static Ref<Shader> Create(const SOMA_String& filepath);
		static Ref<Shader> Create(const SOMA_String& name, const SOMA_String& filepath);


	};

	class ShaderLibrary {
	public:
		void AddShader(const Ref<Shader>& s);
		void AddShader(const SOMA_String& name, const Ref<Shader>& s);
		Ref<Shader> Load(const SOMA_String& filepath);
		Ref<Shader> Load(const SOMA_String& name, const SOMA_String& filepath);
		Ref<Shader> Get(const SOMA_String& name);
	private:
		Map<SOMA_String, Ref<Shader>> m_shaders;
	};

}


//class Shader
//{
//public:
//	inline Shader(RenderDevice& deviceIn, const SOMA_String& text) :
//		device(&deviceIn),
//		deviceId(device->createShaderProgram(text)) {}
//	inline ~Shader()
//	{
//		deviceId = device->releaseShaderProgram(deviceId);
//	}
//
//	inline void setUniformBuffer(const SOMA_String& name, UniformBuffer& buffer);
//	inline void setSampler(const SOMA_String& name, Texture& texture, Sampler& sampler,
//		uint32 unit);
//	inline void setSampler(const SOMA_String& name, uint32 texture, Sampler& sampler,
//		uint32 unit);
//	inline uint32 getId();
//private:
//	RenderDevice* device;
//	uint32 deviceId;
//};
//
//inline uint32 Shader::getId()
//{
//	return deviceId;
//}
//
//inline void Shader::setUniformBuffer(const SOMA_String& name, UniformBuffer& buffer)
//{
//	device->setShaderUniformBuffer(deviceId, name, buffer.getId());
//}
//
//inline void Shader::setSampler(const SOMA_String& name, Texture& texture, Sampler& sampler,
//	uint32 unit)
//{
//	device->setShaderSampler(deviceId, name, texture.getId(), sampler.getId(), unit);
//}
//inline void Shader::setSampler(const SOMA_String& name, uint32 texture, Sampler& sampler,
//	uint32 unit)
//{
//	device->setShaderSampler(deviceId, name, texture, sampler.getId(), unit);
//}