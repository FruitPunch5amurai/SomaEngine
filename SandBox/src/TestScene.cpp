#include <somapch.hpp>
#include <core/Window.hpp>
#include <rendering/ModelLoader.hpp>

#include <math/Transform.hpp>
#include <math/Matrix.hpp>
#include <math/math.hpp>
#include <core/Timing.hpp>
#include <input/Input.hpp>
#include <imgui/ImGuiLayer.hpp>

#include <Soma.hpp>

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
	float vertices[3 * 3] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,-0.0f,
		0.0f,0.5f,0.0f
	};
	uint32 indexes[3] = { 0,1,2 };

	m_vertexArray = m_game->renderDevice->GenSimpleVAO(vertices,
		sizeof(vertices),
		indexes,
		sizeof(indexes),
		OpenGLRenderDevice::BufferUsage::USAGE_STATIC_DRAW);
	SOMA_String shaderText;
	StringFuncs::loadTextFileWithIncludes(shaderText, "C:\\Users\\fruit\\Desktop\\Engines\\SomaEngine\\SomaEngine\\SandBox\\res\\shaders\\nullShader.glsl", "#include");
	m_testShader = new Shader(*m_game->renderDevice, shaderText);
	/*Systems*/
	//systemsManager.Configure();

	/*Model Loading*/
	/*model = m_game->resourceManager.loadModel("./res/models/cube.obj", *m_game->renderDevice, RenderDevice::USAGE_STATIC_DRAW);
	model->loadTextures(&m_game->resourceManager, *m_game->renderDevice, OpenGLRenderDevice::PixelFormat::FORMAT_RGBA);*/

	//entt::entity previousEnt;
}

void TestScene::onExit()
{
	/*m_game->renderDevice->releaseUniformBuffer(uniformBuffer->getId());*/
}

void TestScene::update(float dt)
{

}

void TestScene::draw(float dt)
{
	if (m_renderContext == nullptr)
		return;
	m_game->renderDevice->ClearV2(true, true, false, Color(0.0f, 0.15f, 0.3f), 0);
	RenderDevice::DrawParams drawParams;
	drawParams.primitiveType = RenderDevice::PRIMITIVE_TRIANGLES;
	drawParams.faceCulling = RenderDevice::FACE_CULL_NONE;
	drawParams.shouldWriteDepth = true;
	drawParams.depthFunc = RenderDevice::DRAW_FUNC_LESS;

	m_game->renderDevice->DrawV2(m_vertexArray,m_testShader->getId(), drawParams, 3);

	///*Draw things here*/
	//uniformBufferArray[1] = m_fpCamera->GetViewMatrix();
	//uniformBuffer->update(&uniformBufferArray[0]);
	///*================*/

	//m_renderContext->flush();
}
