#include "somapch.hpp"

#include "core/game/ResourceManager.hpp"
#include <rendering/ModelLoader.hpp>
//
//
//ResourceManager::ResourceManager()
//{
//}
//
//ResourceManager::~ResourceManager()
//{
//	cleanUp();
//}
//
//Model* ResourceManager::loadModel(SOMA_String filepath,RenderDevice& deviceIn,enum RenderDevice::BufferUsage usage)
//{
//	return m_modelCache.loadModel(filepath, deviceIn, usage);
//}
//Shader* ResourceManager::loadShader(SOMA_String filepath, RenderDevice& deviceIn)
//{
//	return m_shaderCache.loadShader(filepath,deviceIn);
//}
//Texture* ResourceManager::loadTexture(SOMA_String filepath, RenderDevice& deviceIn, OpenGLRenderDevice::PixelFormat format)
//{
//	return m_textureCache.loadTexture(filepath, deviceIn, format);
//}
//
//bool ResourceManager::cleanUp()
//{
//	bool success = false;
//	success = m_modelCache.cleanUp() == true && success?true:false;
//	success = m_textureCache.cleanUp() == true && success ? true : false;
//	success = m_shaderCache.cleanUp() == true && success ? true : false;
//	return success;
//}
//
//void ResourceManager::cleanUpModel(SOMA_String filepath)
//{
//	m_modelCache.cleanUpModel(filepath);
//}
//
//Shader* ShaderCache::loadShader(SOMA_String filepath, RenderDevice& deviceIn) {
//	auto it = m_shaderMap.find(filepath);
//	if (it == m_shaderMap.end())
//	{
//		SOMA_String shaderText;
//		StringFuncs::loadTextFileWithIncludes(shaderText, filepath, "#include");
//		Shader* newShader = new Shader(deviceIn, shaderText);
//		if (newShader == nullptr)
//			return nullptr;
//		m_shaderMap.insert(make_pair(filepath, newShader));
//		return newShader;
//	}
//	return it->second;
//}
//bool ShaderCache::cleanUp() {
//	Map<SOMA_String, Shader*>::iterator it;
//	for (it = m_shaderMap.begin(); it != m_shaderMap.end(); it++)
//	{
//		delete it->second;
//	}
//	m_shaderMap.clear();
//	return true;
//}
//void ShaderCache::cleanUpShader(SOMA_String filepath) {
//
//}
//
//Texture* TextureCache::loadTexture(SOMA_String filepath, RenderDevice& deviceIn, OpenGLRenderDevice::PixelFormat format)
//{
//	auto it = m_textureMap.find(filepath);
//	if (it == m_textureMap.end())
//	{
//
//		ArrayBitmap image;
//		if (!image.load(filepath))
//		{
//			return nullptr;
//		}
//		Texture* tex = new Texture(deviceIn, image, format, true, false);
//		m_textureMap.insert(make_pair(filepath, tex));
//		return tex;
//	}
//	return it->second;
//}
//
//bool TextureCache::cleanUp()
//{
//	Map<SOMA_String, Texture*>::iterator it;
//	for (it = m_textureMap.begin(); it != m_textureMap.end(); it++)
//	{
//		delete it->second;
//	}
//	m_textureMap.clear();
//	return true;
//}
//
//void TextureCache::cleanUpTexture(SOMA_String filepath)
//{
//}
//
//Model* ModelCache::loadModel(SOMA_String filepath, RenderDevice& deviceIn, 
//	RenderDevice::BufferUsage usage)
//{
//	auto it = m_modelMap.find(filepath);
//	if (it == m_modelMap.end())
//	{
//
//		Model* model = ModelLoader::loadModels(filepath);
//		if (model == nullptr)
//			return nullptr;
//
//		model->generateVAOs(deviceIn, usage);
//
//		m_modelMap.insert(make_pair(filepath, model));
//
//		return model;
//	}
//	return it->second;
//}
//
//bool ModelCache::cleanUp()
//{
//	Map<SOMA_String, Model*>::iterator it;
//	for (it = m_modelMap.begin(); it != m_modelMap.end(); it++)
//	{
//		it->second->cleanUp();
//	}
//	m_modelMap.clear();
//	return true;
//}
//
//void ModelCache::cleanUpModel(SOMA_String filepath)
//{
//	auto it = m_modelMap.find(filepath);
//	if (it == m_modelMap.end())
//	{
//		it->second->cleanUp();
//	}
//}
