#pragma once

#include "rendering/RenderDevice.hpp"
#include "rendering/UniformBuffer.hpp"
#include "rendering/Texture.hpp"
#include "rendering/Sampler.hpp"

class Shader
{
public:
	inline Shader(RenderDevice& deviceIn, const SOMA_String& text) :
		device(&deviceIn),
		deviceId(device->createShaderProgram(text)) {}
	inline ~Shader()
	{
		deviceId = device->releaseShaderProgram(deviceId);
	}

	inline void setUniformBuffer(const SOMA_String& name, UniformBuffer& buffer);
	inline void setSampler(const SOMA_String& name, Texture& texture, Sampler& sampler,
		uint32 unit);
	inline void setSampler(const SOMA_String& name, uint32 texture, Sampler& sampler,
		uint32 unit);
	inline uint32 getId();
private:
	RenderDevice* device;
	uint32 deviceId;

	NULL_COPY_AND_ASSIGN(Shader);
};

inline uint32 Shader::getId()
{
	return deviceId;
}

inline void Shader::setUniformBuffer(const SOMA_String& name, UniformBuffer& buffer)
{
	device->setShaderUniformBuffer(deviceId, name, buffer.getId());
}

inline void Shader::setSampler(const SOMA_String& name, Texture& texture, Sampler& sampler,
	uint32 unit)
{
	device->setShaderSampler(deviceId, name, texture.getId(), sampler.getId(), unit);
}
inline void Shader::setSampler(const SOMA_String& name, uint32 texture, Sampler& sampler,
	uint32 unit)
{
	device->setShaderSampler(deviceId, name, texture, sampler.getId(), unit);
}