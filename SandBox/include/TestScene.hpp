#pragma once
#include <core/game/IMainGame.hpp>
#include <core/game/IScene.hpp>
#include <camera/FPCamera.hpp>
#include <entt/entt.hpp>
#include <entt/SystemsManager.hpp>
#include <rendering/Model.hpp>
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

	GameRenderContext* m_renderContext;
	FPCamera* m_fpCamera;

	Model* model;

	InputControl horizontal;
	InputControl vertical;

	VertexArray* vertexArray;
	Texture* texture;
	Sampler* sampler;
	Shader* shader;
	UniformBuffer* uniformBuffer;
	SOMA_Array<Matrix> uniformBufferArray;

	SystemsManager systemsManager;
	entt::registry enttRegistry;
	entt::dispatcher eventDispatcher;

};