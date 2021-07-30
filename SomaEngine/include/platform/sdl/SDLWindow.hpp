#pragma once

#include "core/common.hpp"
#include <SDL/SDL.h>
#include "platform/generic/GenericWindow.hpp"
#include "input/InputManager.hpp"


class  SDLWindow : public GenericWindow {
	friend class SDLEventProcessor;
public: 
	SDLWindow(const WindowProps& props);
	virtual ~SDLWindow();

	void update() override;
	inline unsigned int  getWidth() const override { return winData.width; }
	inline unsigned int  getHeight() const override { return winData.height; }
	inline virtual void setWidth(uint32 w) override { winData.width = w; }
	inline virtual void setHeight(uint32 h) override { winData.height = h; }
	void SetEventCallback(const EventCallbackFn& callback) override { winData.EventCallback = callback; }
	struct WindowData {
		std::string title;
		unsigned int  width, height;
		bool vSync;

		EventCallbackFn EventCallback;
	};

	virtual bool IsKeyPressed(uint32 key) const override;
	virtual bool IsMouseButtonPressed(uint32 key) const override;
	virtual glm::vec2 GetMousePosition() const override;
	virtual void KeyPress(uint32 keyId)override;
	virtual void KeyRelease(uint32 keyId)override;
	virtual void SetMouseCoords(float x, float y)override;
	virtual void UpdateInput() override;

private:
	virtual void Init(const WindowProps& props);
	virtual void Destroy();
	SDL_GLContext m_context;
	SDL_Window* window;
	WindowData winData;

	SOMA_ENGINE::InputManager m_inputManager;
};