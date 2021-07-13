#pragma once

#include <rendering/IndexedModel.hpp>
#include <rendering/Material.hpp>
#include <rendering/VertexArray.hpp>
#include <rendering/Texture.hpp>

class ResourceManager;
class Model {
public:
	Model();
	~Model();
	SOMA_Array<IndexedModel> meshes;
	SOMA_Array<uint32> materialIndices;
	SOMA_Array<MaterialSpec> materials;
	SOMA_Array<VertexArray*> VAOs;

	void generateVAOs(RenderDevice& deviceIn,enum RenderDevice::BufferUsage usage);
	void loadTextures(ResourceManager* rManager, RenderDevice& deviceIn, OpenGLRenderDevice::PixelFormat format);
	void cleanUp();


private:

};