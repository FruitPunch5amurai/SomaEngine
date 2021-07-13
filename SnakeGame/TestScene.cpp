#include <iostream>
#include <core/Window.hpp>
#include <GL/glew.h>
#include <rendering/ModelLoader.hpp>
#include <iostream>
#include <math/Transform.hpp>
#include <math/Matrix.hpp>
#include <math/math.hpp>
#include <core/Timing.hpp>
#include <input/Input.hpp>

#include "RenderMeshSystem.hpp"
#include "SnakeControlSystem.hpp"
#include "SnakeBodySystem.hpp"
#include "LerpComponent.h"
#include "LerpSystem.h"
#include "TestScene.hpp"

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

	m_fpCamera = new FPCamera(*m_game->window, m_eventHandler);
	m_fpCamera->transform.setTranslation(Vector3f(0.0f, 0.0f, 11.0f));
	uniformBufferArray.push_back(m_fpCamera->GetProjection()); //Matrix::perspective(Math::toRadians(70.0f / 2.0f), 4.0f / 3.0f, 0.1f, 1000.0f));
	uniformBufferArray.push_back(m_fpCamera->GetViewMatrix()); //Matrix::perspective(Math::toRadians(70.0f / 2.0f), 4.0f / 3.0f, 0.1f, 1000.0f));
	uniformBuffer = new UniformBuffer(*m_game->renderDevice, sizeof(Matrix) * 2, OpenGLRenderDevice::BufferUsage::USAGE_STATIC_DRAW, &uniformBufferArray[0]);
	//Load Sampler
	sampler = new Sampler(*m_game->renderDevice, RenderDevice::FILTER_LINEAR_MIPMAP_LINEAR);
	//Load a shader
	shader = m_game->resourceManager.loadShader("./res/shaders/basicShader.glsl", *m_game->renderDevice);
	shader->setUniformBuffer("Matrices", *uniformBuffer);

	RenderDevice::DrawParams drawParams;
	drawParams.primitiveType = RenderDevice::PRIMITIVE_TRIANGLES;
	drawParams.faceCulling = RenderDevice::FACE_CULL_NONE;
	drawParams.shouldWriteDepth = true;
	drawParams.depthFunc = RenderDevice::DRAW_FUNC_LESS;

	m_renderContext = new GameRenderContext(*m_game->renderDevice, *m_game->renderTarget, drawParams, *shader, *sampler);

	/*Systems*/
	systemsManager.Add<RenderMeshSystem>(*m_renderContext);
	systemsManager.Add<LerpSystem>();
	systemsManager.Add<SnakeBodySystem>();
	systemsManager.Add<SnakeControlSystem>();
	systemsManager.Configure();

	/*Model Loading*/
	model = m_game->resourceManager.loadModel("./res/models/cube.obj", *m_game->renderDevice, RenderDevice::USAGE_STATIC_DRAW);
	model->loadTextures(&m_game->resourceManager, *m_game->renderDevice, OpenGLRenderDevice::PixelFormat::FORMAT_RGBA);

	MovementControlComponent movementControlComponent;
	movementControlComponent.horizontal = &horizontal;
	movementControlComponent.vertical = &vertical;

	entt::entity previousEnt;
	/*Test Entities*/
	for (int i = 0; i < 100; i++)
	{

		TransformComponent transformComponent;
		transformComponent.transform.setTranslation(Vector3f(0.0f - (2.0f * i), 0.0f, 0.0f));

		MeshComponent renderableMesh;
		renderableMesh.model = model;

		LerpComponent lerpComponent;
		lerpComponent.destination = transformComponent.transform.getTranslation();
		lerpComponent.start = transformComponent.transform.getTranslation();

		SnakeBodyComponent snakeBodyComponent;

		if (i != 0)
		{
			snakeBodyComponent.nextSnakeBody = previousEnt;
		}
		auto body = enttRegistry.create();
		/*Add Entities*/
		enttRegistry.emplace<TransformComponent>(body, transformComponent);
		enttRegistry.emplace<MeshComponent>(body, renderableMesh);
		enttRegistry.emplace<LerpComponent>(body, lerpComponent);
		enttRegistry.emplace<SnakeBodyComponent>(body, snakeBodyComponent);
		if (i == 0)
		{
			enttRegistry.emplace<MovementControlComponent>(body, movementControlComponent);
		}
		previousEnt = body;
	}
	m_eventHandler.addKeyControl(Input::KEY_LEFT, horizontal, -1.0f);
	m_eventHandler.addKeyControl(Input::KEY_RIGHT, horizontal, 1.0f);
	m_eventHandler.addKeyControl(Input::KEY_UP, vertical, 1.0f);
	m_eventHandler.addKeyControl(Input::KEY_DOWN, vertical, -1.0f);
}

void TestScene::onExit()
{
	m_game->renderDevice->releaseUniformBuffer(uniformBuffer->getId());
}

void TestScene::update(float dt)
{
	m_game->processMessages(dt, m_eventHandler);
	systemsManager.System<LerpSystem>()->Update(enttRegistry, eventDispatcher, dt);
	systemsManager.System<SnakeBodySystem>()->Update(enttRegistry, eventDispatcher, dt);
	systemsManager.System<SnakeControlSystem>()->Update(enttRegistry, eventDispatcher, dt);
}

void TestScene::draw(float dt)
{
	if (m_renderContext == nullptr)
		return;
	m_renderContext->clear(Color(0.0f, 0.15f, 0.3f), true);

	/*Draw things here*/
	uniformBufferArray[1] = m_fpCamera->GetViewMatrix();
	uniformBuffer->update(&uniformBufferArray[0]);

	systemsManager.System<RenderMeshSystem>()->Update(enttRegistry, eventDispatcher, dt);

	/*================*/

	m_renderContext->flush();
}
