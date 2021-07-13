#pragma once
#include <core/common.hpp>
#define SCREEN_INDEX_NO_SCREEN -1

enum class ScreenState {
	NONE,
	RUNNING,
	EXIT_APPLICATION,
	TRANSITION
};

class IMainGame;

class SOMA_API IScene {
public:
	friend class SceneList;

	IScene() {};
	virtual ~IScene() {};

	//Return the index of the next or previous screen when changing
	virtual int getNextSceneIndex() const = 0;
	virtual int getPreviousSceneIndex() const = 0;


	//Called at beggining and end of application
	virtual void build() = 0;
	virtual void destroy() = 0;

	//Called when a screen enters and exits focus
	virtual void onEntry() = 0;
	virtual void onExit() = 0;

	//Called in main game loop
	virtual void update(float dt) = 0;
	virtual void draw(float dt) = 0;

	int getIndex() const { return m_sceneIndex; }
	ScreenState getState() const { return m_currentState; }

	void setState(ScreenState state) { m_currentState = state; }
	void setRunning() { m_currentState = ScreenState::RUNNING; }
	void setParentGame(IMainGame* game) { m_game = game; }
protected:
	int m_sceneIndex = -1;

	IMainGame* m_game = nullptr;

	ScreenState m_currentState = ScreenState::NONE;

};