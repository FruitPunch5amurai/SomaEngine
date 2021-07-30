#include <somapch.hpp>
#include <core/Window.hpp>
#include <rendering/ModelLoader.hpp>
#include <rendering/RenderCommand.hpp>
#include <rendering/Texture.hpp>
#include <math/Transform.hpp>
#include <math/Matrix.hpp>
#include <math/math.hpp>
#include <core/Timing.hpp>
#include <imgui/ImGuiLayer.hpp>
#include <Soma.hpp>
#include <imgui/imgui.h>
#include "TestScene.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <rendering/Model.hpp>
#include <input/Input.hpp>
#include <camera/CameraController.hpp>

class TestLayer : public SOMA_ENGINE::Layer
{
public:
	TestLayer() : Layer("Test") {}
	void OnAttach() override {

//		m_shaderLibrary.Load("res/shaders/nullShader.glsl");
		m_shaderLibrary.Load("res/shaders/modelShader.glsl");
		/*Square*/
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);

		//m_squareVA.reset(SOMA_ENGINE::VertexArray::Create());
		//float squareVertices[5 * 4] = {
		//	-0.5,-0.5,0.0f, 0.0f,0.0f,
		//	 0.5,-0.5,0.0f,	1.0f,0.0f,
		//	 0.5,0.5,0.0f,	1.0f,1.0f,
		//	-0.5,0.5,0.0f,	0.0,1.0f
		//};
		//SOMA_ENGINE::Ref<SOMA_ENGINE::VertexBuffer> squareVB = 
		//	SOMA_ENGINE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		//SOMA_ENGINE::BufferLayout squarelayout = {
		//	{SOMA_ENGINE::ShaderDataType::Float3, "aPosition"},
		//	{SOMA_ENGINE::ShaderDataType::Float2, "aTexCoord"}
		//};
		//squareVB->SetLayout(squarelayout);
		//m_squareVA->AddVertexBuffer(squareVB);

		//uint32 squareIndexes[6] = {
		//	0,1,2,2,3,0
		//};
		//std::shared_ptr<SOMA_ENGINE::IndexBuffer> squareIB;
		//squareIB.reset(SOMA_ENGINE::IndexBuffer::Create(squareIndexes, sizeof(squareIndexes)));
		//m_squareVA->SetIndexBuffer(squareIB);

		/*Camera*/
		m_cameraController.reset(new SOMA_ENGINE::CameraController(
			glm::vec3(0.0f, 0.0f, 9.0f),
			glm::vec3(0.0f, -90.0f, 0.0f),IMainGame::Get().window->GetWidth(), IMainGame::Get().window->GetHeight()));

		/*Material*/
		m_cubeMaterial.ambient = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);
		m_cubeMaterial.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_cubeMaterial.specular = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		m_cubeMaterial.shininess = 32.0f;

		/*Uniform Buffer*/
		m_uniformBufferArray.push_back(m_cameraController->GetProjectionMatrix());
		m_uniformBufferArray.push_back(m_cameraController->GetViewMatrix());
		m_uniformBufferArray.push_back(glm::mat4(1.0f));
		m_uniformBuffer.reset(SOMA_ENGINE::UniformBuffer::Create(&m_uniformBufferArray[0],
			sizeof(glm::mat4) * 3));
		m_materialUniformBuffer.reset(SOMA_ENGINE::UniformBuffer::Create(&m_cubeMaterial,
			sizeof(SOMA_ENGINE::Material)));

		auto shader = m_shaderLibrary.Get("modelShader");
		shader->BindUniformBuffer("Matrices", m_uniformBuffer.get());
		shader->BindUniformBuffer("Material", m_materialUniformBuffer.get());

		/*Load Model*/
		m_model = std::make_shared<SOMA_ENGINE::Model>("res/models/backpack.obj",
			m_shaderLibrary.Get("modelShader"));


		SOMA_ENGINE::FrameBufferSpecification fbSpec;
		fbSpec.width = IMainGame::Get().window->GetWidth();
		fbSpec.height = IMainGame::Get().window->GetHeight();
		m_frameBuffer = SOMA_ENGINE::FrameBuffer::Create(fbSpec);

	};
	void OnDetach() override {
	};
	void OnUpdate(float deltaTime) override {


		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::Z)) {
			m_position = glm::vec3(m_position.x - deltaTime, m_position.y, m_position.z);
		}

		if (SOMA_ENGINE::Input::IsKeyPressed(SOMA_ENGINE::Key::X)) {
			m_position = glm::vec3(m_position.x + deltaTime, m_position.y, m_position.z);
		}
		m_cameraController->OnUpdate(deltaTime);
		m_uniformBufferArray[0] = m_cameraController->GetProjectionMatrix();
		m_uniformBufferArray[1] = m_cameraController->GetViewMatrix();
		m_uniformBufferArray[2] = glm::translate(glm::mat4(1.0f), m_position);

	}
	void OnDraw() override {
		m_frameBuffer->Bind();
		SOMA_ENGINE::RenderCommand::SetClearColor(glm::vec4(0.0f, 0.15f, 0.3f, 1.0f));
		SOMA_ENGINE::RenderCommand::Clear();

		SOMA_ENGINE::Renderer::Begin(m_cameraController->GetCamera());

		/*TODO: Move this logic somewhere else*/
		m_shaderLibrary.Get("modelShader")
			->UploadUniformBuffer("Matrices",&m_uniformBufferArray[0], sizeof(glm::mat4) * 3, 0);

		SOMA_ENGINE::Renderer::Submit(m_model);

		SOMA_ENGINE::Renderer::End();

		m_frameBuffer->Unbind();

	}
	void OnImGuiRender() override {
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		bool p_open = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				if (ImGui::MenuItem("Close", NULL, false, &p_open != NULL))
					p_open = false;
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Begin("Settings");

		uint32 textureId = m_frameBuffer->GetColorAttachmentID();
		ImGui::Image((void*)textureId, ImVec2(IMainGame::Get().window->GetWidth(), IMainGame::Get().window->GetHeight()), ImVec2{ 0,1 }, ImVec2{ 1,0 });
		ImGui::End();

		ImGui::End();

	};
	void OnEvent(SOMA_ENGINE::Event& e) override {
		m_cameraController->OnEvent(e);
	};
private:
	/*OpenGL Test*/
	glm::vec3 m_position;
	//std::shared_ptr<SOMA_ENGINE::VertexArray> m_squareVA;
	std::shared_ptr<SOMA_ENGINE::CameraController> m_cameraController;
	std::shared_ptr<SOMA_ENGINE::UniformBuffer> m_uniformBuffer;
	std::shared_ptr<SOMA_ENGINE::UniformBuffer> m_materialUniformBuffer;
	std::shared_ptr<SOMA_ENGINE::FrameBuffer> m_frameBuffer;
	SOMA_Array<glm::mat4> m_uniformBufferArray;
	SOMA_ENGINE::Material m_cubeMaterial;
	SOMA_ENGINE::ShaderLibrary m_shaderLibrary;

	std::shared_ptr<SOMA_ENGINE::Model> m_model;


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
