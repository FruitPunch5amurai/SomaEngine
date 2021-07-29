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
		DIFFUSE,
		SPECULAR,
		HEIGHT,
		NORMAL
	};
	struct MeshTexture {
		Ref<Texture2D> texture;
		MeshTextureType type;
		SOMA_String path;
	};

	class Mesh {
	public:
		SOMA_Array<float> data;
		SOMA_Array<uint32> indices;
		SOMA_Array<MeshTexture> textures;

		Mesh(SOMA_Array<float> data, 
			SOMA_Array<uint32> indices,
			SOMA_Array<MeshTexture> textures,
			Ref<Shader> shaderRef);

		void Bind();
		void Unbind();

		Ref<VertexArray> GetVertexArray() { return m_vertexArray; }
	private:
		//render data
		Ref<VertexArray> m_vertexArray;
		Ref<Shader> m_shaderRef;

		void SetupMesh();
	};

}