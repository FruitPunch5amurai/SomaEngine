#include "MainGame.hpp"
#include "TestScene.hpp"
#include <core/game/SceneList.hpp>

MainGame::MainGame()
{
	m_windowTitle = "Snake Game";

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
	//m_gamePlayScreen = new OrthographicTest();//new GameScene();

	m_sceneList->addScene(m_gamePlayScreen);
	m_sceneList->setScene(m_gamePlayScreen->getIndex());

}

void MainGame::onExit()
{
}
