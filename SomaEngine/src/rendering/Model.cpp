#include "somapch.hpp"

#include "rendering/Model.hpp"
#include <core/game/ResourceManager.hpp>
#include <core/Logger.hpp>
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
			/*Texture* tex = rManager->loadTexture(it->second,deviceIn,format);*/
			//mat.ids.insert(std::make_pair(it->first,tex->getId()));
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

namespace SOMA_ENGINE {
	void Model::LoadModel(const SOMA_String& filepath)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(filepath,
            aiProcess_Triangulate |
            aiProcess_GenSmoothNormals |
            aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			SOMA_CORE_ERROR("Failed to load model!");
			return;
		}
		m_name = filepath.substr(0, filepath.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}
	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}
	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
        // data to fill
        SOMA_Array<float> data;
        SOMA_Array<uint32> indices;
        SOMA_Array<MeshTexture> textures;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            // positions
            data.push_back(mesh->mVertices[i].x);
            data.push_back(mesh->mVertices[i].y);
            data.push_back(mesh->mVertices[i].z);
            // normals
            if (mesh->HasNormals())
            {
                data.push_back(mesh->mNormals[i].x);
                data.push_back(mesh->mNormals[i].y);
                data.push_back(mesh->mNormals[i].z);
            }
            else {
                data.push_back(0.0f);
                data.push_back(0.0f);
                data.push_back(0.0f);
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).

                data.push_back(mesh->mTextureCoords[0][i].x);
                data.push_back(mesh->mTextureCoords[0][i].y);
                /*
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
                */
            }
            else
            {
                data.push_back(0.0f);
                data.push_back(0.0f);
            }
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        SOMA_Array<MeshTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, MeshTextureType::DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        SOMA_Array<MeshTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, MeshTextureType::SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        SOMA_Array<MeshTexture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, MeshTextureType::NORMAL);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        SOMA_Array<MeshTexture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, MeshTextureType::HEIGHT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        // return a mesh object created from the extracted mesh data
        return Mesh(data, indices, textures,m_shaderRef);
    }
    SOMA_Array<MeshTexture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, MeshTextureType texType)
    {
        SOMA_Array<MeshTexture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < m_texturesLoaded.size(); j++)
            {
                if (std::strcmp(m_texturesLoaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(m_texturesLoaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip)
            {   // if texture hasn't been loaded already, load it
                MeshTexture texture;
                texture.texture =SOMA_ENGINE::Texture2D::Create(str.C_Str());
                texture.type = texType;
                texture.path = str.C_Str();
                textures.push_back(texture);
                m_texturesLoaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }
}