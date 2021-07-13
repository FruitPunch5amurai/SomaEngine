#include "somapch.hpp"

#include "rendering/Model.hpp"
#include <core/game/ResourceManager.hpp>
Model::Model()
{
}

Model::~Model()
{
	cleanUp();
}

void Model::loadTextures(ResourceManager* rManager, RenderDevice& deviceIn, OpenGLRenderDevice::PixelFormat format)
{
	for (MaterialSpec& mat : materials)
	{
		Map<SOMA_String, SOMA_String>::iterator it;
		for (it = mat.textureNames.begin(); it != mat.textureNames.end(); it++)
		{
			Texture* tex = rManager->loadTexture(it->second,deviceIn,format);
			mat.ids.insert(std::make_pair(it->first,tex->getId()));
		}
	}
}

void Model::cleanUp()
{
	for (VertexArray* vao : VAOs)
	{
		delete vao;
	}
}

void Model::generateVAOs(RenderDevice& deviceIn, RenderDevice::BufferUsage usage)
{
	for (IndexedModel mesh : meshes)
	{
		VAOs.push_back(new VertexArray(deviceIn, mesh, usage));
	}
}
