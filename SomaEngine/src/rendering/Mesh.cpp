#include "somapch.hpp"
#include "rendering/Mesh.hpp"
namespace SOMA_ENGINE
{
	Mesh::Mesh(SOMA_Array<float> data, SOMA_Array<uint32> indices,
		SOMA_Array<MeshTexture> textures, Ref<Shader> shaderRef)
	{
		this->data = data;
		this->indices = indices;
		this->textures = textures;
		this->m_shaderRef = shaderRef;

		SetupMesh();
	}

	void Mesh::Bind()
	{
		m_shaderRef->Bind();
		uint32 count = 0;
		uint32 diffuseNr = 0;
		uint32 specularNr = 0;
		uint32 normalNr = 0;
		uint32 heightNr = 0;

		for each (MeshTexture tex in textures)
		{
			tex.texture->Bind(count);
			switch (tex.type)
			{
			case MeshTextureType::DIFFUSE:
				m_shaderRef->UploadInt("tex_diffuse" + diffuseNr, count);
				break;
			}
			count++;
		}
		m_vertexArray->Bind();
	}

	void Mesh::Unbind()
	{
		m_vertexArray->Unbind();
	}

	void Mesh::SetupMesh()
	{
		m_vertexArray.reset(SOMA_ENGINE::VertexArray::Create());
			
		Ref<SOMA_ENGINE::VertexBuffer> VB = 
			SOMA_ENGINE::VertexBuffer::Create(&data[0],data.size() * sizeof(float));

		SOMA_ENGINE::BufferLayout layout = {
			{SOMA_ENGINE::ShaderDataType::Float3, "aPosition"},
			{SOMA_ENGINE::ShaderDataType::Float3, "aNormal"},
			{SOMA_ENGINE::ShaderDataType::Float2, "aTexCoord"}
		};
		VB->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(VB);

		std::shared_ptr<SOMA_ENGINE::IndexBuffer> IB;
		IB.reset(SOMA_ENGINE::IndexBuffer::Create(&indices[0], indices.size()));
		m_vertexArray->SetIndexBuffer(IB);
	}
}