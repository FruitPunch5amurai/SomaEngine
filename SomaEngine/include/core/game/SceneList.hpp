#pragma once


#include "core/common.hpp"
class IMainGame;
class IScene;

class SOMA_API SceneList {
public:
	SceneList(IMainGame* game);
	~SceneList();

	void moveNext();
	void movePrevious();

	void setScene(int nextScene);
	void addScene(IScene* newScene);
	void switchTo(int sceneId);

	void destroy();

	IScene* getCurrent();

	int getScreenIndex() { return m_currentSceneIndex; }
private:
	IMainGame* m_game = nullptr;
	SOMA_Array<IScene*> m_scenes;
	uint32 m_currentSceneIndex = -1;
};