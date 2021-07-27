#include <somapch.hpp>
#include <core/Window.hpp>
#include <rendering/ModelLoader.hpp>
#include <rendering/RenderCommand.hpp>
#include <rendering/Texture.hpp>
#include <math/Transform.hpp>
#include <math/Matrix.hpp>
#include <math/math.hpp>
#include <core/Timing.hpp>
#include <input/Input.hpp>
#include <imgui/ImGuiLayer.hpp>
#include <Soma.hpp>
#include <imgui/imgui.h>
#include "TestScene.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "core/Input.hpp"

class TestLayer : public SOMA_ENGINE::Layer
{
public:
	TestLayer() : Layer("Test") {}
	void OnAttach() override {

		m_shaderLibrary.Load("res/shaders/nullShader.glsl");
		/*Square*/
		m_squarePos = glm::vec3(0.0f, 0.0f, 0.0f);

		m_squareVA.reset(SOMA_ENGINE::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5,-0.5,0.0f, 0.0f,0.0f,
			 0.5,-0.5,0.0f,	1.0f,0.0f,
			 0.5,0.5,0.0f,	1.0f,1.0f,
			-0.5,0.5,0.0f,	0.0,1.0f
		};
		std::shared_ptr<SOMA_ENGINE::VertexBuffer> squareVB;
		squareVB.reset(SOMA_ENGINE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		SOMA_ENGINE::BufferLayout squarelayout = {
			{SOMA_ENGINE::ShaderDataType::Float3, "aPosition"},
			{SOMA_ENGINE::ShaderDataType::Float2, "aTexCoord"}
		};
		squareVB->SetLayout(squarelayout);
		m_squareVA->AddVertexBuffer(squareVB);

		uint32 squareIndexes[6] = {
			0,1,2,2,3,0
		};
		std::shared_ptr<SOMA_ENGINE::IndexBuffer> squareIB;
		squareIB.reset(SOMA_ENGINE::IndexBuffer::Create(squareIndexes, sizeof(squareIndexes)));
		m_squareVA->SetIndexBuffer(squareIB);


		m_cameraProps.width = IMainGame::Get().window->getWidth();
		m_cameraProps.height = IMainGame::Get().window->getHeight();
		m_cameraProps.cameraSpeed = 1.5f;
		m_cameraProps.cameraSensitivity = 0.1f;
		m_cameraProps.fov = 45.0f;
		m_cameraProps.fov_near = 0.1f;
		m_cameraProps.fov_far = 1000.0f;
		m_cameraProps.zoom = 0.0f;
		m_cameraProps.left = -1.6f;
		m_cameraProps.right = 1.6f;
		m_cameraProps.bottom = -0.9f;
		m_cameraProps.top = 0.9f;
		m_cameraProps.isOrthographic = false;

		/*Camera*/
		m_camera.reset(new SOMA_ENGINE::FirstPersonCamera(
			glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, -90.0f, 0.0f),
			&m_cameraProps));
		//m_camera.reset(new SOMA_ENGINE::FirstPersonCamera(
		//	glm::vec3(0.0f, 0.0f, 0.0f),
		//	glm::vec3(0.0f, 0.0f, 0.0f),
		//	&m_cameraProps));

		/*Material*/
		m_cubeMaterial.ambient = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);
		m_cubeMaterial.diffuse = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);
		m_cubeMaterial.specular = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		m_cubeMaterial.shininess = 32.0f;

		/*Uniform Buffer*/
		m_uniformBufferArray.push_back(m_camera->GetProjection());
		m_uniformBufferArray.push_back(m_camera->GetView());
		m_uniformBufferArray.push_back(glm::mat4(1.0f));
		m_uniformBuffer.reset(SOMA_ENGINE::UniformBuffer::Create(&m_uniformBufferArray[0],
			sizeof(glm::mat4) * 3));
		m_materialUniformBuffer.reset(SOMA_ENGINE::UniformBuffer::Create(&m_cubeMaterial,
			sizeof(SOMA_ENGINE::MaterialSpec)));

		auto shader = m_shaderLibrary.Get("nullShader");
		shader->UploadUniformBuffer("Matrices", m_uniformBuffer.get());
		shader->UploadUniformBuffer("Material", m_materialUniformBuffer.get());

		m_texture.reset(SOMA_ENGINE::Texture2D::Create("res/textures/container.png"));



	};
	void OnDetach() override {
	};
	void OnUpdate(float deltaTime) override {

		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::SDL_SCANCODE_A)) {
			m_camera->Move(SOMA_ENGINE::CameraMovement::LEFT, deltaTime);
		}
		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::SDL_SCANCODE_D)) {
			m_camera->Move(SOMA_ENGINE::CameraMovement::RIGHT, deltaTime);
		}
		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::SDL_SCANCODE_W)) {
			m_camera->Move(SOMA_ENGINE::CameraMovement::FOWARD, deltaTime);
		}
		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::SDL_SCANCODE_S)) {
			m_camera->Move(SOMA_ENGINE::CameraMovement::BACKWARD, deltaTime);
		}
		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::SDL_SCANCODE_Q)) {
			m_camera->Move(SOMA_ENGINE::CameraMovement::UP, deltaTime);
		}
		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::SDL_SCANCODE_E)) {
			m_camera->Move(SOMA_ENGINE::CameraMovement::DOWN, deltaTime);
		}
		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::SDL_SCANCODE_Z)) {
			m_squarePos = glm::vec3(m_squarePos.x - deltaTime, m_squarePos.y, m_squarePos.z);
		}

		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::SDL_SCANCODE_X)) {
			m_squarePos = glm::vec3(m_squarePos.x + deltaTime, m_squarePos.y, m_squarePos.z);
		}
		m_uniformBufferArray[1] = m_camera->GetView();
		m_uniformBufferArray[2] = glm::translate(glm::mat4(1.0f),m_squarePos);

	}
	void OnDraw() override {
		SOMA_ENGINE::RenderCommand::SetClearColor(glm::vec4(0.0f, 0.15f, 0.3f, 1.0f));
		SOMA_ENGINE::RenderCommand::Clear();

		SOMA_ENGINE::Renderer::Begin(m_camera);

		m_uniformBuffer->Update(&m_uniformBufferArray[0], sizeof(glm::mat4) * 3);

		m_texture->Bind();

		SOMA_ENGINE::Renderer::Submit(m_squareVA, m_shaderLibrary.Get("nullShader"));

		SOMA_ENGINE::Renderer::End();
	}
	void OnImGuiRender() override {

	};
	void OnEvent(SOMA_ENGINE::Event& event) override {};
private:
	/*OpenGL Test*/
	glm::vec3 m_squarePos;


	std::shared_ptr<SOMA_ENGINE::VertexArray> m_squareVA;
	std::shared_ptr<SOMA_ENGINE::Camera> m_camera;
	std::shared_ptr<SOMA_ENGINE::UniformBuffer> m_uniformBuffer;
	std::shared_ptr<SOMA_ENGINE::UniformBuffer> m_materialUniformBuffer;
	std::shared_ptr<SOMA_ENGINE::FrameBuffer> m_frameBuffer;
	SOMA_ENGINE::Ref<SOMA_ENGINE::Texture2D> m_texture;
	SOMA_Array<glm::mat4> m_uniformBufferArray;
	SOMA_ENGINE::MaterialSpec m_cubeMaterial;
	SOMA_ENGINE::CameraProps m_cameraProps;
	SOMA_ENGINE::ShaderLibrary m_shaderLibrary;

};


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
	/*Camera ImGui Layer*/
	m_game->PushLayer(new TestLayer());
}

void TestScene::onExit()
{
}

void TestScene::update(float dt)
{


}
void TestScene::draw()
{

}
