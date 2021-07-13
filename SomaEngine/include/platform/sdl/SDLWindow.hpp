#pragma once

#include "core/common.hpp"
#include <SDL/SDL.h>
#include "platform/generic/GenericWindow.hpp"


class SOMA_API SDLWindow : public GenericWindow {
	friend class SDLEventProcessor;
public: 
	SDLWindow(const WindowProps& props);
	virtual ~SDLWindow();

	void update() override;
	inline unsigned int  getWidth() const override { return winData.width; }
	inline unsigned int  getHeight() const override { return winData.height; }
	void SetEventCallback(const EventCallbackFn& callback) override { winData.EventCallback = callback; }
	struct WindowData {
		std::string title;
		unsigned int  width, height;
		bool vSync;

		EventCallbackFn EventCallback;
	};
private:
	virtual void Init(const WindowProps& props);
	virtual void Destroy();
	SDL_GLContext m_context;
	SDL_Window* window;
	WindowData winData;

};