#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "core/common.hpp"
#include "rendering/Shader.hpp"
#include "rendering/Buffer.hpp"
#include <platform/opengl/VertexArray.hpp>

namespace SOMA_ENGINE
{
	enum class MeshTextureType {
		DIFFUSE
	};
	struct MeshVertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	struct MeshTexture {
		uint32 id;
		MeshTextureType type;
	};

	class Mesh {
	public:
		SOMA_Array<float> data;
		SOMA_Array<uint32> indices;
		SOMA_Array<MeshTexture> textures;

		Mesh(SOMA_Array<float> data, 
			SOMA_Array<uint32> indices,
			SOMA_Array<MeshTexture> textures);
		std::shared_ptr<VertexArray> m_vertexArray;
	private:
		//render data

		void SetupMesh();
	};

}