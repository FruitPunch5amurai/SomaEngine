#include "somapch.hpp"

#include "core/game/IMainGame.hpp"
#include "core/game/SceneList.hpp"
#include "core/game/IScene.hpp"
#include "core/Timing.hpp"
#include "core/Logger.hpp"
#include "events/Event.hpp"
#include <rendering/RenderCommand.hpp>

#define BIND_EVENT_FN(x) std::bind(&IMainGame::x,this,std::placeholders::_1)


IMainGame* IMainGame::s_Instance = nullptr; //Singleton

IMainGame::IMainGame()
{
	//SOMA_ASSERT(!s_Instance, "IMainGame already exists");
	s_Instance = this;

	m_sceneList = std::make_unique<SceneList>(this);
}

IMainGame::~IMainGame()
{
}

void IMainGame::run()
{
	if (!initialize()) return;

	double t = 0.0;
	double dt = 1.0f/60.0f;	
	double currentTime = Time::getTime();

	//Frame Counter
	int nbFrame = 0;
	float nbLastFrame = (float)currentTime;
	float nbCurrentFrame;

	//Semi Fixed Timestep
	while (running) {
		double newTime = Time::getTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		//Frame Counter
		nbCurrentFrame = (float)newTime;
		nbFrame++;		
		if (nbCurrentFrame - nbLastFrame > 1.0f)
		{
			double msPerFrame = 1000.0 / (double)nbFrame;
			nbLastFrame = nbCurrentFrame;
			SOMA_CORE_DEBUG("{0} ms , FPS {1}", msPerFrame, nbFrame);
			nbFrame = 0;
		}

		bool shouldRender = false;
		while (frameTime > 0.0) {
			float deltaTime = (float) Math::min(frameTime, dt);
			update(deltaTime);
			for (SOMA_ENGINE::Layer* layer : m_layerStack)
				layer->OnUpdate(deltaTime);
			frameTime -= deltaTime;
			t += deltaTime;
			shouldRender = true;
		}
		if (shouldRender) {
			draw();
		}
		processMessages();
	}
	exitGame();
}

void IMainGame::exitGame()
{
	if (m_currentScene)
	{
		m_currentScene->onExit();
	}
	if (m_sceneList)
	{
		m_sceneList->destroy();
		m_sceneList.reset();
	}
	/*resourceManager.cleanUp();*/
	delete eventProcessor;
	delete window;
}

void IMainGame::PushLayer(SOMA_ENGINE::Layer* layer)
{
	m_layerStack.PushLayer(layer);
	layer->OnAttach();
}

void IMainGame::PushOverlay(SOMA_ENGINE::Layer* overlay)
{
	m_layerStack.PushOverlay(overlay);
	overlay->OnAttach();
}

void IMainGame::OnEvent(SOMA_ENGINE::Event& e)
{
	SOMA_ENGINE::EventDispatcher evtDispatcher(e);

	evtDispatcher.Dispatch<SOMA_ENGINE::WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

	/*Handle the event for each layer*/
	for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
			break;
	}
}

void IMainGame::update(float dt)
{
	if (m_currentScene)
	{
		switch (m_currentScene->getState())
		{
		case ScreenState::RUNNING:
			m_currentScene->update(dt);
			break;
		case ScreenState::TRANSITION:
			m_currentScene->onExit();
			m_currentScene = m_sceneList->getCurrent();
			if (m_currentScene)
			{
				m_currentScene->setRunning();
				m_currentScene->onEntry();
			}
			break;
		case ScreenState::EXIT_APPLICATION:
			exitGame();
			break;
		default:
			break;
		}
	}
	else {
		exitGame();
	}
}

void IMainGame::draw()
{
	if (m_currentScene && m_currentScene->getState() == ScreenState::RUNNING)
		m_currentScene->draw();
	
	for (SOMA_ENGINE::Layer* layer : m_layerStack)
		layer->OnDraw();

	m_imGuiLayer->Begin();
	{
		for (SOMA_ENGINE::Layer* layer : m_layerStack)
			layer->OnImGuiRender();
	}
	m_imGuiLayer->End();

	window->update();
}

bool IMainGame::initialize()
{

	if (!initializeSystems()) return false;
	
	onInit();
	addScenes();

	m_currentScene = m_sceneList->getCurrent();
	if (m_currentScene)
	{
		m_currentScene->onEntry();
		m_currentScene->setRunning();
	}
	return true;
}

bool IMainGame::initializeSystems()
{
	SOMA_ENGINE::Logger::Init();
	SOMA_CORE_DEBUG("Logger Initialized");

	window = GenericWindow::create(WindowProps(m_windowTitle));
	eventProcessor = GenericEventProcessor::create(window);
	window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	SOMA_ENGINE::RenderCommand::Init();

	m_imGuiLayer = new SOMA_ENGINE::ImGuiLayer();
	PushOverlay(m_imGuiLayer);

	return true;
}

bool IMainGame::OnWindowClose(SOMA_ENGINE::WindowCloseEvent& e)
{
	running = false;
	return true;
}
