#pragma once


#include <core/Window.hpp>
#include <rendering/RenderDevice.hpp>
#include <rendering/RenderTarget.hpp>
#include <GameRenderContext.hpp>
#include <InputHandler.hpp>
#include <core/game/ResourceManager.hpp>
#include <core/EventProcessor.hpp>
#include <core/LayerStack.hpp>
#include <imgui/ImGuiLayer.hpp>

#include "events/ApplicationEvent.hpp"

class SceneList;
class IScene;

class  IMainGame {

public:
	IMainGame();
	virtual ~IMainGame();

	virtual void onInit() = 0;
	virtual void addScenes() = 0;
	virtual void onExit() = 0;
	void run();
	void exitGame();
	
	//Window GetWindow() { return m_window; }
	//Window* GetWindowPointer() { return &m_window; }
	float getDeltaTime() { return m_deltaTime; }
	inline void processMessages(IApplicationInputHandler& eventHandler) {
		eventProcessor->processMessages(eventHandler);
	}
	inline static IMainGame& Get() { return *s_Instance; }
	SOMA_ENGINE::ImGuiLayer* GetImGuiLayer() { return m_imGuiLayer; }
	void PushLayer(SOMA_ENGINE::Layer* layer);
	void PushOverlay(SOMA_ENGINE::Layer* overlay);
	void OnEvent(SOMA_ENGINE::Event& e);

	//ResourceManager resourceManager;
	//SpriteBatch spriteBatch;
	/*ResourceManager resourceManager;*/
	RenderDevice* renderDevice;
	RenderTarget* renderTarget;
	Window* window;
	InputHandler inputHandler;

protected:
	virtual void update(float dt);
	virtual void draw(float dt);

	bool initialize();
	bool initializeSystems();

	EventProcessor* eventProcessor;

	std::unique_ptr<SceneList> m_sceneList = nullptr;
	IScene* m_currentScene;
	
	SOMA_ENGINE::LayerStack m_layerStack;

	float m_fps = 0;
	float m_deltaTime;

	SOMA_String m_windowTitle = "Default";
	bool running = true;

private:
	SOMA_ENGINE::ImGuiLayer* m_imGuiLayer;
	bool OnWindowClose(SOMA_ENGINE::WindowCloseEvent& e);
	static IMainGame* s_Instance;
};