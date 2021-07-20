#pragma once
#include <core/game/IMainGame.hpp>
#include <core/game/IScene.hpp>
#include <entt/entt.hpp>
#include <rendering/Model.hpp>


#include <rendering/Buffer.hpp>
#include <rendering/Renderer.hpp>
#include <platform/opengl/OpenGLVertexArray.hpp>
#include <camera/FirstPersonCamera.hpp>
#include <memory>
class TestScene : public IScene {
public:
	TestScene();
	~TestScene();

	//Return the index of the next or previous screen when changing
	virtual int getNextSceneIndex() const override;
	virtual int getPreviousSceneIndex() const override;


	//Called at beggining and end of application
	virtual void build() override;
	virtual void destroy() override;

	//Called when a screen enters and exits focus
	virtual void onEntry() override;
	virtual void onExit() override;

	//Called in main game loop
	virtual void update(float dt) override;
	virtual void draw(float dt) override;

private:

	/*RenderContext* m_renderContext;*/

	Model* model;

	InputControl horizontal;
	InputControl vertical;

	VertexArray* vertexArray;
	SOMA_Array<Matrix> uniformBufferArray;

	entt::registry enttRegistry;
	entt::dispatcher eventDispatcher;

	/*OpenGL Test*/
	std::shared_ptr<SOMA_ENGINE::VertexBuffer> m_vertexBuffer;
	std::shared_ptr<SOMA_ENGINE::IndexBuffer> m_indexBuffer;
	std::shared_ptr<SOMA_ENGINE::VertexArray> m_vertexArray;

	std::shared_ptr<SOMA_ENGINE::VertexArray> m_squareVA;
	std::shared_ptr<SOMA_ENGINE::Shader> m_shader;
	std::shared_ptr<SOMA_ENGINE::Camera> m_camera;
	std::shared_ptr<SOMA_ENGINE::UniformBuffer> m_uniformBuffer;
	SOMA_Array<glm::mat4> m_uniformBufferArray;
	SOMA_ENGINE::CameraProps m_cameraProps;

};