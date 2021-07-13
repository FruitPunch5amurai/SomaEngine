// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//#include <core/Application.hpp>
//#include <core/Window.hpp>
//#include <GL/glew.h>
//#include <rendering/RenderDevice.hpp>
//#include <rendering/RenderTarget.hpp>
//#include <rendering/RenderContext.hpp>
//#include <rendering/ModelLoader.hpp>
//#include <iostream>
//#include <math/Transform.hpp>
//#include <math/Matrix.hpp>
//#include <math/math.hpp>
//#include <core/Timing.hpp>
//#include <GameEventHandler.hpp>
//#include <input/Input.hpp>
//#include <camera/FPCamera.hpp>
//#include <entt/entt.hpp>
//#include <entt/SystemsManager.hpp>
//#include <GameRenderContext.hpp>
//
//#include "RenderMeshSystem.hpp"
//#include "MovementControlSystem.hpp"
//#include "LerpComponent.h"
//#include "LerpSystem.h"

#include "MainGame.hpp"

#ifdef main
#undef main
#endif
int main()
{

    MainGame* game = new MainGame();
    game->run();
    return 0;

}
    //Application* app = Application::create();
    //Window window(*app, 800, 600, "Snake Game");
    //RenderDevice device(window);

    //Array<IndexedModel> models;
    //Array<uint32> modelMaterialIndices;
    //Array<MaterialSpec> modelMaterials;
    //Array<Matrix> uniformBufferArray;

    //ModelLoader::loadModels("./res/models/cube.obj", models,
    //    modelMaterialIndices, modelMaterials);

    //GameEventHandler eventHandler;

    ///*Camera*/
    //FPCamera fpCamera(window, eventHandler);
    //fpCamera.transform.setTranslation(Vector3f(0.0f, 3.0f, 20.0f));
    //uniformBufferArray.push_back(fpCamera.GetProjection()); //Matrix::perspective(Math::toRadians(70.0f / 2.0f), 4.0f / 3.0f, 0.1f, 1000.0f));
    //uniformBufferArray.push_back(fpCamera.GetViewMatrix()); //Matrix::perspective(Math::toRadians(70.0f / 2.0f), 4.0f / 3.0f, 0.1f, 1000.0f));

    //VertexArray vertexArray(device, models[0], RenderDevice::USAGE_STATIC_DRAW);
    //UniformBuffer uniformBuffer(device, sizeof(Matrix) * 2, OpenGLRenderDevice::BufferUsage::USAGE_STATIC_DRAW, &uniformBufferArray[0]);
    //Sampler sampler(device, RenderDevice::FILTER_LINEAR_MIPMAP_LINEAR);

    //DDSTexture ddsTexture;
    //if (!ddsTexture.load("./res/textures/bricks.dds")) {
    //    DEBUG_LOG("Main", LOG_ERROR, "Could not load texture!");
    //    return 1;
    //}
    //Texture texture(device, ddsTexture);

    ////Load a shader
    //String shaderText;
    //StringFuncs::loadTextFileWithIncludes(shaderText, "./res/shaders/basicShader.glsl", "#include");
    //Shader shader(device, shaderText);
    //shader.setSampler("diffuse", texture, sampler, 0);
    //shader.setUniformBuffer("Matrices", uniformBuffer);

    //RenderDevice::DrawParams drawParams;
    //drawParams.primitiveType = RenderDevice::PRIMITIVE_TRIANGLES;
    //drawParams.faceCulling = RenderDevice::FACE_CULL_NONE;
    //drawParams.shouldWriteDepth = true;
    //drawParams.depthFunc = RenderDevice::DRAW_FUNC_LESS;

    ///*Render Pipeline*/
    //RenderTarget target(device);
    //GameRenderContext renderContext(device, target, drawParams, shader, sampler);
    //Color color(0.0f, 0.15f, 0.3f);

    ///*Entt*/
    //SystemsManager systemsManager;
    //entt::registry enttRegistry;
    //entt::dispatcher eventDispatcher;
    ///*systemsManager.Add<MovementControlSystem>();*/
    //systemsManager.Add<RenderMeshSystem>(renderContext);
    //systemsManager.Add<LerpSystem>();
    //systemsManager.Configure();

    //TransformComponent transformComponent, transformComponent2;
    //transformComponent.transform.setTranslation(Vector3f(-5.0f,0.0f,0.0f));
    //
    //transformComponent2.transform.setTranslation(Vector3f(-2.9f, 0.0f, 0.0f));

    //MeshComponent renderableMesh, renderableMesh2;
    //renderableMesh.vertexArray = &vertexArray;
    //renderableMesh.texture = &texture;
    //
    //renderableMesh2.vertexArray = &vertexArray;
    //renderableMesh2.texture = &texture;

    //LerpComponent lerpComponent, lerpComponent2;
    //lerpComponent.destination = transformComponent.transform.getTranslation() + Vector3f(13.0f, 0.0f, 0.0f);
    //lerpComponent.start = transformComponent.transform.getTranslation();

    //lerpComponent2.destination = transformComponent2.transform.getTranslation() + Vector3f(13.0f, 0.0f, 0.0f);
    //lerpComponent2.start = transformComponent2.transform.getTranslation();

    //auto entity = enttRegistry.create();
    //auto entity2 = enttRegistry.create();
    //enttRegistry.emplace<TransformComponent>(entity, transformComponent);
    //enttRegistry.emplace<MeshComponent>(entity, renderableMesh);
    //enttRegistry.emplace<LerpComponent>(entity, lerpComponent);
    //enttRegistry.emplace<TransformComponent>(entity2, transformComponent2);
    //enttRegistry.emplace<MeshComponent>(entity2, renderableMesh2);
    //enttRegistry.emplace<LerpComponent>(entity2, lerpComponent2);


    //uint32 fps = 0;
    //double lastTime = Time::getTime();
    //double fpsTimeCounter = 0.0;
    //double updateTimer = 1.0;
    //float frameTime = 1.0 / 60.0;

    //while (app->isRunning()) {
    //    double currentTime = Time::getTime();
    //    double passedTime = currentTime - lastTime;
    //    lastTime = currentTime;

    //    fpsTimeCounter += passedTime;
    //    updateTimer += passedTime;

    //    if (fpsTimeCounter >= 1.0) {
    //        double msPerFrame = 1000.0 / (double)fps;
    //        DEBUG_LOG("FPS", "NONE", "%f ms (%d fps)", msPerFrame, fps);
    //        fpsTimeCounter = 0;
    //        fps = 0;
    //    }
    //    bool shouldRender = true;
    //    //while (updateTimer >= frameTime) {
    //        app->processMessages(frameTime, eventHandler);
    //        ////fpCamera.ProcessKeyboard(frameTime);
    //        systemsManager.System<LerpSystem>()->Update(enttRegistry, eventDispatcher, frameTime);

    //        updateTimer -= frameTime;
    //        shouldRender = true;
    //    //}

    //    if (shouldRender) {
    //        // Begin scene render
    //        uniformBufferArray[1] = fpCamera.GetViewMatrix();
    //        uniformBuffer.update(&uniformBufferArray[0]);
    //        renderContext.clear(color, true);
    //        systemsManager.System<RenderMeshSystem>()->Update(enttRegistry, eventDispatcher, frameTime);
    //        renderContext.flush();
    //        //// End scene render

    //        window.present();
    //        fps++;
    //    }
    //    else {
    //        Time::sleep(1);
    //    }

    //}
    //delete app;
    //return 0;