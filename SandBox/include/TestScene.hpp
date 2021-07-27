#pragma once
#include <core/game/IMainGame.hpp>
#include <core/game/IScene.hpp>
#include <entt/entt.hpp>
#include <rendering/Model.hpp>
#include <rendering/FrameBuffer.hpp>

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
	virtual void draw() override;

private:

	/*RenderContext* m_renderContext;*/

	Model* model;

	InputControl horizontal;
	InputControl vertical;

	VertexArray* vertexArray;
	SOMA_Array<Matrix> uniformBufferArray;

	entt::registry enttRegistry;
	entt::dispatcher eventDispatcher;



};