#include <somapch.hpp>
#include <core/game/SceneList.hpp>

#include "MainGame.hpp"
#include "TestScene.hpp"

MainGame::MainGame()
{
	m_windowTitle = "SandBox";

}

MainGame::~MainGame()
{
}

void MainGame::onInit()
{

}

void MainGame::addScenes()
{
	m_gamePlayScreen = new TestScene();

	m_sceneList->addScene(m_gamePlayScreen);
	m_sceneList->setScene(m_gamePlayScreen->getIndex());

}

void MainGame::onExit()
{
}
