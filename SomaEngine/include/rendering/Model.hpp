#pragma once

#include <rendering/IndexedModel.hpp>
#include <rendering/Material.hpp>
#include <rendering/VertexArray.hpp>
#include <rendering/Texture.hpp>

#include <rendering/Mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//class ResourceManager;
//class Model {
//public:
//	Model();
//	~Model();
//	SOMA_Array<IndexedModel> meshes;
//	SOMA_Array<uint32> materialIndices;
//	SOMA_Array<MaterialSpec> materials;
//	SOMA_Array<VertexArray*> VAOs;
//
//	void generateVAOs(RenderDevice& deviceIn,enum RenderDevice::BufferUsage usage);
//	void loadTextures(ResourceManager* rManager, RenderDevice& deviceIn, OpenGLRenderDevice::PixelFormat format);
//	void cleanUp();
//
//
//private:
//
//};

namespace SOMA_ENGINE {
	class Model {
	public:
		Model(const SOMA_String& filepath, Ref<Shader> shaderRef) {
			m_shaderRef = shaderRef;
			LoadModel(filepath);
		}
		SOMA_Array<Mesh> meshes;
	private:

		SOMA_String m_name;
		void LoadModel(const SOMA_String& filepath);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		SOMA_Array<MeshTexture> m_texturesLoaded;
		Ref<Shader> m_shaderRef;
		SOMA_Array<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, MeshTextureType texType);
	};
}