#include "somapch.hpp"

#include "core\game\SceneList.hpp"
#include "core\game\IScene.hpp"
SceneList::SceneList(IMainGame* game)
{
	//Empty
	m_game = game;
}

SceneList::~SceneList()
{
	//Empty
}

void SceneList::moveNext()
{
	IScene* currentScene = getCurrent();
	if (currentScene->getNextSceneIndex() != SCREEN_INDEX_NO_SCREEN)
	{
		m_currentSceneIndex = currentScene->getNextSceneIndex();
		currentScene->m_currentState = ScreenState::TRANSITION;
	}
}

void SceneList::movePrevious()
{
	IScene* currentScene = getCurrent();
	if (currentScene->getPreviousSceneIndex() != SCREEN_INDEX_NO_SCREEN)
	{
		m_currentSceneIndex = currentScene->getPreviousSceneIndex();
		currentScene->m_currentState = ScreenState::TRANSITION;
	}
}

void SceneList::setScene(int nextScene)
{
	m_currentSceneIndex = nextScene;
}

void SceneList::addScene(IScene* newScene)
{
	newScene->m_sceneIndex = (int)m_scenes.size();
	m_scenes.push_back(newScene);
	newScene->build();
	newScene->setParentGame(m_game);
}

void SceneList::switchTo(int sceneId)
{
	getCurrent()->setState(ScreenState::TRANSITION);
	m_currentSceneIndex = sceneId;
}

void SceneList::destroy()
{
	for (auto& s : m_scenes)
	{
		s->destroy();
		delete s;
	}
	m_scenes.resize(0);
	m_currentSceneIndex = SCREEN_INDEX_NO_SCREEN;
}

IScene* SceneList::getCurrent()
{
	if (m_currentSceneIndex == SCREEN_INDEX_NO_SCREEN)
		return nullptr;
	return m_scenes[m_currentSceneIndex];
}
