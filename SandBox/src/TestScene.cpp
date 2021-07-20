#include <somapch.hpp>
#include <core/Window.hpp>
#include <rendering/ModelLoader.hpp>
#include <rendering/RenderCommand.hpp>
#include <math/Transform.hpp>
#include <math/Matrix.hpp>
#include <math/math.hpp>
#include <core/Timing.hpp>
#include <input/Input.hpp>
#include <imgui/ImGuiLayer.hpp>

#include <Soma.hpp>

#include "TestScene.hpp"
#include <glm/ext/matrix_transform.hpp>

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

int TestScene::getNextSceneIndex() const
{
	return 0;
}

int TestScene::getPreviousSceneIndex() const
{
	return 0;
}

void TestScene::build()
{
}

void TestScene::destroy()
{
}

void TestScene::onEntry()
{
	float vertices[3 * 3] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,-0.0f,
		0.0f,0.5f,0.0f
	};
	uint32 indexes[3] = { 0,1,2 };

	m_shader.reset(SOMA_ENGINE::Shader::Create("C:\\Users\\fruit\\Desktop\\Engines\\SomaEngine\\SomaEngine\\SandBox\\res\\shaders\\nullShader.glsl"));

	m_vertexArray.reset(SOMA_ENGINE::VertexArray::Create());
	m_vertexBuffer.reset(SOMA_ENGINE::VertexBuffer::Create(vertices, sizeof(vertices)));
	SOMA_ENGINE::BufferLayout layout = {
		{SOMA_ENGINE::ShaderDataType::Float3, "position"}
	};
	m_vertexBuffer->SetLayout(layout);
	m_vertexArray->AddVertexBuffer(m_vertexBuffer);

	m_indexBuffer.reset(SOMA_ENGINE::IndexBuffer::Create(indexes, sizeof(indexes) / sizeof(uint32)));
	m_vertexArray->SetIndexBuffer(m_indexBuffer);

	/*Square*/
	m_squareVA.reset(SOMA_ENGINE::VertexArray::Create());
	float squareVertices[3 * 4] = {
		-0.5f,-0.5f,0.0f,
		0.5f, -0.5f,-0.0f,
		0.5f, 0.5f,0.0f,
		-0.5f, 0.5f,0.0f
	};
	std::shared_ptr<SOMA_ENGINE::VertexBuffer> squareVB;
	squareVB.reset(SOMA_ENGINE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	SOMA_ENGINE::BufferLayout squarelayout = {
		{SOMA_ENGINE::ShaderDataType::Float3, "position"}
	};
	squareVB->SetLayout(squarelayout);
	m_squareVA->AddVertexBuffer(squareVB);

	uint32 squareIndexes[6] = { 0,1,2,2,3,0 };
	std::shared_ptr<SOMA_ENGINE::IndexBuffer> squareIB;
	squareIB.reset(SOMA_ENGINE::IndexBuffer::Create(squareIndexes, sizeof(squareIndexes)));
	m_squareVA->SetIndexBuffer(squareIB);


	m_cameraProps.width = m_game->window->getWidth();
	m_cameraProps.height = m_game->window->getHeight();
	m_cameraProps.cameraSpeed = 1.5f;
	m_cameraProps.cameraSensitivity = 0.1f;
	m_cameraProps.fov = 45.0f;
	m_cameraProps.fov_near = 0.1f;
	m_cameraProps.fov_far = 1000.0f;
	m_cameraProps.zoom = 0.0f;

	/*Camera*/
	m_camera.reset(new SOMA_ENGINE::FirstPersonCamera(
		glm::vec3(0.0f, 0.0f, 6.0f), 
		glm::vec3(0.0f,-60.0f,0.0f),
		&m_cameraProps));

	/*Uniform Buffer*/
	m_uniformBufferArray.push_back(m_camera->GetProjection());
	m_uniformBufferArray.push_back(m_camera->GetView());
	m_uniformBuffer.reset(SOMA_ENGINE::UniformBuffer::Create(&m_uniformBufferArray[0],sizeof(glm::mat4) * 2));
	m_shader->UploadUniformBuffer("Matrices", m_uniformBuffer.get());


	
}

void TestScene::onExit()
{
}

void TestScene::update(float dt)
{

}

void TestScene::draw(float dt)
{
	SOMA_ENGINE::RenderCommand::SetClearColor(glm::vec4(0.0f, 0.15f, 0.3f, 1.0f));
	SOMA_ENGINE::RenderCommand::Clear();

	SOMA_ENGINE::Renderer::Begin(m_camera);
	m_shader->Bind();

	//m_shader->SetMat4("u_projection", m_camera->GetProjection());
	//m_shader->SetMat4("u_view", m_camera->GetView());
	//m_shader->SetMat4("u_model", glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.5, -0.8f)));
	m_uniformBuffer->Update(&m_uniformBufferArray[0], sizeof(glm::mat4) * 2);

	SOMA_ENGINE::Renderer::Submit(m_squareVA);

	SOMA_ENGINE::Renderer::End();


	/*m_game->renderDevice->DrawV2(m_vertexArray,m_testShader->getId(), drawParams, 3);*/

	///*Draw things here*/
	//uniformBufferArray[1] = m_fpCamera->GetViewMatrix();
	//uniformBuffer->update(&uniformBufferArray[0]);
	///*================*/

	//m_renderContext->flush();
}
