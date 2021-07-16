#pragma once


#include "rendering/Model.hpp"
#include "rendering/Texture.hpp"
#include <rendering/Shader.hpp>
class  TextureCache
{
public:
	Texture* loadTexture(SOMA_String filepath, RenderDevice& deviceIn, enum OpenGLRenderDevice::PixelFormat format);
	bool cleanUp();
	void cleanUpTexture(SOMA_String filepath);
private:
	Map<SOMA_String, Texture*> m_textureMap;
};
class  ModelCache
{
public:
	Model* loadModel(SOMA_String filepath, RenderDevice& deviceIn,
		enum RenderDevice::BufferUsage usage);
	bool cleanUp();
	void cleanUpModel(SOMA_String filepath);
private:
	Map<SOMA_String, Model*> m_modelMap;
};
class  ShaderCache
{
public:
	Shader* loadShader(SOMA_String filepath, RenderDevice& deviceIn);
	bool cleanUp();
	void cleanUpShader(SOMA_String filepath);
private:
	Map<SOMA_String, Shader*> m_shaderMap;
};

class  ResourceManager {
public:
	ResourceManager();
	~ResourceManager();
	Model* loadModel(SOMA_String filepath, RenderDevice& deviceIn,enum RenderDevice::BufferUsage usage);
	Texture* loadTexture(SOMA_String filepath, RenderDevice& deviceIn, OpenGLRenderDevice::PixelFormat format);
	Shader* loadShader(SOMA_String filepath, RenderDevice& deviceIn);

	bool cleanUp();
	void cleanUpModel(SOMA_String filepath);

private:
	TextureCache m_textureCache;
	ModelCache m_modelCache;
	ShaderCache m_shaderCache;

};