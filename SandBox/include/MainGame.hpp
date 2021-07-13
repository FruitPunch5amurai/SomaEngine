#pragma once

#include <core/game/IScene.hpp>
#include <core/game/IMainGame.hpp>

class MainGame : public IMainGame {
public:
	MainGame();
	~MainGame();

	virtual void onInit() override;
	virtual void addScenes() override;
	virtual void onExit() override;

private:
	IScene* m_gamePlayScreen = nullptr;
	std::unique_ptr<IScene> m_lightTestScene = nullptr;
};